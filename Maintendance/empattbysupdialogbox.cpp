#include "empattbysupdialogbox.h"
#include "ui_empattbysupdialogbox.h"

EmpAttBySupDialogBox::EmpAttBySupDialogBox(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EmpAttBySupDialogBox)
{
    ui->setupUi(this);
}

EmpAttBySupDialogBox::~EmpAttBySupDialogBox()
{
    delete ui;
}

void EmpAttBySupDialogBox::_setSup(Supervisor* sup)
{
    currentSup = sup;
}

void EmpAttBySupDialogBox::on_pushButton_clicked()
{
    QString ID = ui->EmpIDTextEdit->toPlainText();
    Employee * emp = new Employee(ID, "random", Position::normal_employee,{},{});
    ViewAttendance viewAttendance (this);
    viewAttendance._setEmployee(emp);
    viewAttendance. _displayList();
    viewAttendance.exec();

}

