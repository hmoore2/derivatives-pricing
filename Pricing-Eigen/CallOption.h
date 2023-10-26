#pragma once

#include "stdafx.h"
#include "BlackScholesModel.h"
#include "PathIndependentOption.h"

class CallOption : public PathIndependentOption {
public:

    /*  Returns the payoff at maturity given a column vector
        of scenarios */
    MatrixXd payoffAtMaturity( const MatrixXd& stockAtMaturity ) const;

    double price( const BlackScholesModel& bsm )
        const;
};

void testCallOption();