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
    currentDir = nullptr;  // Ensure no Director is set when Supervisor is logged in
    _toggleButtons();
}

void SupervisorLogin::_setCurrentDir(Director * dir)
{
    currentDir  = dir;
    currentSup = nullptr;  // Ensure no Supervisor is set when Director is logged in
    _toggleButtons();
}

void SupervisorLogin::_toggleButtons() {
    // Hide buttons if a Director is logged in, otherwise show them
    bool isDirector = currentDir != nullptr;

    ui->viewAttendanceButton->setVisible(!isDirector);
    ui->viewAbsenteeRecordsButton->setVisible(!isDirector);
    ui->viewLeaveDetailsButton->setVisible(!isDirector);

}

void SupervisorLogin::on_logOutButton_clicked()
{
    emit emitLogout();
}

void SupervisorLogin::on_viewAttendanceButton_clicked()
{
    if (currentSup) {
        ViewAttendance viewAttendance(this);
        viewAttendance._setSup(currentSup);
        viewAttendance._displayList();
        viewAttendance.exec();
    }
    else {
        qDebug() << "Error SupervisorLogin has no supervisor set";
    }
}

void SupervisorLogin::on_viewEmployeeAttendanceButton_clicked()
{
    EmpAttBySupDialogBox empAttDialog(this);
    empAttDialog._setSup(currentSup);
    empAttDialog.exec();
}

void SupervisorLogin::on_approveRejectLeaveButton_clicked()
{

    PendingLeavesTable leavesTable(this);
    if(currentDir)
    {
        leavesTable._setDir(currentDir);
        qDebug() << "Director set for pending leaves table";
    }
    else
    {
        leavesTable._setSup(currentSup);
        qDebug() << "Supervisor set for pending leaves table";
    }
    leavesTable._displayList();
    leavesTable.exec();
}
