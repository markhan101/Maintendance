#ifndef PENDINGLEAVESTABLE_H
#define PENDINGLEAVESTABLE_H

#include <QWidget>
#include <QDialog>
#include "supervisor.h"
#include "director.h"
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
    void _setDir(Director *);
    void _displayList();

private slots:
    void _onRowSelected(int row);
    void updateAfterProcess();  // New slot for updating after processing

private:
    Ui::PendingLeavesTable *ui;
    Supervisor * currentSup;
    Director * currentDir;
    LeaveDetailDialog* leaveDetailDialog;  // Single instance
};

#endif
