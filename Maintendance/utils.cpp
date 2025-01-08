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
    QVector<QString> eids = _fetchEIDs();
    return eids.contains(id);
}

QString _generateApplicationID(QString ID)
{
    QString prefix = ID;

    QString uuidPart = QUuid::createUuid().toString(QUuid::WithoutBraces).left(8);

    QString applicationID = QString("%1_%2").arg(prefix).arg(uuidPart);

    return applicationID;
}

    LeaveRecord _getRecord(QString AID)
    {
        LeaveRecord record;


        QString baseDir = QCoreApplication::applicationDirPath();
        QDir dir(baseDir);
        dir.cd("../../..");

        QString ID = AID.split('_').first();
        QString Folder = FolderSelection(ID);


        QString filePath = dir.absoluteFilePath(
            QString("records/%1/%2/%2_leaves.txt").arg(Folder).arg(ID)
            );

        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qWarning() << "Failed to open file:" << filePath;
            return record;  // Return an empty record in case of failure
        }



        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(" - ");

            if (fields.size() == 7 && fields[0] == AID)
            {
                record.ID = fields[0];
                record.leaveType = fields[1];
                record.fromDate = fields[2];
                record.toDate = fields[3];
                record.days = fields[4];
                record.reason = fields[5];
                record.status = fields[6];
                break;
            }
        }

        file.close();
        return record;
    }


QString FolderSelection(QString id)
{
    QString Folder;
    if(id[0]=='g'){
        Folder="guard";
    }
    else if (id[0] == 'e'){
        Folder = "emp";
    }
    else if (id[0]=='d'){
        Folder = "director";
    }
    else {
        Folder = "supervisor";
    }
    return Folder;

}


QString _getPosStr(int type)
{
    if (type == 0)
    {
        return "Casual";
    }
    else if (type == 1)
    {
        return "Earned";
    }
    else if (type == 2)
    {
        return "Official";
    }
    else if (type == 3)
    {
        return "Unpaid";
    }
    else
    {
        return "Unknown"; // In case the type is not valid
    }
}


QString _getDayStr(int dayOfWeek) {
    if (dayOfWeek == 1) {
        return "Monday";
    } else if (dayOfWeek == 2) {
        return "Tuesday";
    } else if (dayOfWeek == 3) {
        return "Wednesday";
    } else if (dayOfWeek == 4) {
        return "Thursday";
    } else if (dayOfWeek == 5) {
        return "Friday";
    } else if (dayOfWeek == 6) {
        return "Saturday";
    } else if (dayOfWeek == 7) {
        return "Sunday";
    }
    return "";
}


QVector<QString> _fetchEIDs()
{
    // Vector to hold employee IDs starting with 'e' or 'g'
    QVector<QString> employeeIDs;

    // Get the path to the users.txt file
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    QString filePath = dir.absoluteFilePath("records/users.txt");

    QFile file(filePath);
    // If the file doesn't open, return an empty vector
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open users.txt for fetching EIDs for display:" << filePath;
        return {};
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        // Split the line at the '-' character to separate ID and password
        QStringList parts = line.split('-');
        if (parts.size() == 2) {
            QString id = parts[0];  // Get the ID part
            // Only append IDs that start with 'e' or 'g'
            if (id.startsWith('e') || id.startsWith('g')) {
                employeeIDs.append(id);
            }
        }
    }

    file.close();

    return employeeIDs;
}
