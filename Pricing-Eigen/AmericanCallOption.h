#pragma once

#include "stdafx.h"
#include "BlackScholesModel.h"
#include "EarlyExerciseOptionBase.h"


class AmericanCallOption : public EarlyExerciseOptionBase {
public:
	double price(const BlackScholesModel& bsm, int numAssetSteps)
		const;
};

