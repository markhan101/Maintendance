#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),guardlogin(nullptr),genEmpLogin(nullptr),supervisorLogin(nullptr)
{
    ui->setupUi(this);
    this->setFixedSize(900,600);
    _showLoginDialog();
}

MainWindow::~MainWindow()
{
    delete guardlogin;
    delete ui;
}

void MainWindow::_showLoginDialog()
{
    while (true) {  
        LoginDialog loginDialog(this);
        int result = loginDialog.exec();
        
        if (result == QDialog::Accepted) {
            Position pos = loginDialog._getPosition();
            QString userID = loginDialog._getUserID();
            qDebug() << userID;

            switch (pos) {
                case Position::guard:
                    _setupGuardUI(userID);
                    return;  
                case Position::normal_employee:
                    _setupEmployeeUI(userID);
                    return;  
                case Position::supervisor:
                    _setupSupervisorUI(userID);
                    return;
                case Position::director:
                    _setupDirectorUI(userID);//needed to be done
                    return;
                default:
                    QMessageBox::critical(this, "Error", "Invalid user role!");
                   
            }
        } else {
           
            this->close();
            return;   
        }
    }
}

void MainWindow::_setupGuardUI(QString id)
{
    guardlogin = new GuardLogin(this);

    AttendanceLog* attLog = new AttendanceLog();
    LeaveBalance* leaveBalance = new LeaveBalance(id);

    Guard* newGuard = new Guard(id, Position::guard, attLog, leaveBalance);
    guardlogin->setCurrentGuard(newGuard);

    connect(guardlogin, &GuardLogin::emitLogout, this, &MainWindow::_handleEmitLogout);

    guardlogin->show();
}

void MainWindow::_setupEmployeeUI(QString id)
{
    genEmpLogin = new GeneralEmployeeLogin(this);

    AttendanceLog* attLog = new AttendanceLog();
    LeaveBalance* leaveBalance = new LeaveBalance(id);

    Employee* newEmp = new Employee(id, Position::normal_employee, attLog, leaveBalance);
    genEmpLogin->_setEmployee(newEmp);

    connect(genEmpLogin, &GeneralEmployeeLogin::emitLogout, this, &MainWindow::_handleEmitLogout);

    genEmpLogin->show();
}

void MainWindow::_setupSupervisorUI(QString id)
{
    supervisorLogin = new SupervisorLogin(this);

    AttendanceLog* attLog = new AttendanceLog();
    LeaveBalance* leaveBalance = new LeaveBalance(id);

    Supervisor* newSup = new Supervisor(id, Position::supervisor, attLog, leaveBalance);
    supervisorLogin->_setCurrentSup(newSup);

    connect(supervisorLogin, &SupervisorLogin::emitLogout, this, &MainWindow::_handleEmitLogout);

    supervisorLogin->show();
}

void MainWindow::_setupDirectorUI(QString id)
{
    directorLogin = new DirectorLogin(this);

    AttendanceLog* attLog = new AttendanceLog();
    LeaveBalance* leaveBalance = new LeaveBalance(id);

    Director* newDir = new Director(id, Position::director, attLog, leaveBalance);
    directorLogin->_setDirector(newDir);

    //connect(supervisorLogin, &SupervisorLogin::emitLogout, this, &MainWindow::_handleEmitLogout);
    connect(directorLogin, &DirectorLogin::emitLogout, this, &MainWindow::_handleEmitLogout);
    directorLogin->show();

}



void MainWindow::_handleEmitLogout()
{
    if (guardlogin)
    {
        guardlogin->close();
        delete guardlogin;
        guardlogin = nullptr;
    }
    else if(genEmpLogin)
    {
        genEmpLogin->close();
        delete genEmpLogin;
        genEmpLogin = nullptr;
    }
    else if(supervisorLogin)
    {
        supervisorLogin->close();
        delete supervisorLogin;
        supervisorLogin = nullptr;
    }
    else if(directorLogin)
    {
        directorLogin->close();
        delete directorLogin;
        directorLogin = nullptr;
    }

    _showLoginDialog();
}
