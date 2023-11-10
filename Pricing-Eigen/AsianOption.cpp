//
// Created by hezza on 11/10/2023.
//

#include "AsianOption.h"

#include "MathsLib.h"

MatrixXd AsianOption::Payoff(
        const MatrixXd& prices ) const {
    MatrixXd average = prices.rowwise().mean();
    average.array() -= GetStrike();
    MatrixXd p = (average.array() < 0).select(0, average);
    return p;
}
