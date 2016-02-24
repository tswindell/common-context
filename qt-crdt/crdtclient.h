#ifndef CRDTCLIENT_H
#define CRDTCLIENT_H

#include "grpcclient.h"
#include "grpcpendingcall.h"

#include "crdt.grpc.pb.h"

class GrpcChannel;

class CrdtClient : public GrpcClient
{
    Q_OBJECT

public:
    explicit CrdtClient(QObject *parent = 0);
            ~CrdtClient();

    GrpcPendingResponse<crdt::CreateResponse>* Create(const QString &typeId, const QString &storageId, const QString &cryptoId);
    GrpcPendingResponse<crdt::AttachResponse>* Attach(const QString &resourceId, const QString &resourceKey);

    GrpcPendingResponse<crdt::CommitResponse>* Commit(const QString &aRefId);
    GrpcPendingResponse<crdt::DetachResponse>* Detach(const QString &aRefId);
    GrpcPendingResponse<crdt::EqualsResponse>* Equals(const QString &aRefId, const QString &bRefId);
    GrpcPendingResponse<crdt::CloneResponse>*   Clone(const QString &aRefId);
    GrpcPendingResponse<crdt::MergeResponse>*   Merge(const QString &aRefId, const QString &bRefId);

    QString errorString() const;

protected:
    void onChannelChanged();

private:
    class CrdtClientPrivate *d_ptr;
    Q_DECLARE_PRIVATE(CrdtClient)
};

#endif // CRDTCLIENT_H
