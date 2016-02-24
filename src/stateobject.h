#ifndef STATEOBJECT_H
#define STATEOBJECT_H

#include <QObject>
#include <QQmlListProperty>

class StateProperty;

class StateObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<StateProperty> properties READ properties NOTIFY propertiesChanged)

public:
    explicit StateObject(QObject *parent = 0);
            ~StateObject();

    QQmlListProperty<StateProperty> properties();

    Q_INVOKABLE StateProperty* findByName(const QString &name) const;

    void appendProperty(StateProperty *prop);
    void removeProperty(StateProperty *prop);

Q_SIGNALS:
    void propertiesChanged();

private:
    class StateObjectPrivate *d_ptr;
    Q_DECLARE_PRIVATE(StateObject)
};

#endif // STATEOBJECT_H
