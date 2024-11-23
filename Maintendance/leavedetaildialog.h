#ifndef LEAVEDETAILDIALOG_H
#define LEAVEDETAILDIALOG_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class LeaveDetailDialog;
}

class LeaveDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LeaveDetailDialog(QWidget *parent = nullptr);
    ~LeaveDetailDialog();

private:
    Ui::LeaveDetailDialog *ui;
};

#endif // LEAVEDETAILDIALOG_H
