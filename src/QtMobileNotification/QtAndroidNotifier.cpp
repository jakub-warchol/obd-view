#include "QtAndroidNotifier.h"

#include <QVariant>
#include <QtAndroid>
//------------------------------------------------------------------------------

bool QtAndroidNotifier::show(const QVariant &notificationParameters)
{
    QVariantMap parameters = notificationParameters.toMap();
    QString caption = parameters.value("caption", "").toString();
    QAndroidJniObject jniCaption = QAndroidJniObject::fromString(caption);

    QAndroidJniObject::callStaticMethod<void>("pl/edu/pwsztar/obdview/javalib/QtAndroidNotifications",
                                              "notify",
                                              "(Landroid/content/Context;Ljava/lang/String;)V",
                                              QtAndroid::androidContext().object(),
                                              jniCaption.object<jstring>()
                                            );
    return true;
}

//------------------------------------------------------------------------------
