#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QObject>

// models
#include "src/models/error_model/errormessagesmodel.h"
#include "src/models/diagnostic_data_model/other_data_model/otherdiagnosticdatamodel.h"
#include "src/models/diagnostic_data_model/gauges_model/gaugesmodel.h"

/*!
 * \brief The ModelManager class - provides interface to manage models from C++ and QML
 */
class ModelManager : public QObject
{
    Q_OBJECT

    // models
    Q_PROPERTY(ErrorMessagesModel* errorModel READ errorModel NOTIFY errorModelChanged)
    Q_PROPERTY(OtherDiagnosticDataModel* otherDataModel READ otherDataModel NOTIFY otherDataModelChanged)
    Q_PROPERTY(GaugesModel* gaugesModel READ gaugesModel NOTIFY gaugesModelChanged)

public:
    static ModelManager* getInstance(QObject *parent = nullptr);

    ErrorMessagesModel* errorModel() const;
    OtherDiagnosticDataModel* otherDataModel() const;
    GaugesModel* gaugesModel() const;

signals:
    void errorModelChanged(ErrorMessagesModel* errorModel);
    void otherDataModelChanged(OtherDiagnosticDataModel* otherDataModel);
    void gaugesModelChanged(GaugesModel* gaugesModel);

private:
    explicit ModelManager(QObject *parent = nullptr);

    static ModelManager *m_instance;

    //model instances
    ErrorMessagesModel* m_errorModel;
    OtherDiagnosticDataModel* m_otherDataModel;
    GaugesModel* m_gaugesModel;
};

#endif // MODELMANAGER_H
