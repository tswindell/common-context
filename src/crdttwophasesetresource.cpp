#include "crdttwophasesetresource.h"

#include "crdt/twophasesetclient.h"

class CrdtTwoPhaseSetResourcePrivate
{
public:
    CrdtTwoPhaseSetResourcePrivate(const QString &pUuid, const QString &pReferenceId, TwoPhaseSetClient *pClient)
        : uuid(pUuid), referenceId(pReferenceId), client(pClient)
    {/*...*/}

    QString            uuid;
    QString            referenceId;
    TwoPhaseSetClient *client;
};

CrdtTwoPhaseSetResource::CrdtTwoPhaseSetResource(const QString &uuid, const QString &referenceId, TwoPhaseSetClient *client, Context *context)
    : QObject((QObject*)context), Resource(uuid, context), d_ptr(new CrdtTwoPhaseSetResourcePrivate(uuid, referenceId, client))
{
}

CrdtTwoPhaseSetResource::~CrdtTwoPhaseSetResource()
{
    delete d_ptr;
}

QString CrdtTwoPhaseSetResource::type() const
{
    return TWO_PHASE_SET_RESOURCE_TYPE_ID;
}

QVariant CrdtTwoPhaseSetResource::value()
{
    return QVariant::fromValue(this);
}
