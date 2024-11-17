#include "markattendancescreen.h"
#include "ui_markattendancescreen.h"
#include<iostream>

MarkAttendanceScreen::MarkAttendanceScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MarkAttendanceScreen),currentGuard(nullptr)
{
    ui->setupUi(this);
   // connect(ui->confirmAttendanceButton,&QPushButton::clicked,this,&MarkAttendanceScreen::on_confirmAttendance_clicked);
}

MarkAttendanceScreen::~MarkAttendanceScreen()
{
    delete ui;
}

void MarkAttendanceScreen::_setGuard(Guard *guard)
{
    currentGuard = guard;
}

void MarkAttendanceScreen::_howToMark(bool isPresent)
{
    QString id = ui->attendanceIDTextBox->toPlainText();
    std::string id_str = id.toStdString();
    currentGuard->_markAttendance(id_str, isPresent , 8);

}


void MarkAttendanceScreen::on_confirmAttendanceButton_clicked()
{
    _howToMark(true);
    this->close();
}


void MarkAttendanceScreen::on_MarkAbsent_clicked()
{
    _howToMark(false);
    this->close();
}

