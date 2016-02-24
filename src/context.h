#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QHash>

#include "crdt/grpcchannel.h"

class Resource;
class ResourceFactory;
class ResourceModel;

class Context : public QObject
{
    Q_OBJECT

    friend class Resource;
    friend class ResourceModel;

public:
    struct Tag
    {
        QString uuid;
        QString name;
        QString target;
    };

    explicit Context(const QString &referenceId, GrpcChannel *channel, QObject *parent = 0);
            ~Context();

    ResourceFactory* getTypeFactory(const QString &typeId);
    void             addTypeFactory(ResourceFactory *factory);

    Q_INVOKABLE ResourceModel* resources();
    Q_INVOKABLE QStringList    tags() const;

    Q_INVOKABLE Resource*      findById(const QString &id) const;
    Q_INVOKABLE ResourceModel* findByTag(const QString &tag);
    Q_INVOKABLE ResourceModel* findByType(const QString &type);

    Q_INVOKABLE Resource* create(const QString &typeId);
    Q_INVOKABLE void      insert(Resource* resource);
    Q_INVOKABLE void      remove(Resource* resource);

    Q_INVOKABLE void      tag(const QString &tag, Resource *resource);
    Q_INVOKABLE void      untag(const QString &tag, Resource *resource);

Q_SIGNALS:
    void resourceAdded(Resource *resource);
    void resourceRemoved(const QString &resourceId);

protected:
    void onObjectAdded(const QString &object);
    void onObjectRemoved(const QString &object);

private:
    class ContextPrivate *d_ptr;
    Q_DECLARE_PRIVATE(Context)
};

#endif // CONTEXT_H
