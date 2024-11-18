#ifndef LEAVEBALANCE_H
#define LEAVEBALANCE_H

#include <unordered_map>
#include "utils.h"
#include "loginpass.h"

class LeaveBalance
{
private:
    std::unordered_map<LeaveTypes,int> balance;
    const LoginPass* loginPass;
public:
    LeaveBalance(const LoginPass* lp = nullptr);

    void _updateLeaveBalance(LeaveTypes, int);
    int _getLeaveBalance(LeaveTypes);
    void displayLeaveBalance();
    void loadBalanceFromFile();
};

#endif // LEAVEBALANCE_H
