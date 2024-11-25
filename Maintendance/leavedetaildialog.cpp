#include "leavedetaildialog.h"
#include "ui_leavedetaildialog.h"

LeaveDetailDialog::LeaveDetailDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LeaveDetailDialog), currentSup(nullptr),currentDir(nullptr)
{
    ui->setupUi(this);

}

LeaveDetailDialog::~LeaveDetailDialog()
{
    delete ui;
}

void LeaveDetailDialog::_setSup(Supervisor * sup) {
    qDebug() << "Setting Supervisor: " << sup;
    currentSup = sup;
}

void LeaveDetailDialog::_setDir(Director * dir) {
    qDebug() << "Setting Director: " << dir;
    currentDir = dir;
}


void LeaveDetailDialog::_displayLeaveInfo(PendingList row, QString ID)
{

    LeaveRecord lvR;
    lvR = _getRecord(row.AID);

    ui->empIDDisplayLabel->setText(ID);
    ui->appIDDisplayLabel->setText(lvR.ID);
    ui->fromDateDisplayLabel->setText(lvR.fromDate);
    ui->toDateDisplayLabel->setText(lvR.toDate);
    ui->reasonDisplayLabel->setText(lvR.reason);
    ui->typeOfLeaveDisplayLabel->setText(_getPosStr(lvR.leaveType.toInt()));

}


void LeaveDetailDialog::on_approveButton_clicked()
{
    QString AID = ui->appIDDisplayLabel->text();

    if (currentSup)
    {
        currentSup->_approveOrRejectLeave(AID, true);  // Approve leave as Supervisor
        currentSup->_removePendingLeave(AID);          // Remove from pending list
    }
    else if (currentDir)
    {
        currentDir->_approveOrRejectLeave(AID, true);  // Approve leave as Director
        currentDir->_removePendingLeave(AID);          // Remove from pending list
    }
    else
    {
        QMessageBox::warning(this, "Error", "Neither Supervisor nor Director is set");
        return;
    }

    // Display success message and emit signal
    QMessageBox::information(this, "Success", "Leave application approved.");
    emit LeaveProcessed();  // Signal to update any lists/tables
    this->close();  // Close the dialog
}



void LeaveDetailDialog::on_rejectButton_clicked()
{
    QString AID = ui->appIDDisplayLabel->text();
    if (currentSup)
    {
        currentSup->_approveOrRejectLeave(AID, false);
        currentSup->_removePendingLeave(AID);
    }
    else if (currentDir)
    {
        currentDir->_approveOrRejectLeave(AID, false);
        currentDir->_removePendingLeave(AID);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Neither Supervisor nor Director is set");
        return;
    }



    QMessageBox::information(this, "Success", "Leave application rejected.");

    emit LeaveProcessed();
    close();  
}

