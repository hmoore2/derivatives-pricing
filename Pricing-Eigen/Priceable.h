//
// Created by hezza on 11/9/2023.
//

#ifndef PRICING_PRICING_PRICING_EIGEN_PRICEABLE_H_
#define PRICING_PRICING_PRICING_EIGEN_PRICEABLE_H_
#include "BlackScholesModel.h"


/**
 *   Represents a general security
 */
class Priceable {
 public:
  /*  Compute the price of the security in the
	  Black--Scholes world */
  virtual double Price(
	  const BlackScholesModel& model ) const = 0;
};

#endif //PRICING_PRICING_PRICING_EIGEN_PRICEABLE_H_
