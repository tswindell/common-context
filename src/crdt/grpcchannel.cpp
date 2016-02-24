#include "common.h"

#include "grpcchannel.h"
#include "grpcchannel_p.h"

#include "grpcpendingcall.h"

#include <QDebug>

void GrpcChannelPrivate::startWorker()
{
    TRACE;
    this->worker = std::async(std::launch::async, [this] {
        void *tag = NULL;
        bool ok = false;

        while(true)
        {
            if(!cq->Next(&tag, &ok))
            {
                qDebug() << "ERROR: CompletionQueue::Next failed";
                return;
            }

            if(!ok)
            {
                qDebug() << "ERROR: Request returned error.";
                return;
            }

            GrpcPendingCall *call = static_cast<GrpcPendingCall*>(tag);
            if(call == NULL)
            {
                qDebug() << "Failed to cast PendingCall* instance.";
                return;
            }

            qDebug() << "I: Completing RPC call.";
            call->cont();
        }
    });
}

GrpcChannel::GrpcChannel(QObject *parent)
    : QObject(parent), d_ptr(new GrpcChannelPrivate)
{
    Q_D(GrpcChannel);
    d->cq.reset(new grpc::CompletionQueue);
}

GrpcChannel::~GrpcChannel()
{
    Q_D(GrpcChannel);
    d->cq->Shutdown();
    delete d_ptr;
}

void GrpcChannel::connectToHost(const QString &hostport)
{
    Q_D(GrpcChannel);
    if(d->channel.get() != NULL)
    {
        qWarning() << "Channel already initialized.";
        return;
    }

    d->channel = grpc::CreateChannel(hostport.toStdString(), grpc::InsecureCredentials());
    d->startWorker();
}
