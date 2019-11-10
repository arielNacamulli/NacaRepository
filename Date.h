//
// Created by ariel on 07/11/2019.
//

#ifndef DATECLASS_DATE_H
#define DATECLASS_DATE_H

#include<iostream>

using std::string;

enum yearF {ACT365 = 1, ACT360, E30_360};
enum dateFormat {ddmmyyyy, ddmmyyyy_, mmddyyyy, mmddyyyy_};

class Date {
private:
    unsigned day;
    unsigned month;
    unsigned year;

public:
    // Getters and Setters
    unsigned int getDay() const;
    void setDay(unsigned int day);
    unsigned int getMonth() const;
    void setMonth(unsigned int month);
    unsigned int getYear() const;
    void setYear(unsigned int year);

    // Constructor
    Date(unsigned int day, unsigned int month, unsigned int year);
    explicit Date(const string &s, unsigned format = ddmmyyyy);
    explicit Date(unsigned int num);

    // Utilities
    bool isLeap(unsigned int _year) const;
    bool isLeap() const;
    void print() const;

    unsigned int daysInMonth(unsigned int _month, unsigned int _year) const;

    unsigned int date2num() const;

    // Operators
    Date operator+ (unsigned int days) const;
    int operator- (const Date &rhs) const;
    bool operator> (const Date &rhs) const;
    bool operator< (const Date &rhs) const;
    bool operator== (const Date &rhs) const;
    bool operator!= (const Date &rhs) const;
    bool operator>= (const Date &rhs) const;
    bool operator<= (const Date &rhs) const;
};

Date num2date(unsigned int num);

double act365(const Date &startDate, const Date &endDate);

double act360(const Date &startDate, const Date &endDate);

double yearfrac(const Date &startDate, const Date &endDate, unsigned flag);

double e30vs360(const Date &startDate, const Date &endDate);

Date string2date(const string &s, unsigned format);

#endif //DATECLASS_DATE_H
