// Date.h

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

using namespace std;

class Date
{
private:
    int *dateArray;       // Pointer to dynamic array holding [month, day, year]
    static int dateCount; // Static member to track number of Date objects created

    // Determines whether a given year is a leap year.
    bool isLeapYear(int year) const;

    // Returns the number of days in a given month for a specified year.
    int daysInMonth(int month, int year) const;

    // Validates if the given date components represent a valid date.
    bool isValidDate(int M, int D, int Y) const;

public:
    // Converts the Gregorian date to Julian date
    int g2j() const;

    // Converts a Julian date to Gregorian date
    void j2g(int JD);

    // Default constructor initializing to (01/01/1970)
    Date();

    // Constructor that initializes date with provided values
    Date(int M, int D, int Y);

    // Constructor that initializes date from a Julian date
    Date(int J);

    // Return the Julian date representation
    int julian() const;

    // Copy constructor
    Date(const Date &d);

    // Destructor to free dynamically allocated memory
    ~Date();

    // Assignment operator
    Date &operator=(const Date &d);
    // Add days to date
    Date operator+(int days) const;
    // Subtract days from date
    Date operator-(int days) const;
    // Prefix increment operator
    Date &operator++();
    // Postfix increment operator
    Date operator++(int);
    // Prefix decrement operator
    Date &operator--();
    // Postfix decrement operator
    Date operator--(int);

    // Static function to return the count of Date objects
    static int count();

    // Getter functions for day, month, and year
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    // Getter functions for month name
    string getMonthName() const;
    // Getter functions for day name
    string getDayName() const;
};

// Overloaded comparison operators 
bool operator>(const Date &lhs, const Date &rhs);
bool operator<(const Date &lhs, const Date &rhs);
bool operator==(const Date &lhs, const Date &rhs);

// Overloaded arithmetic operators
Date operator+(int days, const Date &d);
int operator-(const Date &lhs, const Date &rhs);

// Overloaded output stream operator to print date in MM/DD/YYYY format
ostream &operator<<(ostream &os, const Date &date);

#endif
