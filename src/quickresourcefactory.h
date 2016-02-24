#ifndef QUICKRESOURCEFACTORY_H
#define QUICKRESOURCEFACTORY_H

#include <QObject>

class QuickResourceFactory : public QObject
{
    Q_OBJECT
public:
    explicit QuickResourceFactory(QObject *parent = 0);

signals:

public slots:
};

#endif // QUICKRESOURCEFACTORY_H