#ifndef SUPERVISORLOGIN_H
#define SUPERVISORLOGIN_H

#include <QWidget>

namespace Ui {
class SupervisorLogin;
}

class SupervisorLogin : public QWidget
{
    Q_OBJECT

public:
    explicit SupervisorLogin(QWidget *parent = nullptr);
    ~SupervisorLogin();

private slots:
    void on_logOutButton_clicked();

private:
    Ui::SupervisorLogin *ui;


signals:
    void emitLogout();
};

#endif // SUPERVISORLOGIN_H
