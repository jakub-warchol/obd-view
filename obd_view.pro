QT += quick core widgets network concurrent positioning quickcontrols2 location

CONFIG += c++17

HEADERS += \
    src/api/connection_manager/connectionmanager.h \
    src/api/rest_client/restclient.h \
    src/api/rest_client/thingspeakrestclient.h \
    src/items/map_route/maproute.h \
    src/models/diagnostic_data_model/gauges_model/gaugesmodel.h \
    src/models/diagnostic_data_model/other_data_model/otherdiagnosticdatamodel.h \
    src/models/error_model/error_description/errordescriptiondtcsfileparser.h \
    src/models/error_model/error_description/errordescriptionprovider.h \
    src/models/error_model/errormessagesmodel.h \
    src/models/modelmanager.h \
    src/settings/settingsmanager.h \
    src/worker/data_structs/diagnostic_data.h \
    src/worker/data_structs/error_data.h \
    src/worker/data_structs/gps_data.h \
    src/worker/json_parser/jsonparser.h \
    src/worker/workerthread.h \

SOURCES += \
    src/api/connection_manager/connectionmanager.cpp \
    src/api/rest_client/restclient.cpp \
    src/api/rest_client/thingspeakrestclient.cpp \
    src/items/map_route/maproute.cpp \
    src/main.cpp \
    src/models/diagnostic_data_model/gauges_model/gaugesmodel.cpp \
    src/models/diagnostic_data_model/other_data_model/otherdiagnosticdatamodel.cpp \
    src/models/error_model/error_description/errordescriptiondtcsfileparser.cpp \
    src/models/error_model/error_description/errordescriptionprovider.cpp \
    src/models/error_model/errormessagesmodel.cpp \
    src/models/modelmanager.cpp \
    src/settings/settingsmanager.cpp \
    src/worker/json_parser/jsonparser.cpp \
    src/worker/workerthread.cpp \

RESOURCES += qml.qrc \
    resources.qrc


# Add Qt Notification
include($$PWD/src/QtMobileNotification/QtMobileNotification.pri)
include($$PWD/src/QtMobileNotification/deployment.pri)


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# Android config
# Android OpenSSL lib
android: include(src/android_openssl/openssl.pri)

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
ANDROID_ABIS = armeabi-v7a arm64-v8a x86 # check it manually!!!
DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

# iOS config
ios {
    # set info
    QMAKE_TARGET_BUNDLE_PREFIX = pl.edu.pwsztar
}
android: include(/home/jakub/Android/Sdk/android_openssl/openssl.pri)
