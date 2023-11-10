//
// Created by hezza on 11/10/2023.
//

#include "PutOption.h"
#include "MathsLib.h"


MatrixXd PutOption::PayoffAtMaturity(const MatrixXd& stock_at_maturity ) const {
    MatrixXd strike = MatrixXd::Ones(stock_at_maturity.rows(), stock_at_maturity.cols()) * GetStrike();
    MatrixXd val = strike - stock_at_maturity;
    val = (val.array() < 0).select(0, val);  // Set negative values to zero.
    return val;
}


double PutOption::Price(
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
    return -s* Normcdf(-d1) + exp(-r*t)*k* Normcdf(-d2);
}

