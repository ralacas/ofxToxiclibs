#ifndef __SCALE_MAP_H__
#define __SCALE_MAP_H__

#ifdef _WIN32
	#pragma once
#endif

#include "LinearInterpolation.h"
#include "..\util\DoubleRange.h"
#include "MathUtils.h"

namespace toxi
{
	namespace math
	{
		class ScaleMap
		{
			public:
				ScaleMap( void );
				ScaleMap( double minIn, double maxIn, double minOut, double maxOut );
				ScaleMap(const ScaleMap copyFrom);
				~ScaleMap( void );

			protected:
				InterpolateStrategy mapFunction;
				double interval;
				double mapRange;
				util::datatypes::DoubleRange in;
				util::datatypes::DoubleRange out;

			public:
				double getClippedValueFor( double val );
				double getInputMedian( void );
				double getMappedMedian( void );
				double getMappedValueFor( double val );
				double getOutputMedian( void );
				void setInputRange( double min, double max );
				void setMapFunction( toxi::math::InterpolateStrategy func );
				void setOutputRange( double min, double max );
				
				util::datatypes::DoubleRange getOutputRange( void ) const
				{
					return this->out;
				}
				
				util::datatypes::DoubleRange getInputRange( void ) const
				{
					return this->in;
				}
		};
	}
}

#endif