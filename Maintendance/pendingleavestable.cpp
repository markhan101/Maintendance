#include "pendingleavestable.h"
#include "ui_pendingleavestable.h"

PendingLeavesTable::PendingLeavesTable(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PendingLeavesTable)
    , currentSup(nullptr)
    , currentDir(nullptr)
    , leaveDetailDialog(nullptr)  // Initialize to nullptr
{
    ui->setupUi(this);
}

PendingLeavesTable::~PendingLeavesTable()
{
    delete ui;
    if (leaveDetailDialog) {
        delete leaveDetailDialog;
        leaveDetailDialog = nullptr;
    }
}

void PendingLeavesTable::updateAfterProcess()
{
    if (leaveDetailDialog) {
        leaveDetailDialog->deleteLater();  // Schedule for deletion
        leaveDetailDialog = nullptr;
    }
    _displayList();
}

void PendingLeavesTable::_setSup(Supervisor * sup)
{
    currentSup = sup;
}
void PendingLeavesTable::_setDir(Director* dir)
{
    currentDir = dir;
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

    QVector<PendingList> pendingLeaves ;
    if(currentSup)
       pendingLeaves =  currentSup->_getPendingList();
    else if (currentDir)
        pendingLeaves = currentDir->_getPendingList();

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
    // If there's an existing dialog, clean it up
    if (leaveDetailDialog) {
        leaveDetailDialog->disconnect();  // Disconnect all signals
        leaveDetailDialog->deleteLater();
        leaveDetailDialog = nullptr;
    }

    QString selectedAID = ui->pendingLeaveTable->item(row, 1)->text();
    QString selectedDate = ui->pendingLeaveTable->item(row, 2)->text();
    PendingList pendingLeave;
    pendingLeave.AID = selectedAID;
    pendingLeave.date = selectedDate;
    QString ID = selectedAID.split('_').first();

    leaveDetailDialog = new LeaveDetailDialog(this);

    if(currentSup)
        leaveDetailDialog->_setSup(currentSup);
    else if (currentDir)
        leaveDetailDialog->_setDir(currentDir);

    leaveDetailDialog->_displayLeaveInfo(pendingLeave, ID);

    // Single connection for processing completion
    connect(leaveDetailDialog, &LeaveDetailDialog::LeaveProcessed,
            this, &PendingLeavesTable::updateAfterProcess,
            Qt::QueuedConnection);

    leaveDetailDialog->show();  // Use show() instead of exec()
}

void PendingLeavesTable::on_closeButton_clicked()
{
    accept();
}


