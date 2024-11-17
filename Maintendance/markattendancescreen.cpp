#include "markattendancescreen.h"
#include "ui_markattendancescreen.h"


MarkAttendanceScreen::MarkAttendanceScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MarkAttendanceScreen),currentGuard(nullptr)
{


    ui->setupUi(this);


    ui->attendanceIDTextBox->setAlignment(Qt::AlignCenter);

    ui->attendanceDateDateEdit->setCalendarPopup(true);

    ui->extraHoursComboBox->setPlaceholderText("Choose Hours");
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
    qDebug() << h;
    return h.toInt();
}

void MarkAttendanceScreen::_howToMark(bool isPresent)
{
    QString id = ui->attendanceIDTextBox->toPlainText();
    std::string id_str = id.toStdString();
    currentGuard->_markAttendance(id_str, isPresent , ui->attendanceDateDateEdit->date(), 8 + _getHours(ui->extraHoursComboBox->currentText())); //missing the last date parameter

}


void MarkAttendanceScreen::on_confirmAttendanceButton_clicked()
{
    _howToMark(true);
    this->close();
}


void MarkAttendanceScreen::on_MarkAbsent_clicked()
{
    _howToMark(false);
    this->close();
}

