#include "Date.h"

// Static member initialization
int Date::dateCount = 0;

// Private member functions
bool Date::isLeapYear(int year) const
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::daysInMonth(int month, int year) const
{
    const int days[] = {0, 31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[month];
}

bool Date::isValidDate(int M, int D, int Y) const
{
    return M >= 1 && M <= 12 && D >= 1 && D <= daysInMonth(M, Y);
}

// Public member functions
int Date::g2j() const
{
    int Y = dateArray[2];
    int M = dateArray[0];
    int D = dateArray[1];
    return D - 32076 + 1461 * (Y + 4800 + (M - 14) / 12) / 4 + 367 * (M - 2 - (M - 14) / 12 * 12) / 12 - 3 * ((Y + 4900 + (M - 14) / 12) / 100) / 4;
}

void Date::j2g(int JD)
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

Date::Date()
{
    dateArray = new int[3];
    dateArray[0] = 1;
    dateArray[1] = 1;
    dateArray[2] = 1970;
    dateCount++;
}

Date::Date(int M, int D, int Y)
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

Date::Date(int J)
{
    dateArray = new int[3];
    j2g(J);
    dateCount++;
}

int Date::julian() const
{
    return g2j();
}

Date::Date(const Date &d)
{
    dateArray = new int[3];
    dateArray[0] = d.dateArray[0];
    dateArray[1] = d.dateArray[1];
    dateArray[2] = d.dateArray[2];
    dateCount++;
}

Date::~Date()
{
    delete[] dateArray;
    dateCount--;
}

Date &Date::operator=(const Date &d)
{
    if (this != &d)
    {
        dateArray[0] = d.dateArray[0];
        dateArray[1] = d.dateArray[1];
        dateArray[2] = d.dateArray[2];
    }
    return *this;
}

Date Date::operator+(int days) const
{
    Date temp(*this);
    while (days--)
    {
        ++temp;
    }
    return temp;
}

Date Date::operator-(int days) const
{
    Date temp(*this);
    while (days--)
    {
        --temp;
    }
    return temp;
}

Date &Date::operator++()
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

Date Date::operator++(int)
{
    Date tmp(*this);
    ++(*this);
    return tmp;
}

Date &Date::operator--()
{
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

Date Date::operator--(int)
{
    Date tmp(*this);
    --(*this);
    return tmp;
}

int Date::count()
{
    return dateCount;
}

int Date::getDay() const
{
    return dateArray[1];
}

int Date::getMonth() const
{
    return dateArray[0];
}

int Date::getYear() const
{
    return dateArray[2];
}

string Date::getMonthName() const
{
    const string months[] = {
        "Invalid Month", "January", "February", "March", "April",
        "May", "June", "July", "August", "September",
        "October", "November", "December"};
    return months[getMonth()];
}

string Date::getDayName() const
{
    string day_name[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    int JD = julian();
    int day = JD % 7;
    return day_name[day];
}

// Overloaded global operators
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

Date operator+(int days, const Date &d)
{
    return d + days;
}

int operator-(const Date &lhs, const Date &rhs)
{
    return lhs.g2j() - rhs.g2j();
}

std::ostream &operator<<(std::ostream &os, const Date &date)
{
    os << date.getMonth() << "/" << date.getDay() << "/" << date.getYear();
    return os;
}