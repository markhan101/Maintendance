#ifndef VIEWATTENDANCE_H
#define VIEWATTENDANCE_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include "guard.h"

namespace Ui {
class ViewAttendance;
}

class ViewAttendance : public QDialog
{
    Q_OBJECT

public:
    explicit ViewAttendance(QWidget *parent = nullptr);
    ~ViewAttendance();
    void setGuard(Guard *guard);
    //void displayList(std::vector<std::string>);
    void displayList();
private:
    Ui::ViewAttendance *ui;
    Guard *currentGuard;
};

#endif // VIEWATTENDANCE_H
