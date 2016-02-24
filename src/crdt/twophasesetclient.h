#ifndef TWOPHASESETCLIENT_H
#define TWOPHASESETCLIENT_H

#include "grpcclient.h"
#include "grpcpendingcall.h"
#include "crdt.grpc.pb.h"

class TwoPhaseSetClient : public GrpcClient
{
    Q_OBJECT

public:
    explicit TwoPhaseSetClient(QObject *parent = 0);
            ~TwoPhaseSetClient();

    GrpcPendingReader<crdt::ResourceObject>*        List(const QString &refId);
    GrpcPendingResponse<crdt::SetInsertResponse>*   Insert(const QString &refId, const QString &data);
    GrpcPendingResponse<crdt::SetRemoveResponse>*   Remove(const QString &refId, const QString &data);
    GrpcPendingResponse<crdt::SetLengthResponse>*   Length(const QString &refId);
    GrpcPendingResponse<crdt::SetContainsResponse>* Contains(const QString &refId, const QString &data);

Q_SIGNALS:
    void objectAdded(const QString &object);
    void objectRemoved(const QString &object);

protected:
    void onChannelChanged();

private:
    class TwoPhaseSetClientPrivate *d_ptr;
    Q_DECLARE_PRIVATE(TwoPhaseSetClient)
};

#endif // TWOPHASESETCLIENT_H
