#include "markattendancescreen.h"
#include "ui_markattendancescreen.h"


MarkAttendanceScreen::MarkAttendanceScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MarkAttendanceScreen),currentGuard(nullptr)
{


    ui->setupUi(this);


    ui->attendanceIDTextBox->setAlignment(Qt::AlignCenter);

    ui->attendanceDateDateEdit->setCalendarPopup(true);
    ui->attendanceDateDateEdit->setMinimumDate(QDate::currentDate().addDays(-365));

    ui->extraHoursComboBox->setPlaceholderText("By default this is 0");
    ui->extraHoursComboBox->setMaxCount(3);
    ui->extraHoursComboBox->addItem("1");
    ui->extraHoursComboBox->addItem("2");
    ui->extraHoursComboBox->addItem("3");
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

int MarkAttendanceScreen::_getHours (QString h)
{
    if(h=="")
        return 0;
    return h.toInt();
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
QString _getDateStr(QDate date)
{
    return date.toString("yyyy/MM/dd");
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


    AttendanceEntry* obj = new AttendanceEntry(_getDayStr(ui->attendanceDateDateEdit->date().dayOfWeek()),_getDateStr(ui->attendanceDateDateEdit->date()),isPresent,8 + _getHours(ui->extraHoursComboBox->currentText()));
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
    if(_howToMark(false))
        this->close();
    else return;
}


void MarkAttendanceScreen::on_MarkAbsent_clicked()
{

    if(_howToMark(false))
        this->close();
    else return;
}

