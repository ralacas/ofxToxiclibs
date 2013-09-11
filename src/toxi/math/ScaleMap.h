#pragma once

#ifndef __SCALE_MAP_H__
#define __SCALE_MAP_H__

#include "LinearInterpolation.h"
#include "MathUtils.h"
#include "../util/datatypes/DoubleRange.h"

namespace toxi
{
	namespace math
	{
		class DoubleRange;
		class MathUtils;
		class LinearInterpolation;
		class InterpolateStrategy;
		class ScaleMap
		{
			public:
				ScaleMap( double minIn, double maxIn, double minOut, double maxOut );
				ScaleMap( const ScaleMap& copyFrom );
				~ScaleMap( void );

				ScaleMap& operator= (const ScaleMap &cSource);

				InterpolateStrategy * mapFunction;
				double *interval;
				double *mapRange;
				toxi::util::datatypes::DoubleRange * in;
				toxi::util::datatypes::DoubleRange * out;

				double getClippedValueFor( double val );
				double getInputMedian( void );
				double getMappedMedian( void );
				double getMappedValueFor( double val );
				double getOutputMedian( void );
				void setInputRange( double min, double max );
				void setMapFunction( toxi::math::InterpolateStrategy * func );
				void setOutputRange( double min, double max );
				
				toxi::util::datatypes::DoubleRange * getOutputRange( void );
				toxi::util::datatypes::DoubleRange * getInputRange( void );
		};
	}
}

#endif