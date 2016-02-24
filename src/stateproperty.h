#ifndef STATEPROPERTY_H
#define STATEPROPERTY_H

#include <QObject>
#include <QVariant>

class StateObject;

class StateProperty : public QObject
{
    Q_OBJECT

    Q_PROPERTY(StateObject* context READ context)
    Q_PROPERTY(QString      name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString      type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QVariant     object READ object WRITE setObject NOTIFY objectChanged)

public:
    explicit StateProperty(QObject *parent = 0);
            ~StateProperty();

    StateObject* context() const;

    QString name() const;
    Q_INVOKABLE void setName(const QString &name);

    QString type() const;
    Q_INVOKABLE void setType(const QString &type);

    QVariant object() const;
    Q_INVOKABLE void setObject(const QVariant &variant);

Q_SIGNALS:
    void contextChanged();
    void nameChanged();
    void typeChanged();
    void objectChanged();

private:
    class StatePropertyPrivate *d_ptr;
    Q_DECLARE_PRIVATE(StateProperty)
};

#endif // STATEPROPERTY_H
