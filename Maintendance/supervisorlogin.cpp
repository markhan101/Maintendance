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

void SupervisorLogin::on_logOutButton_clicked()
{
    emit emitLogout();
}


void SupervisorLogin::on_viewAttendanceButton_clicked()
{

}

