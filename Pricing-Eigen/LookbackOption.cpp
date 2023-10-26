//
// Created by Henry Moore on 22/10/2023.
//

#include "LookbackOption.h"


MatrixXd LookbackOption::payoff(
        const MatrixXd& prices ) const {
    MatrixXd max = prices.rowwise().maxCoeff();
    max.array() -=  getStrike();
    MatrixXd p = (max.array() < 0).select(0, max);
    return p;
}