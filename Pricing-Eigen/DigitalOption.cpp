//
// Created by hezza on 11/10/2023.
//

#include "DigitalOption.h"
#include "MathsLib.h"

MatrixXd DigitalOption::payoffAtMaturity(const MatrixXd& stockAtMaturity ) const {
    MatrixXd val = stockAtMaturity.array() - getStrike();
    val =  (val.array() < 0).select(0, val);
    val = (val.array() > 0).select(1, val);
    return val;
}


double DigitalOption::price(
        const BlackScholesModel& bsm ) const {
    double S = bsm.stockPrice;
    double K = getStrike();
    double sigma = bsm.volatility;
    double r = bsm.riskFreeRate;
    double T = getMaturity() - bsm.date;

    double numerator = log( S/K ) + ( r + sigma*sigma*0.5)*T;
    double denominator = sigma * sqrt(T );
    double d1 = numerator/denominator;
    double d2 = d1 - denominator;
    return  exp(-r*T)*normcdf(d2);
}

