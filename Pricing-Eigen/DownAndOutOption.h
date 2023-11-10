//
// Created by Henry Moore on 21/10/2023.
//

#ifndef PRICING_DOWNANDOUTOPTION_H
#define PRICING_DOWNANDOUTOPTION_H


#include "KnockoutOption.h"

class DownAndOutOption : public KnockoutOption {
public:
    MatrixXd Payoff(
            const MatrixXd& prices ) const;
};


#endif //PRICING_DOWNANDOUTOPTION_H
