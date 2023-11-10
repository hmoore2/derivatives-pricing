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

    /*  Returns the Payoff at maturity given a column vector
        of scenarios */
    MatrixXd PayoffAtMaturity(const MatrixXd& stock_at_maturity ) const;

    double Price(const BlackScholesModel& bsm )
    const;
};

void TestPutOption();


#endif //PRICINGLIBRARY_PUTOPTION_H
