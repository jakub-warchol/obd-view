#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QObject>
#include <QMap>
#include <QDateTime>

/*!
 * \brief The JsonParser class - provides API to parsing JSON
 */
class JsonParser : public QObject
{
    Q_OBJECT
public:
    explicit JsonParser(QByteArray jsonContent, QObject *parent = nullptr);
    ~JsonParser() override;

    bool receivedNewData() const;
    QVariant value(const QString &key) const;
    QDateTime lastEntryDate() const;

private:
    static QDateTime m_lastEntry;

    void toMap();

    QByteArray m_jsonContent;
    QMap<QString, QVariant> m_jsonFields;
    QDateTime m_entry;

};

#endif // JSONPARSER_H
