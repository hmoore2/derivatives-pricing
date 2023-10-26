//
// Created by Henry Moore on 21/10/2023.
//


#include "KnockoutOption.h"

class UpAndInOption : public KnockoutOption {
public:
    MatrixXd payoff(
            const MatrixXd& prices ) const;
};

