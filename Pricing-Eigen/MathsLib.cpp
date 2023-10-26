//
// Created by hezza on 07/10/2023.
//

#include "MathsLib.h"
#include <cmath>
using namespace std;


/*  MersenneTwister random number generator */


static mt19937 mersenneTwister;


void rng( const string& description ) {
    //ASSERT( description=="default" );
    mersenneTwister.seed(mt19937::default_seed);
}

MatrixXd randuniform( int rows, int cols ) {
    MatrixXd ret(rows, cols);
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            ret(i, j) = (mersenneTwister() + 0.5) /(mersenneTwister.max() + 1.0);
        }
    }
    return ret;
}



MatrixXd randn( int rows, int cols ) {
    MatrixXd ret = randuniform(rows, cols );
    for (int j=0; j<cols; j++) {
        for (int i=0; i<rows; i++) {
            ret(i,j)=norminv( ret(i,j) );
        }
    }
    return ret;
}

double bisection(function<double(double)> f, double low, double high,double tolerance, double target){
    double x = 0.5*(low + high);
    double y = f(x);

    do{
        if (y < target) low = x;

        if ( y > target) high = x;

        x = 0.5 * (low + high);

        y = f(x);
    }
    while ((fabs(y-target)> tolerance));
    return x;

}

double impliedVolatility(double S, double r, double K, double T, double price){
    //Todo: Add option to use Newton-Raphson
    auto lambda = [S, r, K, T](double sigma) {
        double numerator = log( S/K ) + ( r + sigma*sigma*0.5)*T;
        double denominator = sigma * sqrt(T );
        double d1 = numerator/denominator;
        double d2 = d1 - denominator;
        return S*normcdf(d1) - exp(-r*T)*K*normcdf(d2);
    };
    return bisection(lambda,0,100,0.001, price);
}


const double ROOT_2_PI = sqrt( 2.0 * PI );

static inline double hornerFunction( double x, double a0, double a1) {
    return a0 + x*a1;
}

static inline double hornerFunction( double x, double a0, double a1, double a2) {
    return a0 + x*hornerFunction( x, a1, a2);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3) {
    return a0 + x*hornerFunction( x, a1, a2, a3);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4) {
    return a0 + x*hornerFunction( x, a1, a2, a3, a4);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
                                     double a5) {
    return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
                                     double a5, double a6) {
    return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5, a6);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
                                     double a5, double a6, double a7) {
    return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5, a6, a7);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
                                     double a5, double a6, double a7, double a8) {
    return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5, a6, a7, a8);
}


double normcdf( double x ) {
    if (x<=0) {
        return 1-normcdf(-x);
    }
    double k = 1/(1 + 0.2316419*x);
    double poly = hornerFunction(k,
                                 0.0, 0.319381530, -0.356563782,
                                 1.781477937,-1.821255978,1.330274429);
    double approx = 1.0 - 1.0/ROOT_2_PI * exp(-0.5*x*x) * poly;
    return approx;
}

/*  Constants required for Moro's algorithm */
static const double a0 = 2.50662823884;
static const double a1 = -18.61500062529;
static const double a2 = 41.39119773534;
static const double a3 = -25.44106049637;
static const double b1 = -8.47351093090;
static const double b2 = 23.08336743743;
static const double b3 = -21.06224101826;
static const double b4 = 3.13082909833;
static const double c0 = 0.3374754822726147;
static const double c1 = 0.9761690190917186;
static const double c2 = 0.1607979714918209;
static const double c3 = 0.0276438810333863;
static const double c4 = 0.0038405729373609;
static const double c5 = 0.0003951896511919;
static const double c6 = 0.0000321767881768;
static const double c7 = 0.0000002888167364;
static const double c8 = 0.0000003960315187;

double norminv( double x ) {
    // We use Moro's algorithm
    double y = x - 0.5;
    if (y<0.42 && y>-0.42) {
        double r = y*y;
        return y*hornerFunction(r,a0,a1,a2,a3)/hornerFunction(r,1.0,b1,b2,b3,b4);
    } else {
        double r;
        if (y<0.0) {
            r = x;
        } else {
            r = 1.0 - x;
        }
        double s = log( -log( r ));
        double t = hornerFunction(s,c0,c1,c2,c3,c4,c5,c6,c7,c8);
        if (x>0.5) {
            return t;
        } else {
            return -t;
        }
    }
}

double integrate(function<double(double)> f, double a, double b, int nSteps){
    double total = 0.0;
    double h = (b-a) / nSteps;
    for(int i = 0; i<nSteps;i++){
        double x = a + i*h + 0.5*h;
        total += h*f(x);
    }
    return total;
}

class SinFunction{
public:
    double operator()(double x){
        return sin(x);
    }
};
///////////////////////////////////////////////
//
//   TESTS
//
///////////////////////////////////////////////
/*
static void testRanduniform() {
    rng("default");
    MatrixXd m = randuniform(1000,1);
    ASSERT( m.rows()==1000 );
    ASSERT_APPROX_EQUAL( meanCols(m).asScalar(), 0.5, 0.1);
    ASSERT( maxOverCols(m).asScalar()<1.0);
    ASSERT( minOverCols(m).asScalar()>0.0);
}

static void testRandn() {
    rng("default");
    MatrixXd m = randn(10000,1);
    ASSERT( m.rows()==10000 );
    ASSERT_APPROX_EQUAL( meanCols(m).asScalar(), 0.0, 0.1);
    ASSERT_APPROX_EQUAL( stdCols(m).asScalar(), 1.0, 0.1);
}


static void testImpliedVolatility() {
    //Todo: Get back to c=10
    double S = 100; // underlying price
    double K = 100; // strike price
    double r = 0.05; // risk-free rate
    double T = 1; // time to maturity
    double C = 10; // call option price
    cout << "Implied volatility: " << impliedVolatility(S, r, K, T, C) << endl;
}



static void testBisection(){
    auto lambda = [](double x){
        return pow(x,2) - 2;
    };
    double actual = bisection(lambda,0,2,0.01,0);
    double expected = sqrt(2);
    ASSERT_APPROX_EQUAL( actual, expected, 0.01);

    auto lambda2 = [](double x){
        return sin(x) - 0.5;
    };
    double actual2 = bisection(lambda2,0,2,0.0000001,0);
    double expected2 = PI/6;
    ASSERT_APPROX_EQUAL( actual2, expected2, 0.000001);

}

static void testLambdaIntegral() {
    auto lambda = [](double x) {
        return sqrt(1 + pow(sin(x), 2));
    };

    double actual = integrate(lambda, 0, PI, 1000);
    double expected = 3.820197789;
    ASSERT_APPROX_EQUAL(actual, expected, 0.000001);
}

static void testIntegral() {
    SinFunction integrand;
    double actual = integrate( integrand, 1, 3, 1000 );
    double expected = -cos(3.0)+cos(1.0);
    ASSERT_APPROX_EQUAL( actual, expected, 0.000001);
}



void testMatlib() {
    TEST(testImpliedVolatility);
    TEST(testLambdaIntegral);
    TEST(testIntegral);
    TEST( testBisection);
    TEST( testRandn);
    TEST( testRanduniform);
}
*/