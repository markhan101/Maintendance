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

