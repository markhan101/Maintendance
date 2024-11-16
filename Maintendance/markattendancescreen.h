#ifndef MARKATTENDANCESCREEN_H
#define MARKATTENDANCESCREEN_H

#include <QWidget>
#include <QDialog>

#include "guard.h"

namespace Ui {
class MarkAttendanceScreen;
}

class MarkAttendanceScreen : public QDialog
{
    Q_OBJECT

public:
    explicit MarkAttendanceScreen(QWidget *parent = nullptr);
    ~MarkAttendanceScreen();
    void setGuard(Guard *guard);

private slots:


    void on_confirmAttendanceButton_clicked();

    void on_MarkAbsent_clicked();

private:
    Ui::MarkAttendanceScreen *ui;
    Guard *currentGuard;

};

#endif // MARKATTENDANCESCREEN_H
