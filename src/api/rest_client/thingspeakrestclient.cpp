#include <QUrl>
#include "thingspeakrestclient.h"

#define THINGSPEAK_URL QStringLiteral("https://api.thingspeak.com/channels/")
#define THINGSPEAK_CHANNEL_URL QStringLiteral("https://api.thingspeak.com/users/%1/channels.json")
#define THINGSPEAK_USERNAME "mwa0000015491829"

ThingSpeakRestClient::ThingSpeakRestClient(QObject *parent) :
    RestClient(parent)
{}

void ThingSpeakRestClient::getChannelFeed(const QString &channelId) const
{
    auto url = buildUrl(channelId, ThingSpeakRestClient::ChannelFeed);
    get(url);
}

void ThingSpeakRestClient::getChannelField(const QString &channelId, int fieldId) const
{
    auto url = buildUrl(channelId, ThingSpeakRestClient::ChannelField, fieldId);
    get(url);
}

void ThingSpeakRestClient::getChannelStatus(const QString &channelId) const
{
    auto url = buildUrl(channelId, ThingSpeakRestClient::ChannelStatus);
    get(url);
}

bool ThingSpeakRestClient::findChannelIdByImei()
{
    auto url = buildUrl("", ThingSpeakRestClient::ChannelList);
    get(url);

    return false;
}

QUrl ThingSpeakRestClient::buildUrl(const QString &channelId, ThingSpeakRestClient::HttpRequestType requestType, QVariant fieldId) const
{
    auto urlString = THINGSPEAK_URL;
    urlString += channelId;

    switch (requestType) {
    case ChannelFeed:
        urlString += QStringLiteral("/feeds.json?results=2");
        break;
    case ChannelField:
        urlString += QString("/fields/%1.json?results=2").arg(fieldId.toInt());
        break;
    case ChannelStatus:
        urlString += QStringLiteral("/status.json");
        break;
    case ChannelList:
        urlString = THINGSPEAK_CHANNEL_URL.arg(THINGSPEAK_USERNAME);
    }

    return QUrl(urlString);
}
