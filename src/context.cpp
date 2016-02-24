#include "context.h"
#include "context_p.h"

#include <QHash>
#include <QUuid>

#include <QDebug>

#include "context.pb.h"

#include "resource.h"
#include "resourcefactory.h"
#include "resourcemodel.h"

#include "contextresourcefactory.h"
#include "crdtgrowonlysetresourcefactory.h"
#include "crdttwophasesetresourcefactory.h"

Context::Context(const QString &referenceId, GrpcChannel *channel, QObject *parent)
    : QObject(parent), d_ptr(new ContextPrivate(referenceId, channel))
{
    Q_D(Context);

    // Initialize 2PSet interface client.
    d->twophaseset = new TwoPhaseSetClient(this);
    d->twophaseset->setChannel(channel);

    // Register built-in resource type factories.
    this->addTypeFactory(new ContextResourceFactory(channel, this));
    this->addTypeFactory(new CrdtGrowOnlySetResourceFactory(channel, this));
    this->addTypeFactory(new CrdtTwoPhaseSetResourceFactory(channel, this));

    // Connect to CRDT events for 2PSet updates.
    QObject::connect(d->twophaseset, &TwoPhaseSetClient::objectAdded,
                     this, &Context::onObjectAdded);
    QObject::connect(d->twophaseset, &TwoPhaseSetClient::objectRemoved,
                     this, &Context::onObjectRemoved);

    // Load in initial state to populate internal data structures.
    auto response = d->twophaseset->List(d->referenceId);
    if(response->isError())
    {
        qWarning() << "CRDT TwoPhaseSet List request failed.";
        return;
    }

    //TODO: Implement item iteration in gRPC client code.
}

Context::~Context()
{
    Q_D(Context);
    delete d_ptr;
}

void Context::onObjectAdded(const QString &object)
{
    Q_D(Context);
    ContextElement element;

    // Deserialize object into element for processing.
    element.ParseFromString(object.toStdString());

    QString uuid = QString::fromStdString(element.uuid());
    if(element.has_resource()) // Switch resource context element type.
    {
        // Extract resource information.
        QString resourceId   = QString::fromStdString(element.resource().id());
        QString resourceKey  = QString::fromStdString(element.resource().key());
        QString resourceType = QString::fromStdString(element.resource().type());

        // Find resource value for type.
        ResourceFactory *factory = d->factories.value(resourceType);
        if(factory == NULL)
        {
            qWarning() << "W: Failed to find resource factory for type:" << resourceType;
            return;
        }

        // Create resource interface using factory.
        Resource* resource = factory->restore(uuid, resourceId, resourceKey, this);
        if(resource == NULL) return;

        // Add resource to resource directory.
        d->resources.insert(uuid, resource);
    }
    else if(element.has_link()) // Switch link context element type.
    {
        // Extract link information.
        QString name   = QString::fromStdString(element.link().name());
        QString target = QString::fromStdString(element.link().target());

        // Default is empty tag list if we don't find any below.
        QList<Context::Tag> tags;

        // Attempt to get current collection of target tag.
        if(d->tags.contains(name)) tags = d->tags.value(name);

        // Create new tag data structure.
        Context::Tag tag;
        tag.uuid   = uuid;
        tag.name   = name;
        tag.target = target;

        // Add tag data structure to tag name list.
        tags.append(tag);
        // Update tag.
        d->tags.insert(name, tags);
    }

    // Add context element to context cache. This is to guard against possibly
    // different protobuf serialization results.
    d->cache.insert(uuid, object);
}

void Context::onObjectRemoved(const QString &object)
{
    Q_D(Context);
    ContextElement element;

    // Deserialize object into element for processing.
    element.ParseFromString(object.toStdString());

    // Extract uuid for element that has been removed.
    QString uuid = QString::fromStdString(element.uuid());

    if(element.has_resource()) // Switch object is resource data.
    {
        Resource *resource = d->resources.value(uuid);

        // Remove all tags that link to this resource.
        foreach(QString tag, resource->tags()) {
            this->untag(tag, resource);
        }

        // Remove resource from directory.
        d->resources.remove(uuid);
    }
    else if(element.has_link()) // Switch object is resource link.
    {
        // Search through all tags to find this uuid.
        //FIXME: Need to update tags data list!
        foreach(QString tagName, d->tags.keys())
        {
            bool found = false;

            QList<Context::Tag> tags = d->tags.value(tagName);

            foreach(const Context::Tag tag, tags)
            {
                if(tag.uuid == uuid)
                {
                    tags.removeOne(tag);
                    found = true;
                    break;
                }
            }

            if(found) break;
        }
    }

    // Remove element cache item.
    d->cache.remove(uuid);
}

ResourceFactory* Context::getTypeFactory(const QString &typeId)
{
    Q_D(Context);
    if(!d->factories.contains(typeId)) return NULL;
    return d->factories.value(typeId);
}

void Context::addTypeFactory(ResourceFactory *factory)
{
    Q_D(Context);
    if(factory == NULL) return;
    d->factories.insert(factory->type(), factory);
}

ResourceModel* Context::resources()
{
    Q_D(Context);
    return new ResourceModel(d->resources.values(), this);
}

QStringList Context::tags() const
{
    Q_D(const Context);
    return d->tags.keys();
}

Resource* Context::findById(const QString &id) const
{
    Q_D(const Context);
    return d->resources.value(id);
}

ResourceModel* Context::findByTag(const QString &tag)
{
    Q_D(Context);
    ResourceModel *model = new ResourceModel(d->resources.values(), this);
    model->appendTagFilter(tag);
    return model;
}

ResourceModel* Context::findByType(const QString &type)
{
    Q_D(Context);
    ResourceModel *model = new ResourceModel(d->resources.values(), this);
    model->appendTypeFilter(type);
    return model;
}

Resource* Context::create(const QString &typeId)
{
    ResourceFactory *factory = getTypeFactory(typeId);

    if(factory == NULL)
    {
        qWarning() << "Unrecognised factory Id specified:" << typeId;
        return NULL;
    }

    return factory->create(QUuid::createUuid().toString(), this);
}

void Context::insert(Resource *resource)
{
    Q_D(Context);
    if(resource == NULL)
    {
        qWarning() << "Invalid NULL resource specified.";
        return;
    }

    if(d->resources.contains(resource->uuid()))
    {
        qWarning() << "Context already contains resource:" << resource->uuid();
        return;
    }

    // Generate serialized record, for manipulating CRDB two phase set.
    ContextElement_Resource elementResource;
    elementResource.set_id(resource->resourceId().toStdString());
    elementResource.set_key(resource->resourceKey().toStdString());
    elementResource.set_type(resource->type().toStdString());

    ContextElement element;
    element.set_uuid(resource->uuid().toStdString());
    element.set_allocated_resource(&elementResource);

    QString object = QString::fromStdString(element.SerializeAsString());
    auto insertResponse = d->twophaseset->Insert(d->referenceId, object);
    if(insertResponse->isError())
    {
        qWarning() << "E: Failed to send insert request:"
                   << insertResponse->errorString();
    }
}

void Context::remove(Resource *resource)
{
    Q_D(Context);
    if(resource == NULL)
    {
        qWarning() << "Invalid NULL resource specified.";
        return;
    }

    if(!d->resources.contains(resource->uuid()))
    {
        qWarning() << "Context does not contain resource:" << resource->uuid();
        return;
    }

    QString object = d->cache.value(resource->uuid());
    auto removeResponse = d->twophaseset->Remove(d->referenceId, object);
    if(removeResponse->isError())
    {
        qWarning() << "E: Failed to send insert request:"
                   << removeResponse->errorString();
    }
}

void Context::tag(const QString &tag, Resource *resource)
{
    Q_D(Context);
    if(!d->tags.contains(tag))
    {
        d->tags.insert(tag, QList<Context::Tag>());
    }

    QList<Context::Tag> tags = d->tags.value(tag);
    foreach(Context::Tag tag, tags)
    {
        if(tag.target == resource->uuid()) return;
    }

    Context::Tag t;
    t.uuid = QUuid::createUuid().toString();
    t.name = tag;
    t.target = resource->uuid();

    tags.append(t);
    d->tags.insert(tag, tags);
}

void Context::untag(const QString &tag, Resource *resource)
{
    Q_D(Context);
    if(!d->tags.contains(tag)) return;

    QList<Context::Tag> tags;

    foreach(Context::Tag iter, d->tags.value(tag))
    {
        if(iter.target != resource->uuid())
        {
            tags.append(iter);
        }
    }

    d->tags.insert(tag, tags);
}
