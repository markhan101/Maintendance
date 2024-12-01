#include "viewattendance.h"
#include "ui_viewattendance.h"

ViewAttendance::ViewAttendance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ViewAttendance), currentGuard(nullptr), currentEmp(nullptr), currentSup(nullptr)
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

void ViewAttendance::_setSup(Supervisor* sup)
{
    currentSup = sup;
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
    else
        return Position::supervisor;

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
    else if(pos == normal_employee)
        log = currentEmp->_viewAttendance();
    else
        log = currentSup->_viewAttendance();


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


        QTableWidgetItem* presentItem = new QTableWidgetItem();
        QString status = entry._isPresent();  // Assuming getAttendanceStatus() returns a QString like "1", "0", "UL", "EL", "CL", "OL"
        presentItem->setFlags(presentItem->flags() & ~Qt::ItemIsEditable);
        ui->attendanceTable->setItem(row, 3, presentItem);

        if (status == "1") {
            presentItem->setText("Yes");
            presentItem->setForeground(QBrush(Qt::green));  // Set text color to green for "Yes"
        } else if (status == "0") {
            presentItem->setText("No");
            presentItem->setForeground(QBrush(Qt::red));  // Set text color to red for "No"
        } else if (status == "UL") {
            presentItem->setText("UL");
            presentItem->setForeground(QBrush(Qt::blue));  // Set text color to blue for "UL"
        } else if (status == "EL") {
            presentItem->setText("EL");
            presentItem->setForeground(QBrush(Qt::yellow));  // Set text color to yellow for "EL"
        } else if (status == "CL") {
            presentItem->setText("CL");
            presentItem->setForeground(QBrush(Qt::magenta));  // Set text color to magenta for "CL"
        } else if (status == "OL") {
            presentItem->setText("OL");
            presentItem->setForeground(QBrush(Qt::cyan));  // Set text color to cyan for "OL"
        }

        presentItem->setTextAlignment(Qt::AlignCenter);
    }


    ui->attendanceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->attendanceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}





void ViewAttendance::on_goBackButton_clicked()
{
    this->reject();
}

