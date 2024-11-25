#include "pendingleavestable.h"
#include "ui_pendingleavestable.h"

PendingLeavesTable::PendingLeavesTable(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PendingLeavesTable), currentSup(nullptr), currentDir(nullptr)
{
    ui->setupUi(this);
}

PendingLeavesTable::~PendingLeavesTable()
{
    delete ui;
}

void PendingLeavesTable::_setSup(Supervisor * sup)
{
    currentSup = sup;
}

void PendingLeavesTable::_setDir(Director * dir)
{
    currentDir = dir;
}




void PendingLeavesTable::_displayList()
{

    ui->pendingLeaveTable->clearContents();
    ui->pendingLeaveTable->setRowCount(0);

    QVector<PendingList> pendingLeaves;
    if(currentDir)
    pendingLeaves = currentDir->_getPendingList();
    else
    pendingLeaves = currentSup->_getPendingList();

    ui->pendingLeaveTable->setRowCount(pendingLeaves.size());

    for (int row = 0; row < pendingLeaves.size(); ++row)
    {
        const auto& leave = pendingLeaves[row];


        QString employeeID = leave.AID.split('_').first();


        QTableWidgetItem* empIdItem = new QTableWidgetItem(employeeID);
        empIdItem->setFlags(empIdItem->flags() & ~Qt::ItemIsEditable);
        empIdItem->setTextAlignment(Qt::AlignCenter);
        ui->pendingLeaveTable->setItem(row, 0, empIdItem);


        QTableWidgetItem* appIdItem = new QTableWidgetItem(leave.AID);
        appIdItem->setFlags(appIdItem->flags() & ~Qt::ItemIsEditable);
        appIdItem->setTextAlignment(Qt::AlignCenter);
        ui->pendingLeaveTable->setItem(row, 1, appIdItem);


        QTableWidgetItem* dateItem = new QTableWidgetItem(leave.date);
        dateItem->setFlags(dateItem->flags() & ~Qt::ItemIsEditable);
        dateItem->setTextAlignment(Qt::AlignCenter);
        ui->pendingLeaveTable->setItem(row, 2, dateItem);

    }


    ui->pendingLeaveTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->pendingLeaveTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pendingLeaveTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pendingLeaveTable->setSelectionMode(QAbstractItemView::SingleSelection);


   connect(ui->pendingLeaveTable, &QTableWidget::cellClicked, this, &PendingLeavesTable::_onRowSelected);
}


void PendingLeavesTable::_onRowSelected(int row)
{
    // Retrieve selected leave information from the table
    QString selectedAID = ui->pendingLeaveTable->item(row, 1)->text();
    QString selectedDate = ui->pendingLeaveTable->item(row, 2)->text();

    // Store the selected leave in a PendingList structure
    PendingList pendingLeave;
    pendingLeave.AID = selectedAID;
    pendingLeave.date = selectedDate;

    QString ID = selectedAID.split('_').first();  // Extract the ID from AID

    LeaveDetailDialog leaveDetail(this);  // Create the leave detail dialog

    // Set either the supervisor or director in the leave detail dialog
    if (currentSup)
    {
        leaveDetail._setSup(currentSup);  // Set the supervisor
    }
    else if (currentDir)
    {
        leaveDetail._setDir(currentDir);  // Set the director
    }

    // Display the leave information in the dialog
    leaveDetail._displayLeaveInfo(pendingLeave, ID);

    // Connect the LeaveProcessed signal to refresh the pending leave list after action
    connect(&leaveDetail, &LeaveDetailDialog::LeaveProcessed, this, &PendingLeavesTable::_displayList);

    // Show the dialog modally
    leaveDetail.exec();
}





