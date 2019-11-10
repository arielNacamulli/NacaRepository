#include <iostream>
#include "DiscountCurve.h"

int main() {
    /*
    Date data(9,06,1995);
    data.print();
    unsigned num = data.date2num();
    num2date(num).print();

    Date data2 = data + 100;
    data2.print();

    string s = "09061995";

    Date data3(s,ddmmyyyy);

    data3.print();


    std::cout << std::stoi(s.substr(0,2)) << std::endl;

    vector <double> a = {1,2,3,4};
    vector <double> b = {1,3,5,7};
    double c = interp1(a,b,2.1);
    */

    double r = 0.01;

    double B = rate2discount(r,1);

    std::cout << B << std::endl;

    vector<Date> Ddates = {Date(20,02,2008), Date(26,02,2008), Date(19,03,2008),
                          Date(21,04,2008), Date(19,05,2008),Date(19,8,2008),
                          Date(19,11,2008), Date(19,2,2009)};
    Date settDate = Date(19,02,2008);

    vector<double> Dprices = {0.0401,0.0407,0.0415,0.0424,0.0433,0.0432,0.0432,0.0432};

    vector<Date> FDates = {Date(17,03,2008), Date(16,6,2008), Date(15,9,2008),
                           Date(15,12,2008), Date(16,03,2009), Date(15,6,2009),
                           Date(14,9,2009), Date(14,12,2009)};
    vector<double> FPrices = {0.043175,0.039325,0.036275,0.034725,0.033925,0.03425,0.035075,0.0363};




    vector<Date> SDates = {Date(19,2,2009),Date(19,2,2010),Date(21,2,2011),Date(20,2,2012),Date(19,2,2013),Date(19,2,2014),Date(19,2,2015),Date(19,2,2016),
                           Date(20,2,2017),Date(19,2,2018),Date(19,2,2019),Date(19,2,2020),Date(19,2,2021),Date(21,2,2022),Date(20,2,2023),Date(19,2,2024),
                           Date(19,2,2025),Date(19,2,2026),Date(19,2,2027),Date(21,2,2028),Date(19,2,2029),Date(19,2,2030),Date(19,2,2031),Date(19,2,2032),
                           Date(21,2,2033),Date(20,2,2034),Date(19,2,2035),Date(19,2,2036),Date(19,2,2037),Date(19,2,2038),Date(21,2,2039),Date(20,2,2040),
                           Date(19,2,2041),Date(19,2,2042),Date(19,2,2043),Date(19,2,2044),Date(20,2,2045),Date(19,2,2046),Date(19,2,2047),Date(19,2,2048),
                           Date(19,2,2049),Date(21,2,2050),Date(20,2,2051),Date(19,2,2052),Date(19,2,2053),Date(19,2,2054),Date(19,2,2055),Date(21,2,2056),
                           Date(19,2,2057),Date(19,2,2058)};

    vector<double> SPrices = {0.0413,0.038715,0.03892,0.03958,0.04042,0.04127,0.04212,0.04293,0.04367,0.04434,0.04493,
                              0.04544,0.04587727,0.046249296,0.04656,0.046819707,0.04703513,0.047,0.047,0.04746,0.047545113,
                              0.04760858,0.04765238,0.04767876,0.04769,0.047688145,0.047675354,0.047653459,0.047624313,
                              0.04759,0.047551901,0.047511215,0.047467933,0.047422577,0.047375563,0.047327305,0.047277948,
                              0.047228582,0.047179083,0.04713,0.047081534,0.047033692,0.046986904,0.046940695,0.046894732,
                              0.046849311,0.046804223,0.046759139,0.046714589,0.04667};


    DiscountCurve ciao(settDate, Ddates, Dprices, FDates, FPrices, SDates, SPrices);

    curve a = ciao.bootstrap();


    return 0;
}