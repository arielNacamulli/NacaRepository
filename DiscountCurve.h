//
// Created by ariel on 08/11/2019.
//

#ifndef DATECLASS_DISCOUNTCURVE_H
#define DATECLASS_DISCOUNTCURVE_H

//#include "Discounts.cpp"
//#include "Date.h"
//#include <vector>
#include <cmath>
#include <vector>
#include "Date.h"

using std::vector;

struct curve {
    vector<Date> dates;
    vector<double> discounts;
    vector<double> zRates;
};

class DiscountCurve {
private:
    vector<Date> depoDates;
    vector<double> depoPrices;
    vector<Date> futuresDates;
    vector<double> futuresPrices;
    vector<Date> swapDates;
    vector<double> swapPrices;
    Date settDate;

public:
    DiscountCurve(const Date &_settDate, const vector<Date> &dDates,const vector<double> &dPrices,const vector<Date> &fDates,
                  const vector<double> &fPrices,const vector<Date> &sDates,const vector<double> &sPrices);

    curve bootstrap() const;
    void swapDiscount(vector <double> &disc, const vector<Date> &dates, size_t idx) const;

};

double rate2discount(double r, double T);
double discount2rate(double B, double T);
double interp1(const vector<double> &x,const vector<double> &y, double xstar);
vector<double>::const_iterator findInterval(const vector<double> &x, double x0);
double libor2discount(double L, const Date &sett, const Date &date);
double interp1(const vector<Date> &x,const vector<double> &y, const Date &xstar);
vector<Date>::const_iterator findInterval(const vector<Date> &x, Date x0);
vector<double> rate2discount(const vector<double> &r, const Date &settDate, const vector<Date> &dates);
vector <double> discount2rate(const vector<double> &B, const Date &settDate, const vector<Date> &dates);
double interpolDiscount(const vector<Date> &dates, const vector<double> &rates, const Date &date);


#endif //DATECLASS_DISCOUNTCURVE_H
