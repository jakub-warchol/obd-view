#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QQuickItem>

#include "src/models/diagnostic_data_model/gauges_model/gaugesmodel.h"
#include "src/models/diagnostic_data_model/other_data_model/otherdiagnosticdatamodel.h"
#include "src/models/error_model/errormessagesmodel.h"
#include "src/api/rest_client/thingspeakrestclient.h"
#include "src/items/map_route/maproute.h"
#include "src/QtMobileNotification/QtNotification.h"

/*!
 * \brief The WorkerThread class - provides methodology to update data in separate thread
 */
class WorkerThread : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MapRoute* mapRoute READ mapRoute WRITE setMapRoute NOTIFY mapRouteChanged)
public:
    explicit WorkerThread(QObject *parent = nullptr);
    ~WorkerThread() override;
    quintptr workerThreadQuintptr() const;
    MapRoute *mapRoute() const;

public slots:
    void startWorkerThread(const QString channelId);
    void setMapRoute(MapRoute *mapRoute);

signals:
    void mapRouteChanged(MapRoute* mapRoute);

private slots:
    void askServer() const;
    void run();
    void evaluateData(QString content);

private:
    void sendMessage(const QByteArray &message, int id) const;

    GaugesModel *m_gaugesModel;
    OtherDiagnosticDataModel *m_diagnosticModel;
    ErrorMessagesModel *m_errorsModel;
    ThingSpeakRestClient *m_restClient;

    QThread *m_workerThread;
    QTimer *m_timer;
    QTimer *m_coordsTimer;
    QTimer *m_diagnosticTimer;
    QTimer *m_errorTimer;
    QString m_channelId;

    MapRoute* m_mapRoute;
    QtNotification *m_mobileNotification;

    QString m_lastAlertMsg;
};

#endif // WORKERTHREAD_H
