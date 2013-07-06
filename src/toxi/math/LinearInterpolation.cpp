#include "LinearInterpolation.h"


toxi::math::LinearInterpolation::LinearInterpolation(void)
{
}


toxi::math::LinearInterpolation::~LinearInterpolation(void)
{
}

double toxi::math::LinearInterpolation::interpolate( double a, double b, double f )
{
	return a + (b - a) * f;
}

float toxi::math::LinearInterpolation::interpolate( float a, float b, float f )
{
	return a + (b - a) * f;
}
