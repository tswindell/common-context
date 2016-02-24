#include "common.h"
#include "growonlysetclient.h"

class GrowOnlySetClientPrivate
{
public:
    GrowOnlySetClientPrivate() {/*...*/}

    std::unique_ptr<crdt::GrowOnlySet::Stub> stub;
};

GrowOnlySetClient::GrowOnlySetClient(QObject *parent)
    : GrpcClient(parent)
{
    TRACE;
    QObject::connect(this, &GrpcClient::channelChanged,
                     this, &GrowOnlySetClient::onChannelChanged);
}

GrowOnlySetClient::~GrowOnlySetClient()
{
    TRACE;
    delete d_ptr;
}

void GrowOnlySetClient::onChannelChanged()
{
    TRACE;
    Q_D(GrowOnlySetClient);
    if(channel() == NULL) return;
    d->stub = crdt::GrowOnlySet::NewStub(transport());
}

GrpcPendingReader<crdt::ResourceObject>* GrowOnlySetClient::List(const QString &refId)
{
    TRACE;
    Q_D(GrowOnlySetClient);
    if(channel() == NULL) return NULL;

    crdt::SetListRequest request;
    request.set_referenceid(refId.toStdString());

    auto response = new GrpcPendingReader<crdt::ResourceObject>;
    response->setReader(d->stub->AsyncList(&response->context, request, cqueue(), response));
    response->finish();
    return response;
}

GrpcPendingResponse<crdt::SetInsertResponse>* GrowOnlySetClient::Insert(const QString &refId, const QString &data)
{
    TRACE;
    Q_D(GrowOnlySetClient);
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

GrpcPendingResponse<crdt::SetLengthResponse>* GrowOnlySetClient::Length(const QString &refId)
{
    TRACE;
    Q_D(GrowOnlySetClient);
    if(channel() == NULL) return NULL;

    crdt::SetLengthRequest request;
    request.set_referenceid(refId.toStdString());

    auto response = new GrpcPendingResponse<crdt::SetLengthResponse>;
    response->setReader(d->stub->AsyncLength(&response->context, request, cqueue()));
    response->finish();
    return response;
}

GrpcPendingResponse<crdt::SetContainsResponse>* GrowOnlySetClient::Contains(const QString &refId, const QString &data)
{
    TRACE;
    Q_D(GrowOnlySetClient);
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
