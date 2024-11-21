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
    connect(ui->fromDateDateEdit, &QDateEdit::dateChanged, this, &LeaveApplicationForm::_getFromDate);
    connect(ui->toDateDateEdit, &QDateEdit::dateChanged, this, &LeaveApplicationForm::_getToDate);
   // connect(ui->applyConfirmButton, &QPushButton::clicked, this,  &LeaveApplicationForm::on_applyConfirmButton_clicked);
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

    LeaveTypes type = _getTypeOfLeave(ui->typeOfLeaveComboBox->currentText());
    QDate fromDate = ui->fromDateDateEdit->date();
    QDate toDate = ui->toDateDateEdit->date();
    int daysRequested = fromDate.daysTo(toDate) + 1;
    QString reason = _getReason();

    if(!currentGuard) {
        return;
    }

    // causal leaves less than 4 days
    if(type == LeaveTypes::Casual && daysRequested <= 4) {

        handleCasualShortLeave(daysRequested, reason);
    } else {

        handleOtherLeaveTypes(type, daysRequested);
    }
}

void LeaveApplicationForm::handleCasualShortLeave(int daysRequested, QString reason)
    {
        LeaveBalance* balance = currentGuard->getLeaveBalance();
        
        if(balance->_getLeaveBalance(LeaveTypes::Casual) >= daysRequested) {
            balance->_updateLeaveBalance(LeaveTypes::Casual, daysRequested, reason);
            
            QString balanceMsg = QString("Remaining Leave Balances:\n"
                                     "Casual: %1\n"
                                     "Earned: %2\n"
                                     "Official: %3\n"
                                     "Unpaid: %4")
                                 .arg(balance->_getLeaveBalance(LeaveTypes::Casual))
                                 .arg(balance->_getLeaveBalance(LeaveTypes::Earned))
                                 .arg(balance->_getLeaveBalance(LeaveTypes::Official))
                                 .arg(balance->_getLeaveBalance(LeaveTypes::Unpaid));

            QMessageBox::information(this, "Leave Balance", balanceMsg);
            this->accept();
        } else {
            QMessageBox::warning(this, "Insufficient Balance", 
                "You don't have enough casual leave balance.");
        }
    }



    void LeaveApplicationForm::handleOtherLeaveTypes(LeaveTypes type, int daysRequested)
    {
         LeaveBalance* balance = currentGuard->getLeaveBalance();

        if(balance->_getLeaveBalance(type)>=daysRequested){
            

        }
        
       
        

        // Placeholder for different leave approval process
        QMessageBox::information(this, "Leave Application", 
            "This type of leave requires special approval process.\n"
            "Feature coming soon.");
        // TODO: Implement different approval workflow
    }




