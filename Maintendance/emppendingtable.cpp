#include "emppendingtable.h"
#include "ui_emppendingtable.h"

EmpPendingTable::EmpPendingTable(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EmpPendingTable)
{
    ui->setupUi(this);

    // Connect radio buttons to the slot for filtering
    connect(ui->allRadioButton, &QRadioButton::toggled, this, &EmpPendingTable::filterTable);
    connect(ui->pendingRadioButton, &QRadioButton::toggled, this, &EmpPendingTable::filterTable);
    connect(ui->approvedRadioButton, &QRadioButton::toggled, this, &EmpPendingTable::filterTable);
    connect(ui->rejectedRadioButton, &QRadioButton::toggled, this, &EmpPendingTable::filterTable);

    connect(ui->closeButton, &QPushButton::clicked, this, &QDialog::accept);
}

EmpPendingTable::~EmpPendingTable()
{
    delete ui;
}

void EmpPendingTable::_setEmp(Employee * emp)
{
    currentEmp = emp;
}

void EmpPendingTable::_populateTable()
{
    QVector<LeaveRecord> leaveApps = currentEmp->_getAllApplications();

    ui->leaveTable->clearContents();
    ui->leaveTable->setRowCount(leaveApps.size());

    for (int row = 0; row < leaveApps.size(); row++) {
        const LeaveRecord& app = leaveApps[row];

        QTableWidgetItem* appID = new QTableWidgetItem(app.ID);
        appID->setFlags(appID->flags() & ~Qt::ItemIsEditable);
        appID->setTextAlignment(Qt::AlignCenter);
        ui->leaveTable->setItem(row, 0, appID);

        QTableWidgetItem* from = new QTableWidgetItem(app.fromDate);
        from->setFlags(from->flags() & ~Qt::ItemIsEditable);
        from->setTextAlignment(Qt::AlignCenter);
        ui->leaveTable->setItem(row, 1, from);

        QTableWidgetItem* to = new QTableWidgetItem(app.toDate);
        to->setFlags(to->flags() & ~Qt::ItemIsEditable);
        to->setTextAlignment(Qt::AlignCenter);
        ui->leaveTable->setItem(row, 2, to);

        QTableWidgetItem* reasonItem = new QTableWidgetItem(app.reason);
        reasonItem->setFlags(reasonItem->flags() & ~Qt::ItemIsEditable);
        reasonItem->setTextAlignment(Qt::AlignCenter);
        ui->leaveTable->setItem(row, 3, reasonItem);

        QTableWidgetItem* statusItem = new QTableWidgetItem(app.status);
        statusItem->setFlags(statusItem->flags() & ~Qt::ItemIsEditable);
        statusItem->setTextAlignment(Qt::AlignCenter);

        // Set text color based on status
        if (app.status == "Rejected") {
            statusItem->setBackground(QBrush(Qt::red));  // Red for rejected
        } else if (app.status == "Pending") {
            statusItem->setBackground(QBrush(Qt::yellow));  // Yellow for pending
        } else if (app.status == "Approved") {
            statusItem->setBackground(QBrush(Qt::green));  // Green for approved
        }

        ui->leaveTable->setItem(row, 4, statusItem);
    }

    ui->leaveTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

// Slot to filter the table based on the selected status
void EmpPendingTable::filterTable()
{
    // Get the selected filter option
    QString selectedFilter;
    if (ui->pendingRadioButton->isChecked()) {
        selectedFilter = "Pending";
    } else if (ui->approvedRadioButton->isChecked()) {
        selectedFilter = "Approved";
    } else if (ui->rejectedRadioButton->isChecked()) {
        selectedFilter = "Rejected";
    }
    else if (ui->allRadioButton->isChecked())
    {
        selectedFilter = "";
    }

    QVector<LeaveRecord> leaveApps = currentEmp->_getAllApplications();
    QVector<LeaveRecord> filtered;
    ui->leaveTable->clearContents();




    for(int i = 0; i < leaveApps.size(); i++)
    {
        if(selectedFilter == "")
        {
            filtered = leaveApps;
            break;
        }
        else if (leaveApps[i].status == selectedFilter.toLower())
        {
            filtered.append(leaveApps[i]);
        }

    }

    ui->leaveTable->clearContents();
    ui->leaveTable->setRowCount(filtered.size());

    for (int row = 0; row < filtered.size(); row++) {
        const LeaveRecord& app = filtered[row];

        QTableWidgetItem* appID = new QTableWidgetItem(app.ID);
        appID->setFlags(appID->flags() & ~Qt::ItemIsEditable);
        appID->setTextAlignment(Qt::AlignCenter);
        ui->leaveTable->setItem(row, 0, appID);

        QTableWidgetItem* from = new QTableWidgetItem(app.fromDate);
        from->setFlags(from->flags() & ~Qt::ItemIsEditable);
        from->setTextAlignment(Qt::AlignCenter);
        ui->leaveTable->setItem(row, 1, from);

        QTableWidgetItem* to = new QTableWidgetItem(app.toDate);
        to->setFlags(to->flags() & ~Qt::ItemIsEditable);
        to->setTextAlignment(Qt::AlignCenter);
        ui->leaveTable->setItem(row, 2, to);

        QTableWidgetItem* reasonItem = new QTableWidgetItem(app.reason);
        reasonItem->setFlags(reasonItem->flags() & ~Qt::ItemIsEditable);
        reasonItem->setTextAlignment(Qt::AlignCenter);
        ui->leaveTable->setItem(row, 3, reasonItem);

        QTableWidgetItem* statusItem = new QTableWidgetItem(app.status);
        statusItem->setFlags(statusItem->flags() & ~Qt::ItemIsEditable);
        statusItem->setTextAlignment(Qt::AlignCenter);

        // Set text color based on status
        if (app.status == "Rejected") {
            statusItem->setBackground(QBrush(Qt::red));  // Red for rejected
        } else if (app.status == "Pending") {
            statusItem->setBackground(QBrush(Qt::yellow));  // Yellow for pending
        } else if (app.status == "Approved") {
            statusItem->setBackground(QBrush(Qt::green));  // Green for approved
        }

        ui->leaveTable->setItem(row, 4, statusItem);
    }

    ui->leaveTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void EmpPendingTable::on_closeButton_clicked()
{
    accept();
}

