#include "context.h"

#include "contextresource.h"
#include "contextresourcefactory.h"

#include <QDebug>

#include "crdt/grpcpendingcall.h"
#include "crdt/crdtclient.h"

class ContextResourceFactoryPrivate
{
public:
    ContextResourceFactoryPrivate(GrpcChannel *pChannel)
        : channel(pChannel), crdt(NULL)
    {/*...*/}

    GrpcChannel *channel;
    CrdtClient  *crdt;
};

ContextResourceFactory::ContextResourceFactory(GrpcChannel *channel, QObject *parent)
    : QObject(parent), d_ptr(new ContextResourceFactoryPrivate(channel))
{
    Q_D(ContextResourceFactory);

    d->crdt = new CrdtClient(this);
    d->crdt->setChannel(channel);
}

ContextResourceFactory::~ContextResourceFactory()
{
    delete d_ptr;
}

QString ContextResourceFactory::type() const
{
    return CONTEXT_RESOURCE_TYPE_ID;
}

Resource* ContextResourceFactory::create(const QString &uuid, Context *context)
{
    Q_D(ContextResourceFactory);
    // Do Create request.
    auto createResponse = d->crdt->Create("crdt:2pset", "ipfs", "aes-256-cbc");
    createResponse->waitForFinished();

    QString resourceId  = QString::fromStdString(createResponse->reply()->resourceid());
    QString resourceKey = QString::fromStdString(createResponse->reply()->resourcekey());

    // Do Attach request.
    auto attachResponse = d->crdt->Attach(resourceId, resourceKey);
    attachResponse->waitForFinished();

    QString referenceId = QString::fromStdString(attachResponse->reply()->referenceid());

    // Create underlying Context instance.
    Context *subject = new Context(referenceId, d->channel, context);

    // Create Context instance declarative resource wrapper.
    ContextResource *resource = new ContextResource(uuid, subject);
    resource->setResourceId(resourceId);
    resource->setResourceKey(resourceKey);

    return resource;
}

Resource* ContextResourceFactory::restore(const QString &uuid,
                                          const QString &resourceId,
                                          const QString &resourceKey,
                                          Context *context)
{
    Q_D(ContextResourceFactory);
    auto attachResponse = d->crdt->Attach(resourceId, resourceKey);
    attachResponse->waitForFinished();

    QString          referenceId = QString::fromStdString(attachResponse->reply()->referenceid());
    Context             *subject = new Context(referenceId, d->channel, context);
    ContextResource    *resource = new ContextResource(uuid, subject);
    resource->setResourceId(resourceId);
    resource->setResourceKey(resourceKey);

    return resource;
}
