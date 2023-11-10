#pragma once

#include "stdafx.h"
#include "BlackScholesModel.h"
#include "PathIndependentOption.h"

class CallOption : public PathIndependentOption {
public:

    /*  Returns the Payoff at maturity given a column vector
        of scenarios */
    MatrixXd PayoffAtMaturity(const MatrixXd& stock_at_maturity ) const;

    double Price(const BlackScholesModel& bsm )
        const;
};

void testCallOption();