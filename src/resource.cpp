#include "resource.h"

#include "context.h"
#include "context_p.h"

class ResourcePrivate
{
public:
    ResourcePrivate(const QString &pUuid, Context *pContext)
        : uuid(pUuid), context(pContext)
    {/*...*/}

    QString uuid;

    Context *context;

    QString resourceId;
    QString resourceKey;
};

Resource::Resource(const QString &uuid, Context *context)
    : d(new ResourcePrivate(uuid, context))
{
}

Resource::~Resource()
{
    delete d;
}

QString Resource::uuid() const
{
    return d->uuid;
}

//TODO: Rethink the underlying tagging data organisation.
QStringList Resource::tags() const
{
    QStringList results;
    foreach(QList<Context::Tag> tags, d->context->d_ptr->tags)
    {
        foreach(Context::Tag tag, tags)
        {
            if(tag.target == d->uuid)
            {
                results.append(tag.name);
            }
        }
    }
    return results;
}

QString Resource::resourceId() const
{
    return d->resourceId;
}

void Resource::setResourceId(const QString &resourceId)
{
    d->resourceId = resourceId;
}

QString Resource::resourceKey() const
{
    return d->resourceKey;
}

void Resource::setResourceKey(const QString &resourceKey)
{
    d->resourceKey = resourceKey;
}
