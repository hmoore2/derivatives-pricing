//
// Created by hezza on 11/10/2023.
//

#ifndef PRICING_PRICING_PRICING_EIGEN_DIGITALOPTION_H_
#define PRICING_PRICING_PRICING_EIGEN_DIGITALOPTION_H_

#include "stdafx.h"
#include "BlackScholesModel.h"
#include "PathIndependentOption.h"



class DigitalOption : public PathIndependentOption {
public:
    /*  Returns the Payoff at maturity given a column vector
        of scenarios */
    MatrixXd PayoffAtMaturity(const MatrixXd& stock_at_maturity ) const;

    double Price(const BlackScholesModel& bsm )
    const;
};

void TestDigitalOption();

#endif //PRICING_PRICING_PRICING_EIGEN_DIGITALOPTION_H_
