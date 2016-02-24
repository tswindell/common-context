#include "stateobject.h"
#include "stateproperty.h"

class StateObjectPrivate
{
public:
    StateObjectPrivate()
    {/*...*/}

    QList<StateProperty*> properties;
};

StateObject::StateObject(QObject *parent)
    : QObject(parent), d_ptr(new StateObjectPrivate)
{

}

StateObject::~StateObject()
{
    delete d_ptr;
}

QQmlListProperty<StateProperty> StateObject::properties()
{
    Q_D(StateObject);
    return QQmlListProperty<StateProperty>(this, d->properties);
}

StateProperty* StateObject::findByName(const QString &name) const
{
    Q_D(const StateObject);
    foreach(StateProperty *iter, d->properties)
    {
        if(iter->name() == name) return iter;
    }
    return NULL;
}

void StateObject::appendProperty(StateProperty *prop)
{
    Q_D(StateObject);
    d->properties.append(prop);
    emit propertiesChanged();
}

void StateObject::removeProperty(StateProperty *prop)
{
    Q_D(StateObject);
    d->properties.removeOne(prop);
    emit propertiesChanged();}
