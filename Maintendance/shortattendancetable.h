#ifndef SHORTATTENDANCETABLE_H
#define SHORTATTENDANCETABLE_H

#include <QWidget>
#include <QDialog>
#include "supervisor.h"
#include "guard.h"
#include "utils.h"


namespace Ui {
class ShortAttendanceTable;
}

class ShortAttendanceTable : public QDialog
{
    Q_OBJECT

public:
    explicit ShortAttendanceTable(QWidget *parent = nullptr);
    ~ShortAttendanceTable();
    void _setSup(Supervisor*);
    void _populateTable();

private:
    Ui::ShortAttendanceTable *ui;
    Supervisor * currentSup;
};

#endif // SHORTATTENDANCETABLE_H
