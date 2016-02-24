#ifndef GRPCCHANNEL_H
#define GRPCCHANNEL_H

#include <QObject>

class GrpcClient;

class GrpcChannel : public QObject
{
    Q_OBJECT

public:
    explicit GrpcChannel(QObject *parent = 0);
            ~GrpcChannel();

    void connectToHost(const QString &hostport);

private:
    class GrpcChannelPrivate *d_ptr;
    Q_DECLARE_PRIVATE(GrpcChannel)

    friend class GrpcClient;
};

#endif // GRPCCHANNEL_H
