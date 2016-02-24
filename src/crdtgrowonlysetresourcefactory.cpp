#include "crdtgrowonlysetresource.h"
#include "crdtgrowonlysetresourcefactory.h"

#include "context.h"

#include "crdt/crdtclient.h"
#include "crdt/growonlysetclient.h"

class CrdtGrowOnlySetResourceFactoryPrivate
{
public:
    CrdtGrowOnlySetResourceFactoryPrivate(GrpcChannel *pChannel)
        : channel(pChannel), crdt(NULL), client(NULL)
    {/*...*/}

    GrpcChannel       *channel;

    CrdtClient        *crdt;
    GrowOnlySetClient *client;
};

CrdtGrowOnlySetResourceFactory::CrdtGrowOnlySetResourceFactory(GrpcChannel *channel, QObject *parent)
    : QObject(parent), d_ptr(new CrdtGrowOnlySetResourceFactoryPrivate(channel))
{
    Q_D(CrdtGrowOnlySetResourceFactory);

    d->crdt   = new CrdtClient(this);
    d->crdt->setChannel(channel);

    d->client = new GrowOnlySetClient(this);
    d->client->setChannel(channel);
}

CrdtGrowOnlySetResourceFactory::~CrdtGrowOnlySetResourceFactory()
{
    delete d_ptr;
}

QString CrdtGrowOnlySetResourceFactory::type() const
{
    return GROW_ONLY_SET_RESOURCE_TYPE_ID;
}

Resource* CrdtGrowOnlySetResourceFactory::create(const QString &uuid, Context *context)
{
    Q_D(CrdtGrowOnlySetResourceFactory);
    auto createResponse = d->crdt->Create("crdt:gset", "ipfs", "aes-256-cbc");
    createResponse->waitForFinished();

    QString resourceId  = QString::fromStdString(createResponse->reply()->resourceid());
    QString resourceKey = QString::fromStdString(createResponse->reply()->resourcekey());

    // Do Attach request.
    auto attachResponse = d->crdt->Attach(resourceId, resourceKey);
    attachResponse->waitForFinished();

    QString referenceId = QString::fromStdString(attachResponse->reply()->referenceid());

    // Create Context instance declarative resource wrapper.
    CrdtGrowOnlySetResource *resource = new CrdtGrowOnlySetResource(uuid, referenceId, d->client, context);
    resource->setResourceId(resourceId);
    resource->setResourceKey(resourceKey);

    return resource;
}

Resource* CrdtGrowOnlySetResourceFactory::restore(const QString &uuid, const QString &resourceId, const QString &resourceKey, Context *context)
{
    Q_D(CrdtGrowOnlySetResourceFactory);
    auto attachResponse = d->crdt->Attach(resourceId, resourceKey);
    attachResponse->waitForFinished();

    QString referenceId = QString::fromStdString(attachResponse->reply()->referenceid());
    CrdtGrowOnlySetResource *resource = new CrdtGrowOnlySetResource(uuid, referenceId, d->client, context);
    resource->setResourceId(resourceId);
    resource->setResourceKey(resourceKey);

    return resource;
}
