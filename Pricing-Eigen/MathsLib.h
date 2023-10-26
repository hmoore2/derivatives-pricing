//
// Created by hezza on 07/10/2023.
//

#ifndef PRICINGLIBRARY_MATHSLIB_H
#define PRICINGLIBRARY_MATHSLIB_H
#include <Eigen/Dense>
#include <functional>
#include "stdafx.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

const double PI = 3.1415926535897932384626433832795028842;

double bisection(std::function<double(double)> f, double low, double high,double tolerance, double target);

double norminv( double x );

double impliedVolatility(double S, double r, double K, double T, double price);

double normcdf( double x );

double integrate(std::function<double(double)> f, double a, double b, int nSteps);

/*  Create uniformly distributed random numbers */
MatrixXd randuniform( int rows, int cols );
/*  Create normally distributed random numbers */
MatrixXd randn( int rows, int cols );
/*  Seeds the default random number generator */
void rng( const std::string& setting );

void testMatlib();


#endif //PRICINGLIBRARY_MATHSLIB_H
