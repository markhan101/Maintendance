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
    Employee* emp = new Employee(ID, "Employee", Position::normal_employee, attLog, leaveBalance);
    
    // Display attendance using existing ViewAttendance dialog
    ViewAttendance viewAttendance(this);
    viewAttendance._setEmployee(emp);
    viewAttendance._displayList();
    viewAttendance.exec();
    
    delete emp;

}

void EmpAttBySupDialogBox::displayAllEmployeeAttendance() {
    // Create table to display results
    QTableWidget* table = new QTableWidget(this);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"Employee ID", "Monthly %", "Weekly %"});
    
    // Get all employee IDs (e1, e2, e3, etc.)
    QStringList employeeIds;
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");
    QDir empDir(dir.absoluteFilePath("records/emp"));
    
    for (const QString& empFolder : empDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        if (empFolder.startsWith("e")) {
            employeeIds.append(empFolder);
        }
    }
    
    table->setRowCount(employeeIds.size());
    
   
    int row = 0;
    for (const QString& empId : employeeIds) {
        
        AttendanceLog* attLog = new AttendanceLog();
        LeaveBalance* leaveBalance = new LeaveBalance(empId);
        Employee* emp = new Employee(empId, "Employee", Position::normal_employee, attLog, leaveBalance);
        
       
        AttendanceLog* log = emp->_viewAttendance();
        QDate currentDate = QDate::currentDate();
        
        
        double monthlyPercent = log->_getMonthlyAttendancePercentage(currentDate);
        double weeklyPercent = log->_getWeeklyAttendancePercentage(currentDate);
        
        
        table->setItem(row, 0, new QTableWidgetItem(empId));
        table->setItem(row, 1, new QTableWidgetItem(QString::number(monthlyPercent, 'f', 2) + "%"));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(weeklyPercent, 'f', 2) + "%"));
        
        
        delete emp;
        row++;
    }
    
    
    table->setGeometry(30, 90, 440, 300);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->show();
}

