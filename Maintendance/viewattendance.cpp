#include "viewattendance.h"
#include "ui_viewattendance.h"

ViewAttendance::ViewAttendance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ViewAttendance)
{
    ui->setupUi(this);


    ui->attendanceList->addItem("hello");
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
    if(!currentGuard)
    {
        qDebug() << "Error: currentGuard is null!";
        return;
    }

    //example
    std::vector<std::string> l1 = currentGuard->_viewAttendance();

    for (std::string str : l1) {
        ui->attendanceList->addItem(QString::fromStdString(str));
    }

}


