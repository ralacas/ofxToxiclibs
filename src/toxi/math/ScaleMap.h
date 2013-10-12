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
				ScaleMap( const double & minIn, const double & maxIn, const double & minOut, const double & maxOut );
				ScaleMap( const ScaleMap& copyFrom );
				~ScaleMap( void );

				ScaleMap& operator= (const ScaleMap &cSource);

				toxi::math::InterpolateStrategy * mapFunction;
				double interval;
				double mapRange;
				toxi::util::datatypes::DoubleRange in;
				toxi::util::datatypes::DoubleRange out;

				double getClippedValueFor( const double & val ) const;
				double getInputMedian( void );
				double getMappedMedian( void );
				double getMappedValueFor( const double & val );
				double getOutputMedian( void );
				void setInputRange( const double & min, const double & max );
				void setMapFunction( toxi::math::InterpolateStrategy & func );
				void setOutputRange( const double & min, const double & max );
				
				toxi::util::datatypes::DoubleRange getOutputRange( void );
				toxi::util::datatypes::DoubleRange getInputRange( void );
		};
	}
}

#endif