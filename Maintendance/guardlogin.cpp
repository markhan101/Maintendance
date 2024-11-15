#include "guardlogin.h"
#include "ui_guardlogin.h"

GuardLogin::GuardLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GuardLogin), markAttendance(nullptr), currentGuard(nullptr)
{
    ui->setupUi(this);
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
    /*if (!markAttendance) {
        markAttendance = new MarkAttendanceScreen(this);
    }

    if (currentGuard) {
        markAttendance->setGuard(currentGuard);
    }

    markAttendance->show();*/

    // Create the modal dialog
    MarkAttendanceScreen attendanceDialog(this);

    // Show the dialog modally
    if (attendanceDialog.exec() == QDialog::Accepted) {
        // The dialog was closed with "accept()"
        qDebug() << "Attendance marked successfully!";
    }
}
