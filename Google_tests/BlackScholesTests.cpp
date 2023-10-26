//
// Created by Henry Moore on 21/10/2023.
//
#include "gtest/gtest.h"
#include "../Pricing-Eigen/MathsLib.h"
#include "../Pricing-Eigen/BlackScholesModel.h"
#include "../Pricing-Eigen/CallOption.h"
#include "../Pricing-Eigen/ContinuousTimeOption.h"
#include "../Pricing-Eigen/ContinuousTimeOptionBase.h"
#include "../Pricing-Eigen/MonteCarloPricer.h"
#include "../Pricing-Eigen/DigitalOption.h"
#include "../Pricing-Eigen/PutOption.h"
#include "../Pricing-Eigen/AsianOption.h"
#include "../Pricing-Eigen/UpAndOutOption.h"
#include "../Pricing-Eigen/DownAndOutOption.h"
#include "../Pricing-Eigen/UpAndInOption.h"
#include "../Pricing-Eigen/LookbackOption.h"
#include "../Pricing-Eigen/AmericanCallOption.h"


TEST(AmericanOption, price){
    AmericanCallOption americanCallOption;
    americanCallOption.setStrike(95.0);
    americanCallOption.setMaturity(1.0);
    int NAS = 200;

    BlackScholesModel bsm;
    bsm.volatility = 0.3;
    bsm.riskFreeRate = 0.1;
    bsm.stockPrice = 100;
    double price = americanCallOption.price(bsm, NAS);
    ASSERT_NEAR(price,19.478084290351838, 0.01);
}



TEST(BlackScholesModel, pricePath){
    rng("default");

    BlackScholesModel bsm;
    bsm.riskFreeRate = 0.05;
    bsm.volatility = 0.1;
    bsm.stockPrice = 100.0;
    bsm.date = 2.0;

    int nPaths = 100000;
    int nsteps = 5;
    double maturity = 4.0;
    MatrixXd paths =
            bsm.generateRiskNeutralPricePaths( maturity,
                                               nPaths,
                                               nsteps );
    MatrixXd finalPrices = paths.col( nsteps-1 );
    ASSERT_NEAR(finalPrices.rowwise().mean().mean(),
                         exp( bsm.riskFreeRate*2.0)*bsm.stockPrice, 0.1);
}

TEST(MonteCarloPricer, callOptionMC){
    rng("default");

    CallOption c;
    c.setStrike( 110 );
    c.setMaturity( 2 );

    BlackScholesModel m;
    m.volatility = 0.1;
    m.riskFreeRate = 0.05;
    m.stockPrice = 100.0;
    m.drift = 0.1;
    m.date = 1;

    MonteCarloPricer pricer;
    double price = pricer.price( c, m );
    double expected = c.price( m );
    ASSERT_NEAR( price, expected, 0.1 );
}

TEST(CallOption, callOptionPrice){
    rng("default");

    CallOption c;
    c.setStrike( 110 );
    c.setMaturity( 2 );

    BlackScholesModel m;
    m.volatility = 0.1;
    m.riskFreeRate = 0.05;
    m.stockPrice = 100.0;
    m.drift = 0.1;
    m.date = 1;

    MonteCarloPricer pricer;
    pricer.nScenarios = 10000;
    double price = pricer.price( c, m );
    double expected = c.price( m );
    ASSERT_NEAR( price, expected, 0.1 );
}

TEST(digitalOption, testDigitalOptionPrice){
    DigitalOption digitalOption;
    digitalOption.setStrike( 105.0 );
    digitalOption.setMaturity( 2.0 );

    BlackScholesModel bsm;
    bsm.date = 1.0;
    bsm.volatility = 0.1;
    bsm.riskFreeRate = 0.05;
    bsm.stockPrice = 100.0;


    double price = digitalOption.price( bsm );
    ASSERT_NEAR( price, 0.4612, 0.01);
}

TEST(putOption, testPutOption){
    PutOption putOption;
    putOption.setStrike( 105.0 );
    putOption.setMaturity( 2.0 );

    BlackScholesModel bsm;
    bsm.date = 1.0;
    bsm.volatility = 0.1;
    bsm.riskFreeRate = 0.05;
    bsm.stockPrice = 100.0;

    double price = putOption.price( bsm );
    ASSERT_NEAR( price, 3.92, 0.01);
}

TEST(asianOption, testAsianOption){
    AsianOption asianOption;
    asianOption.setStrike( 105.0 );
    asianOption.setMaturity( 2.0 );

    CallOption callOption;
    callOption.setStrike( 105.0 );
    callOption.setMaturity( 2.0 );

    DigitalOption digitalOption;
    digitalOption.setStrike( 105.0 );
    digitalOption.setMaturity( 2.0 );

    BlackScholesModel bsm;
    bsm.date = 1.0;
    bsm.volatility = 0.1;
    bsm.riskFreeRate = 0.05;
    bsm.stockPrice = 100.0;

    double price = asianOption.price( bsm );
    double callPrice = callOption.price( bsm );
    double digitalPrice = digitalOption.price( bsm );
    ASSERT_LE( price, callPrice);
    ASSERT_LE( digitalPrice, price);
}

TEST(UpAndOutOption, testUpAndOutOptionPrice){

    CallOption callOption;
    callOption.setStrike( 105.0 );
    callOption.setMaturity( 2.0 );

    UpAndOutOption upAndOutOption;
    upAndOutOption.setStrike( 105.0 );
    upAndOutOption.setMaturity( 2.0 );
    upAndOutOption.setBarrier(4000);

    UpAndOutOption upAndOutOption2;
    upAndOutOption2.setStrike( 105.0 );
    upAndOutOption2.setMaturity( 2.0 );
    upAndOutOption2.setBarrier(140);

    BlackScholesModel bsm;
    bsm.date = 1.0;
    bsm.volatility = 0.1;
    bsm.riskFreeRate = 0.05;
    bsm.stockPrice = 100.0;

    double callPrice = callOption.price( bsm );
    double upAndOutPrice = upAndOutOption.price( bsm );
    double upAndOutPrice2 = upAndOutOption2.price( bsm );

    ASSERT_NEAR( upAndOutPrice, callPrice, 0.1);
    ASSERT_LE( upAndOutPrice2, callPrice);
}

TEST(UpAndOutDownAndOut, UpAndOutOptionPriceTestAnalytical){

    CallOption callOption;
    callOption.setStrike( 105.0 );
    callOption.setMaturity( 2.0 );

    UpAndOutOption upAndOutOption;
    upAndOutOption.setStrike( 105.0 );
    upAndOutOption.setMaturity( 2.0 );
    upAndOutOption.setBarrier(110);

    UpAndInOption upAndInOption;
    upAndInOption.setStrike( 105.0 );
    upAndInOption.setMaturity( 2.0 );
    upAndInOption.setBarrier(110);

    BlackScholesModel bsm;
    bsm.date = 1.0;
    bsm.volatility = 0.1;
    bsm.riskFreeRate = 0.05;
    bsm.stockPrice = 100.0;

    double callPrice = callOption.price( bsm );
    double upAndOutPrice = upAndOutOption.price( bsm );
    double upAndInPrice = upAndInOption.price( bsm );
    // The value of an up-and-in call option plus an up-and out should be the same as a vanilla call.
    double total = upAndInPrice + upAndOutPrice;

    ASSERT_NEAR(callPrice, total, 0.1);

}

TEST(LookbackOption, LookbackOptionPrice){

    CallOption callOption;
    callOption.setStrike( 105.0 );
    callOption.setMaturity( 2.0 );

    LookbackOption lookbackOption;
    lookbackOption.setStrike(105.0);
    lookbackOption.setMaturity(105.0);

    BlackScholesModel bsm;
    bsm.date = 1.0;
    bsm.volatility = 0.1;
    bsm.riskFreeRate = 0.05;
    bsm.stockPrice = 100.0;

    double callPrice = callOption.price( bsm );
    double lookbackPrice = lookbackOption.price(bsm);

    ASSERT_LE(callPrice, lookbackPrice);
}


