#include "contextresource.h"
#include "context.h"

class ContextResourcePrivate
{
public:
    ContextResourcePrivate(Context *pContext)
        : context(pContext)
    {/*...*/}

    Context *context;
};

ContextResource::ContextResource(const QString &uuid, Context *context)
    : QObject(context), Resource(uuid, context), d_ptr(new ContextResourcePrivate(context))
{
}

ContextResource::~ContextResource()
{
    delete d_ptr;
}

QString ContextResource::type() const
{
    return CONTEXT_RESOURCE_TYPE_ID;
}

QVariant ContextResource::value()
{
    Q_D(const ContextResource);
    return QVariant::fromValue(d->context);
}
