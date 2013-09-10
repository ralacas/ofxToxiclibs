#include "ScaleMap.h"

namespace toxi
{
	namespace math
	{

		ScaleMap::ScaleMap( const double minIn, const double maxIn, const double minOut, const double maxOut )
		{
			this->interval = new double;
			this->mapRange = new double;
			setInputRange( minIn, maxIn );
			setOutputRange( minOut, maxOut );
			mapFunction = new toxi::math::LinearInterpolation();
		}

		ScaleMap::ScaleMap(const ScaleMap& copyFrom)
		{
			this->mapFunction = copyFrom.mapFunction;
			this->interval = copyFrom.interval;
			this->mapRange = copyFrom.mapRange;
			this->in = copyFrom.in;
			this->out = copyFrom.out;
		}

		ScaleMap::~ScaleMap(void)
		{
			delete mapFunction;
			delete interval;
			delete mapRange;
			delete in;
			delete out;
		}

		double ScaleMap::getClippedValueFor( double val )
		{
			double cl = ( val - in->getMin() ) / *this->interval; 
			double t = toxi::math::MathUtils::clipNormalized( cl );
			if ( toxi::math::MathUtils::isNan( t ) ) {
				t = 0;
			}
			return mapFunction->interpolate(out->getMin(), out->getMax(), t);
		}

		double ScaleMap::getInputMedian( void )
		{
			return (in->getMin() + in->getMax()) * 0.5;
		}

		double ScaleMap::getMappedMedian( void )
		{
			return this->getMappedValueFor(0.5);
		}

		double ScaleMap::getMappedValueFor( double val )
		{
			double t = ((val - in->getMin()) / *this->interval);
			
			if ( MathUtils::isNan( t ) ) {
				t = 0;
			}
			
			return mapFunction->interpolate(out->getMin(), out->getMax(), t);
		}

		double ScaleMap::getOutputMedian( void )
		{
			return ( out->getMin() + out->getMax() ) * 0.5;
		}

		void ScaleMap::setInputRange( const double min, const double max )
		{
			
			this->in = new toxi::util::datatypes::DoubleRange( min, max );
			*this->interval = max - min;
		}

		void ScaleMap::setMapFunction( InterpolateStrategy *  func )
		{
			this->mapFunction = func;
		}

		void ScaleMap::setOutputRange( const double min, const double max )
		{
			this->out = new toxi::util::datatypes::DoubleRange(min, max);
			*this->mapRange = max - min;
		}

		ScaleMap& ScaleMap::operator=( const ScaleMap &copyFrom )
		{
			mapFunction = copyFrom.mapFunction;
			interval = copyFrom.interval;
			mapRange = copyFrom.mapRange;
			in = copyFrom.in;
			out = copyFrom.out;
		}

		toxi::util::datatypes::DoubleRange * ScaleMap::getOutputRange( void )
		{
			return this->out;
		}

		toxi::util::datatypes::DoubleRange * ScaleMap::getInputRange( void )
		{
			return this->in;
		}

	}
}