#ifndef QUICKRESOURCE_H
#define QUICKRESOURCE_H

#include <QObject>

class QuickResource : public QObject
{
    Q_OBJECT
public:
    explicit QuickResource(QObject *parent = 0);

signals:

public slots:
};

#endif // QUICKRESOURCE_H