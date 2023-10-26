//
// Created by Henry Moore on 22/10/2023.
//

#include "RandomBase.h"

MatrixXd randTest::randUniform()  {
    MatrixXd ret(getDim1(), getDim2());
    for (int i=0; i<getDim1(); i++) {
        for (int j=0; j<getDim2(); j++) {
            ret(i, j) = (mersenneTwister() + 0.5) /(mersenneTwister.max() + 1.0);
        }
    }
    return ret;
}

/*  Create normally distributed random numbers */
MatrixXd randTest::randn() {
    MatrixXd ret = randuniform(getDim1(), getDim2() );
    for (int j=0; j<getDim2(); j++) {
        for (int i=0; i<getDim1(); i++) {
            ret(i,j)=norminv( ret(i,j) );
        }
    }
    return ret;
}