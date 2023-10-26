#pragma once

#include "stdafx.h"
#include "ContinuousTimeOptionBase.h"

/**
 *   This states that all path independent options
 *   have a payoff determined by the final stock price
 */

using Eigen::MatrixXd;
using Eigen::VectorXd;


class PathIndependentOption :
        public ContinuousTimeOptionBase {
public:
    /*  A virtual destructor */
    virtual ~PathIndependentOption() {}
    /*  Returns the payoff at maturity given a column vector
        of scenarios */
    virtual MatrixXd payoffAtMaturity( const MatrixXd& finalStockPrice) const
        = 0;
    /*  Compute the payoff from a price path */   
    MatrixXd payoff(
            const MatrixXd& stockPrices ) const {
        return payoffAtMaturity( stockPrices.col(stockPrices.cols()-1));
    }
    /*  Is the option path dependent? */
    bool isPathDependent() const {
        return false;
    };
};