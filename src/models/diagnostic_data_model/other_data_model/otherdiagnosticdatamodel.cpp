#include "otherdiagnosticdatamodel.h"

OtherDiagnosticDataModel* OtherDiagnosticDataModel::m_instance = nullptr;
OtherDiagnosticDataModel *OtherDiagnosticDataModel::getInstance(QObject *parent)
{
    if(m_instance == nullptr) {
        m_instance = new OtherDiagnosticDataModel(parent);
    }

    return m_instance;
}

/*!
 * \brief OtherDiagnosticDataModel::addDiagnosticData - add new data to model
 * \param iconSrc
 * \param description
 * \param value
 * \param availabled
 * \param fieldName
 */
void OtherDiagnosticDataModel::addDiagnosticData(QString iconSrc, QString description, QVariant value, bool availabled, DiagnosticData::FieldName fieldName)
{
    auto diagnosticData = new DiagnosticData;
    diagnosticData->m_iconSrc       = iconSrc;
    diagnosticData->m_description   = description;
    diagnosticData->m_value         = value;
    diagnosticData->m_fieldName     = fieldName;
    diagnosticData->m_availabled    = availabled;

    m_diagnosticsData.push_back(diagnosticData);
}

/*!
 * \brief OtherDiagnosticDataModel::updateDiagnosticValue - ipdate value for field
 * \param updatedFields
 */
void OtherDiagnosticDataModel::updateDiagnosticValue(const DiagnosticMap updatedFields)
{
    bool modelToSorted  = false;
    bool modelUpdated   = false;

    for(auto diagnosticData : m_diagnosticsData) {

        auto updatedField = updatedFields.value(diagnosticData->m_fieldName);
        if(diagnosticData->m_value != updatedField.second) {
            diagnosticData->m_value = updatedField.second;
            modelUpdated = true;
        }

        if(diagnosticData->m_availabled != updatedField.first) {
            diagnosticData->m_availabled = updatedField.first;
            modelToSorted = true;
            modelUpdated = true;
        }
    }

    if(modelUpdated) {
        emit dataChanged(index(0), index(m_diagnosticsData.size() - 1), {DiagnosticValue});
    }

    if(modelToSorted) {
        sortByAvailabled(); // availability changing requires reset model
    }
}

OtherDiagnosticDataModel::OtherDiagnosticDataModel(QObject *parent) :
    QAbstractListModel(parent)
{
    addDiagnosticData(QStringLiteral("qrc:/icons/icon_car_torque"), QStringLiteral("Intake Pressure"), QStringLiteral("0"), false, DiagnosticData::IntakePressure);
    addDiagnosticData(QStringLiteral("qrc:/icons/icon_car_fuel"), QStringLiteral("Fuel Pressure"), QStringLiteral("0"), false, DiagnosticData::FuelPressure);
    addDiagnosticData(QStringLiteral("qrc:/icons/icon_car_fuel"), QStringLiteral("Fuel Inject Timing"), QStringLiteral("0"), false, DiagnosticData::FuelInjectTiming);
    addDiagnosticData(QStringLiteral("qrc:/icons/icon_car_thermometer"), QStringLiteral("Intake Temperature"), QStringLiteral("0"), false, DiagnosticData::IntakeTemperature);
    addDiagnosticData(QStringLiteral("qrc:/icons/icon_car_thermometer"), QStringLiteral("Oil Temperature"), QStringLiteral("0"), false, DiagnosticData::OilTemperature);
    addDiagnosticData(QStringLiteral("qrc:/icons/icon_car_fuel"), QStringLiteral("Fuel Level"), QStringLiteral("0"), false, DiagnosticData::FuelLevel);
    addDiagnosticData(QStringLiteral("qrc:/icons/icon_car_throttle"), QStringLiteral("Throttle Position"), QStringLiteral("0"), false, DiagnosticData::ThrottlePosition);
    addDiagnosticData(QStringLiteral("qrc:/icons/icon_car_battery"), QStringLiteral("Voltage"), QStringLiteral("0"), false, DiagnosticData::Voltage);

    sortByAvailabled();

    qRegisterMetaType<DiagnosticMap>();
}

void OtherDiagnosticDataModel::sortByAvailabled()
{
    beginResetModel();

    std::stable_partition(m_diagnosticsData.begin(), m_diagnosticsData.end(), [](DiagnosticData* data) {
        return data->m_availabled;
    });

    endResetModel();
}

int OtherDiagnosticDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_diagnosticsData.size();
}

QVariant OtherDiagnosticDataModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= 0 && index.row() < m_diagnosticsData.size()) {
        switch (role) {
            case DiagnosticIconSource:
                return m_diagnosticsData[index.row()]->m_iconSrc;
            case DiagnosticDescription:
                return m_diagnosticsData[index.row()]->m_description;
            case DiagnosticValue:
                return m_diagnosticsData[index.row()]->m_value;
        case DiagnosticAvailabled:
                return m_diagnosticsData[index.row()]->m_availabled;
            default:
                qDebug("%s: Role not supposed", __PRETTY_FUNCTION__);
                return {};
        }
    }

    qDebug("%s: Index not supposed", __PRETTY_FUNCTION__);
    return {};

}

QHash<int, QByteArray> OtherDiagnosticDataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DiagnosticIconSource]     = "dataIconSrc";
    roles[DiagnosticDescription]    = "dataDsc";
    roles[DiagnosticValue]          = "dataValue";
    roles[DiagnosticAvailabled]     = "availabled";

    return roles;
}
