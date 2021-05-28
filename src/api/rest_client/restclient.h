#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QObject>
#include <QVariant>

// forward class declarations
class QNetworkAccessManager;
class QNetworkReply;

/*!
 * \brief The RestClient class provides interface for network query
 */
class RestClient : public QObject
{
    Q_OBJECT
public:
    explicit RestClient(QObject *parent = nullptr);

protected:
    void get(const QUrl &url) const;

signals:
    void dataReceived(QString content);

private slots:
    void readNetworkReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_networkManager;
};

#endif // RESTCLIENT_H
