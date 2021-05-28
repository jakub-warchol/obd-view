#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include "src/api/rest_client/thingspeakrestclient.h"
#include "src/settings/settingsmanager.h"

/*!
 * \brief The ConnectionManager class rpovides credentials
 */
class ConnectionManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString imeiNumber READ imeiNumber WRITE setImeiNumber NOTIFY imeiNumberChanged)
    Q_PROPERTY(QString channelId READ channelId WRITE setChannelId NOTIFY channelIdChanged)

public:
    static ConnectionManager *getInstance(QObject *parent = nullptr);

    QString imeiNumber() const;
    QString channelId() const;

public slots:
    void setImeiNumber(QString imeiNumber);
    void setChannelId(QString channelId);
    void checkImei();

private slots:
    void parseReceivedData(QString content);

signals:
    void imeiNumberChanged(QString imeiNumber);
    void channelIdChanged(QString channelId);
    void connectionFinished(bool imeiFound);

private:
    explicit ConnectionManager(QObject *parent = nullptr);

    static ConnectionManager *m_instance;

    ThingSpeakRestClient *m_restClient;
    SettingsManager *m_settingsManager;
    QString m_imeiNumber;
    QString m_channelId;

    //TODO: settings manager (load/store imei)
};

#endif // CONNECTIONMANAGER_H
