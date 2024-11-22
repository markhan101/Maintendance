#include "leaveapplicationform.h"
#include "ui_leaveapplicationform.h"

LeaveApplicationForm::LeaveApplicationForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LeaveApplicationForm), currentGuard(nullptr), currentEmployee(nullptr)
{
    ui->setupUi(this);
    ui->fromDateDateEdit->setCalendarPopup(true);
    ui->fromDateDateEdit->setMinimumDate(QDate::currentDate());

    ui->toDateDateEdit->setCalendarPopup(true);
    ui->toDateDateEdit->setMinimumDate(QDate::currentDate());

    connect(ui->typeOfLeaveComboBox, &QComboBox::textActivated, this, &LeaveApplicationForm::_getTypeOfLeave);
    connect(ui->fromDateDateEdit, &QDateEdit::dateChanged, this, &LeaveApplicationForm::_updateToDateMinimum);

    //connect(ui->applyConfirmButton, &QPushButton::clicked, this,  &LeaveApplicationForm::on_applyConfirmButton_clicked);
}

LeaveApplicationForm::~LeaveApplicationForm()
{
    delete ui;
}

void LeaveApplicationForm::_setGuard(Guard* guard)
{
    currentGuard = guard;
}

void LeaveApplicationForm::_setEmployee(Employee * emp)
{
    currentEmployee = emp;
}

void LeaveApplicationForm:: _updateToDateMinimum(QDate fromDate)
{
    ui->toDateDateEdit->setMinimumDate(fromDate);

}


LeaveTypes LeaveApplicationForm::_getTypeOfLeave(QString type)
{
    qDebug() << "type is:" << type;
    if(type == "Casual")
        return LeaveTypes::Casual;
    else if (type == "Earned")
        return LeaveTypes::Earned;
    else if (type == "Official")
        return LeaveTypes::Official;
    else return LeaveTypes::Unpaid;
}

QString LeaveApplicationForm::_getFromDate(QDate fromDate)
{
    qDebug() << "this is the date selected:" << fromDate.toString(Qt::ISODate);
    return fromDate.toString(Qt::ISODate);
}

QString LeaveApplicationForm::_getToDate(QDate toDate)
{
    qDebug() << "this is the date selected:" << toDate.toString(Qt::ISODate);
    return toDate.toString(Qt::ISODate);
}

QString LeaveApplicationForm::_getReason()
{
    QString reason = ui->leaveReasonTextEdit->toPlainText();
    return reason;
}


void LeaveApplicationForm::on_applyConfirmButton_clicked()
{
    if (!currentGuard && !currentEmployee) {
        QMessageBox::warning(this, "Error", "No user information available");
        return;
    }

    LeaveTypes type = _getTypeOfLeave(ui->typeOfLeaveComboBox->currentText());
    QDate fromDate = ui->fromDateDateEdit->date();
    QDate toDate = ui->toDateDateEdit->date();
    int daysRequested = fromDate.daysTo(toDate) + 1;
    
    if (daysRequested < 1) {
        QMessageBox::warning(this, "Error", "Invalid date range selected");
        return;
    }

    QString reason = _getReason();
    if (reason.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please provide a reason for leave");
        return;
    }

    // Get balance and user ID based on current user type
    LeaveBalance* balance = nullptr;
    QString userID;
    
    if (currentGuard) {
        balance = currentGuard->getLeaveBalance();
        userID = currentGuard->_get_uID();
    } else {
        balance = currentEmployee->getLeaveBalance();
        userID = currentEmployee->_get_uID();
    }

    if (!balance) {
        QMessageBox::warning(this, "Error", "Could not retrieve leave balance");
        return;
    }

    LeaveApplication* lv = new LeaveApplication(
        userID,
        type,
        balance,
        _getDateStr(fromDate),
        _getDateStr(toDate),
        reason,
        _getDateStr(QDate::currentDate()),
        "pending",
        daysRequested
    );

    bool success = false;
    if (type == LeaveTypes::Casual && daysRequested <= 4) {
        success = lv->handleCasualShortLeave();
        if (success) {
            QMessageBox::information(this, "Success", 
                "Short leave application approved");
        }
    } else {
        success = lv->handleOtherLeaveTypes(type, daysRequested);
        if (success) {
            QMessageBox::information(this, "Success", 
                "Leave application submitted for approval");
        }
    }

    if (!success) {
        QMessageBox::warning(this, "Error",
            "Failed to process leave application");
    }

    delete lv;
    if (success) {
        this->accept();
    }
}










