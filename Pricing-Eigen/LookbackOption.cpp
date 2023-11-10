//
// Created by Henry Moore on 22/10/2023.
//

#include "LookbackOption.h"


MatrixXd LookbackOption::Payoff(
        const MatrixXd& prices ) const {
    MatrixXd max = prices.rowwise().maxCoeff();
    max.array() -= GetStrike();
    MatrixXd p = (max.array() < 0).select(0, max);
    return p;
}