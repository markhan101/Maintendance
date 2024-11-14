#ifndef LEAVEBALANCE_H
#define LEAVEBALANCE_H

#include <unordered_map>
#include "utils.h"

class LeaveBalance
{
private:
    std::unordered_map<LeaveTypes,int> balance;
public:
    LeaveBalance();

    void _updateLeaveBalance(LeaveTypes, int);
    int _getLeaveBalance(LeaveTypes);
    void displayLeaveBalance();
};

#endif // LEAVEBALANCE_H
