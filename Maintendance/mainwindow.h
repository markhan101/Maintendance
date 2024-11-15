#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QDialog>
#include "logindialog.h"
#include "utils.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void setupGuardUI();
    void setupEmployeeUI();
    void setupDirectorUI();
    void showLoginDialog();
};
#endif // MAINWINDOW_H
