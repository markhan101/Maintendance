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


/*void ViewAttendance::_displayList()
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
*/

void ViewAttendance::_displayList()
{
    AttendanceLog* log;
    Position pos = _getUserPos();

    // Retrieve the attendance log based on the user's position
    if(pos == guard)
        log = currentGuard->_viewAttendance();
    else
        log = currentEmp->_viewAttendance();

    std::vector<AttendanceEntry>& entries = log->_getEntries();


    ui->attendanceTable->clearContents();
    ui->attendanceTable->setRowCount(0);


    ui->attendanceTable->setRowCount(entries.size());


    for (size_t row = 0; row < entries.size(); ++row)
    {
        const auto& entry = entries[row];


        QTableWidgetItem* dateItem = new QTableWidgetItem(entry._getDate());
        dateItem->setFlags(dateItem->flags() & ~Qt::ItemIsEditable);
        dateItem->setTextAlignment(Qt::AlignCenter);
        ui->attendanceTable->setItem(row, 0, dateItem);


        QTableWidgetItem* dayItem = new QTableWidgetItem(entry._getDay());
        dayItem->setFlags(dayItem->flags() & ~Qt::ItemIsEditable);
        dayItem->setTextAlignment(Qt::AlignCenter);
        ui->attendanceTable->setItem(row, 1, dayItem);


        QTableWidgetItem* hoursItem = new QTableWidgetItem(QString::number(entry._getHours()));
        hoursItem->setFlags(hoursItem->flags() & ~Qt::ItemIsEditable);
        hoursItem->setTextAlignment(Qt::AlignCenter);
        ui->attendanceTable->setItem(row, 2, hoursItem);


        QTableWidgetItem* presentItem = new QTableWidgetItem(entry._isPresent() ? "Yes" : "No");
        presentItem->setFlags(presentItem->flags() & ~Qt::ItemIsEditable);
        ui->attendanceTable->setItem(row, 3, presentItem);
        if (entry._isPresent())
        {
            presentItem->setForeground(QBrush(Qt::green));  // Set text color to green for "Yes"
        } else
        {
            presentItem->setForeground(QBrush(Qt::red));    // Set text color to red for "No"
        }
        presentItem->setTextAlignment(Qt::AlignCenter);
    }


    ui->attendanceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->attendanceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}




