#ifndef LEAVEDETAILDIALOG_H
#define LEAVEDETAILDIALOG_H

#include <QWidget>
#include <QDialog>

#include "supervisor.h"
#include "director.h"
#include "leaveapplication.h"

namespace Ui {
class LeaveDetailDialog;
}

class LeaveDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LeaveDetailDialog(QWidget *parent = nullptr);
    ~LeaveDetailDialog();
    void _setSup(Supervisor* sup);
    void _setDir(Director *dir);

    void _displayLeaveInfo(PendingList, QString ID);

private slots:
    void on_approveButton_clicked();

    void on_rejectButton_clicked();
signals:
    void LeaveProcessed();

private:
    Ui::LeaveDetailDialog *ui;
    Supervisor *CurrentSup;
    Director * currentDir;
};

#endif // LEAVEDETAILDIALOG_H
