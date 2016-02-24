#include "grpcclient.h"

#include "grpcchannel.h"
#include "grpcchannel_p.h"

class GrpcClientPrivate
{
public:
    GrpcClientPrivate()
        : channel(NULL)
    {/*...*/}

    GrpcChannel *channel;
};

GrpcClient::GrpcClient(QObject *parent)
    : QObject(parent), d_ptr(new GrpcClientPrivate)
{
}

GrpcClient::~GrpcClient()
{
    delete d_ptr;
}

GrpcChannel* GrpcClient::channel() const
{
    Q_D(const GrpcClient);
    return d->channel;
}

void GrpcClient::setChannel(GrpcChannel *channel)
{
    Q_D(GrpcClient);
    if(d->channel != channel)
    {
        d->channel = channel;
        emit channelChanged();
    }
}

void GrpcClient::connectToHost(const QString &hostport)
{
    Q_D(GrpcClient);
    d->channel = new GrpcChannel(this);
    d->channel->connectToHost(hostport);
    emit channelChanged();

    QObject::connect(this, &GrpcClient::channelChanged,
                     d->channel, &QObject::deleteLater);
}

std::shared_ptr<grpc::Channel> GrpcClient::transport()
{
    Q_D(GrpcClient);
    return d->channel->d_ptr->channel;
}

grpc::CompletionQueue* GrpcClient::cqueue()
{
    Q_D(GrpcClient);
    return d->channel->d_ptr->cq.get();
}
