#include "crdtclient.h"

#include "grpcchannel.h"
#include "grpcchannel_p.h"
#include "grpcpendingcall.h"

#include "common.h"

#include "crdt.grpc.pb.h"

class CrdtClientPrivate
{
public:
    CrdtClientPrivate() {/*...*/}

    std::unique_ptr<crdt::CRDT::Stub> stub;
};

CrdtClient::CrdtClient(QObject *parent)
    : GrpcClient(parent), d_ptr(new CrdtClientPrivate)
{
    TRACE;
    QObject::connect(this, &GrpcClient::channelChanged, this, &CrdtClient::onChannelChanged);
}

CrdtClient::~CrdtClient()
{
    TRACE;
    delete d_ptr;
}

void CrdtClient::onChannelChanged()
{
    TRACE;
    Q_D(CrdtClient);
    if(channel() == NULL) return;
    d->stub = crdt::CRDT::NewStub(transport());
}

GrpcPendingResponse<crdt::CreateResponse>* CrdtClient::Create(const QString &typeId, const QString &storageId, const QString &cryptoId)
{
    TRACE;
    Q_D(CrdtClient);
    if(channel() == NULL) return NULL;

    crdt::CreateRequest request;
    request.set_resourcetype(typeId.toStdString());
    request.set_storageid(storageId.toStdString());
    request.set_cryptoid(cryptoId.toStdString());

    auto response = new GrpcPendingResponse<crdt::CreateResponse>;
    response->setReader(d->stub->AsyncCreate(&response->context, request, cqueue()));
    response->finish();
    return response;
}

GrpcPendingResponse<crdt::AttachResponse>* CrdtClient::Attach(const QString &resourceId, const QString &resourceKey)
{
    TRACE;
    Q_D(CrdtClient);
    if(channel() == NULL) return NULL;

    crdt::AttachRequest request;
    request.set_resourceid(resourceId.toStdString());
    request.set_resourcekey(resourceKey.toStdString());

    auto response = new GrpcPendingResponse<crdt::AttachResponse>;
    response->setReader(d->stub->AsyncAttach(&response->context, request, cqueue()));
    response->finish();
    return response;
}

GrpcPendingResponse<crdt::CommitResponse>* CrdtClient::Commit(const QString &aRefId)
{
    TRACE;
    Q_D(CrdtClient);
    if(channel() == NULL) return NULL;

    crdt::CommitRequest request;
    request.set_referenceid(aRefId.toStdString());

    auto response = new GrpcPendingResponse<crdt::CommitResponse>;
    response->setReader(d->stub->AsyncCommit(&response->context, request, cqueue()));
    response->finish();
    return response;
}

GrpcPendingResponse<crdt::DetachResponse>* CrdtClient::Detach(const QString &aRefId)
{
    TRACE;
    Q_D(CrdtClient);
    if(channel() == NULL) return NULL;

    crdt::DetachRequest request;
    request.set_referenceid(aRefId.toStdString());

    auto response = new GrpcPendingResponse<crdt::DetachResponse>;
    response->setReader(d->stub->AsyncDetach(&response->context, request, cqueue()));
    response->finish();
    return response;
}

GrpcPendingResponse<crdt::CloneResponse>* CrdtClient::Clone(const QString &aRefId)
{
    TRACE;
    Q_D(CrdtClient);
    if(channel() == NULL) return NULL;

    crdt::CloneRequest request;
    request.set_referenceid(aRefId.toStdString());

    auto response = new GrpcPendingResponse<crdt::CloneResponse>;
    response->setReader(d->stub->AsyncClone(&response->context, request, cqueue()));
    response->finish();
    return response;
}

GrpcPendingResponse<crdt::EqualsResponse>* CrdtClient::Equals(const QString &aRefId, const QString &bRefId)
{
    TRACE;
    Q_D(CrdtClient);
    if(channel() == NULL) return NULL;

    crdt::EqualsRequest request;
    request.set_referenceid(aRefId.toStdString());
    request.set_otherreferenceid(bRefId.toStdString());

    auto response = new GrpcPendingResponse<crdt::EqualsResponse>;
    response->setReader(d->stub->AsyncEquals(&response->context, request, cqueue()));
    response->finish();
    return response;
}

GrpcPendingResponse<crdt::MergeResponse>* CrdtClient::Merge(const QString &aRefId, const QString &bRefId)
{
    TRACE;
    Q_D(CrdtClient);
    if(channel() == NULL) return NULL;

    crdt::MergeRequest request;
    request.set_referenceid(aRefId.toStdString());
    request.set_otherreferenceid(bRefId.toStdString());

    auto response = new GrpcPendingResponse<crdt::MergeResponse>;
    response->setReader(d->stub->AsyncMerge(&response->context, request, cqueue()));
    response->finish();
    return response;
}
