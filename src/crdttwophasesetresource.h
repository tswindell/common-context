#ifndef CRDTTWOPHASESETRESOURCE_H
#define CRDTTWOPHASESETRESOURCE_H

#include <QObject>
#include "resource.h"

#define TWO_PHASE_SET_RESOURCE_TYPE_ID "crdt:2pset"

class TwoPhaseSetClient;

class CrdtTwoPhaseSetResource : public QObject, public Resource
{
    Q_OBJECT

public:
    explicit CrdtTwoPhaseSetResource(const QString &uuid, const QString &referenceId, TwoPhaseSetClient *client, Context *context);
            ~CrdtTwoPhaseSetResource();

    QString   type() const;
    QVariant value();

private:
    class CrdtTwoPhaseSetResourcePrivate *d_ptr;
    Q_DECLARE_PRIVATE(CrdtTwoPhaseSetResource)
};

#endif // CRDTTWOPHASESETRESOURCE_H
