#ifndef CRDTGROWONLYSETRESOURCE_H
#define CRDTGROWONLYSETRESOURCE_H

#include <QObject>
#include "resource.h"

#define GROW_ONLY_SET_RESOURCE_TYPE_ID "crdt:gset"

class GrowOnlySetClient;

class CrdtGrowOnlySetResource : public QObject, public Resource
{
    Q_OBJECT

public:
    explicit CrdtGrowOnlySetResource(const QString &uuid, const QString &referenceId, GrowOnlySetClient *client, Context *context);
            ~CrdtGrowOnlySetResource();

    QString   type() const;
    QVariant value();

private:
    class CrdtGrowOnlySetResourcePrivate *d_ptr;
    Q_DECLARE_PRIVATE(CrdtGrowOnlySetResource)
};

#endif // CRDTGROWONLYSETRESOURCE_H
