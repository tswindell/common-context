#ifndef GRPCCHANNEL_P_H
#define GRPCCHANNEL_P_H

#include <grpc++/create_channel.h>
#include <grpc++/completion_queue.h>

#include <future>

class GrpcChannelPrivate
{
public:
    GrpcChannelPrivate()
    {/*...*/}

    std::shared_ptr<grpc::Channel>         channel;
    std::unique_ptr<grpc::CompletionQueue> cq;

    std::future<void> worker;

    void startWorker();
};

#endif // GRPCCHANNEL_P_H
