#ifndef MARKATTENDANCESCREEN_H
#define MARKATTENDANCESCREEN_H

#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include "guard.h"
#include "attendanceentry.h"

namespace Ui {
class MarkAttendanceScreen;
}

class MarkAttendanceScreen : public QDialog
{
    Q_OBJECT

public:
    explicit MarkAttendanceScreen(QWidget *parent = nullptr);
    ~MarkAttendanceScreen();
    QDate _getAttendanceDate(QDate date);
    int _getHours(QString);
    void _setGuard(Guard *guard);

    bool _howToMark(bool);

private slots:


    void on_confirmAttendanceButton_clicked();
    void on_MarkAbsent_clicked();

private:
    Ui::MarkAttendanceScreen *ui;
    Guard *currentGuard;

};

#endif // MARKATTENDANCESCREEN_H
