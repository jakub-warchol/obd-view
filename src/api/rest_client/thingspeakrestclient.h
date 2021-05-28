#ifndef THINGSPEAKRESTCLIENT_H
#define THINGSPEAKRESTCLIENT_H

#include "restclient.h"

/*!
 * \brief The ThingSpeakRestClient class - REST client for ThingSpeak
 */
class ThingSpeakRestClient : public RestClient
{
    Q_OBJECT

public:
    enum HttpRequestType {
        ChannelFeed,
        ChannelField,
        ChannelStatus,
        ChannelList
    };

    //TODO: channel ids enum

    explicit ThingSpeakRestClient(QObject *parent = nullptr);
    bool findChannelIdByImei();
    void getChannelStatus(const QString &channelId) const;

public slots:
    void getChannelFeed(const QString& channelId) const;
    void getChannelField(const QString& channelId, int fieldId) const;

private:
    QUrl buildUrl(const QString& channelId, ThingSpeakRestClient::HttpRequestType requestType, QVariant fieldId = {}) const;
};

#endif // THINGSPEAKRESTCLIENT_H
