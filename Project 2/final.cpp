// Elias Woldie
// Class (CECS 342-07)
// Project Name (Prog 1 – Fibonacci Race)
// 10/03/2023
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <string>
using namespace std;

class Date
{
private:
    int *dateArray;       // Pointer to dynamic array holding [month, day, year]
    static int dateCount; // Static member to track number of Date objects created

    // Determines whether a given year is a leap year.
    bool isLeapYear(int year) const
    {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // Returns the number of days in a given month for a specified year.
    int daysInMonth(int month, int year) const
    {
        const int days[] = {0, 31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return days[month];
    }

    // Validates if the given date components represent a valid date.
    bool isValidDate(int M, int D, int Y) const
    {
        return M >= 1 && M <= 12 && D >= 1 && D <= daysInMonth(M, Y);
    }

public:

    // Converts the Gregorian date to Julian date
    int g2j() const
    {
        int Y = dateArray[2];
        int M = dateArray[0];
        int D = dateArray[1];
        return D - 32076 + 1461 * (Y + 4800 + (M - 14) / 12) / 4 + 367 * (M - 2 - (M - 14) / 12 * 12) / 12 - 3 * ((Y + 4900 + (M - 14) / 12) / 100) / 4;
    }

    // Converts a Julian date to Gregorian date
    void j2g(int JD)
    {
        int l, n, i, j;
        l = JD + 68569;
        n = 4 * l / 146097;
        l = l - (146097 * n + 3) / 4;
        i = 4000 * (l + 1) / 1461001;
        l = l - 1461 * i / 4 + 31;
        j = 80 * l / 2447;
        dateArray[1] = l - 2447 * j / 80;
        l = j / 11;
        dateArray[0] = j + 2 - 12 * l;
        dateArray[2] = 100 * (n - 49) + i + l;
    }

    // Default constructor initializing to (01/01/1970)
    Date()
    {
        dateArray = new int[3];
        dateArray[0] = 1;
        dateArray[1] = 1;
        dateArray[2] = 1970;
        dateCount++;
    }

    // Constructor that initializes date with provided values
    Date(int M, int D, int Y)
    {
        dateArray = new int[3];
        if (isValidDate(M, D, Y))
        {
            dateArray[0] = M;
            dateArray[1] = D;
            dateArray[2] = Y;
        }
        else
        {
            dateArray[0] = 1;
            dateArray[1] = 1;
            dateArray[2] = 1970;
        }
        dateCount++;
    }

    // Constructor that initializes date from a Julian date
    Date(int J)
    {
        dateArray = new int[3];
        j2g(J);
        dateCount++;
    }

    // Return the Julian date representation
    int julian() const
    {
        return g2j();
    }

    // Copy constructor
    Date(const Date &d)
    {
        dateArray = new int[3];
        dateArray[0] = d.dateArray[0];
        dateArray[1] = d.dateArray[1];
        dateArray[2] = d.dateArray[2];
        dateCount++;
    }

    // Destructor to free dynamically allocated memory
    ~Date()
    {
        delete[] dateArray;
        dateCount--;
    }
    
    // Assignment operator
    Date &operator=(const Date &d)
    {
        if (this != &d)
        {
            dateArray[0] = d.dateArray[0];
            dateArray[1] = d.dateArray[1];
            dateArray[2] = d.dateArray[2];
        }
        return *this;
    }

    // Add days to date
    Date operator+(int days) const
    {
        Date temp(*this);
        while (days--)
        {
            ++temp;
        }
        return temp;
    }

    // Subtract days from date
    Date operator-(int days) const
    {
        Date temp(*this);
        while (days--)
        {
            --temp;
        }
        return temp;
    }

    // Prefix increment operator 
    Date &operator++()
    { 
        dateArray[1]++;
        if (dateArray[1] > daysInMonth(dateArray[0], dateArray[2]))
        {
            dateArray[1] = 1;
            dateArray[0]++;
            if (dateArray[0] > 12)
            {
                dateArray[0] = 1;
                dateArray[2]++;
            }
        }
        return *this;
    }

    // Postfix increment operator 
    Date operator++(int)
    { // Postfix
        Date tmp(*this);
        ++(*this);
        return tmp;
    }

    // Prefix decrement operator 
    Date &operator--()
    { // Prefix
        dateArray[1]--;
        if (dateArray[1] < 1)
        {
            dateArray[0]--;
            if (dateArray[0] < 1)
            {
                dateArray[0] = 12;
                dateArray[2]--;
            }
            dateArray[1] = daysInMonth(dateArray[0], dateArray[2]);
        }
        return *this;
    }

    // Postfix decrement operator 
    Date operator--(int)
    { // Postfix
        Date tmp(*this);
        --(*this);
        return tmp;
    }

    // Static function to return the count of Date objects
    static int count()
    {
        return dateCount;
    }

    // Getter functions for day, month, and year
    int getDay() const { return dateArray[1]; }
    int getMonth() const { return dateArray[0]; }
    int getYear() const { return dateArray[2]; }

    // Getter functions for month name
    string getMonthName() const
    {
        const string months[] = {
            "Invalid Month", "January", "February", "March", "April",
            "May", "June", "July", "August", "September",
            "October", "November", "December"};
        return months[getMonth()]; 
    }

    // Getter functions for day name
    string getDayName() const
    {
        string day_name[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        int JD = julian();
        int day = JD % 7;
        return day_name[day];
    }
};

// Overloaded comparison operators
bool operator>(const Date &lhs, const Date &rhs)
{
    return lhs.g2j() > rhs.g2j();
}

bool operator<(const Date &lhs, const Date &rhs)
{
    return lhs.g2j() < rhs.g2j();
}

bool operator==(const Date &lhs, const Date &rhs)
{
    return lhs.g2j() == rhs.g2j();
}

// Overloaded arithmetic operators
Date operator+(int days, const Date &d)
{
    return d + days;
}
int operator-(const Date &lhs, const Date &rhs)
{
    // Use your G2J function to get the Julian dates
    return lhs.g2j() - rhs.g2j();
}

// Overloaded output stream operator to print date in MM/DD/YYYY format
std::ostream &operator<<(std::ostream &os, const Date &date)
{
    os << date.getMonth() << "/" << date.getDay() << "/" << date.getYear();
    return os;
}

// Initialize static member
int Date::dateCount = 0;

int main()
{
    Date epoch;
    Date duedate(10, 3, 2023);
    Date today(duedate);
    cout << endl;
    cout << "Today is " << today << endl;
    cout << "This program is due on " << duedate;
    cout << endl;
    cout << "(3)Right now there are " << Date::count() << " Date objects\n";
    {
        Date d1, d2, d3;
        cout << "(6)Inside this block there are " << Date::count() << " Date objects\n";
    }
    cout << "(3)Outside the block there are " << Date::count() << " Date objects\n";
    Date dtemp(duedate);
    dtemp++;
    cout << "If you turn this assignment in on " << dtemp << " then is will be late.\n";
    cout << "It is due on " << --dtemp << " so don't be late.\n";
    cout << "One week from due date is " << duedate + 7 << endl;
    cout << "One week from due date is " << 7 + duedate << endl;
    cout << "One week earlier from due date is " << duedate - 7 << endl;
    cout << "The Unix Epoch date is " << epoch << " : ";
    cout << "The Epoch date was " << duedate - epoch << " days ago\n";
    cout << "Today is Julian date " << duedate.julian() << endl;
    ;
    cout << "Tomorrrow is Julian date " << (++duedate).julian() << endl;
    ;
    cout << "The very first Julian date was " << Date(10, 3, 2023) - Date(10, 3, 2023).julian() << endl;
    cout << "The very first Julian date was " << today - today.julian() << endl;
    Date yesterday, tomorrow;
    yesterday = today - 1;
    tomorrow = today + 1;
    cout << "Yesterday was " << yesterday << endl;
    cout << "Today is " << today << endl;
    cout << "Tomorrow is " << tomorrow << endl;
    cout << "Today is ";
    cout << ((today > tomorrow) ? "greater than" : "not greater than");
    cout << " than tomorrow\n";
    cout << "Today is ";
    cout << ((today < tomorrow) ? "less than" : "not less than");
    cout << " than tomorrow\n";
    cout << "Today is ";
    cout << ((today == tomorrow) ? "equal to" : "not equal to");
    cout << " tomorrow\n";
    getchar();
    return 0;
}