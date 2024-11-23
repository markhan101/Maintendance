#include "leavedetaildialog.h"
#include "ui_leavedetaildialog.h"

LeaveDetailDialog::LeaveDetailDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LeaveDetailDialog)
{
    ui->setupUi(this);
}

LeaveDetailDialog::~LeaveDetailDialog()
{
    delete ui;
}
