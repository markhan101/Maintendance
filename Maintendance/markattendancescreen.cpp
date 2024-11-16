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

void MarkAttendanceScreen::setGuard(Guard *guard)
{
    currentGuard = guard;
}

//void MarkAttendanceScreen::on_confirmAttendance_clicked()
/*
    QString id = ui->attendanceIDTextBox->toPlainText();
    //covert Qstring to normal string
    //unorder set. add and before if it is already present
    std::string id_str = id.toStdString();



    //std::cout<<id<<std::endl;
    
    currentGuard->_markAttendance(id_str,8);
    this->close();
*/


void MarkAttendanceScreen::on_confirmAttendanceButton_clicked()
{
    QString id = ui->attendanceIDTextBox->toPlainText();
    //covert Qstring to normal string
    //unorder set. add and before if it is already present
    std::string id_str = id.toStdString();

    bool ispresent = true;



    //std::cout<<id<<std::endl;

    currentGuard->_markAttendance(id_str, ispresent , 8);
    this->close();
}


void MarkAttendanceScreen::on_MarkAbsent_clicked()
{
    //absent wala
    QString id = ui->attendanceIDTextBox->toPlainText();
    //covert Qstring to normal string
    //unorder set. add and before if it is already present
    std::string id_str = id.toStdString();

    bool ispresent = false;



    //std::cout<<id<<std::endl;

    currentGuard->_markAttendance(id_str, ispresent , 0);
    this->close();
}

