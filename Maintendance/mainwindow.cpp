#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showLoginDialog();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLoginDialog()
{
    LoginDialog loginDialog(this);
    if (loginDialog.exec() == QDialog::Accepted)
    {
        Position pos = loginDialog.getPosition();
        int userID = loginDialog.getUserID();

        switch (pos)
        {
        case Position::guard:
            setupGuardUI();
            break;
        case Position::normal_employee:
            setupEmployeeUI();
            break;
        case Position::director:
            setupDirectorUI();
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

void MainWindow::setupGuardUI()
{
    // Show limited functionality for guard role
    // Guards have restricted access to certain features
    // Only basic monitoring and reporting features are available
    ui->leaveRequestButton->hide();
    ui->manageEmployeesButton->hide();
    // Show guard-specific widgets
    ui->loademployees->show();
    connect(ui->manageEmployeesButton,  &QPushButton::clicked, [=]() {
        _loadGuardAttendanceUI(userID));
}

void MainWindow::setupEmployeeUI()
{
    // Show employee functionality
    ui->manageEmployeesButton->hide();
    ui->leaveRequestButton->show();
}

void MainWindow::setupDirectorUI()
{
    // Show all functionality
    ui->leaveRequestButton->show();
    ui->manageEmployeesButton->show();
}
