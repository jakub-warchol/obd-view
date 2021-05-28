#ifndef ERRORDESCRIPTIONDTCSFILEPARSER_H
#define ERRORDESCRIPTIONDTCSFILEPARSER_H

#include <QObject>
#include <QHash>
#include <mutex>

/*!
 * \brief The ErrorDescriptionDTCsFileParser class - reads error description from CSV
 */
class ErrorDescriptionDTCsFileParser : public QObject
{
    Q_OBJECT
public:
    explicit ErrorDescriptionDTCsFileParser(QObject *parent = nullptr);

    QString errorDescription(const QString &code);

private:
    void initCodeContainer();

    std::once_flag m_readFlag;
    QHash<QString, QString> m_obdCodes;
};

#endif // ERRORDESCRIPTIONDTCSFILEPARSER_H
