#include "pendingleavestable.h"
#include "ui_pendingleavestable.h"

PendingLeavesTable::PendingLeavesTable(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PendingLeavesTable)
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



void PendingLeavesTable::_displayList()
{

    ui->pendingLeaveTable->clearContents();
    ui->pendingLeaveTable->setRowCount(0);


    QVector<PendingList> pendingLeaves = currentSup->_getPendingList();
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


void PendingLeavesTable::_onRowSelected()
{
    //open a new dialog box do somme
    //modify the vector stored in the supervisor class

    LeaveDetailDialog leaveDetail(this);
    leaveDetail.exec();

}




