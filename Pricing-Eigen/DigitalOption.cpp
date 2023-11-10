//
// Created by hezza on 11/10/2023.
//

#include "DigitalOption.h"
#include "MathsLib.h"

MatrixXd DigitalOption::PayoffAtMaturity(const MatrixXd& stock_at_maturity ) const {
    MatrixXd val = stock_at_maturity.array() - GetStrike();
    val =  (val.array() < 0).select(0, val);
    val = (val.array() > 0).select(1, val);
    return val;
}


double DigitalOption::Price(
        const BlackScholesModel& bsm ) const {
    double s = bsm.stock_price_;
    double k = GetStrike();
    double sigma = bsm.volatility_;
    double r = bsm.risk_free_rate_;
    double t = GetMaturity() - bsm.date_;

    double numerator = log(s/k ) + ( r + sigma*sigma*0.5)*t;
    double denominator = sigma * sqrt(t );
    double d1 = numerator/denominator;
    double d2 = d1 - denominator;
    return  exp(-r*t)* Normcdf(d2);
}

