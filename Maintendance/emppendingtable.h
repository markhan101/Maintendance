#ifndef EMPPENDINGTABLE_H
#define EMPPENDINGTABLE_H

#include <QDialog>
#include "employee.h"

namespace Ui {
class EmpPendingTable;
}

class EmpPendingTable : public QDialog
{
    Q_OBJECT

public:
    explicit EmpPendingTable(QWidget *parent = nullptr);
    ~EmpPendingTable();

    void _setEmp(Employee*);
    void _populateTable();

private slots:
    void filterTable();

    void on_closeButton_clicked();

private:
    Ui::EmpPendingTable *ui;
    Employee *currentEmp;

};

#endif // EMPPENDINGTABLE_H
