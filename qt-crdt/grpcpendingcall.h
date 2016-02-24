#ifndef CRDTPENDINGREPLY_H
#define CRDTPENDINGREPLY_H

#include <QObject>

#include <QReadWriteLock>
#include <QWaitCondition>

#include <QDebug>

#include "common.h"

#include <grpc++/channel.h>
#include <future>

class GrpcPendingCall
{
public:
    virtual void cont() = 0;

    grpc::ClientContext context;
    grpc::Status        status;

    GrpcPendingCall() : m_finished(false) {/*...*/}

    bool isFinished() { QReadLocker locker(&m_mutex); return m_finished; }

    void waitForFinished()
    {
        QReadLocker locker(&m_mutex);
        if(!m_finished) m_wait_finished.wait(&m_mutex);
    }

    bool isError() { QReadLocker locker(&m_mutex); return !status.ok(); }

    QString errorString()
    {
        QReadLocker locker(&m_mutex);
        if(!status.ok())
        {
            return QString::fromStdString(status.error_message());
        }

        return QString();
    }

protected:
    QReadWriteLock m_mutex;
    QWaitCondition m_wait_finished;

    bool m_finished;
};

/* --- */
template <typename T>
class GrpcPendingResponse : public GrpcPendingCall
{
public:
    GrpcPendingResponse()
        : m_reply(new T)
    {/*...*/}

    ~GrpcPendingResponse() { delete m_reply; }

    T* reply() { QReadLocker locker(&m_mutex); return m_finished ? m_reply : NULL; }

    void setReader(std::unique_ptr<grpc::ClientAsyncResponseReader<T>> reader)
    {
        QWriteLocker locker(&m_mutex);
        m_reader = std::move(reader);
    }

    void finish()
    {
        QWriteLocker locker(&m_mutex);
        m_reader->Finish(m_reply, &status, this);
    }

    void cont()
    {
        TRACE;
        QWriteLocker locker(&m_mutex);
        m_finished = true;
        m_wait_finished.wakeAll();
    }

private:
    T *m_reply;

    std::unique_ptr<grpc::ClientAsyncResponseReader<T>> m_reader;
};

/* --- */
template <typename T>
class GrpcPendingReader : public GrpcPendingCall
{
public:
    void setReader(std::unique_ptr<grpc::ClientAsyncReader<T>> reader)
    {
        TRACE;
        QWriteLocker locker(&m_mutex);
        m_reader = std::move(reader);
    }

    void finish()
    {
        QWriteLocker locker(&m_mutex);
    }

    void cont()
    {
        TRACE;
        QWriteLocker locker(&m_mutex);
    }

private:
    std::unique_ptr<grpc::ClientAsyncReader<T>> m_reader;
};


/* --- */
template <typename T>
class GrpcPendingWriter : public GrpcPendingCall
{
public:
    void setWriter(std::unique_ptr<grpc::ClientAsyncWriter<T>> writer)
    {
        TRACE;
        QWriteLocker locker(&m_mutex);
        m_writer = std::move(writer);
    }

    void cont()
    {
        TRACE;
        QWriteLocker locker(&m_mutex);
    }

private:
    std::unique_ptr<grpc::ClientAsyncWriter<T>> m_writer;
};


/* --- */
template <typename R, typename W>
class GrpcPendingReaderWriter : public GrpcPendingCall
{
public:
    void setReaderWriter(std::unique_ptr<grpc::ClientAsyncReaderWriter<R, W>> readerwriter)
    {
        TRACE;
        QWriteLocker locker(&m_mutex);
        m_readerwriter = std::move(readerwriter);
    }

    void cont()
    {
        TRACE;
        QWriteLocker locker(&m_mutex);
    }

private:
    std::unique_ptr<grpc::ClientAsyncReaderWriter<R, W>> m_readerwriter;
};

#endif // CRDTPENDINGREPLY_H
