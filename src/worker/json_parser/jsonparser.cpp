#include "jsonparser.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QDebug>

QDateTime JsonParser::m_lastEntry = QDateTime::fromSecsSinceEpoch(0);
JsonParser::JsonParser(QByteArray jsonContent, QObject *parent) :
    QObject(parent),
    m_jsonContent(jsonContent),
    m_jsonFields({})
{
    toMap();
}

JsonParser::~JsonParser()
{
    if(receivedNewData()) {
        m_lastEntry = m_entry;
    }
}

bool JsonParser::receivedNewData() const
{
    return m_entry > m_lastEntry;
}

/*!
 * \brief JsonParser::value - get value for key
 * \param key
 * \return
 */
QVariant JsonParser::value(const QString &key) const
{
    return m_jsonFields.value(key);
}

/*!
 * \brief JsonParser::lastEntryDate - get last entry date
 * \return
 */
QDateTime JsonParser::lastEntryDate() const
{
    return m_entry;
}

void JsonParser::toMap()
{
    auto jsonDoc = QJsonDocument::fromJson(m_jsonContent);
    auto jsonObj = jsonDoc.object();
    auto jsonMap = jsonObj.toVariantMap();

    auto jsonFeeds  = jsonMap["feeds"];
    auto lastFeeds  = qvariant_cast<QVariantList>(jsonFeeds).last();
    auto feeds      = qvariant_cast<QVariantMap>(lastFeeds);

    auto date = feeds["created_at"].toString();
    m_entry = QDateTime::fromString(date, Qt::ISODate);
    if(receivedNewData()) {
        auto keys = feeds.keys();
        auto values = feeds.values();
        for(int i = 0; i < feeds.size(); i++) {
            auto key = keys.at(i);
            if(key.startsWith(QStringLiteral("field"))) {
                auto value = values.at(i);
                m_jsonFields.insert(key, value);
            }
        }
    }
}
