//
// Created by Henry Moore on 22/10/2023.
//

#ifndef PRICING_PRICING_PRICING_EIGEN_LOOKBACKOPTION_H_
#define PRICING_PRICING_PRICING_EIGEN_LOOKBACKOPTION_H_

#include "ContinuousTimeOptionBase.h"

class LookbackOption : public ContinuousTimeOptionBase {
public:
    MatrixXd Payoff(const MatrixXd& prices) const;

    bool IsPathDependent() const {
        return true;
    }
};
#endif //PRICING_PRICING_PRICING_EIGEN_LOOKBACKOPTION_H_
