#include "utils.h"

QString _getPreDir(QString id)
{
    if(id.at(0) == 'e')
        return "emp";
    else if (id.at(0) == 'g')
        return "guard";
    else if (id.at(0) == 's')
        return "supervisor";
    else if (id.at(0) == 'd')
        return "director";
    return "";
}

QString _getDateStr(QDate date)
{
    return date.toString("yyyy/MM/dd");
}


bool _sanitizeInput(QString id)
{
    if (id[0] == 'e' || id[0] == 'g' || id[0] == 's' || id[0] == 'd')
        return true;
    return false;
}

QString _generateApplicationID(QString ID)
{
    QString prefix = ID;

    QString uuidPart = QUuid::createUuid().toString(QUuid::WithoutBraces).left(8);

    QString applicationID = QString("%1_%2").arg(prefix).arg(uuidPart);

    return applicationID;
}
