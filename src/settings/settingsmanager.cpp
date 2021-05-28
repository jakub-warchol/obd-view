#include "settingsmanager.h"
#include <QStandardPaths>

#define SETTINGS_FILENAME QStringLiteral("settings.ini")

SettingsManager::SettingsManager(QObject *parent) :
    QObject(parent)
{
    auto configPath = QStandardPaths::displayName(QStandardPaths::AppConfigLocation) + SETTINGS_FILENAME;
    m_settings = new QSettings(configPath, QSettings::IniFormat, this);
}

/*!
 * \brief SettingsManager::loadImei - load IMEI from settings file
 * \return
 */
QVariant SettingsManager::loadImei() const
{
    return loadData(imei_number_tag);
}

/*!
 * \brief SettingsManager::storeImei - store IMEI in settings file
 * \param imei
 */
void SettingsManager::storeImei(QVariant imei)
{
    storeData(imei_number_tag, imei);
}

void SettingsManager::storeData(const QString &tag, QVariant value)
{
    m_settings->setValue(tag, value);
}

void SettingsManager::storeData(const QString &group, const QString &tag, QVariant value)
{
    m_settings->beginGroup(group);
    storeData(tag, value);
    m_settings->endGroup();
}

QVariant SettingsManager::loadData(const QString &tag) const
{
    return m_settings->value(tag);
}

QVariant SettingsManager::loadData(const QString &group, const QString &tag) const
{
    m_settings->beginGroup(group);
    auto value = loadData(tag);
    m_settings->endGroup();

    return value;
}
