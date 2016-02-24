#ifndef RESOURCEMODEL_H
#define RESOURCEMODEL_H

#include <QAbstractListModel>

class Context;
class Resource;

class ResourceModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        IdRole = Qt::UserRole + 1,
        TypeRole,
        ValueRole
    } ResourceRoles;

    explicit ResourceModel(QList<Resource*> resources, Context *context);
            ~ResourceModel();

    void appendTagFilter(const QString &tag);
    void removeTagFilter(const QString &tag);

    void appendTypeFilter(const QString &type);
    void removeTypeFilter(const QString &type);

    QHash<int,QByteArray> roleNames() const;

    int  rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

protected Q_SLOTS:
    void onResourceAdded(Resource *resource);
    void onResourceRemoved(const QString &id);

private:
    class ResourceModelPrivate *d_ptr;
    Q_DECLARE_PRIVATE(ResourceModel)
};

#endif // RESOURCEMODEL_H
