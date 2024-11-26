#ifndef DIRECTORLOGIN_H
#define DIRECTORLOGIN_H

#include <QWidget>
#include <QDialog>
#include <director.h>
#include "empattbysupdialogbox.h"
#include "pendingleavestable.h"

namespace Ui {
class DirectorLogin;
}

class DirectorLogin : public QWidget
{
    Q_OBJECT

public:
    explicit DirectorLogin(QWidget *parent = nullptr);
    ~DirectorLogin();

    void _setDirector(Director * dir);

private:
    Ui::DirectorLogin *ui;
    Director * currentDir;
signals:
    void emitLogout();
private slots:
    void on_Logout_clicked();
    void on_viewEmpAttButton_clicked();
    void on_approveRejectButton_clicked();
};

#endif // DIRECTORLOGIN_H
