#pragma once

#ifndef __INTERPOLATE_STRATEGY_H__
#define __INTERPOLATE_STRATEGY_H__

#include <iostream>

namespace toxi
{
	namespace math
	{
		class InterpolateStrategy
		{
			public:
				InterpolateStrategy(void);
				~InterpolateStrategy(void);

				virtual double InterpolateStrategy::interpolate( const double & a, const double & b, const double & f ) = 0;
				virtual float InterpolateStrategy::interpolate( const float & a, const float & b, const float & f) = 0;
		};
	}
}

#endif