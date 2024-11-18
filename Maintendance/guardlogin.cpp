#include "guardlogin.h"
#include "ui_guardlogin.h"

GuardLogin::GuardLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GuardLogin), currentGuard(nullptr)
{
    ui->setupUi(this);
    connect(ui->logOutButton, &QPushButton::clicked, this, &GuardLogin::on_logOutButton_clicked);

}

GuardLogin::~GuardLogin()
{

    delete currentGuard;
    currentGuard = nullptr;
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


void GuardLogin::on_viewAttendanceButton_clicked()
{
    if (currentGuard) {
        ViewAttendance *viewAttendance = new ViewAttendance(this);
        viewAttendance->_setGuard(currentGuard);
        viewAttendance->_displayList();
        viewAttendance->exec();
    } else {
        qDebug() << "Error GuardLogin has no currentGuard set";
    }
}


void GuardLogin::on_requestLeaveButton_clicked()
{
    if (currentGuard) {
        LeaveApplicationForm *leaveapplication = new LeaveApplicationForm(this);
        leaveapplication->_setGuard(currentGuard);
        leaveapplication->show();
    } else {
        qDebug() << "Error GuardLogin has no currentGuard set";
    }

}

