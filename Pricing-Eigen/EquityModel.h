//
// Created by hezza on 11/10/2023.
//

#ifndef PRICINGLIBRARY_EQUITYMODEL_H
#define PRICINGLIBRARY_EQUITYMODEL_H

#include <Eigen/Dense>
#include <random>

using Eigen::MatrixXd;
using Eigen::VectorXd;


// Abstract class for equity model,e.g. b-s, stoch vol, local vol.

class EquityModel {
public:
    virtual MatrixXd generatePricePaths(double toDate,
                              int nPaths,
                              int nSteps) const = 0;

    virtual MatrixXd generateRiskNeutralPricePaths(double toDate,
                                         int nPaths,
                                         int nSteps) const = 0;

    virtual double getRiskFreeRate() const = 0;

    virtual double getDate() const = 0;

private:
    virtual MatrixXd generatePricePaths(
                              double toDate,
                              int nPaths,
                              int nSteps,
                              double drift) const =0;

};


#endif //PRICINGLIBRARY_EQUITYMODEL_H
