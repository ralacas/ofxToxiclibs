#ifndef __INTERPOLATE_STRATEGY_H__
#define __INTERPOLATE_STRATEGY_H__

#ifdef _WIN32
	#pragma once
#endif

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

#endif