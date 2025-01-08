#ifndef MARKATTENDANCESCREEN_H
#define MARKATTENDANCESCREEN_H

#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include "guard.h"
#include "attendanceentry.h"
#include "utils.h"

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
    void _setMinToTime (QTime);
    bool _howToMark(bool);
    double _calculateHours();

private slots:


    void on_confirmAttendanceButton_clicked();
    void on_MarkAbsent_clicked();

    void on_approveButton_clicked();

private:
    Ui::MarkAttendanceScreen *ui;
    Guard *currentGuard;

};

#endif // MARKATTENDANCESCREEN_H
