#include "stateproperty.h"
#include "stateobject.h"

class StatePropertyPrivate
{
public:
    StatePropertyPrivate()
    {/*...*/}

    StateObject *context;
    QString      name;
    QString      type;
    QVariant     object;
};

StateProperty::StateProperty(QObject *parent)
    : QObject(parent), d_ptr(new StatePropertyPrivate)
{
    Q_D(StateProperty);
    d->context = qobject_cast<StateObject*>(parent);
}

StateProperty::~StateProperty()
{
    delete d_ptr;
}

StateObject* StateProperty::context() const
{
    Q_D(const StateProperty);
    return d->context;
}

QString StateProperty::name() const
{
    Q_D(const StateProperty);
    return d->name;
}

void StateProperty::setName(const QString &name)
{
    Q_D(StateProperty);
    if(d->name != name)
    {
        d->name = name;
        emit nameChanged();
    }
}

QString StateProperty::type() const
{
    Q_D(const StateProperty);
    return d->type;
}

void StateProperty::setType(const QString &type)
{
    Q_D(StateProperty);
    if(d->type != type)
    {
        d->type = type;
        emit typeChanged();
    }
}

QVariant StateProperty::object() const
{
    Q_D(const StateProperty);
    return d->object;
}

void StateProperty::setObject(const QVariant &variant)
{
    Q_D(StateProperty);
    if(d->object != variant)
    {
        d->object = variant;
        emit objectChanged();
    }
}
