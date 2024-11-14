#include "leavebalance.h"

LeaveBalance::LeaveBalance()
{
    balance[Casual] = 15;
    balance[Earned] = 21;
    balance[Official] = 100;
    balance[Unpaid] = 1460;
}

void LeaveBalance::_updateLeaveBalance(LeaveTypes type, int days)
{
    balance[type] -= days;
}

int LeaveBalance::_getLeaveBalance(LeaveTypes type)
{
    return balance[type];
}

void LeaveBalance::displayLeaveBalance()
{
    //to be implemented and connected with UI
}
