//
// Created by hezza on 11/10/2023.
//

#include "PutOption.h"
#include "MathsLib.h"


MatrixXd PutOption::payoffAtMaturity( const MatrixXd& stockAtMaturity ) const {
    MatrixXd strike = MatrixXd::Ones(stockAtMaturity.rows(), stockAtMaturity.cols()) * getStrike();
    MatrixXd val = strike - stockAtMaturity;
    val = (val.array() < 0).select(0, val);  // Set negative values to zero.
    return val;
}


double PutOption::price(
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
    return -S*normcdf(-d1) + exp(-r*T)*K*normcdf(-d2);
}

//////////////////////////

/*
static void testPutOptionPrice() {
    PutOption putOption;
    putOption.setStrike( 105.0 );
    putOption.setMaturity( 2.0 );

    BlackScholesModel bsm;
    bsm.date = 1.0;
    bsm.volatility = 0.1;
    bsm.riskFreeRate = 0.05;
    bsm.stockPrice = 100.0;

    double price = putOption.price( bsm );
    ASSERT_APPROX_EQUAL( price, 3.92, 0.01);

}

void testPutOption() {
    TEST( testPutOptionPrice );
}
*/
