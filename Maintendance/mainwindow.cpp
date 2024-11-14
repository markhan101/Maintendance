#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "animationlabel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AnimationLabel animLabel;
    animLabel.show();

}

MainWindow::~MainWindow()
{
    delete ui;
}


