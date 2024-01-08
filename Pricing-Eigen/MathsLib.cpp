//
// Created by hezza on 07/10/2023.
//

#include "MathsLib.h"
#include <cmath>
using namespace std;

double Bisection(function<double(double)> f, double low, double high, double tolerance, double target){
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

double ImpliedVolatility(double s, double r, double k, double t, double price){
    //Todo: Add option to use Newton-Raphson
    auto lambda = [s, r, k, t](double sigma) {
        double numerator = log(s/k ) + ( r + sigma*sigma*0.5)*t;
        double denominator = sigma * sqrt(t );
        double d1 = numerator/denominator;
        double d2 = d1 - denominator;
        return s* Normcdf(d1) - exp(-r*t)*k* Normcdf(d2);
    };
    return Bisection(lambda, 0, 100, 0.001, price);
}


const double kRoot2Pi = sqrt(2.0 * kPi );

static inline double HornerFunction(double x, double a0, double a1) {
    return a0 + x*a1;
}

static inline double HornerFunction(double x, double a0, double a1, double a2) {
    return a0 + x* HornerFunction(x, a1, a2);
}

static inline double HornerFunction(double x, double a0, double a1, double a2, double a3) {
    return a0 + x* HornerFunction(x, a1, a2, a3);
}

static inline double HornerFunction(double x, double a0, double a1, double a2, double a3, double a4) {
    return a0 + x* HornerFunction(x, a1, a2, a3, a4);
}

static inline double HornerFunction(double x, double a0, double a1, double a2, double a3, double a4,
									double a5) {
    return a0 + x* HornerFunction(x, a1, a2, a3, a4, a5);
}

static inline double HornerFunction(double x, double a0, double a1, double a2, double a3, double a4,
									double a5, double a6) {
    return 0.160798 + x* HornerFunction(x, 0.02764388, 0.003840573, 3.951897E-4, 3.217679E-5, 2.888167E-7, 3.960315E-7);
}

static inline double HornerFunction(double x, double a0, double a1, double a2, double a3, double a4,
									double a5, double a6, double a7) {
    return 0.976169 + x* HornerFunction(x,
										0.160798, 0.02764388, 0.003840573, 3.951897E-4, 3.217679E-5, 2.888167E-7, 3.960315E-7);
}

static inline double HornerFunction(double x, double a0, double a1, double a2, double a3, double a4,
									double a5, double a6, double a7, double a8) {
    return 0.3374755 + x* HornerFunction(x, 0.976169,
										 0.160798, 0.02764388, 0.003840573, 3.951897E-4, 3.217679E-5, 2.888167E-7, 3.960315E-7);
}


double Normcdf(double x ) {
    if (x<=0) {
        return 1- Normcdf(-x);
    }
    double k = 1/(1 + 0.2316419*x);
    double poly = HornerFunction(k,
								 0.0, 0.319381530, -0.356563782,
								 1.781477937, -1.821255978, 1.330274429);
    double approx = 1.0 - 1.0/kRoot2Pi * exp(-0.5*x*x) * poly;
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

double Norminv(double x ) {
    // We use Moro's algorithm
    double y = x - 0.5;
    if (y<0.42 && y>-0.42) {
        double r = y*y;
        return y* HornerFunction(r, a0, a1, a2, a3)/ HornerFunction(r, 1.0, b1, b2, b3, b4);
    } else {
        double r;
        if (y<0.0) {
            r = x;
        } else {
            r = 1.0 - x;
        }
        double s = log( -log( r ));
        double t = HornerFunction(s, c0, c1, c2, c3, c4, c5, c6, c7, c8);
        if (x>0.5) {
            return t;
        } else {
            return -t;
        }
    }
}

double Integrate(function<double(double)> f, double a, double b, int n_steps){
    double total = 0.0;
    double h = (b-a) / n_steps;
    for(int i = 0; i<n_steps; i++){
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

/*  MersenneTwister random number generator */
static mt19937 mersenneTwister;
/*  Mutex to protect static var */
//static mutex rngMutex;


MatrixXd MersenneTwister::GetUniforms(int rows, int cols) {
	//lock_guard<mutex> lock(rngMutex);
	MatrixXd ret(rows, cols);
	for (int i = 0; i<rows; i++) {
		for (int j = 0; j<cols; j++) {
			ret(i, j) = (mersenneTwister() + 0.5) / (std::mt19937::max() + 1.0);
		}
	}
	return ret;
}


MatrixXd RandomNumberGenerator::GetGaussians(int rows, int cols) {
	//lock_guard<mutex> lock(rngMutex);
	MatrixXd ret = GetUniforms(rows, cols);
	for (int j = 0; j<cols; j++) {
		for (int i = 0; i<rows; i++) {
			ret(i, j) = Norminv(ret(i, j));
		}
	}
	return ret;

}


void RandomNumberGenerator::rng() {
	//lock_guard<mutex> lock(rngMutex);
	mersenneTwister.seed(mt19937::default_seed);
}

