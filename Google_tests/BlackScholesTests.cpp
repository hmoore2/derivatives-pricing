//
// Created by Henry Moore on 21/10/2023.
//
#include "gtest/gtest.h"
#include "../Pricing-Eigen/MathsLib.h"
#include "../Pricing-Eigen/Portfolio.h"
#include "../Pricing-Eigen/Priceable.h"
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
#include <memory>

#include <cmath>

TEST(AmericanOption, price){
    AmericanCallOption american_call_option;
  	american_call_option.SetStrike(95.0);
  	american_call_option.SetMaturity(1.0);
    int nas = 200;

    BlackScholesModel bsm;
    bsm.volatility_ = 0.3;
    bsm.risk_free_rate_ = 0.1;
    bsm.stock_price_ = 100;
    double price = american_call_option.Price(bsm, nas);
    ASSERT_NEAR(price,19.478084290351838, 0.01);
}



TEST(BlackScholesModel, pricePath){
    //Rng("default");

    BlackScholesModel bsm;
    bsm.risk_free_rate_ = 0.05;
    bsm.volatility_ = 0.1;
    bsm.stock_price_ = 100.0;
    bsm.date_ = 2.0;

    int n_paths = 100000;
    int nsteps = 5;
    double maturity = 4.0;

	std::shared_ptr<RandomNumberGenerator> mtw(std::make_shared<MersenneTwister>());
    MatrixXd paths =
		bsm.GenerateRiskNeutralPricePaths(maturity,
										  n_paths,
										  nsteps, mtw);
    MatrixXd final_prices = paths.col(nsteps-1 );
    ASSERT_NEAR(final_prices.rowwise().mean().mean(),
				exp( bsm.risk_free_rate_*2.0)*bsm.stock_price_, 0.1);
}

TEST(MonteCarloPricer, callOptionMC){
    //Rng("default");

    CallOption c;
  	c.SetStrike(110);
 	 c.SetMaturity(2);

    BlackScholesModel m;
    m.volatility_ = 0.1;
    m.risk_free_rate_ = 0.05;
    m.stock_price_ = 100.0;
    m.drift_ = 0.1;
    m.date_ = 1;

	std::shared_ptr<RandomNumberGenerator> mtw(std::make_shared<MersenneTwister>());


	MonteCarloPricer pricer;
    double price = pricer.Price(c,m, mtw);
    double expected = c.Price(m);
    ASSERT_NEAR( price, expected, 0.1 );
}

TEST(CallOption, callOptionPrice){
    //Rng("default");

    CallOption c;
  	c.SetStrike(110);
  	c.SetMaturity(2);

    BlackScholesModel m;
    m.volatility_ = 0.1;
    m.risk_free_rate_ = 0.05;
    m.stock_price_ = 100.0;
    m.drift_ = 0.1;
    m.date_ = 1;
	std::shared_ptr<RandomNumberGenerator> mtw(std::make_shared<MersenneTwister>());


	MonteCarloPricer pricer;
    pricer.n_scenarios_ = 10000;
    double price = pricer.Price(c,m, mtw);
    double expected = c.Price(m);
    ASSERT_NEAR( price, expected, 0.1 );
}

TEST(digitalOption, testDigitalOptionPrice){
    DigitalOption digital_option;
 	digital_option.SetStrike(105.0);
  	digital_option.SetMaturity(2.0);

    BlackScholesModel bsm;
    bsm.date_ = 1.0;
    bsm.volatility_ = 0.1;
    bsm.risk_free_rate_ = 0.05;
    bsm.stock_price_ = 100.0;


    double price = digital_option.Price(bsm);
    ASSERT_NEAR( price, 0.4612, 0.01);
}

TEST(putOption, TestPutOption){
    PutOption put_option;
  put_option.SetStrike(105.0);
  put_option.SetMaturity(2.0);

    BlackScholesModel bsm;
    bsm.date_ = 1.0;
    bsm.volatility_ = 0.1;
    bsm.risk_free_rate_ = 0.05;
    bsm.stock_price_ = 100.0;

    double price = put_option.Price(bsm);
    ASSERT_NEAR( price, 3.92, 0.01);
}

TEST(asianOption, testAsianOption){
    AsianOption asian_option;
  asian_option.SetStrike(105.0);
  asian_option.SetMaturity(2.0);

    CallOption call_option;
  call_option.SetStrike(105.0);
  call_option.SetMaturity(2.0);

    DigitalOption digital_option;
  digital_option.SetStrike(105.0);
  digital_option.SetMaturity(2.0);

    BlackScholesModel bsm;
    bsm.date_ = 1.0;
    bsm.volatility_ = 0.1;
    bsm.risk_free_rate_ = 0.05;
    bsm.stock_price_ = 100.0;

    double price = asian_option.Price(bsm);
    double call_price = call_option.Price(bsm);
    double digital_price = digital_option.Price(bsm);
    ASSERT_LE(price, call_price);
    ASSERT_LE(digital_price, price);
}

TEST(UpAndOutOption, testUpAndOutOptionPrice){

    CallOption call_option;
  call_option.SetStrike(105.0);
  call_option.SetMaturity(2.0);

    UpAndOutOption up_and_out_option;
  up_and_out_option.SetStrike(105.0);
  up_and_out_option.SetMaturity(2.0);
  up_and_out_option.SetBarrier(4000);

    UpAndOutOption up_and_out_option_2;
  up_and_out_option_2.SetStrike(105.0);
  up_and_out_option_2.SetMaturity(2.0);
  up_and_out_option_2.SetBarrier(140);

    BlackScholesModel bsm;
    bsm.date_ = 1.0;
    bsm.volatility_ = 0.1;
    bsm.risk_free_rate_ = 0.05;
    bsm.stock_price_ = 100.0;

    double call_price = call_option.Price(bsm);
    double up_and_out_price = up_and_out_option.Price(bsm);
    double up_and_out_price_2 = up_and_out_option_2.Price(bsm);

    ASSERT_NEAR(up_and_out_price, call_price, 0.1);
    ASSERT_LE(up_and_out_price_2, call_price);
}

TEST(UpAndOutDownAndOut, UpAndOutOptionPriceTestAnalytical){

    CallOption call_option;
  call_option.SetStrike(105.0);
  call_option.SetMaturity(2.0);

    UpAndOutOption up_and_out_option;
  up_and_out_option.SetStrike(105.0);
  up_and_out_option.SetMaturity(2.0);
  up_and_out_option.SetBarrier(110);

    UpAndInOption up_and_in_option;
  up_and_in_option.SetStrike(105.0);
  up_and_in_option.SetMaturity(2.0);
  up_and_in_option.SetBarrier(110);

    BlackScholesModel bsm;
    bsm.date_ = 1.0;
    bsm.volatility_ = 0.1;
    bsm.risk_free_rate_ = 0.05;
    bsm.stock_price_ = 100.0;

    double call_price = call_option.Price(bsm);
    double up_and_out_price = up_and_out_option.Price(bsm);
    double up_and_in_price = up_and_in_option.Price(bsm);
    // The value of an up-and-in call option plus an up-and out should be the same as a vanilla call.
    double total = up_and_in_price + up_and_out_price;

    ASSERT_NEAR(call_price, total, 0.1);

}

TEST(LookbackOption, LookbackOptionPrice){

    CallOption call_option;
  	call_option.SetStrike(105.0);
  	call_option.SetMaturity(2.0);

    LookbackOption lookback_option;
  	lookback_option.SetStrike(105.0);
  	lookback_option.SetMaturity(105.0);

    BlackScholesModel bsm;
    bsm.date_ = 1.0;
    bsm.volatility_ = 0.1;
    bsm.risk_free_rate_ = 0.05;
    bsm.stock_price_ = 100.0;

    double call_price = call_option.Price(bsm);
    double lookbackPrice = lookback_option.Price(bsm);

    ASSERT_LE(call_price, lookbackPrice);
}


TEST(Decorator, decoratorPricingTest){

	CallOption c;
	c.SetStrike(110);
	c.SetMaturity(2);

	BlackScholesModel m;
	m.volatility_ = 0.1;
	m.risk_free_rate_ = 0.05;
	m.stock_price_ = 100.0;
	m.drift_ = 0.1;
	m.date_ = 1;

	std::shared_ptr<RandomNumberGenerator> random(std::make_shared<Antithetic_decorator>
									  (std::make_shared<MersenneTwister>()));

	MonteCarloPricer pricer;
	pricer.n_scenarios_ = 10000;
	double price = pricer.Price(c,m, random);
	double expected = c.Price(m);
	ASSERT_NEAR( price, expected, 0.1 );
}


TEST(Decorator, randDecorator){

	std::shared_ptr<RandomNumberGenerator> random(std::make_shared<Antithetic_decorator>
													  (std::make_shared<MersenneTwister>()));
	MatrixXd normals = random->GetGaussians(1000,2000);
	double average = normals.rowwise().mean().mean();
	ASSERT_NEAR( average, 0, 0.001 );
}

TEST(RandomNumberGenerator, num_recipes_rand){

	std::shared_ptr<RandomNumberGenerator> random(std::make_shared<Ran>(5432));
	MatrixXd normals = random->GetGaussians(1000,2000);
	double average = normals.rowwise().mean().mean();
	ASSERT_NEAR( average, 0, 0.001 );
}