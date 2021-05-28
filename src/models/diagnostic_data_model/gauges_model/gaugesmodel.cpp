#include "gaugesmodel.h"

GaugesModel* GaugesModel::m_instance = nullptr;
GaugesModel *GaugesModel::getInstance(QObject *parent)
{
    if(m_instance == nullptr) {
        m_instance = new GaugesModel(parent);
    }

    return m_instance;
}

GaugesModel::GaugesModel(QObject *parent) :
    QObject(parent),
    m_kph(0),
    m_rpm(0)
{}

int GaugesModel::kph() const
{
    return m_kph;
}

int GaugesModel::rpm() const
{
    return m_rpm;
}

void GaugesModel::setKph(int kph)
{
    if (m_kph == kph)
        return;

    m_kph = kph;
    emit kphChanged(m_kph);
}

void GaugesModel::setRpm(int rpm)
{
    if (m_rpm == rpm)
        return;

    m_rpm = rpm;
    emit rpmChanged(m_rpm);
}
