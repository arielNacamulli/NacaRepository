//
// Created by ariel on 08/11/2019.
//

#include "DiscountCurve.h"

#define NUMFUTURES 7

DiscountCurve::DiscountCurve(const Date &_settDate, const vector<Date> &dDates,const vector<double> &dPrices,
                             const vector<Date> &fDates, const vector<double> &fPrices,const vector<Date> &sDates,
                             const vector<double> &sPrices):
                             depoDates(dDates),depoPrices(dPrices),futuresDates(fDates),futuresPrices(fPrices),
                             swapDates(sDates),swapPrices(sPrices), settDate(_settDate){}

curve DiscountCurve::bootstrap() const{
    curve res;
    res.dates.push_back(settDate);
    res.discounts.push_back(1.0);
    res.zRates.push_back(0.0);

    // Depos
    for (size_t i = 0;i < depoDates.size() && depoDates[i] < futuresDates.front(); i++){
        res.discounts.push_back(libor2discount(depoPrices[i],settDate,depoDates[i]));
        res.dates.push_back(depoDates[i]);
        res.zRates.push_back(discount2rate(res.discounts.back(),yearfrac(settDate,res.dates.back(),ACT365)));
    }

    // Futures
    for (size_t i = 0; i < NUMFUTURES; i++){
        double fwdDiscount = rate2discount(futuresPrices[i],yearfrac(futuresDates[i],futuresDates[i+1], ACT360));
        double test = yearfrac(futuresDates[i],futuresDates[i+1], ACT360);
        double initialDiscount = interpolDiscount(res.dates,res.zRates,futuresDates[i]);
        res.discounts.push_back(fwdDiscount * initialDiscount);
        res.dates.push_back(futuresDates[i+1]);
        std::cout<<yearfrac(settDate,res.dates.back(),ACT365)<<std::endl;

        res.zRates.push_back(discount2rate(res.discounts.back(),yearfrac(settDate,res.dates.back(),ACT365)));
    }

    // Swaps
    curve temp;
    temp.dates.push_back(settDate); temp.discounts.push_back(1); temp.zRates.push_back(0);
    temp.discounts.push_back(interpolDiscount(res.dates,res.zRates,swapDates.front()));
    temp.dates.push_back(swapDates.front());
    temp.zRates.push_back(discount2rate(res.discounts.back(),yearfrac(settDate,res.dates.back(),ACT365)));

    for (size_t i = 1; i < swapDates.size(); i++){
        swapDiscount(temp.discounts, temp.dates, i);
        temp.dates.push_back(swapDates[i]);
        temp.zRates.push_back(discount2rate(temp.discounts.back(),yearfrac(settDate,temp.dates.back(),ACT365)));
    }

    res.dates.insert(res.dates.end(),temp.dates.begin()+2,temp.dates.end());
    res.discounts.insert(res.discounts.end(),temp.discounts.begin()+2,temp.discounts.end());
    res.zRates.insert(res.zRates.end(),temp.zRates.begin()+2,temp.zRates.end());

    return res;
}

void DiscountCurve::swapDiscount(vector<double> &disc, const vector<Date> &dates, size_t idx) const {
    double sum = 0;
    for (size_t i = 1; i <= idx; i++)
        sum += yearfrac(dates[i-1],dates[i],E30_360) * disc[i];

    double discount = (1 - sum*swapPrices[idx]) / (1 + swapPrices[idx]*yearfrac(dates[idx-1],dates[idx],E30_360));
    disc.push_back(discount);
}


double rate2discount(double r, double T){
    return exp(-r*T);
}
double discount2rate(double B, double T){
    return -log(B)/T;
}

vector<double> rate2discount(const vector<double> &r, const Date &settDate, const vector<Date> &dates){
    vector <double> Discount;
    for (size_t i = 0; i < r.size(); i++) {
        double T = yearfrac(settDate,dates[i],ACT365);
        Discount.push_back(exp(-r[i] * T));
    }
    return Discount;
}
vector <double> discount2rate(const vector<double> &B, const Date &settDate, const vector<Date> &dates){
    vector <double> r;
    for (size_t i = 0; i < B.size(); i++) {
        double T = yearfrac(settDate,dates[i],ACT365);
        T == 0 ? r.push_back(0) : r.push_back(-log(B[i]) / T);
    }

    return r;
}

double interp1(const vector<Date> &x, const vector<double> &y, const Date &xstar){
    auto it = findInterval(x,xstar);
    if (it != x.end())
        return y[it-x.begin()] + (y[it-x.begin() + 1] - y[it-x.begin()])/(*(it+1) - *it) * (xstar - *it);
    else // extrpolation
        return y.back() + (y.back() - *(y.end()-2))/(x.back() - *(x.end()-2)) * (xstar - x.back());
}

double interpolDiscount(const vector<Date> &dates, const vector<double> &rates, const Date &date){
    double T = yearfrac(dates.front(),date,ACT365);
    double r = interp1(dates,rates,date);
    return rate2discount(r,T);
}

vector<double>::const_iterator findInterval(const vector<double> &x, double x0){
    if (x0 < x.front() || x0 > x.back())
        return x.end();
    for (auto i = x.begin(); i < x.end() - 1; i++){
        if (x0 < *(i+1))
            return i;
    }
    return x.end(); // shouldn't be reached
}

double libor2discount(double L, const Date &sett, const Date &date){
    return 1/(1 + yearfrac(sett,date,ACT360)*L);
}

double interp1(const vector<double> &x,const vector<double> &y, double xstar){
    auto it = findInterval(x,xstar);

    return y[it-x.begin()] + (y[it-x.begin() + 1] - y[it-x.begin()])/(*(it+1) - *it) * (xstar - *it);
}

vector<Date>::const_iterator findInterval(const vector<Date> &x, Date x0){
    if (x0 < x.front() || x0 > x.back())
        return x.end();
    for (auto i = x.begin(); i < x.end() - 1; i++){
        if (x0 < *(i+1))
            return i;
    }
    return x.end(); // shouldn't be reached
}
