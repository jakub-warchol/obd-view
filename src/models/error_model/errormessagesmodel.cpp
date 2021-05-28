#include "errormessagesmodel.h"
#include <QDateTime>
#include <QDebug>

#include "error_description/errordescriptionprovider.h"

ErrorMessagesModel *ErrorMessagesModel::m_instance = nullptr;
ErrorMessagesModel *ErrorMessagesModel::getInstance(QObject *parent)
{
    if(m_instance == nullptr) {
        m_instance = new ErrorMessagesModel(parent);
    }

    return m_instance;
}

ErrorMessagesModel::ErrorMessagesModel(QObject *parent) :
    QAbstractListModel(parent),
    m_typeCharacters({'P', 'B', 'U', 'C'})
{
    m_descriptionProvider = new ErrorDescriptionProvider(this);
}

int ErrorMessagesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_errors.size();
}

QVariant ErrorMessagesModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= 0 && index.row() < m_errors.size()) {
        switch (role) {
            case ErrorTime:
                return m_errors[index.row()]->m_time;
            case ErrorCodeNo:
                return m_errors[index.row()]->m_codeNo;
            case ErrorCodeDescription:
                return m_errors[index.row()]->m_codeDescription;
            default:
                qDebug("%s: Role not supposed", __PRETTY_FUNCTION__);
                return {};
        }
    }

    qDebug("%s: Index not supposed", __PRETTY_FUNCTION__);
    return {};
}

bool ErrorMessagesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.row() >= 0 && index.row() < m_errors.size()) {
        switch (role) {
            case ErrorTime:
                m_errors[index.row()]->m_time = value.toString();
                emit dataChanged(index, index, {ErrorTime});

                return true;
            case ErrorCodeNo:
                m_errors[index.row()]->m_codeNo = value.toString();
                emit dataChanged(index, index, {ErrorCodeNo});

                return true;
            case ErrorCodeDescription:
                m_errors[index.row()]->m_codeDescription = value.toString();
                emit dataChanged(index, index, {ErrorCodeDescription});

                return true;
            default:
                qDebug("%s: Role not supposed", __PRETTY_FUNCTION__);
                return false;
        }
    }

    qDebug("%s: Index not supposed", __PRETTY_FUNCTION__);
    return false;
}

QHash<int, QByteArray> ErrorMessagesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ErrorTime]                = "time";
    roles[ErrorCodeNo]              = "codeNo";
    roles[ErrorCodeDescription]     = "codeDsc";

    return roles;
}

/*!
 * \brief ErrorMessagesModel::updateErrors - update errors list
 * \param data
 */
void ErrorMessagesModel::updateErrors(const ErrorsVector data)
{
    auto errorSizeDiff = m_errors.size() - data.size();
    removeLastRows(errorSizeDiff);

    for(auto i = 0; i < data.size(); i++) {
        auto error = data.at(i);

        auto date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QString code = "";
        code += m_typeCharacters[error.m_type];
        code += QString::number(error.m_code);

        auto description = m_descriptionProvider->errorDescription(m_typeCharacters[error.m_code], code);

        if(i < m_errors.size()) {
            updateError(i, date, code, description);
        } else {
            addError(date, code, description);
        }
    }
}

/*!
 * \brief ErrorMessagesModel::addError - add new error entry
 * \param time
 * \param codeNo
 * \param codeDescription
 */
void ErrorMessagesModel::addError(QString time, QString codeNo, QString codeDescription)
{
    beginInsertRows(QModelIndex{}, 0, 0);

    auto error = new ErrorData;
    error->m_time = time;
    error->m_codeNo = codeNo;
    error->m_codeDescription = codeDescription;
    m_errors.push_front(error);

    endInsertRows();

    emit dataChanged(index(0, 0), index(0, 0), {ErrorTime, ErrorCodeNo, ErrorCodeDescription});
}

/*!
 * \brief ErrorMessagesModel::updateError - update error on idx position
 * \param idx
 * \param time
 * \param codeNo
 * \param codeDescription
 */
void ErrorMessagesModel::updateError(int idx, QString time, QString codeNo, QString codeDescription)
{
    m_errors[idx]->m_time             = time;
    m_errors[idx]->m_codeNo           = codeNo;
    m_errors[idx]->m_codeDescription  = codeDescription;

    emit dataChanged(index(idx, 0), index(idx, 0), {ErrorTime, ErrorCodeNo, ErrorCodeDescription});
}

/*!
 * \brief ErrorMessagesModel::removeLastRows - remove last rowsCnt rows
 * \param rowsCnt
 */
void ErrorMessagesModel::removeLastRows(int rowsCnt)
{
    if(rowsCnt > 0) {
        qDebug() << "Remove redundant rows:" << rowsCnt;
        beginRemoveRows(QModelIndex(), m_errors.size() - rowsCnt, m_errors.size());

        for(int i = 0; i < rowsCnt; i++) {
            m_errors.pop_back();
        }

        endRemoveRows();
    }
}
