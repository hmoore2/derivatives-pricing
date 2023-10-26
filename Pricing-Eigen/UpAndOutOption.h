//
// Created by hezza on 11/10/2023.
//

#ifndef PRICINGLIBRARY_UPANDOUTOPTION_H
#define PRICINGLIBRARY_UPANDOUTOPTION_H


#include "KnockoutOption.h"

class UpAndOutOption : public KnockoutOption {
public:
    MatrixXd payoff(
            const MatrixXd& prices ) const;
};



#endif //PRICINGLIBRARY_UPANDOUTOPTION_H
