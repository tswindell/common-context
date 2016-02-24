#ifndef CONTEXT_P_H
#define CONTEXT_P_H

#include "crdt/grpcchannel.h"
#include "crdt/twophasesetclient.h"

class ContextPrivate
{
public:
    ContextPrivate(const QString &refId, GrpcChannel *pChannel)
        : referenceId(refId), channel(pChannel)
    {/*...*/}

    // CRDB ReferenceId pointing to this contexts' CRDT resource.
    QString referenceId;

    GrpcChannel       *channel;
    TwoPhaseSetClient *twophaseset;

    // Map of resourceId -> serialized object data for element matching.
    QHash<QString, QString> cache;

    QHash<QString, Resource*>           resources;
    QHash<QString, ResourceFactory*>    factories;
    QHash<QString, QList<Context::Tag>> tags;
};

#endif // CONTEXT_P_H
