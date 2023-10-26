//
// Created by Henry Moore on 22/10/2023.
//

#ifndef PRICING_LOOKBACKOPTION_H
#define PRICING_LOOKBACKOPTION_H

#include "ContinuousTimeOptionBase.h"

class LookbackOption : public ContinuousTimeOptionBase {
public:
    MatrixXd payoff(const MatrixXd& prices) const;

    bool isPathDependent() const {
        return true;
    }
};
#endif //PRICING_LOOKBACKOPTION_H
