#include "errordescriptionprovider.h"
#include "errordescriptiondtcsfileparser.h"

ErrorDescriptionProvider::ErrorDescriptionProvider(QObject *parent) : QObject(parent)
{
    m_dtcParser = new ErrorDescriptionDTCsFileParser(this);
}

/*!
 * \brief ErrorDescriptionProvider::errorDescription - get error description
 * \param type
 * \param code
 * \return
 */
QString ErrorDescriptionProvider::errorDescription(const char &type, const QString &code)
{
    switch (type) {
    case 'B':
        return QStringLiteral("Base trouble");
    case 'C':
        return QStringLiteral("Chassis trouble");
    default:
        return m_dtcParser->errorDescription(code);
    }
}
