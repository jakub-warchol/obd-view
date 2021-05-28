#include "connectionmanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtConcurrent/QtConcurrent>

ConnectionManager* ConnectionManager::m_instance = nullptr;
ConnectionManager *ConnectionManager::getInstance(QObject *parent)
{
    if(m_instance == nullptr) {
        m_instance = new ConnectionManager(parent);
    }

    return m_instance;
}

/*!
 * \brief ConnectionManager::ConnectionManager
 * \param parent
 */
ConnectionManager::ConnectionManager(QObject *parent) :
    QObject(parent),
    m_channelId("")
{
    m_settingsManager = new SettingsManager(this);

    auto savedImei = m_settingsManager->loadImei();
    if(savedImei.isNull()) {
        m_imeiNumber = QStringLiteral("");
    } else {
        m_imeiNumber = savedImei.toString();
    }

    m_restClient = new ThingSpeakRestClient(this);
    connect(m_restClient, &ThingSpeakRestClient::dataReceived, this, &ConnectionManager::parseReceivedData);

    connect(this, &ConnectionManager::connectionFinished, this, [this](bool imeiFound) {
       if(imeiFound) {
           m_settingsManager->storeImei(m_imeiNumber);
       }
    });
}

QString ConnectionManager::imeiNumber() const
{
    return m_imeiNumber;
}

QString ConnectionManager::channelId() const
{
    return m_channelId;
}

void ConnectionManager::setImeiNumber(QString imeiNumber)
{
    if (m_imeiNumber == imeiNumber)
        return;

    m_imeiNumber = imeiNumber;
    emit imeiNumberChanged(m_imeiNumber);
}

void ConnectionManager::setChannelId(QString channelId)
{
    if (m_channelId == channelId)
        return;

    m_channelId = channelId;
    emit channelIdChanged(m_channelId);
}

/*!
 * \brief ConnectionManager::checkImei - check if IMEI exists
 */
void ConnectionManager::checkImei()
{
    m_restClient->findChannelIdByImei();
}

/*!
 * \brief ConnectionManager::parseReceivedData - parse data from server
 * \param content
 */
void ConnectionManager::parseReceivedData(QString content)
{
    bool imeiFound = false;
    if(!content.isEmpty()) {
        QJsonParseError jsonError;
        auto contentArr = content.toUtf8();
        auto jsonDoc = QJsonDocument::fromJson(contentArr, &jsonError);

        auto jsonObject = jsonDoc.object();

        if(jsonError.error != jsonError.NoError) {
            qDebug() << "error:" << jsonError.error << jsonError.errorString();
        } else {
            auto jsonValuesMap = jsonObject.toVariantMap();
            auto channels = jsonValuesMap[QStringLiteral("channels")].toList();

            for(const auto& channel : channels) {
                auto channelMap = channel.toMap();

                auto channelName = channelMap[QStringLiteral("name")].toString();
                if(channelName == m_imeiNumber) {
                    auto channelId = channelMap[QStringLiteral("id")].toLongLong();
                    setChannelId(QString::number(channelId));

                    imeiFound = true;
                    break;
                }
            }
        }
    }

    emit connectionFinished(imeiFound);
}
