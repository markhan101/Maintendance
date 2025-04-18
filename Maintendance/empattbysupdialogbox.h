#ifndef EMPATTBYSUPDIALOGBOX_H
#define EMPATTBYSUPDIALOGBOX_H

#include <QWidget>
#include <QDialog>
#include <QTableWidget>
#include <QHeaderView>
#include "supervisor.h"
#include "viewattendance.h"
#include "utils.h"

namespace Ui {
class EmpAttBySupDialogBox;
}

class EmpAttBySupDialogBox : public QDialog
{
    Q_OBJECT

public:
    explicit EmpAttBySupDialogBox(QWidget *parent = nullptr);
    ~EmpAttBySupDialogBox();

    void _setSup(Supervisor*);



private slots:
    void on_viewButton_clicked();

    void on_backButton_clicked();

private:
    Ui::EmpAttBySupDialogBox *ui;
    Supervisor *currentSup;
    double calculateEmployeeAttendance(const QString& empId);

};

#endif // EMPATTBYSUPDIALOGBOX_H
