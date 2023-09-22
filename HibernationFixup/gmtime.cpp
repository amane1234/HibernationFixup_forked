// gmtime.cpp
// HibernationFixup

#include <stdint.h>
#include <sys/time.h>
#include <stddef.h>

#include "gmtime.h"

// Function to check if a year is a leap year
bool isLeapYear(int year) {
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

// Function to get the number of days in a year
int daysInYear(int year) {
    return isLeapYear(year) ? 366 : 365;
}

// Function to get the number of days in a specific month of a year
int daysInMonth(int month, int year) {
    static int days[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month];
}

// Function to reduce days to the year and update the year parameter
int reduceDaysToYear(time_t &days, int &year) {
    for (year = 1970; days >= daysInYear(year); year++) {
        days -= daysInYear(year);
    }
    return year;
}

// Function to reduce days to months and update the month parameter
int reduceDaysToMonths(time_t &days, int year, int &month) {
    for (month = 0; days >= daysInMonth(month, year); month++) {
        days -= daysInMonth(month, year);
    }
    return month;
}

// Function to convert time in seconds since epoch to a broken-down time structure
struct tm *gmtime_r(time_t timer, struct tm *timeptr) {
    timeptr->tm_sec = timer % 60;
    timer /= 60;
    timeptr->tm_min = timer % 60;
    timer /= 60;
    timeptr->tm_hour = timer % 24;
    timer /= 24;

    int year, month;
    timeptr->tm_year = reduceDaysToYear(timer, year);
    timeptr->tm_mon = reduceDaysToMonths(timer, year, month);
    timeptr->tm_mday = static_cast<int>(timer);

    return timeptr;
}
