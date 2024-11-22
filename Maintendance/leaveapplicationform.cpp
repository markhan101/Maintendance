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

    if (currentGuard) {
        LeaveBalance* balance = currentGuard->getLeaveBalance();
        if (!balance) {
            QMessageBox::warning(this, "Error", "Could not retrieve leave balance");
            return;
        }

        LeaveApplication* lv = new LeaveApplication(
            currentGuard->_get_uID(),
            type,
            balance,
            _getDateStr(fromDate),
            _getDateStr(toDate),
            reason,
            _getDateStr(QDate::currentDate()),
            "approved",
            daysRequested
        );

        if (type == LeaveTypes::Casual && daysRequested <= 4) {
            if (lv->handleCasualShortLeave()) {
                QMessageBox::information(this, "Success", 
                    "Short leave application approved");
                delete lv;
               
                this->accept();
            } else {
                
            }
        } else {
            
            if(lv->handleOtherLeaveTypes(type, daysRequested)){
            QMessageBox::information(this, "Success", 
                "Leave application submitted for approval");
            this->accept();
            delete lv;
            }
            else{
                    QMessageBox::warning(this, "Error",
                    "Failed to process leave application");
                delete lv;
            }

        }
    } //else if (currentEmployee) {
        // Handle employee leave logic similarly
        //handleOtherLeaveTypes(type, daysRequested);
    //}
}










