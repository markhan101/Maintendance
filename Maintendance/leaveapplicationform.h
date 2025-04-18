#ifndef LEAVEAPPLICATIONFORM_H
#define LEAVEAPPLICATIONFORM_H

#include <QWidget>
#include <QDialog>
#include <guard.h>
#include <employee.h>
#include <QString>
#include "utils.h"
#include <QUuid>
#include "leaveapplication.h"

// this class needs to be created
//#include <supervisor.h>


namespace Ui {
class LeaveApplicationForm;
}

class LeaveApplicationForm : public QDialog
{
    Q_OBJECT

public:
    explicit LeaveApplicationForm(QWidget *parent = nullptr);
    ~LeaveApplicationForm();
    void _setGuard(Guard*);
    LeaveTypes _getTypeOfLeave(QString);
    QString _getFromDate(QDate);
    QString _getToDate(QDate);
    QString _getReason();
    void _setEmployee(Employee*);
    void _updateToDateMinimum(QDate);
    

private slots:
    void on_applyConfirmButton_clicked();


    void on_backButton_clicked();

private:
    Ui::LeaveApplicationForm *ui;
    Guard *currentGuard;
    Employee *currentEmployee;
    
   
};

#endif // LEAVEAPPLICATIONFORM_H
