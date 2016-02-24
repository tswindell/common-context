#ifndef STATEOBJECTRESOURCE_H
#define STATEOBJECTRESOURCE_H

#include <QObject>

class StateObjectResource : public QObject
{
    Q_OBJECT
public:
    explicit StateObjectResource(QObject *parent = 0);

signals:

public slots:
};

#endif // STATEOBJECTRESOURCE_H