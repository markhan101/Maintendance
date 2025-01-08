#include "attendancelog.h"

AttendanceLog::AttendanceLog() {}

void AttendanceLog::_addEntry(QString day, QString date, QString attendance, int hours)
{
    attEntries.emplace_back(day, date, attendance, hours);
}
//this function will recieve a pointer for the entry
void AttendanceLog::_addEntry(AttendanceEntry &entry)
{
    attEntries.emplace_back(entry);
}

void AttendanceLog::_displayEntries()
{
    double monthlyPercentage = _getMonthlyAttendancePercentage(QDate::currentDate());
    double weeklyPercentage = _getWeeklyAttendancePercentage(QDate::currentDate());
    
    QString message = QString("Attendance Statistics:\n\n"
                            "Monthly Attendance: %1%\n"
                            "Weekly Attendance: %2%")
                            .arg(monthlyPercentage, 0, 'f', 2)
                            .arg(weeklyPercentage, 0, 'f', 2);

    // This can be connected to UI later
    qDebug() << message;
}

double AttendanceLog::_getAttendancePercentage()const
{
    // Define required hours per week
    const double requiredHours = 8.0;

    // Step 1: Sort the entries based on date
    std::vector<AttendanceEntry> sortedEntries = attEntries;  // Create a copy to sort
    std::sort(sortedEntries.begin(), sortedEntries.end(), [](const AttendanceEntry& a, const AttendanceEntry& b) {
        return a._getDate() < b._getDate();  // Sort based on the date string
    });

    // Step 2: Calculate total hours worked
    double totalHours = 0;
    double totalPossibleHours = 0;

    for (const auto& entry : sortedEntries)
    {
        // Only count attendance if the attendance value is "1", "EL", or "OL"
        if (entry._isPresent() == "1" || entry._isPresent()== "EL" || entry._isPresent()== "OL")
        {
            totalHours += entry._getHours();  // Count the hours worked
        }

        // Always increment total possible hours
        totalPossibleHours += requiredHours;  // Assuming 8 hours required per entry (or week)
    }

    // Step 3: Calculate the percentage
    if (totalPossibleHours == 0)
    {
        return 0;  // Avoid division by zero
    }

    // Return the attendance percentage
    return (totalHours / totalPossibleHours) * 100;
}

double AttendanceLog::_calculatePercentageForDateRange(const QDate& startDate, const QDate& endDate) const {
    double totalHours = 0;
    int workingDays = 0;

    for (const auto& entry : attEntries) {
        QDate entryDate = QDate::fromString(entry._getDate(), "yyyy/MM/dd");

        if (entryDate >= startDate && entryDate <= endDate) {
            // Count only weekdays (Monday to Friday)
            if (entryDate.dayOfWeek() <= 5) {
                workingDays++;
                totalHours += entry._getHours();
            }
        }
    }

    // Expected hours = workingDays * 8 hours
    double expectedHours = workingDays * 8.0;
    if (expectedHours == 0) return 0.0;

    // Calculate percentage (can be over 100%)
    return (totalHours / expectedHours) * 100.0;
}
double AttendanceLog::_getMonthlyAttendancePercentage(const QDate& date) const {
    QDate startOfMonth(date.year(), date.month(), 1);
    QDate endOfMonth(date.year(), date.month(), date.daysInMonth());

    return _calculatePercentageForDateRange(startOfMonth, endOfMonth);
}
double AttendanceLog::_getWeeklyAttendancePercentage(const QDate& date) const {

    QDate startOfWeek = date.addDays(-(date.dayOfWeek() - 1));

    QDate endOfWeek = startOfWeek.addDays(4);

    return _calculatePercentageForDateRange(startOfWeek, endOfWeek);
}

double AttendanceLog::_calculatePercentageForDateRange(const QDate& startDate, const QDate& endDate) const {
    double totalHours = 0;
    int workingDays = 0;
    
    for (const auto& entry : attEntries) {
        QDate entryDate = QDate::fromString(entry._getDate(), "yyyy/MM/dd");
        
        if (entryDate >= startDate && entryDate <= endDate) {
            // Count only weekdays (Monday to Friday)
            if (entryDate.dayOfWeek() <= 5) {
                workingDays++;
                totalHours += entry._getHours();
            }
        }
    }
    
    // Expected hours = workingDays * 8 hours
    double expectedHours = workingDays * 8.0;
    if (expectedHours == 0) return 0.0;
    
    // Calculate percentage (can be over 100%)
    return (totalHours / expectedHours) * 100.0;
}

double AttendanceLog::_getMonthlyAttendancePercentage(const QDate& date) const {
    QDate startOfMonth(date.year(), date.month(), 1);
    QDate endOfMonth(date.year(), date.month(), date.daysInMonth());
    
    return _calculatePercentageForDateRange(startOfMonth, endOfMonth);
}

double AttendanceLog::_getWeeklyAttendancePercentage(const QDate& date) const {
  
    QDate startOfWeek = date.addDays(-(date.dayOfWeek() - 1));
   
    QDate endOfWeek = startOfWeek.addDays(4);
    
    return _calculatePercentageForDateRange(startOfWeek, endOfWeek);
}





