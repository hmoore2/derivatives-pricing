//
// Created by hezza on 11/10/2023.
//

#ifndef PRICINGLIBRARY_ASIANOPTION_H
#define PRICINGLIBRARY_ASIANOPTION_H

#include "ContinuousTimeOptionBase.h"

class AsianOption : public ContinuousTimeOptionBase {
public:
    
    MatrixXd payoff(const MatrixXd& prices) const;

    bool isPathDependent() const {
        return true;
    }
};


#endif //PRICINGLIBRARY_ASIANOPTION_H
