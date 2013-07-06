#pragma once

#include "InterpolateStrategy.h"

class LinearInterpolation :
	public InterpolateStrategy
{
public:
	LinearInterpolation(void);
	~LinearInterpolation(void);

public:
	double interpolate(double a, double b, double f);
	float interpolate(float a, float b, float f);
};

