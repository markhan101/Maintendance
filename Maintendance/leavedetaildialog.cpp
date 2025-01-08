#include "leavedetaildialog.h"
#include "ui_leavedetaildialog.h"

/**
 * @brief Constructor for LeaveDetailDialog.
 * Initializes the UI components and sets up the dialog.
 *
 * @param parent Parent widget (optional).
 */
LeaveDetailDialog::LeaveDetailDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LeaveDetailDialog), currentSup(nullptr),currentDir(nullptr)
{
    ui->setupUi(this);  // Set up the UI components
}

/**
 * @brief Destructor for LeaveDetailDialog.
 * Cleans up the UI components.
 */
LeaveDetailDialog::~LeaveDetailDialog()
{
    delete ui;  // Delete the UI object
}

/**
 * @brief Sets the supervisor object to be used for leave approval or rejection.
 *
 * @param sup The Supervisor object.
 */
void LeaveDetailDialog::_setSup(Supervisor * sup)
{
    CurrentSup = sup;  // Set the supervisor pointer
}

/**
 * @brief Sets the director object to be used for leave approval or rejection.
 *
 * @param dir The Director object.
 */
void LeaveDetailDialog::_setDir(Director *dir)
{
    currentDir = dir;  // Set the director pointer
}

/**
 * @brief Displays the leave application details in the dialog.
 * This function updates the UI components with the information from the leave record.
 *
 * @param row The PendingList row containing the leave application data.
 * @param ID The employee ID to display in the dialog.
 */
void LeaveDetailDialog::_displayLeaveInfo(PendingList row, QString ID)
{
    LeaveRecord lvR = _getRecord(row.AID);  // Retrieve the leave record using the application ID (AID)

    // Set the leave record details in the respective UI labels
    ui->empIDDisplayLabel->setText(ID);
    ui->appIDDisplayLabel->setText(lvR.ID);
    ui->fromDateDisplayLabel->setText(lvR.fromDate);
    ui->toDateDisplayLabel->setText(lvR.toDate);
    ui->reasonDisplayLabel->setText(lvR.reason);
    ui->typeOfLeaveDisplayLabel->setText(_getPosStr(lvR.leaveType.toInt()));  // Convert leave type to string
}

/**
 * @brief Slot for the approve button click event.
 * Approves the leave application and removes it from the pending list.
 */
void LeaveDetailDialog::on_approveButton_clicked()
{
    QString AID = ui->appIDDisplayLabel->text();  // Get the application ID from the UI

    // Check if the supervisor pointer is set and approve or reject the leave
    if (CurrentSup)
    {
        CurrentSup->_approveOrRejectLeave(AID, true);  // Approve the leave
        CurrentSup->_removePendingLeave(AID);  // Remove the leave from the pending list
    }
    else if(currentDir)  // If supervisor pointer is not set, check if director pointer is set
    {
        currentDir->_approveOrRejectLeave(AID, true);  // Approve the leave
        currentDir->_removePendingLeave(AID);  // Remove the leave from the pending list
    }
    else
    {
        // If neither supervisor nor director pointer is set, show an error
        QMessageBox::warning(this, "Pointer Error", "Supervisor or Director pointer not set.");
        return;
    }

    // Show success message and emit signal to indicate leave has been processed
    QMessageBox::information(this, "Success", "Leave application approved.");
    emit LeaveProcessed();  // Emit the LeaveProcessed signal
    hide();  // Hide the dialog instead of closing it
}

/**
 * @brief Slot for the reject button click event.
 * Rejects the leave application and removes it from the pending list.
 */
void LeaveDetailDialog::on_rejectButton_clicked()
{
    QString AID = ui->appIDDisplayLabel->text();  // Get the application ID from the UI

    // Check if the supervisor pointer is set and approve or reject the leave
    if (CurrentSup)
    {
        CurrentSup->_approveOrRejectLeave(AID, false);  // Reject the leave
        CurrentSup->_removePendingLeave(AID);  // Remove the leave from the pending list
    }
    else if(currentDir)  // If supervisor pointer is not set, check if director pointer is set
    {
        currentDir->_approveOrRejectLeave(AID, false);  // Reject the leave
        currentDir->_removePendingLeave(AID);  // Remove the leave from the pending list
    }
    else
    {
        // If neither supervisor nor director pointer is set, show an error
        QMessageBox::warning(this, "Pointer Error", "Supervisor or Director pointer not set.");
        return;
    }

    // Show success message and emit signal to indicate leave has been processed
    QMessageBox::information(this, "Success", "Leave application rejected.");
    emit LeaveProcessed();  // Emit the LeaveProcessed signal
    hide();  // Hide the dialog instead of closing it
}

/**
 * @brief Slot for the back button click event.
 * Closes the dialog (rejects the operation).
 */
void LeaveDetailDialog::on_backButton_clicked()
{
    reject();  // Reject the dialog (close it without any further action)
}
