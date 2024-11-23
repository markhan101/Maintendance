#ifndef PENDINGLEAVESTABLE_H
#define PENDINGLEAVESTABLE_H

#include <QWidget>
#include <QDialog>

#include "supervisor.h"
#include "leavedetaildialog.h"

namespace Ui {
class PendingLeavesTable;
}

class PendingLeavesTable : public QDialog
{
    Q_OBJECT

public:
    explicit PendingLeavesTable(QWidget *parent = nullptr);
    ~PendingLeavesTable();

    void _setSup(Supervisor *);
    void _displayList();
    void _onRowSelected();

private:
    Ui::PendingLeavesTable *ui;
    Supervisor * currentSup;


};

#endif // PENDINGLEAVESTABLE_H
