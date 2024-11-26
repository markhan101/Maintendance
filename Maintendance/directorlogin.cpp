#include "directorlogin.h"
#include "ui_directorlogin.h"

DirectorLogin::DirectorLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DirectorLogin)
{
    ui->setupUi(this);
    connect(ui->Logout, &QPushButton::clicked, this, &DirectorLogin::on_Logout_clicked);
}

DirectorLogin::~DirectorLogin()
{
    delete ui;
}

void DirectorLogin::_setDirector(Director * dir)
{
    currentDir = dir;
}


void DirectorLogin::on_Logout_clicked()
{
    emit emitLogout();
}


void DirectorLogin::on_viewEmpAttButton_clicked()
{
    EmpAttBySupDialogBox  empAttDialog (this);
    empAttDialog.exec();

}


void DirectorLogin::on_approveRejectButton_clicked()
{
    PendingLeavesTable leavesTable(this);
    leavesTable._setDir(currentDir);
    leavesTable._displayList();
    leavesTable.exec();


}

