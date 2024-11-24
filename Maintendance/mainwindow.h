#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QStackedWidget>

#include <QMessageBox>
#include <QDialog>

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>

#include "logindialog.h"
#include "utils.h"
#include "guardlogin.h"
#include "generalemployeelogin.h"
#include "supervisorlogin.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void _handleEmitLogout();

private:
    Ui::MainWindow *ui;
    GuardLogin *guardlogin;
    GeneralEmployeeLogin *genEmpLogin;
    SupervisorLogin *supervisorLogin;

    void _setupGuardUI(QString);
    void _setupEmployeeUI(QString);
    void _setupSupervisorUI(QString);
    void _setupDirectorUI(QString);
    void _showLoginDialog();
};
#endif // MAINWINDOW_H
