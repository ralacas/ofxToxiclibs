#pragma once

#ifndef __LINEAR_INTERPOLATION_H__
#define __LINEAR_INTERPOLATION_H__

#include "InterpolateStrategy.h"

namespace toxi
{
	namespace math
	{
		class LinearInterpolation : public InterpolateStrategy
		{
			public:
				LinearInterpolation(void);
				~LinearInterpolation(void);

				double interpolate(double a, double b, double f);
				float interpolate(float a, float b, float f);
		};
	}
}

#endif