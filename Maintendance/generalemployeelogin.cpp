#include "generalemployeelogin.h"
#include "ui_generalemployeelogin.h"

GeneralEmployeeLogin::GeneralEmployeeLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GeneralEmployeeLogin)
{
    ui->setupUi(this);
    connect(ui->logoutButton, &QPushButton::clicked,this,&GeneralEmployeeLogin::on_logoutButton_clicked);
}

GeneralEmployeeLogin::~GeneralEmployeeLogin()
{
    delete ui;
}

void GeneralEmployeeLogin::on_logoutButton_clicked()
{
    emit emitLogout();
}

void GeneralEmployeeLogin::_setEmployee(Employee* emp)
{
    generalEmp = emp;
}


void GeneralEmployeeLogin::on_viewAttendanceButton_clicked()
{
    if (generalEmp) {
        ViewAttendance viewAttendance (this);
        viewAttendance._setEmployee(generalEmp);
        viewAttendance._displayList();
        viewAttendance.exec();
    } else {
        qDebug() << "Error GuardLogin has no currentGuard set";
    }

}

void GeneralEmployeeLogin::on_viewLeaveBalanceButton_clicked()
{
    if (generalEmp)
    {
        LeaveBalance* leaveBalance = generalEmp->getLeaveBalance();
        
        int casualLeaves = leaveBalance->_getLeaveBalance(LeaveTypes::Casual);
       
        qDebug()<< casualLeaves;
    }
    else
    {
        qDebug() << "Error: generalEmp is nullptr";
    }
}

void GeneralEmployeeLogin::on_requestLeaveButton_clicked()
{
    if (generalEmp) {
        LeaveApplicationForm *leaveapplication = new LeaveApplicationForm(this);
        leaveapplication->_setEmployee(generalEmp);
        leaveapplication->show();
    } else {
        qDebug() << "Error: GeneralEmployeeLogin has no employee set";
    }
}
