#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),guardlogin(nullptr),genEmpLogin(nullptr),supervisorLogin(nullptr)
{
    ui->setupUi(this);
    this->setFixedSize(1123,717);
    _showLoginDialog();
}

MainWindow::~MainWindow()
{
    delete guardlogin;
    delete ui;
}

void MainWindow::_showLoginDialog()
{
    LoginDialog loginDialog(this);
    if (loginDialog.exec() == QDialog::Accepted)
    {
        Position pos = loginDialog._getPosition();
        int userID = loginDialog._getUserID();

        switch (pos)
        {
        case Position::guard:
            _setupGuardUI(userID);
            break;
        case Position::normal_employee:
            _setupEmployeeUI(userID);
            break;
        case Position::director:
            _setupDirectorUI(userID);
            break;
        default:
            QMessageBox::critical(this, "Error", "Invalid user role!");
            close();
        }
    }
    else
    {
        close();
    }
}

void MainWindow::_setupGuardUI(int id)
{
    // Show limited functionality for guard role
    // Guards have restricted access to certain features
    // Only basic monitoring and reporting features are available
    //ui->leaveRequestButton->hide();
    //ui->manageEmployeesButton->hide();

    // Show guard-specific widgets

    guardlogin = new GuardLogin(this);
    connect(guardlogin, &GuardLogin::emitLogout, this, &MainWindow::_handleEmitLogout);
    guardlogin->show();


}

void MainWindow::_setupEmployeeUI(int id)
{
    // Show employee functionality
    genEmpLogin = new GeneralEmployeeLogin(this);
    connect(genEmpLogin, &GeneralEmployeeLogin::emitLogout, this, &MainWindow::_handleEmitLogout);
    genEmpLogin->show();


}

void MainWindow::_setupDirectorUI(int id)
{
    // Show all functionality
    supervisorLogin = new SupervisorLogin(this);
    connect(supervisorLogin, &SupervisorLogin::emitLogout, this, &MainWindow::_handleEmitLogout);
    supervisorLogin -> show();
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

    _showLoginDialog();
}
