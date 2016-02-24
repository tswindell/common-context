#include "crdtgrowonlysetresource.h"

#include "crdt/growonlysetclient.h"

class CrdtGrowOnlySetResourcePrivate
{
public:
    CrdtGrowOnlySetResourcePrivate(const QString &pUuid,
                                   const QString &pRefId,
                                   GrowOnlySetClient *pClient)
        : uuid(pUuid), referenceId(pRefId), client(pClient)
    {/*...*/}

    QString uuid;
    QString referenceId;

    GrowOnlySetClient *client;
};

CrdtGrowOnlySetResource::CrdtGrowOnlySetResource(const QString &uuid, const QString &referenceId, GrowOnlySetClient *client, Context *context)
    : QObject((QObject*)context), Resource(uuid, context), d_ptr(new CrdtGrowOnlySetResourcePrivate(uuid, referenceId, client))
{
}

CrdtGrowOnlySetResource::~CrdtGrowOnlySetResource()
{
    delete d_ptr;
}

QString CrdtGrowOnlySetResource::type() const
{
    return GROW_ONLY_SET_RESOURCE_TYPE_ID;
}

QVariant CrdtGrowOnlySetResource::value()
{
    return QVariant::fromValue(this);
}
