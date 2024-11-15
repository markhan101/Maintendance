#include "guardlogin.h"
#include "ui_guardlogin.h"

GuardLogin::GuardLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GuardLogin), markAttendance(nullptr), currentGuard(nullptr)
{
    ui->setupUi(this);
    connect(ui->logOutButton, &QPushButton::clicked, this, &GuardLogin::on_logOutButton_clicked);

}

GuardLogin::~GuardLogin()
{
    delete ui;
}

void GuardLogin::setCurrentGuard(Guard *guard)
{
    currentGuard = guard;
}

void GuardLogin::on_markAttendanceButton_clicked()
{
    MarkAttendanceScreen attendanceDialog(this);

    if (attendanceDialog.exec() == QDialog::Accepted) {
        qDebug() << "Attendance marked successfully!";
    }
}


void GuardLogin::on_logOutButton_clicked()
{
    emit emitLogout();
}

