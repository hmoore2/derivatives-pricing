//
// Created by hezza on 11/10/2023.
//

#include "UpAndOutOption.h"
#include "MathsLib.h"

using namespace std;

MatrixXd UpAndOutOption::Payoff(
        const MatrixXd& prices ) const {
    MatrixXd max = prices.rowwise().maxCoeff();
    MatrixXd barrier = MatrixXd::Ones(max.rows(), max.cols()) * GetBarrier();
    MatrixXd didnt_hit = (max.array() < barrier.array()).cast<double>();
    MatrixXd p = prices.col(prices.cols()-1);
    p.array() -= GetStrike();
    p = (p.array() < 0).select(0, p);

    p = p.array() * didnt_hit.array();
    return p;
}



