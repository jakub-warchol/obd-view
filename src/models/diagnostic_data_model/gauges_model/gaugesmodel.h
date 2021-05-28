#ifndef GAUGESMODEL_H
#define GAUGESMODEL_H

#include <QObject>

/*!
 * \brief The GaugesModel class - provides model for Gauges
 */
class GaugesModel : public QObject
{
    Q_OBJECT

    // velocity
    Q_PROPERTY(int kph READ kph WRITE setKph NOTIFY kphChanged)

    // rpm
    Q_PROPERTY(int rpm READ rpm WRITE setRpm NOTIFY rpmChanged)

public:
    static GaugesModel* getInstance(QObject *parent = nullptr);

    int kph() const;
    int rpm() const;

public slots:
    void setKph(int kph);
    void setRpm(int rpm);

signals:
    void kphChanged(int kph);
    void rpmChanged(int rpm);

private:
    explicit GaugesModel(QObject *parent = nullptr);

    static GaugesModel *m_instance;

    int m_kph;
    int m_rpm;
};

#endif // GAUGESMODEL_H
