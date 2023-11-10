#pragma once

#include "stdafx.h"
#include "ContinuousTimeOptionBase.h"

/**
 *   This states that all path independent options
 *   have a Payoff determined by the final stock Price
 */

using Eigen::MatrixXd;
using Eigen::VectorXd;


class PathIndependentOption :
        public ContinuousTimeOptionBase {
public:
    /*  A virtual destructor */
    virtual ~PathIndependentOption() {}
    /*  Returns the Payoff at maturity given a column vector
        of scenarios */
    virtual MatrixXd PayoffAtMaturity(const MatrixXd& final_stock_price) const
        = 0;
    /*  Compute the Payoff from a Price path */
    MatrixXd Payoff(
            const MatrixXd& stock_prices ) const {
        return PayoffAtMaturity(stock_prices.col(stock_prices.cols() - 1));
    }
    /*  Is the option path dependent? */
    bool IsPathDependent() const {
        return false;
    };
};