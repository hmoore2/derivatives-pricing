//
// Created by hezza on 11/10/2023.
//

#ifndef PRICINGLIBRARY_PUTOPTION_H
#define PRICINGLIBRARY_PUTOPTION_H
#include "stdafx.h"
#include "BlackScholesModel.h"
#include "PathIndependentOption.h"

class PutOption : public PathIndependentOption {
public:

    /*  Returns the payoff at maturity given a column vector
        of scenarios */
    MatrixXd payoffAtMaturity( const MatrixXd& stockAtMaturity ) const;

    double price( const BlackScholesModel& bsm )
    const;
};

void testPutOption();


#endif //PRICINGLIBRARY_PUTOPTION_H
