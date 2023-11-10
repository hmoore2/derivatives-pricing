#pragma once

#include "stdafx.h"
#include "BlackScholesModel.h"
#include "EarlyExerciseOptionBase.h"


class AmericanCallOption : public EarlyExerciseOptionBase {
public:
	double Price(const BlackScholesModel& bsm, int n_asset_steps)
		const;
};

