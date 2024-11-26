#include "supervisorlogin.h"
#include "ui_supervisorlogin.h"

SupervisorLogin::SupervisorLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SupervisorLogin)
{
    ui->setupUi(this);

    connect(ui->logOutButton, &QPushButton::clicked, this, &SupervisorLogin::on_logOutButton_clicked);
}

SupervisorLogin::~SupervisorLogin()
{
    delete ui;
}

void SupervisorLogin::_setCurrentSup(Supervisor* sup)
{
    currentSup = sup;
}

void SupervisorLogin::on_logOutButton_clicked()
{
    emit emitLogout();
}


void SupervisorLogin::on_viewAttendanceButton_clicked()
{

    if (currentSup) {
        ViewAttendance viewAttendance (this);
        viewAttendance._setSup(currentSup);
        viewAttendance._displayList();
        viewAttendance.exec();
    } else {
        qDebug() << "Error SupervisorLogin has no supervisor set";
    }


}


void SupervisorLogin::on_viewEmployeeAttendanceButton_clicked()
{

    EmpAttBySupDialogBox  empAttDialog (this);
    empAttDialog.exec();

}


void SupervisorLogin::on_approveRejectLeaveButton_clicked()
{
    PendingLeavesTable leavesTable (this);
    leavesTable._setSup(currentSup);
    leavesTable._displayList();
    leavesTable.exec();
}

