#ifndef QTANDROIDNotifier_H
#define QTANDROIDNotifier_H

#include "QtAbstractNotifier.h"

class QtAndroidNotifier : public QtAbstractNotifier
{
public:
    QtAndroidNotifier() {}

public:
    virtual bool show(const QVariant &notificationParameters) override;
};

#endif // QTANDROIDNotifier_H
