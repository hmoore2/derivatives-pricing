//
// Created by hezza on 11/10/2023.
//

#ifndef PRICING_PRICING_PRICING_EIGEN_ASIANOPTION_H_
#define PRICING_PRICING_PRICING_EIGEN_ASIANOPTION_H_

#include "ContinuousTimeOptionBase.h"

class AsianOption : public ContinuousTimeOptionBase {
public:
    
    MatrixXd Payoff(const MatrixXd& prices) const;

    bool IsPathDependent() const {
        return true;
    }
};


#endif //PRICING_PRICING_PRICING_EIGEN_ASIANOPTION_H_
