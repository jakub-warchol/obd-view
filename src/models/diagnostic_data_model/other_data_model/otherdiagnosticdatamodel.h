#ifndef OTHERDIAGNOSTICDATAMODEL_H
#define OTHERDIAGNOSTICDATAMODEL_H

#include <QAbstractListModel>

struct DiagnosticData {
    enum FieldName {
        Unknown = -1,
        IntakePressure,
        FuelPressure,
        FuelInjectTiming,
        IntakeTemperature,
        OilTemperature,
        FuelLevel,
        ThrottlePosition,
        Voltage
    };

    QString m_iconSrc;
    QString m_description;
    QVariant m_value;
    FieldName m_fieldName;
    bool m_availabled;
};

using DiagnosticMap = QMap<DiagnosticData::FieldName, QPair<bool, QVariant>>;
Q_DECLARE_METATYPE(DiagnosticMap)

/*!
 * \brief The OtherDiagnosticDataModel class - provides model for Diagnostic Data
 */
class OtherDiagnosticDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        DiagnosticIconSource = Qt::UserRole + 1,
        DiagnosticDescription,
        DiagnosticValue,
        DiagnosticAvailabled
    };
    Q_ENUM(Roles)

    static OtherDiagnosticDataModel* getInstance(QObject *parent = nullptr);

    void addDiagnosticData(QString iconSrc, QString description, QVariant value, bool availabled = false, DiagnosticData::FieldName fieldName = DiagnosticData::Unknown);

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    void updateDiagnosticValue(const DiagnosticMap updatedFields);

private:
    explicit OtherDiagnosticDataModel(QObject *parent = nullptr);
    void sortByAvailabled();

    static OtherDiagnosticDataModel *m_instance;
    QList<DiagnosticData*> m_diagnosticsData;

};

#endif // OTHERDIAGNOSTICDATAMODEL_H
