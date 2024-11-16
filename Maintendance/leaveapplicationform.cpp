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
    //need to create an Object of Leave application in header which hold all this data and send it;


}

