#include <iostream>
using namespace std;

class Date {
private:
    int day, month, year;
    int* daysInMonth;

    void initializeDaysInMonth() {
        daysInMonth = new int[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (isLeapYear()) daysInMonth[1] = 29;
    }

    bool isLeapYear() const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

public:
    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {
        initializeDaysInMonth();
    }

    ~Date() {
        delete[] daysInMonth;
    }

    void incrementDay() {
        day++;
        if (day > daysInMonth[month - 1]) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
                initializeDaysInMonth();
            }
        }
    }

    Date& operator++() {
        incrementDay();
        return *this;
    }

    Date operator++(int) {
        Date temp = *this;
        incrementDay();
        return temp;
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    bool operator!=(const Date& other) const {
        return !(*this == other);
    }

    bool operator>(const Date& other) const {
        if (year != other.year) 
            return year > other.year;
        if (month != other.month) 
            return month > other.month;
        return day > other.day;
    }

    int getDay() const { 
        return day; }
    int getMonth() const { 
        return month; }
    int getYear() const {
        return year; }

    istream& read(istream& in) {
        char delim;
        in >> day >> delim >> month >> delim >> year;
        initializeDaysInMonth();
        return in;
    }
};

istream& operator>>(istream& in, Date& date) {
    return date.read(in);
}

void printDate(const Date& date) {
    cout << (date.getDay() < 10 ? "0" : "") << date.getDay() << "."
        << (date.getMonth() < 10 ? "0" : "") << date.getMonth() << "."
        << date.getYear();
}

int main() {
    Date date1(31, 12, 2023), date2;
    cout << "Enter date: ";
    cin >> date2;

    cout << "Date 1: ";
    printDate(date1);
    cout << endl;

    cout << "Date 2: ";
    printDate(date2);
    cout << endl;

    if (date1 == date2) cout << "Dates equal.\n";
    else if (date1 > date2) cout << "Date 1 greater.\n";
    else cout << "Date 1 smaller.\n";

    ++date1;
    cout << "Date 1 increment: ";
    printDate(date1);
    cout << endl;
}
