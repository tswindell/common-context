#ifndef CRDTGROWONLYSETRESOURCEFACTORY_H
#define CRDTGROWONLYSETRESOURCEFACTORY_H

#include <QObject>
#include "resourcefactory.h"

class GrpcChannel;

class CrdtGrowOnlySetResourceFactory : public QObject, public ResourceFactory
{
    Q_OBJECT

public:
    explicit CrdtGrowOnlySetResourceFactory(GrpcChannel *channel, QObject *parent = 0);
            ~CrdtGrowOnlySetResourceFactory();

    QString      type() const;

    Resource*  create(const QString &uuid, Context *context);
    Resource* restore(const QString &uuid, const QString &resourceId, const QString &resourceKey, Context *context);

private:
    class CrdtGrowOnlySetResourceFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(CrdtGrowOnlySetResourceFactory)
};

#endif // CRDTGROWONLYSETRESOURCEFACTORY_H
