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

void EmpAttBySupDialogBox::on_viewButton_clicked()
{
 QString ID = ui->EmpIDTextEdit->toPlainText();
    
    if (ID.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter an Employee ID");
        return;
    }
    
    if (!_sanitizeInput(ID)) {
        QMessageBox::warning(this, "Wrong ID", "Please make sure the correct ID is entered.");
        return;
    }

    // Create employee object to view attendance
    AttendanceLog* attLog = new AttendanceLog();
    LeaveBalance* leaveBalance = new LeaveBalance(ID);
    Employee* emp = new Employee(ID, Position::normal_employee, attLog, leaveBalance);
    
    // Display attendance using existing ViewAttendance dialog
    ViewAttendance viewAttendance(this);
    viewAttendance._setEmployee(emp);
    viewAttendance._displayList();
    viewAttendance.exec();
    
    delete emp;

}


