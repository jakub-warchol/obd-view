#ifndef QTIOSNotifier_H
#define QTIOSNotifier_H

#include "QtAbstractNotifier.h"

class QtIosNotifier : public QtAbstractNotifier
{

public:
    QtIosNotifier();

public:
    virtual bool show(const QVariant &notificationParameters) override;

private:
    void                *m_Delegate;
};

#endif // QTIOSNotifier_H
