//
// Created by Henry Moore on 21/10/2023.
//

#include "UpAndInOption.h"
#include "MathsLib.h"

using namespace std;

MatrixXd UpAndInOption::Payoff(
        const MatrixXd& prices ) const {
    MatrixXd max = prices.rowwise().maxCoeff();
    MatrixXd barrier = MatrixXd::Ones(max.rows(), max.cols()) * GetBarrier();
    MatrixXd hit = (max.array() >= barrier.array()).cast<double>();
    MatrixXd p = prices.col(prices.cols()-1);
    p.array() -= GetStrike();
    p = (p.array() < 0).select(0, p);

    p = p.array() * hit.array();
    return p;
}