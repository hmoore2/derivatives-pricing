//
// Created by Henry Moore on 21/10/2023.
//

#include "DownAndOutOption.h"
#include "MathsLib.h"

using namespace std;

MatrixXd DownAndOutOption::payoff(
        const MatrixXd& prices ) const {
    MatrixXd min = prices.rowwise().minCoeff();
    MatrixXd barrier = MatrixXd::Ones(min.rows(), min.cols()) * getBarrier();
    MatrixXd didntHit = (min.array() > barrier.array()).cast<double>();
    MatrixXd p = prices.col(prices.cols()-1);

    p.array() -=  getStrike();
    p = (p.array() < 0).select(0, p);
    p = p.array() * didntHit.array();
    return p;
}