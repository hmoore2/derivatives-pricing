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

const double kPi = 3.1415926535897932384626433832795028842;

double Bisection(std::function<double(double)> f, double low, double high, double tolerance, double target);

double Norminv(double x );

double ImpliedVolatility(double s, double r, double k, double t, double price);

double Normcdf(double x );

double Integrate(std::function<double(double)> f, double a, double b, int n_steps);

/*  Seeds the default random number generator */
void Rng(const std::string& setting );


#endif //PRICINGLIBRARY_MATHSLIB_H
