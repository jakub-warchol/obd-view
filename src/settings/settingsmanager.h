#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>

/*!
 * \brief The SettingsManager class - provides load/store methods for settings
 */
class SettingsManager : public QObject
{
    Q_OBJECT
public:
    explicit SettingsManager(QObject *parent = nullptr);
    QVariant loadImei() const;
    void storeImei(QVariant imei);

private:
    void storeData(const QString &tag, QVariant value);
    void storeData(const QString &group, const QString &tag, QVariant value);
    QVariant loadData(const QString &tag) const;
    QVariant loadData(const QString &group, const QString &tag) const;

    const static inline QString imei_number_tag = "imei_number";

    QSettings *m_settings;
};

#endif // SETTINGSMANAGER_H
