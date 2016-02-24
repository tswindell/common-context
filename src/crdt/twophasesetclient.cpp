#include "common.h"
#include "twophasesetclient.h"

class TwoPhaseSetClientPrivate
{
public:
    TwoPhaseSetClientPrivate() {/*...*/}

    std::unique_ptr<crdt::TwoPhaseSet::Stub> stub;
};

TwoPhaseSetClient::TwoPhaseSetClient(QObject *parent)
    : GrpcClient(parent), d_ptr(new TwoPhaseSetClientPrivate)
{
    TRACE;
    QObject::connect(this, &GrpcClient::channelChanged,
                     this, &TwoPhaseSetClient::onChannelChanged);
}

TwoPhaseSetClient::~TwoPhaseSetClient()
{
    TRACE;
    delete d_ptr;
}

void TwoPhaseSetClient::onChannelChanged()
{
    TRACE;
    Q_D(TwoPhaseSetClient);
    if(channel() == NULL) return;
    d->stub = crdt::TwoPhaseSet::NewStub(transport());
}

GrpcPendingReader<crdt::ResourceObject>* TwoPhaseSetClient::List(const QString &refId)
{
    TRACE;
    Q_D(TwoPhaseSetClient);
    if(channel() == NULL) return NULL;

    crdt::SetListRequest request;
    request.set_referenceid(refId.toStdString());

    auto response = new GrpcPendingReader<crdt::ResourceObject>;
    response->setReader(d->stub->AsyncList(&response->context, request, cqueue(), response));
    response->finish();
    return response;
}

GrpcPendingResponse<crdt::SetInsertResponse>* TwoPhaseSetClient::Insert(const QString &refId, const QString &data)
{
    TRACE;
    Q_D(TwoPhaseSetClient);
    if(channel() == NULL) return NULL;

    crdt::ResourceObject object;
    object.set_referenceid(refId.toStdString());
    object.set_object(data.toStdString());

    crdt::SetInsertRequest request;
    request.set_allocated_object(&object);

    auto response = new GrpcPendingResponse<crdt::SetInsertResponse>;
    response->setReader(d->stub->AsyncInsert(&response->context, request, cqueue()));
    response->finish();
    return response;
}

GrpcPendingResponse<crdt::SetRemoveResponse>* TwoPhaseSetClient::Remove(const QString &refId, const QString &data)
{
    TRACE;
    Q_D(TwoPhaseSetClient);
    if(channel() == NULL) return NULL;

    crdt::ResourceObject object;
    object.set_referenceid(refId.toStdString());
    object.set_object(data.toStdString());

    crdt::SetRemoveRequest request;
    request.set_allocated_object(&object);

    auto response = new GrpcPendingResponse<crdt::SetRemoveResponse>;
    response->setReader(d->stub->AsyncRemove(&response->context, request, cqueue()));
    response->finish();
    return response;
}

GrpcPendingResponse<crdt::SetLengthResponse>* TwoPhaseSetClient::Length(const QString &refId)
{
    TRACE;
    Q_D(TwoPhaseSetClient);
    if(channel() == NULL) return NULL;

    crdt::SetLengthRequest request;
    request.set_referenceid(refId.toStdString());

    auto response = new GrpcPendingResponse<crdt::SetLengthResponse>;
    response->setReader(d->stub->AsyncLength(&response->context, request, cqueue()));
    response->finish();
    return response;
}

GrpcPendingResponse<crdt::SetContainsResponse>* TwoPhaseSetClient::Contains(const QString &refId, const QString &data)
{
    TRACE;
    Q_D(TwoPhaseSetClient);
    if(channel() == NULL) return NULL;

    crdt::ResourceObject object;
    object.set_referenceid(refId.toStdString());
    object.set_object(data.toStdString());

    crdt::SetContainsRequest request;
    request.set_allocated_object(&object);

    auto response = new GrpcPendingResponse<crdt::SetContainsResponse>;
    response->setReader(d->stub->AsyncContains(&response->context, request, cqueue()));
    response->finish();
    return response;
}
