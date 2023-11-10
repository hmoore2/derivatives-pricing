//
// Created by hezza on 10/28/2023.
//

#ifndef PRICING_PRICING_PRICING_EIGEN_RANDOMNUMBERGENERATOR_H_
#define PRICING_PRICING_PRICING_EIGEN_RANDOMNUMBERGENERATOR_H_
#include <Eigen/Dense>
#include <functional>
#include "stdafx.h"
#include <random>

using Eigen::MatrixXd;
using Eigen::VectorXd;

class RandDouble{
 public:
  RandDouble(double low, double high)
	  : r_(bind(std::uniform_real_distribution<>(low, high), std::mt19937()  )){}
  double operator()(){return r_();}

 private:
  std::function<double()> r_;
};


class RandomNumberGenerator{
 public:
  virtual MatrixXd RandNormal(int rows, int cols) = 0;
  virtual MatrixXd RandUniform(int rows, int cols) = 0;
};

class MersenneTwister: public RandomNumberGenerator{
 public:
  MatrixXd RandNormal(int rows, int cols);
  MatrixXd RandUniform(int rows, int cols);
};


class MersenneTwisterAntithetic: public RandomNumberGenerator{
 public:
  MatrixXd RandNormal(int rows, int cols);
  MatrixXd RandUniform(int rows, int cols);
};


#endif //PRICING_PRICING_PRICING_EIGEN_RANDOMNUMBERGENERATOR_H_
