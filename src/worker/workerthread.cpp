#include "workerthread.h"
#include <QDebug>

#include "./json_parser/jsonparser.h"

#include "src/worker/data_structs/diagnostic_data.h"
#include "src/worker/data_structs/error_data.h"
#include "src/worker/data_structs/gps_data.h"

#define GET_BIT(n, b) n & (1L << (7 - b))


WorkerThread::WorkerThread(QObject *parent) :
    QObject(parent),
    m_mapRoute(nullptr)
{
    m_workerThread = new QThread();
    moveToThread(m_workerThread);

    m_gaugesModel       = GaugesModel::getInstance();
    m_diagnosticModel   = OtherDiagnosticDataModel::getInstance();
    m_errorsModel       = ErrorMessagesModel::getInstance();

    m_restClient    = new ThingSpeakRestClient();
    m_timer             = new QTimer();
    m_diagnosticTimer   = new QTimer();
    m_coordsTimer       = new QTimer();
    m_errorTimer        = new QTimer();

    m_mobileNotification = new QtNotification();

    connect(m_workerThread, &QThread::started, this, &WorkerThread::run);
    connect(m_restClient, &ThingSpeakRestClient::dataReceived, this, &WorkerThread::evaluateData, Qt::QueuedConnection);

    connect(m_timer, &QTimer::timeout, this, &WorkerThread::askServer, Qt::QueuedConnection);
    connect(m_diagnosticTimer, &QTimer::timeout, this, [this] {
        QMetaObject::invokeMethod(m_restClient, "getChannelField", Qt::QueuedConnection, Q_ARG(const QString&, m_channelId), Q_ARG(int, 3));
    }, Qt::QueuedConnection);
    connect(m_coordsTimer, &QTimer::timeout, this, [this] {
        QMetaObject::invokeMethod(m_restClient, "getChannelField", Qt::QueuedConnection, Q_ARG(const QString&, m_channelId), Q_ARG(int, 2));
    }, Qt::QueuedConnection);
    connect(m_errorTimer, &QTimer::timeout, this, [this] {
        QMetaObject::invokeMethod(m_restClient, "getChannelField", Qt::QueuedConnection, Q_ARG(const QString&, m_channelId), Q_ARG(int, 1));
    }, Qt::QueuedConnection);

    connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, this, [this] {
        m_timer->stop();
        m_diagnosticTimer->stop();
        m_errorTimer->stop();
        m_coordsTimer->stop();
    });

}

WorkerThread::~WorkerThread()
{
    if(m_restClient) {
        delete m_restClient;
    }

    if(m_timer) {
        delete m_timer;
    }

    if(m_diagnosticTimer) {
        delete m_diagnosticTimer;
    }

    if(m_coordsTimer) {
        delete m_coordsTimer;
    }

    if(m_errorTimer) {
        delete m_errorTimer;
    }

    if(m_mobileNotification) {
        delete m_mobileNotification;
    }
}

/*!
 * \brief WorkerThread::startWorkerThread - start thread
 * \param channelId
 */
void WorkerThread::startWorkerThread(const QString channelId)
{
    m_channelId = channelId;

    if(!m_workerThread->isRunning()) {
        m_timer->moveToThread(m_workerThread);
        m_diagnosticTimer->moveToThread(m_workerThread);
        m_errorTimer->moveToThread(m_workerThread);
        m_coordsTimer->moveToThread(m_workerThread);

        m_restClient->moveToThread(m_workerThread);
    }

    m_workerThread->start();
}

void WorkerThread::setMapRoute(MapRoute *mapRoute)
{
    if (m_mapRoute == mapRoute)
        return;

    m_mapRoute = mapRoute;
    emit mapRouteChanged(m_mapRoute);
}

quintptr WorkerThread::workerThreadQuintptr() const
{
    return reinterpret_cast<quintptr>(m_workerThread);
}

MapRoute *WorkerThread::mapRoute() const
{
    return m_mapRoute;
}

/*!
 * \brief WorkerThread::askServer - ask server for new data
 */
void WorkerThread::askServer() const
{
    QMetaObject::invokeMethod(m_restClient, "getChannelFeed", Qt::QueuedConnection, Q_ARG(const QString&, m_channelId));
}

/*!
 * \brief WorkerThread::run - run timer for automatically invoke askServer
 */
void WorkerThread::run()
{
    qDebug() << "worker thread started";

    this->askServer();

    m_timer->start(1500 /* ms */);
//    m_diagnosticTimer->start(6000 /* ms */);
//    m_errorTimer->start(34000 /* ms */);
//    m_coordsTimer->start(32000 /* ms */);
}

/*!
 * \brief WorkerThread::evaluateData - evalutate received data
 * \param content
 */
void WorkerThread::evaluateData(QString content)
{
    JsonParser parser{content.toUtf8()};
    if(parser.receivedNewData()) {
        auto field1 = parser.value(QStringLiteral("field1")).toString(); // errors
        auto field2 = parser.value(QStringLiteral("field2")).toString(); // coords
        auto field3 = parser.value(QStringLiteral("field3")).toString(); // diagnostic data
        auto field4 = parser.value(QStringLiteral("field4")).toString(); // alert

        auto parsedErrorsData       = QByteArray::fromBase64(field1.toUtf8(), QByteArray::AbortOnBase64DecodingErrors);
        auto parsedCoords           = QByteArray::fromBase64(field2.toUtf8(), QByteArray::AbortOnBase64DecodingErrors);
        auto parsedDiagnosticData   = QByteArray::fromBase64(field3.toUtf8(), QByteArray::AbortOnBase64DecodingErrors);


        // update other diagnostics info
        if(parsedDiagnosticData.isEmpty()) {
            qDebug() << __PRETTY_FUNCTION__ << "cannot parsed diagnostic data";
        } else {
            dataFrame_t dataFrame;
            memcpy(&dataFrame, parsedDiagnosticData.data(), sizeof(dataFrame));

            QMap<DiagnosticData::FieldName, QPair<bool, QVariant>> updatedData;
            updatedData.insert(DiagnosticData::IntakePressure,      {GET_BIT(dataFrame.bank0, 2), dataFrame.intakePressure});
            updatedData.insert(DiagnosticData::FuelPressure,        {GET_BIT(dataFrame.bank0, 3), dataFrame.fuelPressure});
            updatedData.insert(DiagnosticData::FuelInjectTiming,    {GET_BIT(dataFrame.bank0, 4), dataFrame.fuelInjectTiming});
            updatedData.insert(DiagnosticData::IntakeTemperature,   {GET_BIT(dataFrame.bank0, 5), dataFrame.intakeTemp});
            updatedData.insert(DiagnosticData::OilTemperature,      {GET_BIT(dataFrame.bank0, 6), dataFrame.oilTemp});
            updatedData.insert(DiagnosticData::FuelLevel,           {GET_BIT(dataFrame.bank0, 7), dataFrame.fuelLevel});
            updatedData.insert(DiagnosticData::ThrottlePosition,    {GET_BIT(dataFrame.bank1, 0), dataFrame.throttlePosition});
            updatedData.insert(DiagnosticData::Voltage,             {GET_BIT(dataFrame.bank1, 1), dataFrame.voltage / 10.});
            QMetaObject::invokeMethod(m_diagnosticModel, "updateDiagnosticValue", Qt::QueuedConnection, Q_ARG(const DiagnosticMap, updatedData));

            // update speed and rpm
            m_gaugesModel->setKph(dataFrame.speed);
            m_gaugesModel->setRpm(dataFrame.rpm / 100);
        }

        // add new position
        if(parsedCoords.isEmpty()) {
            qDebug() << __PRETTY_FUNCTION__ << "cannot parsed coords data";
        } else {
            gpsFrame_t gpsFrame;
            memcpy(&gpsFrame, parsedCoords.data(), sizeof(gpsFrame_t));
            QMetaObject::invokeMethod(m_mapRoute, "appendPoint", Qt::QueuedConnection, Q_ARG(double, gpsFrame.latitude), Q_ARG(double, gpsFrame.longitude));
        }

        // update error
        if(parsedErrorsData.isEmpty()) {
            qDebug() << __PRETTY_FUNCTION__ << "cannot parsed errors data";
        } else {
            auto errorsCnt = parsedErrorsData.size() / sizeof(errorFrame_t);
            auto error = reinterpret_cast<errorFrame_t*>(parsedErrorsData.data());
            QVector<errorFrame_t> errors(errorsCnt);

            for(auto i = 0; i < errorsCnt; i++) {
                errors[i] = *error++;
            }

            QMetaObject::invokeMethod(m_errorsModel, "updateErrors", Qt::QueuedConnection, Q_ARG(const ErrorsVector, errors));
        }

        // send alert notification
        if(!field4.isEmpty() && m_lastAlertMsg != field4) {
            m_lastAlertMsg = field4;
            QByteArray content = "ThingSpeak alert: " + field4.toUtf8();
            sendMessage(content, 1);
        } else {
            qDebug() << __PRETTY_FUNCTION__ << "no new alert";
        }
    } else {
        qDebug() << __PRETTY_FUNCTION__ << "no new data";
    }
}

/*!
 * \brief WorkerThread::sendMessage - send notification for mobile device
 * \param message
 * \param id
 */
void WorkerThread::sendMessage(const QByteArray &message, int id) const
{
    QVariantMap args;
    args.insert(QStringLiteral("title"), QStringLiteral("Obd View"));
    args.insert(QStringLiteral("caption"), message);
    args.insert(QStringLiteral("id"), id);

    m_mobileNotification->show(QVariant::fromValue(args));
}
