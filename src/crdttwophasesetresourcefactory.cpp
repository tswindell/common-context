#include "crdttwophasesetresource.h"
#include "crdttwophasesetresourcefactory.h"

#include "crdt/crdtclient.h"
#include "crdt/twophasesetclient.h"

class CrdtTwoPhaseSetResourceFactoryPrivate
{
public:
    CrdtTwoPhaseSetResourceFactoryPrivate(GrpcChannel *pChannel)
        : channel(pChannel), crdt(NULL), client(NULL)
    {/*...*/}

    GrpcChannel       *channel;

    CrdtClient        *crdt;
    TwoPhaseSetClient *client;
};

CrdtTwoPhaseSetResourceFactory::CrdtTwoPhaseSetResourceFactory(GrpcChannel *channel, QObject *parent)
    : QObject(parent), d_ptr(new CrdtTwoPhaseSetResourceFactoryPrivate(channel))
{
    Q_D(CrdtTwoPhaseSetResourceFactory);

    d->crdt = new CrdtClient(this);
    d->crdt->setChannel(channel);

    d->client = new TwoPhaseSetClient(this);
    d->client->setChannel(channel);
}

CrdtTwoPhaseSetResourceFactory::~CrdtTwoPhaseSetResourceFactory()
{
    delete d_ptr;
}

QString CrdtTwoPhaseSetResourceFactory::type() const
{
    return TWO_PHASE_SET_RESOURCE_TYPE_ID;
}

Resource* CrdtTwoPhaseSetResourceFactory::create(const QString &uuid, Context *context)
{

}

Resource* CrdtTwoPhaseSetResourceFactory::restore(const QString &uuid, const QString &resourceId, const QString &resourceKey, Context *context)
{

}
