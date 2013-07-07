#include "ScaleMap.h"

toxi::math::ScaleMap::ScaleMap( void )
{

}

toxi::math::ScaleMap::ScaleMap( double minIn, double maxIn, double minOut, double maxOut )
{
	setInputRange( minIn, maxIn );
	setOutputRange( minOut, maxOut );
	mapFunction = LinearInterpolation();
}


toxi::math::ScaleMap::~ScaleMap(void)
{
}

double toxi::math::ScaleMap::getClippedValueFor( double val )
{
	double cl = ( val - in.min ) / interval; 
	double t = toxi::math::MathUtils::clipNormalized( cl );
	if ( toxi::math::MathUtils::isNan( t ) ) {
		t = 0;
	}
	return mapFunction.interpolate(out.min, out.max, t);
}

double toxi::math::ScaleMap::getInputMedian( void )
{
	return (in.min + in.max) * 0.5;
}

toxi::util::datatypes::DoubleRange toxi::math::ScaleMap::getInputRange( void )
{
	 return in;
}

double toxi::math::ScaleMap::getMappedMedian( void )
{
	return getMappedValueFor(0.5);
}

double toxi::math::ScaleMap::getMappedValueFor( double val )
{
	double t = ((val - in.min) / interval);
	if ( toxi::math::MathUtils::isNan( t ) ) {
		t = 0;
	}
	return mapFunction.interpolate(out.min, out.max, t);
}

double toxi::math::ScaleMap::getOutputMedian( void )
{
	return (out.min + out.max) * 0.5;
}

toxi::util::datatypes::DoubleRange toxi::math::ScaleMap::getOutputRange( void )
{
	return out;
}

void toxi::math::ScaleMap::setInputRange( double min, double max )
{
	in = toxi::util::datatypes::DoubleRange(min, max);
	interval = max - min;
}

void toxi::math::ScaleMap::setMapFunction( toxi::math::InterpolateStrategy func )
{
	mapFunction = func;
}

void toxi::math::ScaleMap::setOutputRange( double min, double max )
{
	out = toxi::util::datatypes::DoubleRange(min, max);
	mapRange = max - min;
}
