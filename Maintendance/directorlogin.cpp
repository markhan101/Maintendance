#include "directorlogin.h"
#include "ui_directorlogin.h"

DirectorLogin::DirectorLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DirectorLogin)
{
    ui->setupUi(this);
    typingTimer = new QTimer(this);
    connect(typingTimer, &QTimer::timeout, this, &DirectorLogin::updateWelcomeMessage);  // Connect timer to the slot


}

DirectorLogin::~DirectorLogin()
{
    delete ui;
}

void DirectorLogin::_setDirector(Director * dir)
{
    currentDir = dir;

    fullMessage = QString("Welcome %1").arg(currentDir->_get_uID());
    currentCharIndex = 0; // Reset the index
    ui->welcomeLabel->clear();  // Clear any existing text
    typingTimer->start(100);    // Start typing effect
}


void DirectorLogin::on_Logout_clicked()
{
    emit emitLogout();
}


void DirectorLogin::on_viewEmpAttButton_clicked()
{
    EmpAttBySupDialogBox  empAttDialog (this);
    empAttDialog.exec();

}


void DirectorLogin::on_approveRejectButton_clicked()
{
    PendingLeavesTable leavesTable(this);
    leavesTable._setDir(currentDir);
    leavesTable._displayList();
    leavesTable.exec();


}

void DirectorLogin::updateWelcomeMessage()
{
    if (!currentDir)
    {
        qDebug() << "Error: No guard set";
        typingTimer->stop();  // Stop the timer if there's no guard set
        return;  // Return early if currentGuard is not set
    }

    if (currentCharIndex < fullMessage.length()) {
        ui->welcomeLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 26px; }");
        ui->welcomeLabel->setAlignment(Qt::AlignCenter);
        ui->welcomeLabel->setText(ui->welcomeLabel->text() + fullMessage.at(currentCharIndex));
        currentCharIndex++;
    }
    else
    {
        typingTimer->stop();  // Stop the timer once the full message is displayed
    }
}


