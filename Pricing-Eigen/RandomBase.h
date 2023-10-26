//
// Created by Henry Moore on 22/10/2023.
//

#ifndef PRICING_RANDOMBASE_H
#define PRICING_RANDOMBASE_H

#include "MathsLib.h"
#include <string>

static std::mt19937 mersenneTwister;

class RandomBase {
public:
     virtual MatrixXd randUniform()  = 0;
     virtual MatrixXd randn()  = 0;

     //virtual void reset() = 0;

     inline unsigned long getDim1() const{
         return dim1;
     }

    inline unsigned long getDim2() const{
        return dim2;
    }

    void setDim1(int dimension) {
        dim1 = dimension;
    }

    void setDim2(int dimension) {
        dim2 = dimension;
    }

private:
    long int dim1, dim2;

};

class randTest : public RandomBase{
public:

    MatrixXd randUniform() ;

    MatrixXd randn();

    /*  MersenneTwister random number generator */

private:

};


#endif //PRICING_RANDOMBASE_H
