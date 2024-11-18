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
    void _setGuard(Guard *guard);
    void _setEmployee(Employee *emp);
    void _displayList(std::vector<QString>);
    void _displayList();
    Position _getUserPos();
private:
    Ui::ViewAttendance *ui;
    Guard *currentGuard;
    Employee* currentEmp;
};

#endif // VIEWATTENDANCE_H
