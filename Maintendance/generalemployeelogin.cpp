#include "generalemployeelogin.h"
#include "ui_generalemployeelogin.h"

GeneralEmployeeLogin::GeneralEmployeeLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GeneralEmployeeLogin)
{
    ui->setupUi(this);
    typingTimer = new QTimer(this);
    connect(typingTimer, &QTimer::timeout, this, &GeneralEmployeeLogin::updateWelcomeMessage);  // Connect timer to the slot

}

GeneralEmployeeLogin::~GeneralEmployeeLogin()
{
    delete ui;
}

void GeneralEmployeeLogin::on_logoutButton_clicked()
{
    emit emitLogout();
}

void GeneralEmployeeLogin::_setEmployee(Employee* emp)
{
    generalEmp = emp;
    fullMessage = QString("Welcome %1").arg(generalEmp->_get_uID());
    currentCharIndex = 0; // Reset the index
    ui->welcomeLabel->clear();  // Clear any existing text
    typingTimer->start(100);    // Start typing effect

    updateLeaveBalanceUI();
}


void GeneralEmployeeLogin::on_viewAttendanceButton_clicked()
{
    if (generalEmp) {
        ViewAttendance viewAttendance (this);
        viewAttendance._setEmployee(generalEmp);
        viewAttendance._displayList();
        viewAttendance.exec();
        
    } else {
        qDebug() << "Error GuardLogin has no currentGuard set";
    }

}

void GeneralEmployeeLogin::on_viewLeaveBalanceButton_clicked()
{
    if (generalEmp)
    {
        LeaveBalance* leaveBalance = generalEmp->getLeaveBalance();
        
        int casualLeaves = leaveBalance->_getLeaveBalance(LeaveTypes::Casual);
       
        qDebug()<< casualLeaves;
    }
    else
    {
        qDebug() << "Error: generalEmp is nullptr";
    }
}

void GeneralEmployeeLogin::on_requestLeaveButton_clicked()
{
    if (generalEmp) {
        LeaveApplicationForm *leaveapplication = new LeaveApplicationForm(this);
        leaveapplication->_setEmployee(generalEmp);
        leaveapplication->exec();
        updateLeaveBalanceUI();
    } else {
        qDebug() << "Error: GeneralEmployeeLogin has no employee set";
    }
}

void GeneralEmployeeLogin::on_viewApplicationButton_clicked()
{
    if (generalEmp)
    {
        EmpPendingTable emp(this);
        emp._setEmp(generalEmp);
        emp._populateTable();
        emp.exec();
    }
}

void GeneralEmployeeLogin::updateLeaveBalanceUI()
{
    if (!generalEmp)
    {
        qDebug() << "Error: No guard set";
        return;  // Return early if currentGuard is not set
    }

    QVector<LeaveBalanceRecord> balances = generalEmp->getLeaveBalances();

    if (balances.size() < 4)
    {
        qDebug() << "Error: Not enough leave balances data";
        return;
    }

    // Casual Leave LCD (Dark Gray background, Green text)
    ui->casualLCD->display(balances[0].balance);
    ui->casualLCD->setSegmentStyle(QLCDNumber::Flat);
    ui->casualLCD->setStyleSheet("QLCDNumber { background-color: #222; color: #4CAF50; }");

    // Earned Leave LCD (Dark Blue background, Cyan text)
    ui->earnedLCD->display(balances[1].balance);
    ui->earnedLCD->setSegmentStyle(QLCDNumber::Flat);
    ui->earnedLCD->setStyleSheet("QLCDNumber { background-color: #222; color: #00FFFF; }");

    // Official Leave LCD (Dark Green background, Light Yellow text)
    ui->officialLCD->display(balances[2].balance);
    ui->officialLCD->setSegmentStyle(QLCDNumber::Flat);
    ui->officialLCD->setStyleSheet("QLCDNumber { background-color: #222; color: #FFFF99; }");

    // Unpaid Leave LCD (Dark Red background, White text)
    ui->unpaidLCD->display(balances[3].balance);
    ui->unpaidLCD->setSegmentStyle(QLCDNumber::Flat);
    ui->unpaidLCD->setStyleSheet("QLCDNumber { background-color: #222; color: #FFFFFF; }");
}

void GeneralEmployeeLogin::updateWelcomeMessage()
{
    if (!generalEmp)
    {
        qDebug() << "Error: No guard set";
        typingTimer->stop();  // Stop the timer if there's no guard set
        return;  // Return early if currentGuard is not set
    }

    if (currentCharIndex < fullMessage.length()) {
        ui->welcomeLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 18px; }");
        ui->welcomeLabel->setText(ui->welcomeLabel->text() + fullMessage.at(currentCharIndex));
        currentCharIndex++;
    }
    else
    {
        typingTimer->stop();  // Stop the timer once the full message is displayed
    }
}


