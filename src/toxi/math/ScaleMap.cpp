#include "ScaleMap.h"

namespace toxi
{
	namespace math
	{
		ScaleMap::ScaleMap( void )
		{

		}

		ScaleMap::ScaleMap( const double minIn, const double maxIn, const double minOut, const double maxOut )
		{
			setInputRange( minIn, maxIn );
			setOutputRange( minOut, maxOut );
			mapFunction = LinearInterpolation();
		}

		ScaleMap::ScaleMap(const ScaleMap& copyFrom)
		{
			mapFunction = copyFrom.mapFunction;
			interval = copyFrom.interval;
			mapRange = copyFrom.mapRange;
			in = copyFrom.in;
			out = copyFrom.out;
		}

		ScaleMap::~ScaleMap(void)
		{
		}

		double ScaleMap::getClippedValueFor( double val )
		{
			double cl = ( val - this->in.getMin() ) / this->interval; 
			double t = toxi::math::MathUtils::clipNormalized( cl );
			if ( toxi::math::MathUtils::isNan( t ) ) {
				t = 0;
			}
			return mapFunction.interpolate(this->out.getMin(), this->out.getMax(), t);
		}

		double ScaleMap::getInputMedian( void )
		{
			return (this->in.getMin() + this->in.getMax()) * 0.5;
		}

		double ScaleMap::getMappedMedian( void )
		{
			return this->getMappedValueFor(0.5);
		}

		double ScaleMap::getMappedValueFor( double val )
		{
			double t = ((val - this->in.getMin()) / this->interval);
			
			if ( MathUtils::isNan( t ) ) {
				t = 0;
			}
			
			return this->mapFunction.interpolate(this->out.getMin(), this->out.getMax(), t);
		}

		double ScaleMap::getOutputMedian( void )
		{
			return (this->out.getMin() + this->out.getMax()) * 0.5;
		}

		void ScaleMap::setInputRange( const double min, const double max )
		{
			this->in = toxi::util::datatypes::DoubleRange(min, max);
			this->interval = max - min;
		}

		void ScaleMap::setMapFunction( InterpolateStrategy func )
		{
			this->mapFunction = func;
		}

		void ScaleMap::setOutputRange( const double min, const double max )
		{
			this->out = toxi::util::datatypes::DoubleRange(min, max);
			this->mapRange = max - min;
		}

		ScaleMap& ScaleMap::operator=( const ScaleMap &copyFrom )
		{
			mapFunction = copyFrom.mapFunction;
			interval = copyFrom.interval;
			mapRange = copyFrom.mapRange;
			in = copyFrom.in;
			out = copyFrom.out;
		}

	}
}