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

		ScaleMap::ScaleMap(const ScaleMap copyFrom)
		{
		}

		ScaleMap::~ScaleMap(void)
		{
		}

		double ScaleMap::getClippedValueFor( double val )
		{
			double cl = ( val - this->in.min ) / this->interval; 
			double t = toxi::math::MathUtils::clipNormalized( cl );
			if ( toxi::math::MathUtils::isNan( t ) ) {
				t = 0;
			}
			return mapFunction.interpolate(this->out.min, this->out.max, t);
		}

		double ScaleMap::getInputMedian( void )
		{
			return (this->in.min + this->in.max) * 0.5;
		}

		double ScaleMap::getMappedMedian( void ) const
		{
			return this->getMappedValueFor(0.5);
		}

		double ScaleMap::getMappedValueFor( const double val ) const
		{
			double t = ((val - this->in.min) / this->interval);
			
			if ( MathUtils::isNan( t ) ) {
				t = 0;
			}
			
			return this->mapFunction.interpolate(this->out.min, this->out.max, t);
		}

		double ScaleMap::getOutputMedian( void )
		{
			return (this->out.min + this->out.max) * 0.5;
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
	}
}