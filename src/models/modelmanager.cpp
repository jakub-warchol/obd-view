#include "modelmanager.h"

ModelManager* ModelManager::m_instance = nullptr;
ModelManager *ModelManager::getInstance(QObject *parent)
{
    if(m_instance == nullptr) {
        m_instance = new ModelManager(parent);
    }
    return m_instance;
}

ErrorMessagesModel *ModelManager::errorModel() const
{
    return m_errorModel;
}

OtherDiagnosticDataModel *ModelManager::otherDataModel() const
{
    return m_otherDataModel;
}

GaugesModel *ModelManager::gaugesModel() const
{
    return m_gaugesModel;
}

ModelManager::ModelManager(QObject *parent) : QObject(parent)
{
    m_errorModel        = ErrorMessagesModel::getInstance(this);
    m_otherDataModel    = OtherDiagnosticDataModel::getInstance(this);
    m_gaugesModel       = GaugesModel::getInstance(this);
    qDebug("Models initialized!");
}
