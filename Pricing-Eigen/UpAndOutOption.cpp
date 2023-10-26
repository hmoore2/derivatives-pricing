//
// Created by hezza on 11/10/2023.
//

#include "UpAndOutOption.h"
#include "MathsLib.h"

using namespace std;

MatrixXd UpAndOutOption::payoff(
        const MatrixXd& prices ) const {
    MatrixXd max = prices.rowwise().maxCoeff();
    MatrixXd barrier = MatrixXd::Ones(max.rows(), max.cols()) * getBarrier();
    MatrixXd didntHit = (max.array() < barrier.array()).cast<double>();
    MatrixXd p = prices.col(prices.cols()-1);
    p.array() -=  getStrike();
    p = (p.array() < 0).select(0, p);

    p = p.array() * didntHit.array();
    return p;
}

/////////////////////////////////////
//
//   TESTS
//
/////////////////////////////////////


