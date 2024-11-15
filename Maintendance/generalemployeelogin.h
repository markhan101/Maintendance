#ifndef GENERALEMPLOYEELOGIN_H
#define GENERALEMPLOYEELOGIN_H

#include <QWidget>

namespace Ui {
class GeneralEmployeeLogin;
}

class GeneralEmployeeLogin : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralEmployeeLogin(QWidget *parent = nullptr);
    ~GeneralEmployeeLogin();

private:
    Ui::GeneralEmployeeLogin *ui;

signals:
    void emitLogout();
private slots:
    void on_logoutButton_clicked();
};

#endif // GENERALEMPLOYEELOGIN_H
