#include "CallOption.h"
#include "MathsLib.h"

MatrixXd CallOption::PayoffAtMaturity(const MatrixXd& stock_at_maturity ) const {
    MatrixXd val = stock_at_maturity.array() - GetStrike();
    val = (val.array() < 0).select(0, val);  // Set negative values to zero.
    return val;
}


double CallOption::Price(
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
    return s* Normcdf(d1) - exp(-r*t)*k* Normcdf(d2);
}





//////////////////////////
//
//  Test the call option class
//  
//
//////////////////////////
/*
static void testCallOptionPrice() {
    CallOption callOption;
    callOption.SetStrike( 105.0 );
    callOption.SetMaturity( 2.0 );
    
    BlackScholesModel bsm;
    bsm.date = 1.0;
    bsm.volatility_ = 0.1;
    bsm.risk_free_rate_ = 0.05;
    bsm.stock_price_ = 100.0;

    double Price = callOption.Price( bsm );
    ASSERT_APPROX_EQUAL( Price, 4.046, 0.01);

}

void testCallOption() {
    TEST( testCallOptionPrice );
}
*/