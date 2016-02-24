#ifndef GROWONLYSETCLIENT_H
#define GROWONLYSETCLIENT_H

#include "grpcclient.h"
#include "grpcpendingcall.h"
#include "crdt.grpc.pb.h"

class GrowOnlySetClient : public GrpcClient
{
public:
    explicit GrowOnlySetClient(QObject *parent = 0);
            ~GrowOnlySetClient();

    GrpcPendingReader<crdt::ResourceObject>*        List(const QString &refId);
    GrpcPendingResponse<crdt::SetInsertResponse>*   Insert(const QString &refId, const QString &data);
    GrpcPendingResponse<crdt::SetLengthResponse>*   Length(const QString &refId);
    GrpcPendingResponse<crdt::SetContainsResponse>* Contains(const QString &refId, const QString &data);

protected:
    void onChannelChanged();

private:
    class GrowOnlySetClientPrivate *d_ptr;
    Q_DECLARE_PRIVATE(GrowOnlySetClient)
};

#endif // GROWONLYSETCLIENT_H
