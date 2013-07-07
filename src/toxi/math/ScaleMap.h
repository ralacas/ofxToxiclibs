#pragma once

#include "LinearInterpolation.h"
#include "InterpolateStrategy.h"
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
			~ScaleMap( void );

		protected:
			InterpolateStrategy mapFunction;
			double interval, mapRange;
			toxi::util::datatypes::DoubleRange in;
			toxi::util::datatypes::DoubleRange out;

		public:
			double getClippedValueFor( double val );
			double getInputMedian( void );
			toxi::util::datatypes::DoubleRange getInputRange( void );
			double getMappedMedian( void );
			double getMappedValueFor( double val );
			double getOutputMedian( void );
			toxi::util::datatypes::DoubleRange getOutputRange( void );
			void setInputRange( double min, double max );
			void setMapFunction( toxi::math::InterpolateStrategy func );
			void setOutputRange( double min, double max );
		};
	}
}
