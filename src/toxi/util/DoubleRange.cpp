#include "DoubleRange.h"


toxi::util::datatypes::DoubleRange::DoubleRange( double& _min, double& _max )
{
	std::cout << "toxi::util::datatypes::DoubleRange::DoubleRange" << std::endl;
	std::cout << "min: " << min << " max: " << max << std::endl;
	if ( _min > _max ) 
	{
		double t = _max;
		_max = min;
		_min = t;
	}

	min = _min;
	max = _max;
	curr_value = min;
	std::cout << "min: " << min << " max: " << max << std::endl;
}

toxi::util::datatypes::DoubleRange::DoubleRange( DoubleRange& copyTo )
{
	copyTo.curr_value = curr_value;
	copyTo.min = min;
	copyTo.max = max;
}


toxi::util::datatypes::DoubleRange::~DoubleRange(void)
{
}

std::string toxi::util::datatypes::DoubleRange::to_string( void )
{
	std::stringstream s;
	s << "DoubleRange: " << min << " -> " << max;
	std::string return_string = "DoubleRange: ";
	return s.str();
}

double toxi::util::datatypes::DoubleRange::adjustCurrentBy( double& val )
{
	double re = curr_value + val;
	return setCurrent( re );
}

double toxi::util::datatypes::DoubleRange::getCurrent( void )
{
	return curr_value;
}

double toxi::util::datatypes::DoubleRange::getMedian( void )
{
	return ( min + max ) * 0.5f;
}

double toxi::util::datatypes::DoubleRange::getRange( void )
{
	return max - min;
}

bool toxi::util::datatypes::DoubleRange::isValueInRange( double& val )
{
	return val >= min && val <= max;
}

double toxi::util::datatypes::DoubleRange::pickRandom( void )
{
	curr_value = toxi::math::MathUtils::random( min, max );
	return curr_value;
}

double toxi::util::datatypes::DoubleRange::setCurrent( double& val )
{
	curr_value = toxi::math::MathUtils::clip(val, min, max);
	return curr_value;
}

std::vector<double> toxi::util::datatypes::DoubleRange::toVector( double& step )
{
	std::vector<double> range;
	double part = ( max - min ) / step;
	for(double i=min; i<max; i+=step )
	{
		range.push_back( i );
	}
	return range;
}

double toxi::util::datatypes::DoubleRange::getAt( double& prec )
{
	double re = min + (max - min - toxi::math::MathUtils::EPS) * prec;
	return re;
}

toxi::util::datatypes::DoubleRange* toxi::util::datatypes::DoubleRange::fromSamples( std::vector< double >& samples )
{
	double min = DBL_MIN;
	double max = DBL_MAX;

	for( auto it = samples.begin(); it < samples.end(); ++it )
	{
		min = toxi::math::MathUtils::min(min, *it);
		max = toxi::math::MathUtils::max(max, *it);
	}

	return new toxi::util::datatypes::DoubleRange( min, max );
}
