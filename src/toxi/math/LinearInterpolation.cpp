#include "LinearInterpolation.h"


toxi::math::LinearInterpolation::LinearInterpolation(void)
{
}


toxi::math::LinearInterpolation::~LinearInterpolation(void)
{
}

double toxi::math::LinearInterpolation::interpolate( const double & a, const double & b, const double & f )
{
	//std::cout << "Linear Inpolated" << std::endl;
	return a + (b - a) * f;
}

float toxi::math::LinearInterpolation::interpolate( const float & a, const float & b, const float & f )
{
	//std::cout << "Linear Inpolated" << std::endl;
	return a + (b - a) * f;
}
