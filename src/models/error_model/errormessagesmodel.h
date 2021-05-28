#ifndef ERRORMESSAGESMODEL_H
#define ERRORMESSAGESMODEL_H

#include <QAbstractListModel>
#include <array>
#include "src/worker/data_structs/error_data.h"

struct ErrorData {
    QString m_time;
    QString m_codeNo;
    QString m_codeDescription;
};

using ErrorsVector = QVector<errorFrame_t>;
Q_DECLARE_METATYPE(ErrorsVector)

// forward declaration
class ErrorDescriptionProvider;

/*!
 * \brief The ErrorMessagesModel class - provides model to diagnostic errors
 */
class ErrorMessagesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        ErrorTime = Qt::UserRole + 1,
        ErrorCodeNo,
        ErrorCodeDescription
    };
    Q_ENUM(Roles)

    static ErrorMessagesModel* getInstance(QObject *parent = nullptr);

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    void updateErrors(const ErrorsVector data);

private:
    explicit ErrorMessagesModel(QObject *parent = nullptr);
    void addError(QString time, QString codeNo, QString codeDescription);
    void updateError(int idx, QString time, QString codeNo, QString codeDescription);
    void removeLastRows(int rowsCnt);

    static ErrorMessagesModel* m_instance;
    QList<ErrorData*> m_errors;
    std::array<const char, 4> m_typeCharacters;
    ErrorDescriptionProvider *m_descriptionProvider;
};

#endif // ERRORMESSAGESMODEL_H
