#include "markattendancescreen.h"
#include "ui_markattendancescreen.h"

MarkAttendanceScreen::MarkAttendanceScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MarkAttendanceScreen),currentGuard(nullptr)
{
    ui->setupUi(this);
    connect(ui->confirmAttendanceButton,&QPushButton::clicked,this,&MarkAttendanceScreen::on_confirmAttendance_clicked);
}

MarkAttendanceScreen::~MarkAttendanceScreen()
{
    delete ui;
}

void MarkAttendanceScreen::setGuard(Guard *guard)
{
    currentGuard = guard;
}

void MarkAttendanceScreen::on_confirmAttendance_clicked()
{
    //currentGuard->_markAttendance();
    this->close();
}

