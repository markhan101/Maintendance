#include "viewattendance.h"
#include "ui_viewattendance.h"

ViewAttendance::ViewAttendance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ViewAttendance), currentGuard(nullptr), currentEmp(nullptr)
{
    ui->setupUi(this);
}

ViewAttendance::~ViewAttendance()
{
    delete currentGuard;
    currentGuard = nullptr;
    delete currentEmp;
    currentEmp = nullptr;
    delete ui;
}

void ViewAttendance::_setGuard(Guard *guard)
{
   currentGuard = guard;
}

void ViewAttendance::_setEmployee(Employee* emp)
{
    currentEmp = emp;
}

Position ViewAttendance::_getUserPos()
{
    if(currentGuard)
    { qDebug() << currentGuard->_get_uID();
        return Position::guard;
    }
    else if (currentEmp)
    { qDebug()<< currentEmp->_get_uID();
        return Position::normal_employee;
    }

}


void ViewAttendance::_displayList()
{

    AttendanceLog* log;
    // for now add supervisor and director once those classes have been made
    Position pos = _getUserPos();
    if(pos == guard)
        log = currentGuard->_viewAttendance();
    else
        log = currentEmp->_viewAttendance();

    std::vector<AttendanceEntry>& entries = log->_getEntries();
    
    for (const auto& entry : entries) {
        QString displayStr = QString("%1 | Present: %2 | Hours: %3")
            .arg(entry._getDate())
            .arg(entry._isPresent() ? "Yes" : "No")
            .arg(entry._getHours());
            
        ui->attendanceList->addItem(displayStr);
    }
}


