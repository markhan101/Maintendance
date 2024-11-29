#include "leavedetaildialog.h"
#include "ui_leavedetaildialog.h"

LeaveDetailDialog::LeaveDetailDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LeaveDetailDialog)
{
    ui->setupUi(this);

}

LeaveDetailDialog::~LeaveDetailDialog()
{
    delete ui;
}

void LeaveDetailDialog::_setSup(Supervisor * sup)
{
    CurrentSup = sup;
}

void LeaveDetailDialog::_setDir(Director *dir)
{
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

    if (CurrentSup)
    {
        CurrentSup->_approveOrRejectLeave(AID, true);
        CurrentSup->_removePendingLeave(AID);
    }
    else if(currentDir)
    {
        currentDir->_approveOrRejectLeave(AID, true);
        currentDir->_removePendingLeave(AID);
    }
    else
    {
        QMessageBox::warning(this, "Pointer Error", "Supervisor or Director pointer not set.");
        return;
    }

    QMessageBox::information(this, "Success", "Leave application approved.");
    emit LeaveProcessed();
    hide();  // Hide instead of close
}

void LeaveDetailDialog::on_rejectButton_clicked()
{
    QString AID = ui->appIDDisplayLabel->text();

    if (CurrentSup)
    {
        CurrentSup->_approveOrRejectLeave(AID, false);
        CurrentSup->_removePendingLeave(AID);
    }
    else if(currentDir)
    {
        currentDir->_approveOrRejectLeave(AID, false);
        currentDir->_removePendingLeave(AID);
    }
    else
    {
        QMessageBox::warning(this, "Pointer Error", "Supervisor or Director pointer not set.");
        return;
    }

    QMessageBox::information(this, "Success", "Leave application rejected.");
    emit LeaveProcessed();
    hide();  // Hide instead of close
}
