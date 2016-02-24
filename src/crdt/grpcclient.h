#ifndef GRPCCLIENT_H
#define GRPCCLIENT_H

#include <QObject>
#include <grpc++/channel.h>

class GrpcChannel;

class GrpcClient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(GrpcChannel *channel READ channel WRITE setChannel NOTIFY channelChanged)

public:
    explicit GrpcClient(QObject *parent = 0);
            ~GrpcClient();

    GrpcChannel* channel() const;
    Q_INVOKABLE void setChannel(GrpcChannel *channel);

public Q_SLOTS:
    void connectToHost(const QString &hostport);

Q_SIGNALS:
    void channelChanged();

protected:
    grpc::CompletionQueue*         cqueue();
    std::shared_ptr<grpc::Channel> transport();

private:
    class GrpcClientPrivate *d_ptr;
    Q_DECLARE_PRIVATE(GrpcClient)
};

#endif // GRPCCLIENT_H
