#include "shortattendancetable.h"
#include "ui_shortattendancetable.h"

ShortAttendanceTable::ShortAttendanceTable(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShortAttendanceTable)
{
    ui->setupUi(this);
}

ShortAttendanceTable::~ShortAttendanceTable()
{
    delete ui;
}

void ShortAttendanceTable::_setSup(Supervisor* sup)
{
    currentSup = sup;
}


void ShortAttendanceTable::_populateTable() {
    // Create vectors of pointers instead of objects
    QVector<Employee*> emps;
    QVector<Guard*> guards;
    QVector<QString> eIDs = currentSup->_fetchEIDs();

    for (const QString &id : eIDs) {
        // Create AttendanceLog and LeaveBalance for each Employee/Guard
        AttendanceLog* attLog = new AttendanceLog();
        LeaveBalance* leaveBalance = new LeaveBalance(id);

        if (id.startsWith('g')) {
            // Create and store Guard pointer
            Guard* newGuard = new Guard(id, Position::guard, attLog, leaveBalance);
            guards.append(newGuard);
            emps.append(newGuard);  // Guards are also employees
        } else {
            // Create and store Employee pointer
            Employee* emp = new Employee(id, Position::normal_employee, attLog, leaveBalance);
            emps.append(emp);
        }
    }

    // Update table
    ui->shortLeaveTable->clearContents();
    ui->shortLeaveTable->setRowCount(emps.size());

    for (int row = 0; row < emps.size(); ++row) {
        Employee* emp = emps[row];
        AttendanceLog* log = emp->_viewAttendance();  // Use -> instead of . for pointers
        QDate currentDate = QDate::currentDate();

        double monthlyPercent = log->_getMonthlyAttendancePercentage(currentDate);
        double weeklyPercent = log->_getWeeklyAttendancePercentage(currentDate);

        // Create table items
        QTableWidgetItem* idItem = new QTableWidgetItem(emp->_get_uID());
        idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
        idItem->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem* monthlyItem = new QTableWidgetItem(QString::number(monthlyPercent, 'f', 2));
        monthlyItem->setFlags(monthlyItem->flags() & ~Qt::ItemIsEditable);
        monthlyItem->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem* weeklyItem = new QTableWidgetItem(QString::number(weeklyPercent, 'f', 2));
        weeklyItem->setFlags(weeklyItem->flags() & ~Qt::ItemIsEditable);
        weeklyItem->setTextAlignment(Qt::AlignCenter);

        // Apply formatting
        if (monthlyPercent < 80.0) {
            monthlyItem->setBackground(Qt::red);
        }
        if (weeklyPercent < 80.0) {
            weeklyItem->setBackground(Qt::red);
        }

        // Set items in table
        ui->shortLeaveTable->setItem(row, 0, idItem);
        ui->shortLeaveTable->setItem(row, 1, monthlyItem);
        ui->shortLeaveTable->setItem(row, 2, weeklyItem);
    }

    // Cleanup
    qDeleteAll(emps);  // This will delete both regular employees and guards

    // Table formatting
    ui->shortLeaveTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->shortLeaveTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}






