#include "resourcemodel.h"

#include "context.h"
#include "resource.h"

class ResourceModelPrivate
{
public:
    ResourceModelPrivate(QList<Resource*> pResources, Context *pContext)
        : context(pContext), resources(pResources)
    {/*...*/}

    Context *context;

    QList<Resource*> resources;

    QStringList filterTags;
    QStringList filterTypes;
};

ResourceModel::ResourceModel(QList<Resource*> resources, Context *context)
    : QAbstractListModel(context), d_ptr(new ResourceModelPrivate(resources, context))
{
    QObject::connect(context, &Context::resourceAdded,
                     this, &ResourceModel::onResourceAdded);
    QObject::connect(context, &Context::resourceRemoved,
                     this, &ResourceModel::onResourceRemoved);
}

ResourceModel::~ResourceModel()
{
    delete d_ptr;
}

void ResourceModel::appendTagFilter(const QString &tag)
{
    Q_D(ResourceModel);
    if(d->filterTags.contains(tag)) return;
    d->filterTags.append(tag);
}

void ResourceModel::removeTagFilter(const QString &tag)
{
    Q_D(ResourceModel);
    d->filterTags.removeOne(tag);
}

void ResourceModel::appendTypeFilter(const QString &type)
{
    Q_D(ResourceModel);
    if(d->filterTags.contains(type)) return;
    d->filterTypes.append(type);
}

void ResourceModel::removeTypeFilter(const QString &type)
{
    Q_D(ResourceModel);
    d->filterTypes.removeOne(type);
}

QHash<int,QByteArray> ResourceModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles.insert(ResourceModel::IdRole,    QByteArray("id"));
    roles.insert(ResourceModel::TypeRole,  QByteArray("type"));
    roles.insert(ResourceModel::ValueRole, QByteArray("value"));
    return roles;
}

int ResourceModel::rowCount(const QModelIndex &parent) const
{
    Q_D(const ResourceModel);
    return d->resources.length();
}

QVariant ResourceModel::data(const QModelIndex &index, int role) const
{
    Q_D(const ResourceModel);

    if(!index.isValid()) return QVariant();
    if(index.row() > this->rowCount(QModelIndex()) - 1) return QVariant();

    Resource *resource = d->resources.value(index.row());
    switch(role)
    {
    case ResourceModel::IdRole:
        return QVariant::fromValue(resource->uuid());
        break;

    case ResourceModel::TypeRole:
        return QVariant::fromValue(resource->type());
        break;

    case ResourceModel::ValueRole:
        return resource->value();
        break;
    }

    return QVariant();
}

void ResourceModel::onResourceAdded(Resource *resource)
{
    Q_D(ResourceModel);
    if(d->filterTags.length() == 0 && d->filterTypes.length() == 0)
    {
        d->resources.append(resource);
        return;
    }

    foreach(QString tag, d->filterTags)
    {
        if(resource->tags().contains(tag))
        {
            d->resources.append(resource);
            return;
        }
    }

    foreach(QString type, d->filterTypes)
    {
        if(resource->type() == type)
        {
            d->resources.append(resource);
            return;
        }
    }
}

void ResourceModel::onResourceRemoved(const QString &id)
{
    Q_D(ResourceModel);
    foreach(Resource *resource, d->resources)
    {
        if(resource->uuid() == id)
        {
            d->resources.removeOne(resource);
            return;
        }
    }
}
