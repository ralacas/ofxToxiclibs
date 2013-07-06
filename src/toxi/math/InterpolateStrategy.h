#pragma once

namespace toxi
{
	namespace math
	{
		class InterpolateStrategy
		{
		public:
			InterpolateStrategy(void);
			~InterpolateStrategy(void);

			virtual double InterpolateStrategy::interpolate( double a, double b, double f );
			virtual float InterpolateStrategy::interpolate( float a, float b, float f);
		};


	}
}
