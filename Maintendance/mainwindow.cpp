#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),guardlogin(nullptr)
{
    ui->setupUi(this);
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
            _setupEmployeeUI();
            break;
        case Position::director:
            _setupDirectorUI();
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

void MainWindow::_setupGuardUI(int userID)
{
    // Show limited functionality for guard role
    // Guards have restricted access to certain features
    // Only basic monitoring and reporting features are available
    //ui->leaveRequestButton->hide();
    //ui->manageEmployeesButton->hide();

    // Show guard-specific widgets

    guardlogin = new GuardLogin(this);
    guardlogin->show();


}

void MainWindow::_setupEmployeeUI()
{
    // Show employee functionality

}

void MainWindow::_setupDirectorUI()
{
    // Show all functionality

}
