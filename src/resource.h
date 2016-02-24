#ifndef RESOURCE_H
#define RESOURCE_H

#include <QString>
#include <QVariant>

class Context;

class Resource
{
    friend class Context;
    friend class ResourceFactory;

public:
    explicit Resource(const QString &uuid, Context *context);
            ~Resource();

    QString uuid() const;

    virtual QString   type() const = 0;
    virtual QVariant value() = 0;

    QStringList tags() const;

    // IPFS Hash or CRDT resourceId (might be dynamic)
    QString resourceId() const;
    void setResourceId(const QString &resourceId);

    // Encryption type:key
    QString resourceKey() const;
    void setResourceKey(const QString &resourceKey);

private:
    class ResourcePrivate *d;
};

#endif // RESOURCE_H
