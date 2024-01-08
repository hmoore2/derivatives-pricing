//
// Created by hezza on 07/10/2023.
//

#ifndef PRICINGLIBRARY_MATHSLIB_H
#define PRICINGLIBRARY_MATHSLIB_H
#include <Eigen/Dense>
#include <functional>
#include "stdafx.h"
#include <memory>
using Eigen::MatrixXd;
using Eigen::VectorXd;

const double kPi = 3.1415926535897932384626433832795028842;

double Bisection(std::function<double(double)> f, double low, double high, double tolerance, double target);

double Norminv(double x );

double ImpliedVolatility(double s, double r, double k, double t, double price);

double Normcdf(double x );

double Integrate(std::function<double(double)> f, double a, double b, int n_steps);

// Abstract component

class RandomNumberGenerator{
 public:

  virtual MatrixXd GetUniforms(int rows, int cols) = 0;
  virtual void rng();
  virtual MatrixXd GetGaussians(int rows, int cols);

};

// Concrete component

class MersenneTwister : public RandomNumberGenerator{
 public:

  MatrixXd GetUniforms(int rows, int cols);

};

class Ran : public RandomNumberGenerator{
 public:

  typedef uint64_t Ullong;
  Ullong u,v,w;
  Ran(Ullong j) : v(4101842887655102017LL), w(1) {
	  u = j ^ v; int64();
	  v = u; int64();
	  w = v; int64();
  }

  inline Ullong int64() {
	  u = u * 2862933555777941757LL + 7046029254386353087LL;
	  v ^= v >> 17; v ^= v << 31; v ^= v >> 8;
	  w = 4294957665U*(w & 0xffffffff) + (w >> 32);
	  Ullong x = u ^ (u << 21); x ^= x >> 35; x ^= x << 4;
	  return (x + v) ^ w;
  }

  inline double doub() { return 5.42101086242752217E-20 * int64(); }
  inline unsigned int int32() { return (unsigned int)int64(); }

  MatrixXd GetUniforms(int rows, int cols){
	  MatrixXd ret(rows, cols);
	  for (int i = 0; i<rows; i++) {
		  for (int j = 0; j<cols; j++) {
			  ret(i, j) = doub();
		  }
	  }
	  return ret;
  }
};


// Abstract decorator

class RandomDecorator : public RandomNumberGenerator {
 public:
  explicit RandomDecorator(std::shared_ptr<RandomNumberGenerator> rand)
	  : random_(std::move(rand)) {}

 protected:
  RandomNumberGenerator &randomNumberGenerator() { return *random_; }
  [[nodiscard]] RandomNumberGenerator const &randomNumberGenerator() const { return *random_; }

 private:
  std::shared_ptr<RandomNumberGenerator> random_;
};



class Antithetic_decorator : public RandomDecorator {
 public:

  explicit Antithetic_decorator(std::shared_ptr<RandomNumberGenerator> random) : RandomDecorator(std::move(random)) {}

  MatrixXd GetUniforms(int rows, int cols){
	  MatrixXd ret(rows, cols);
	  if(cols >= rows ){ // Antithetic sampling column-wise
		  for(unsigned long int i = 0; i<cols; i++ )
		  	if (!antithetic_){
				  ret.col(i) = randomNumberGenerator().GetUniforms(rows, 1);
				  antithetic_ = true;
		  	}
		  	else{
				  ret.col(i) = 1 - ret.col(i-1).array();
				  antithetic_ = false;
		  	}
	  }
	  if(cols < rows ){ // Antithetic sampling row-wise
		  for(unsigned long int i = 0; i<rows; i++ )
			  if (!antithetic_){
				  ret.row(i) = randomNumberGenerator().GetUniforms(1, cols);
				  antithetic_ = true;
			  }
			  else{
				  ret.row(i) = 1 - ret.row(i-1).array();
				  antithetic_ = false;
			  }
	  }
	  return ret;
  }
 private:
  bool antithetic_{false};
};




#endif //PRICINGLIBRARY_MATHSLIB_H
