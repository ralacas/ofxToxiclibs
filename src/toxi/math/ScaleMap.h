#pragma once

#ifndef __SCALE_MAP_H__
#define __SCALE_MAP_H__

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
				ScaleMap( void );
				ScaleMap( double minIn, double maxIn, double minOut, double maxOut );
				ScaleMap(const ScaleMap& copyFrom);
				~ScaleMap( void );

				ScaleMap& operator= (const ScaleMap &cSource);

			protected:
				InterpolateStrategy * mapFunction;
				double interval;
				double mapRange;
				DoubleRange * in;
				DoubleRange * out;

			public:
				double getClippedValueFor( double val );
				double getInputMedian( void );
				double getMappedMedian( void );
				double getMappedValueFor( double val );
				double getOutputMedian( void );
				void setInputRange( double min, double max );
				void setMapFunction( toxi::math::InterpolateStrategy func );
				void setOutputRange( double min, double max );
				
				DoubleRange * getOutputRange( void ) const
				{
					return this->out;
				}
				
				DoubleRange * getInputRange( void ) const
				{
					return this->in;
				}
		};
	}
}

#endif