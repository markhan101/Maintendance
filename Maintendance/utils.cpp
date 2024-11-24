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
