#pragma once

#ifndef __LINEAR_INTERPOLATION_H__
#define __LINEAR_INTERPOLATION_H__

#include "InterpolateStrategy.h"
#include <stdio.h>

namespace toxi
{
	namespace math
	{
		class LinearInterpolation : public InterpolateStrategy
		{
			public:
				LinearInterpolation(void);
				~LinearInterpolation(void);

				double interpolate(const double & a, const double & b, const double & f); 
				float interpolate(const float & a, const float & b, const float & f);
		};
	}
}

#endif