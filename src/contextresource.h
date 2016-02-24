#ifndef CONTEXTRESOURCE_H
#define CONTEXTRESOURCE_H

#include <QObject>

#include "resource.h"

#define CONTEXT_RESOURCE_TYPE_ID "web:Context"

class ContextResource : public QObject, public Resource
{
    Q_OBJECT

public:
    explicit ContextResource(const QString &uuid, Context *context);
            ~ContextResource();

    QString type() const;
    QVariant value();

private:
    class ContextResourcePrivate *d_ptr;
    Q_DECLARE_PRIVATE(ContextResource)
};

#endif // CONTEXTRESOURCE_H
