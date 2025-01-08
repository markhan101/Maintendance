#ifndef VIEWATTENDANCE_H
#define VIEWATTENDANCE_H

#include <QWidget>
#include <QDialog>
#include <QString>

#include "guard.h"
#include "supervisor.h"


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
    void _setSup(Supervisor *sup);
    void _displayList(std::vector<QString>);
    void _displayList();
    Position _getUserPos();
private slots:
    void on_goBackButton_clicked();

private:
    Ui::ViewAttendance *ui;

    //!!!!!!WARNING!!!!!!!
    //no need to delete these objects since they are not dynamically allocated and are coming from the previous screen
    //deleting and deallocation them will cause the previous screen to have a null object resulting in segFault
    Guard *currentGuard;
    Employee* currentEmp;
    Supervisor* currentSup;
};

#endif // VIEWATTENDANCE_H
