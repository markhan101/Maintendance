#include "supervisorlogin.h"
#include "ui_supervisorlogin.h"

SupervisorLogin::SupervisorLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SupervisorLogin)
{
    ui->setupUi(this);
    typingTimer = new QTimer(this);
    connect(typingTimer, &QTimer::timeout, this, &SupervisorLogin::updateWelcomeMessage);  // Connect timer to the slot


}

SupervisorLogin::~SupervisorLogin()
{
    delete ui;
}

void SupervisorLogin::_setCurrentSup(Supervisor* sup)
{
    currentSup = sup;

    fullMessage = QString("Welcome %1").arg(currentSup->_get_uID());
    currentCharIndex = 0; // Reset the index
    ui->welcomeLabel->clear();  // Clear any existing text
    typingTimer->start(100);    // Start typing effect
}

void SupervisorLogin::on_logOutButton_clicked()
{
    emit emitLogout();
}

void SupervisorLogin::on_viewAttendanceButton_clicked()
{
    if (currentSup) {
        ViewAttendance viewAttendance(this);
        viewAttendance._setSup(currentSup);
        viewAttendance._displayList();
        viewAttendance.exec();
    }
    else {
        qDebug() << "Error SupervisorLogin has no supervisor set";
    }
}

void SupervisorLogin::on_viewEmployeeAttendanceButton_clicked()
{

EmpAttBySupDialogBox  empAttDialog (this);
    empAttDialog.exec();
}

void SupervisorLogin::on_approveRejectLeaveButton_clicked()
{

    PendingLeavesTable leavesTable(this);
    if(currentDir)
    {
        leavesTable._setDir(currentDir);
        qDebug() << "Director set for pending leaves table";
    }
    else
    {
        leavesTable._setSup(currentSup);
        qDebug() << "Supervisor set for pending leaves table";
    }
    leavesTable._displayList();
    leavesTable.exec();
}




void SupervisorLogin::on_viewAbsenteeRecordsButton_clicked()
{
    ShortAttendanceTable* shortAttTable = new ShortAttendanceTable(this);
    shortAttTable->setAttribute(Qt::WA_DeleteOnClose);
    shortAttTable->_setSup(currentSup);
    shortAttTable->_populateTable();
    shortAttTable->exec();
}


void SupervisorLogin::updateWelcomeMessage()
{
    if (!currentSup)
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
