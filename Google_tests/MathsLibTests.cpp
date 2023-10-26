//
// Created by Henry Moore on 21/10/2023.
//
#include "gtest/gtest.h"
#include "../Pricing-Eigen/MathsLib.h"
#include "../Pricing-Eigen/RandomBase.h"


TEST(MathsLib, Bisection){
    auto lambda = [](double x){
        return pow(x,2) - 2;
    };
    double actual = bisection(lambda,0,2,0.01,0);
    double expected = sqrt(2);
    ASSERT_NEAR( actual, expected, 0.01);

    auto lambda2 = [](double x){
        return sin(x) - 0.5;
    };
    double actual2 = bisection(lambda2,0,2,0.0000001,0);
    double expected2 = PI/6;
    ASSERT_NEAR( actual2, expected2, 0.000001);
}

TEST(MathsLib, randuniform ){
    rng("default");
    MatrixXd m = randuniform(1000,1);
    ASSERT_TRUE( m.rows()==1000 );
    ASSERT_NEAR(m.colwise().mean().mean(), 0.5, 0.1);
    ASSERT_TRUE( m.maxCoeff()<1);
    ASSERT_TRUE( m.minCoeff()>0);
}

TEST(MathsLib, randn){
    rng("default");
    MatrixXd m = randn(10000,1);
    ASSERT_TRUE( m.rows()==10000 );
    ASSERT_NEAR( m.colwise().mean().mean(), 0.0, 0.1);
}

TEST(MathsLib, lambdaIntegral){
    auto lambda = [](double x) {
        return sqrt(1 + pow(sin(x), 2));
    };

    double actual = integrate(lambda, 0, PI, 1000);
    double expected = 3.820197789;
    ASSERT_NEAR(actual, expected, 0.000001);
}


TEST(random, randnMersenne){
    randTest mtr;
    mtr.setDim1(10000);
    mtr.setDim2(1);
    MatrixXd m = mtr.randn();
    ASSERT_TRUE( m.rows()==10000 );
    ASSERT_NEAR( m.colwise().mean().mean(), 0.0, 0.1);
}