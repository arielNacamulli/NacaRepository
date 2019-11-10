//
// Created by ariel on 07/11/2019.
//

#include "Date.h"
#include <limits>
#include <string>

#define REFDAY 1
#define REFMONTH 1
#define REFYEAR 1900

using std::stoi;

Date::Date(unsigned int _day, unsigned int _month, unsigned int _year) : day(_day), month(_month), year(_year) {
    if(day > daysInMonth(_month,_year))
        std::cerr << "Month " << month << " doesn't have " << day << " days!" << std::endl;
}

Date::Date(const string &s, unsigned format) {
    switch(format) {
        case ddmmyyyy_:
            day = stoi(s.substr(0, 2));
            month = stoi(s.substr(3, 2));
            year = stoi(s.substr(6));
        case mmddyyyy:
            month = stoi(s.substr(0, 2));
            day = stoi(s.substr(2, 2));
            year = stoi(s.substr(4));

        case mmddyyyy_:
            month = stoi(s.substr(0, 2));
            day = stoi(s.substr(3, 2));
            year = stoi(s.substr(6));
        default:
            day = stoi(s.substr(0, 2));
            month = stoi(s.substr(2, 2));
            year = stoi(s.substr(4));
    }

    if(day > daysInMonth(month,year))
        std::cerr << "Month " << month << " doesn't have " << day << " days!" << std::endl;

}

Date::Date(unsigned int num) {
    Date tempDate = Date(REFDAY,REFMONTH,REFYEAR) + num;
    day = tempDate.day;
    month = tempDate.month;
    year = tempDate.year;
}

unsigned int Date::daysInMonth(unsigned int _month, unsigned int _year) const {
    if (_month > 12){
        std::cerr << "Month " << _month << " doesn't exist" << std::endl;
        return 0;}
    if (_month == 1 || _month == 3 || _month == 5 || _month == 7 || _month == 8 || _month == 10 || _month == 12)
        return 31;
    if (_month == 2)
        return 28 + isLeap(_year);
    return 30;
}

unsigned int Date::getDay() const {
    return day;
}

void Date::setDay(unsigned int _day) {
    Date::day = _day;
}

unsigned int Date::getMonth() const {
    return month;
}

void Date::setMonth(unsigned int _month) {
    Date::month = _month;
}

unsigned int Date::getYear() const {
    return year;
}

void Date::setYear(unsigned int _year) {
    Date::year = _year;
}

bool Date::isLeap(unsigned int _year) const {
    return !(_year%1000) || (!(_year%4) && (_year%100));
}

bool Date::isLeap() const {
    return isLeap(year);
}

void Date::print() const {
    std::cout<<day<<'-'<<month<<'-'<<year<<std::endl;
}

unsigned int Date::date2num() const{
    // ref date is 01-01-1900 -> datenum(refDate) = 0
    if (year < REFYEAR){
        std::cerr << "Year must be at least " << REFYEAR << ", it is " << year << std::endl;
        return 0;
    }
    unsigned int leaps = 0;

    for (size_t i = REFYEAR; i< year; i++)
        leaps += isLeap(i); // add 1 for each leap year, easier than analytically

    unsigned num = (year - REFYEAR)*365 + leaps;

    for(size_t i = 1; i < month; i++)
        num += daysInMonth(i,year);

    return num + (day-1); // so datenum(refDate) = 0

}

Date Date::operator+(unsigned int days) const {

    if (days<=daysInMonth(month,year) - day)
        return Date(day + days, month, year);
    days = days + day - daysInMonth(month,year);

    unsigned resMonth = month%12+1;;
    unsigned resYear = year + (resMonth == 1);
    while(days>daysInMonth(resMonth,resYear)) {
        days-=daysInMonth(resMonth,resYear);
        resMonth = resMonth%12 + 1;
        resYear = resYear + (resMonth == 1);
    }
    return Date(days, resMonth, resYear);
}

int Date::operator-(const Date &rhs) const {
    return date2num() - rhs.date2num();
}

bool Date::operator>(const Date &rhs) const{
    return date2num() > rhs.date2num();
}

bool Date::operator<(const Date &rhs) const{
    return date2num() < rhs.date2num();
}

bool Date::operator>=(const Date &rhs) const{
    return date2num() >= rhs.date2num();
}

bool Date::operator<=(const Date &rhs) const{
    return date2num() <= rhs.date2num();
}

bool Date::operator==(const Date &rhs) const{
    return date2num() == rhs.date2num();
}

bool Date::operator!=(const Date &rhs) const{
    return date2num() != rhs.date2num();
}

Date num2date(unsigned int num) {
    return Date(1, 1, 1900) + num;
}

double act360(const Date &startDate, const Date &endDate) {
    if(endDate < startDate){
        std::cerr << "Interval must be positive!" << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }
    return (endDate - startDate) / 360.0;
}

double act365(const Date &startDate, const Date &endDate) {
    if(endDate < startDate){
        std::cerr << "Interval must be positive!" << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }
    return (endDate - startDate) / 365.0;
}

double e30vs360(const Date &startDate, const Date &endDate) {
    if(endDate < startDate){
        std::cerr << "Interval must be positive!" << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }
    unsigned int d1 = startDate.getDay();
    unsigned int d2 = startDate.getDay();
    d1 -= d1==31;
    d2 -= d2==31;

    return (endDate.getYear() - startDate.getYear()) + (endDate.getMonth() - startDate.getMonth())/12.0 + (d2 - d1)/360.0 ;
}

double yearfrac(const Date &startDate, const Date &endDate, unsigned flag = 0){
    switch (flag) {
        case ACT365:
            return act365(startDate, endDate);
        case ACT360:
            return act360(startDate,endDate);
        case E30_360:
            return e30vs360(startDate,endDate);
        default:
            return endDate-startDate;
    }
}

Date string2date(const string &s, unsigned format = ddmmyyyy){
    return Date(s,format);
}
