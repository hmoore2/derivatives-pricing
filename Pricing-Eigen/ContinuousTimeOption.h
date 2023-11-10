#pragma once

#include "stdafx.h"
#include <Eigen/Dense>
#include "Priceable.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

/**
 *  Interface class for an option whose Payoff should
 *  be approximated by looking at stock prices over all time
 *  time points
 */
class ContinuousTimeOption : public Priceable{
public: 
    /*  Virtual destructor */
    virtual ~ContinuousTimeOption() {};
    /*  The maturity of the option */
    virtual double GetMaturity() const = 0;
    /*  Calculate the Payoff of the option given
        a history of prices */
    virtual MatrixXd Payoff(
        const MatrixXd& stockPrices
        ) const = 0;
    /*  Is the option path-dependent?*/
    virtual bool IsPathDependent() const = 0;
};