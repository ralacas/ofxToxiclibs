#pragma once

#include "InterpolateStrategy.h"

namespace toxi
{
	namespace math
	{
		class LinearInterpolation :
			public InterpolateStrategy
		{
		public:
			LinearInterpolation(void);
			~LinearInterpolation(void);

			virtual double interpolate(double a, double b, double f);
			virtual float interpolate(float a, float b, float f);
		};
	}
}