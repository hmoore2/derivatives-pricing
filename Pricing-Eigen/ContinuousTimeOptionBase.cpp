#include "ContinuousTimeOptionBase.h"

#include "MonteCarloPricer.h"
/*
#include "CallOption.h"
#include "UpAndOutOption.h"

#include "MathsLib.h"
*/


double ContinuousTimeOptionBase::Price(const BlackScholesModel& model ) const {
    MonteCarloPricer pricer;
	std::shared_ptr<RandomNumberGenerator> random(std::make_shared<MersenneTwister>());

    return pricer.Price(*this, model, random);
}

//////////////////////////////
//
//  Tests
//
//////////////////////////////
/*
static void testPrice() {

    BlackScholesModel bsm;
    bsm.volatility_= 0.1;
    bsm.stock_price_=100;

    CallOption callOption;
    callOption.SetStrike(100);
    callOption.SetMaturity(1.0);

    UpAndOutOption knockoutOption;
    knockoutOption.SetStrike(100);
    knockoutOption.SetMaturity(1.0);
    knockoutOption.SetBarrier(4000);

    ContinuousTimeOptionBase& o1=callOption;
    ContinuousTimeOptionBase& o2=knockoutOption;
    double p1 = o1.Price( bsm );
    double p2 = o2.Price( bsm );
    ASSERT_APPROX_EQUAL( p1, p2, 0.2);
}

void TestContinuousTimeOptionBase() {
    TEST( testPrice );
}
 */