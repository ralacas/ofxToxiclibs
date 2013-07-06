#include "LinearInterpolation.h"


LinearInterpolation::LinearInterpolation(void)
{
}


LinearInterpolation::~LinearInterpolation(void)
{
}

double LinearInterpolation::interpolate( double a, double b, double f )
{
	return a + (b - a) * f;
}

float LinearInterpolation::interpolate( float a, float b, float f )
{
	return a + (b - a) * f;
}
