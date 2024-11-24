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
 if (!CurrentSup) {
        QMessageBox::warning(this, "Error", "Supervisor not set");
        return;
    }

    QString AID = ui->appIDDisplayLabel->text();
    CurrentSup->_approveOrRejectLeave(AID, true);

     CurrentSup->_removePendingLeave(AID);

    QMessageBox::information(this, "Success", "Leave application approved.");

    emit LeaveProcessed(); 
    close(); 

}


void LeaveDetailDialog::on_rejectButton_clicked()
{
   if (!CurrentSup) {
        QMessageBox::warning(this, "Error", "Supervisor not set");
        return;
    }

    QString AID = ui->appIDDisplayLabel->text();
    CurrentSup->_approveOrRejectLeave(AID, false);
    CurrentSup->_removePendingLeave(AID);

    QMessageBox::information(this, "Success", "Leave application rejected.");

    emit LeaveProcessed();
    close();  
}

