#ifndef CONTEXTRESOURCEFACTORY_H
#define CONTEXTRESOURCEFACTORY_H

#include <QObject>
#include "resourcefactory.h"

class GrpcChannel;
class Context;

class ContextResourceFactory : public QObject, public ResourceFactory
{
    Q_OBJECT

public:
    explicit ContextResourceFactory(GrpcChannel *channel, QObject *parent = 0);
            ~ContextResourceFactory();

    QString      type() const;

    Resource*  create(const QString &uuid, Context *context);
    Resource* restore(const QString &uuid, const QString &resourceId, const QString &resourceKey, Context *context);

private:
    class ContextResourceFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(ContextResourceFactory)
};

#endif // CONTEXTRESOURCEFACTORY_H
