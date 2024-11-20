#ifndef LEAVEBALANCE_H
#define LEAVEBALANCE_H

#include <unordered_map>
#include "utils.h"
#include "loginpass.h"

class LeaveBalance
{
private:
    std::unordered_map<LeaveTypes,int> balance;
    QString userId; 
public:
     LeaveBalance(const QString& userId);

    void _updateLeaveBalance(LeaveTypes, int);
    int _getLeaveBalance(LeaveTypes);
    void displayLeaveBalance();
    void loadBalanceFromFile();
    bool saveBalanceToFile();
};

#endif // LEAVEBALANCE_H
