#include "supervisorlogin.h"
#include "ui_supervisorlogin.h"

SupervisorLogin::SupervisorLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SupervisorLogin)
{
    ui->setupUi(this);
    //ui->graphicsView->setBackgroundBrush(QImage("pics.qrc:/pic.png"));
    //ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    connect(ui->logOutButton, &QPushButton::clicked, this, &SupervisorLogin::on_logOutButton_clicked);
}

SupervisorLogin::~SupervisorLogin()
{
    delete ui;
}

void SupervisorLogin::on_logOutButton_clicked()
{
    emit emitLogout();
}

