#include "guardlogin.h"
#include "ui_guardlogin.h"

GuardLogin::GuardLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GuardLogin), currentGuard(nullptr)
{
    ui->setupUi(this); // Set up UI first

    typingTimer = new QTimer(this);
    connect(typingTimer, &QTimer::timeout, this, &GuardLogin::updateWelcomeMessage);  // Connect timer to the slot

    // Assume we call this once the currentGuard is set or after login

}

GuardLogin::~GuardLogin()
{
    delete ui;
}

void GuardLogin::setCurrentGuard(Guard *guard)
{
    currentGuard = guard;

    fullMessage = QString("Welcome %1").arg(currentGuard->_get_uID());
    currentCharIndex = 0; // Reset the index
    ui->welcomeLabel->clear();  // Clear any existing text
    typingTimer->start(100);    // Start typing effect

    updateLeaveBalanceUI(); // Call this after setting the guard
}

void GuardLogin::on_markAttendanceButton_clicked()
{
    MarkAttendanceScreen attendanceDialog(this);

    if (attendanceDialog.exec() == QDialog::Accepted)
    {
        qDebug() << "Attendance marked successfully!";
        updateLeaveBalanceUI();  // Update UI after action
    }
}

void GuardLogin::on_logOutButton_clicked()
{
    emit emitLogout();
}

void GuardLogin::on_viewAttendanceButton_clicked()
{
    if (currentGuard)
    {
        ViewAttendance viewAttendance(this);
        viewAttendance._setGuard(currentGuard);
        viewAttendance._displayList();
        viewAttendance.exec();
    } else
    {
        qDebug() << "Error GuardLogin has no currentGuard set";
    }
}

void GuardLogin::on_requestLeaveButton_clicked()
{
    if (currentGuard)
    {
        LeaveApplicationForm *leaveapplication = new LeaveApplicationForm(this);
        leaveapplication->_setGuard(currentGuard);
        leaveapplication->exec();
        updateLeaveBalanceUI();  // Update UI after action
    }
    else
    {
        qDebug() << "Error GuardLogin has no currentGuard set";
    }
}

void GuardLogin::on_viewLeavesButton_clicked()
{
    EmpPendingTable empPendtable(this);
    empPendtable._setEmp(static_cast<Employee*>(currentGuard));
    empPendtable._populateTable();
    empPendtable.exec();
}

void GuardLogin::updateLeaveBalanceUI()
{
    if (!currentGuard)
    {
        qDebug() << "Error: No guard set";
        return;  // Return early if currentGuard is not set
    }

    QVector<LeaveBalanceRecord> balances = currentGuard->getLeaveBalances();

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

void GuardLogin::updateWelcomeMessage()
{
    if (!currentGuard)
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
