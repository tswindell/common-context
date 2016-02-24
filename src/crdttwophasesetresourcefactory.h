#ifndef CRDTTWOPHASESETRESOURCEFACTORY_H
#define CRDTTWOPHASESETRESOURCEFACTORY_H

#include <QObject>
#include "resourcefactory.h"

class GrpcChannel;

class CrdtTwoPhaseSetResourceFactory : public QObject, public ResourceFactory
{
    Q_OBJECT

public:
    explicit CrdtTwoPhaseSetResourceFactory(GrpcChannel *channel, QObject *parent = 0);
            ~CrdtTwoPhaseSetResourceFactory();

    QString      type() const;

    Resource*  create(const QString &uuid, Context *context);
    Resource* restore(const QString &uuid, const QString &resourceId, const QString &resourceKey, Context *context);

private:
    class CrdtTwoPhaseSetResourceFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(CrdtTwoPhaseSetResourceFactory)
};

#endif // CRDTTWOPHASESETRESOURCEFACTORY_H
