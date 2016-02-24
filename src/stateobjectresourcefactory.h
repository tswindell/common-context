#ifndef STATEOBJECTRESOURCEFACTORY_H
#define STATEOBJECTRESOURCEFACTORY_H

#include <QObject>

class StateObjectResourceFactory : public QObject
{
    Q_OBJECT
public:
    explicit StateObjectResourceFactory(QObject *parent = 0);

signals:

public slots:
};

#endif // STATEOBJECTRESOURCEFACTORY_H