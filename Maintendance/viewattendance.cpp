#include "viewattendance.h"
#include "ui_viewattendance.h"

ViewAttendance::ViewAttendance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ViewAttendance)
{
    ui->setupUi(this);
}

ViewAttendance::~ViewAttendance()
{
    delete ui;
}

void ViewAttendance::setGuard(Guard *guard)
{
   currentGuard = guard;
}

void ViewAttendance::displayList()
{
    if(!currentGuard) {
        qDebug() << "Error: currentGuard is null!";
        return;
    }

    qDebug() << currentGuard->_get_uID();
    AttendanceLog* log = currentGuard->_viewAttendance();
    std::vector<AttendanceEntry>& entries = log->_getEntries();
    
    for (const auto& entry : entries) {
        QString displayStr = QString("%1 | Present: %2 | Hours: %3")
            .arg(entry._getDate())
            .arg(entry._isPresent() ? "Yes" : "No")
            .arg(entry._getHours());
            
        ui->attendanceList->addItem(displayStr);
    }
}


