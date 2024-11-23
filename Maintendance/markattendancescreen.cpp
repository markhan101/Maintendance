#include "markattendancescreen.h"
#include "ui_markattendancescreen.h"


MarkAttendanceScreen::MarkAttendanceScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MarkAttendanceScreen),currentGuard(nullptr)
{


    ui->setupUi(this);


    ui->attendanceIDTextBox->setAlignment(Qt::AlignCenter);

    ui->attendanceDateDateEdit->setCalendarPopup(true);
    ui->attendanceDateDateEdit->setMinimumDate(QDate::currentDate().addDays(-365)); //to be changed

    ui->fromTimeTimeEdit->setDisplayFormat("HH:mm");
    ui->fromTimeTimeEdit->setMinimumTime(QTime(8,0));
    ui->fromTimeTimeEdit->setMaximumTime(QTime(17,0));

    connect(ui->fromTimeTimeEdit, &QTimeEdit::timeChanged, this, &MarkAttendanceScreen::_setMinToTime);


    ui->toTimeTimeEdit->setDisplayFormat("HH:mm");
    ui->toTimeTimeEdit->setMaximumTime(QTime(22,0));


}


void MarkAttendanceScreen::_setMinToTime(QTime time)
{
    ui->toTimeTimeEdit->setMinimumTime(time.addSecs(3600));
}

MarkAttendanceScreen::~MarkAttendanceScreen()
{
    delete ui;
}

void MarkAttendanceScreen::_setGuard(Guard *guard)
{
    currentGuard = guard;
}



QDate MarkAttendanceScreen::_getAttendanceDate(QDate date)
{
    return date;
}



//TO BE ADDED IN UTILS.H
QString _getDayStr(int dayOfWeek)
{
    if (dayOfWeek == 1) {
        return "Monday";
    } else if (dayOfWeek == 2) {
        return "Tuesday";
    } else if (dayOfWeek == 3) {
        return "Wednesday";
    } else if (dayOfWeek == 4) {
        return "Thursday";
    } else if (dayOfWeek == 5) {
        return "Friday";
    } else if (dayOfWeek == 6) {
        return "Saturday";
    } else if (dayOfWeek == 7) {
        return "Sunday";
    }

    return "";
}

//TO BE ADDED IN UTILS



double MarkAttendanceScreen::_calculateHours()
{
    QTime fromTime = ui->fromTimeTimeEdit->time();
    QTime toTime = ui->toTimeTimeEdit->time();

    return (fromTime.secsTo(toTime) / 3600.0);
}

bool MarkAttendanceScreen::_howToMark(bool isPresent)
{
    QString id = ui->attendanceIDTextBox->toPlainText();
    if (id == "")
    {
        QMessageBox::warning(this,"NO ID","Please Make sure ID is entered");
        return false;
    }

    if(ui->attendanceDateDateEdit->date().isNull())
    {
        QMessageBox::warning(this,"No Date", "No Date Selected");
        return false;
    }

    double hours;

    if (!isPresent)
    {
        hours = 0.0;

    }
    else
    {
        hours =  _calculateHours();
    }



    AttendanceEntry* obj = new AttendanceEntry(_getDayStr(ui->attendanceDateDateEdit->date().dayOfWeek()),_getDateStr(ui->attendanceDateDateEdit->date()),isPresent,hours);
    if (currentGuard->_markAttendance(id, obj)) {
        QMessageBox::information(this, "Success", "Attendance marked successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to mark attendance.");
    }

    delete obj;
    obj = nullptr;
    return true;
}


void MarkAttendanceScreen::on_confirmAttendanceButton_clicked()
{
    if(_howToMark(true))
        this->close();
    else return;
}


void MarkAttendanceScreen::on_MarkAbsent_clicked()
{

    if(_howToMark(false))
        this->close();
    else return;
}

