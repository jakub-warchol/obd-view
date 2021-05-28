#include "errordescriptiondtcsfileparser.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

ErrorDescriptionDTCsFileParser::ErrorDescriptionDTCsFileParser(QObject *parent) : QObject(parent)
{}

/*!
 * \brief ErrorDescriptionDTCsFileParser::errorDescription - get desccription for code, if exists
 * \param code
 * \return
 */
QString ErrorDescriptionDTCsFileParser::errorDescription(const QString &code)
{
    std::call_once(m_readFlag, std::bind(&ErrorDescriptionDTCsFileParser::initCodeContainer, this));

    auto alignedCode = code.size() > 4 ? code : code[0] + QString::number(0) + code.mid(1);
    return m_obdCodes.value(alignedCode, QStringLiteral("Unknown trouble"));
}

/*!
 * \brief ErrorDescriptionDTCsFileParser::initCodeContainer - parse CSV file
 */
void ErrorDescriptionDTCsFileParser::initCodeContainer()
{
    QFile file{QStringLiteral(":/resources/files/obd2_codes.csv")};
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream in{&file};
        while(!in.atEnd()) {
            auto line = in.readLine();
            if(line.startsWith(QStringLiteral("#")) || line.startsWith(QStringLiteral("\n")) || line.isEmpty()) {
                continue;
            }

            auto splittedLine = line.split(QStringLiteral(","));
            m_obdCodes.insert(splittedLine[0], splittedLine[1]);
        }

        qDebug() << __PRETTY_FUNCTION__ << "error description initialized";
    } else {
        qDebug() << __PRETTY_FUNCTION__ << "cannot open csv file" << file.fileName();
    }
}
