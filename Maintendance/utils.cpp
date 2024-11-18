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
