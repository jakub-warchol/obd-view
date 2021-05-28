#ifndef ERRORDESCRIPTIONPROVIDER_H
#define ERRORDESCRIPTIONPROVIDER_H

#include <QObject>

// forward declaration
class ErrorDescriptionDTCsFileParser;

/*!
 * \brief The ErrorDescriptionProvider class - provides API for parsing OBD II codes
 */
class ErrorDescriptionProvider : public QObject
{
    Q_OBJECT
public:
    explicit ErrorDescriptionProvider(QObject *parent = nullptr);
    QString errorDescription(const char& type, const QString& code);

private:
    ErrorDescriptionDTCsFileParser *m_dtcParser;
};

#endif // ERRORDESCRIPTIONPROVIDER_H
