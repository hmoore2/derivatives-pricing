//
// Created by Henry Moore on 21/10/2023.
//

#include "DownAndOutOption.h"
#include "MathsLib.h"

using namespace std;

MatrixXd DownAndOutOption::Payoff(
        const MatrixXd& prices ) const {
    MatrixXd min = prices.rowwise().minCoeff();
    MatrixXd barrier = MatrixXd::Ones(min.rows(), min.cols()) * GetBarrier();
    MatrixXd didnt_hit = (min.array() > barrier.array()).cast<double>();
    MatrixXd p = prices.col(prices.cols()-1);

    p.array() -= GetStrike();
    p = (p.array() < 0).select(0, p);
    p = p.array() * didnt_hit.array();
    return p;
}