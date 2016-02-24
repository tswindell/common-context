#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include <QString>

class Context;
class Resource;

class ResourceFactory
{
public:
    virtual QString type() const = 0;

    virtual Resource*  create(const QString &uuid, Context *context) = 0;
    virtual Resource* restore(const QString &uuid, const QString &resourceId, const QString &resourceKey, Context *context) = 0;
};

#endif // RESOURCEFACTORY_H
