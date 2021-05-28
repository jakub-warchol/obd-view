#include "restclient.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

/*!
 * \brief RestClient::RestClient
 * \param parent
 */
RestClient::RestClient(QObject *parent) : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &RestClient::readNetworkReply);
}

/*!
 * \brief RestClient::get - invoke GET method on url
 * \param url
 */
void RestClient::get(const QUrl &url) const
{
    QNetworkRequest request;
    request.setUrl(url);
    m_networkManager->get(request);
}

/*!
 * \brief RestClient::readNetworkReply - read network reply
 * \param reply
 */
void RestClient::readNetworkReply(QNetworkReply *reply)
{
    qDebug() << __PRETTY_FUNCTION__;
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    qDebug() << "Request:" << reply->request().url() << "status code:" << statusCode.toInt();

    QString content;
    if(reply->error() == QNetworkReply::NoError) {
        content = reply->readAll();
    } else {
        content = reply->error() + reply->errorString();
    }

    qDebug() << QStringLiteral("Content:") << content;
    qDebug() << "------------------------\n";

    emit dataReceived(content);
    reply->deleteLater();
}
