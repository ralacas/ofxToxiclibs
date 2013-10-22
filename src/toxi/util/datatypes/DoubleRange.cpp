#include <toxi/util/datatypes/DoubleRange.h>
#include <toxi/math/MathUtils.h>

#include <sstream>
#include <iostream>
#include <cfloat>
#include <iomanip>

namespace toxi
{
	namespace util
	{
		namespace datatypes
		{
			DoubleRange::DoubleRange( void )
			{
				min = new double;
				max = new double;
				curr_value = new double;

				*min = 0.0;
				*max = 0.0;
				*curr_value = 0.0;
			}

			DoubleRange::DoubleRange( const double min, const double max )
			{
				this->min = new double;
				this->max = new double;
				this->curr_value = new double;

				*this->min = (min > max) ? max : min;
				*this->max = (min > max) ? min : max;
				*this->curr_value = *this->min;
			}

			DoubleRange::DoubleRange(const DoubleRange& copyFrom )
			{
				this->min = new double;
				this->max = new double;
				this->curr_value = new double;

				*this->min = *copyFrom.min;
				*this->max = *copyFrom.max;
				*this->curr_value = *copyFrom.curr_value;
			}

			DoubleRange::DoubleRange( DoubleRangeVector* samples )
			{
				double _min = DBL_MAX;
				double _max = DBL_MIN;

				for( auto it = samples->begin(); it < samples->end(); ++it )
				{
					_min = math::MathUtils::min(_min, *it);
					_max = math::MathUtils::max(_max, *it);
				}

				this->min = new double;
				this->max = new double;
				this->curr_value = new double;

				*this->min = _min;
				*this->max = _max;
				*this->curr_value = _min;
			}

			DoubleRange::~DoubleRange(void)
			{
				delete min;
				delete max;
				delete curr_value;
			}

			double DoubleRange::adjustCurrentBy( double val )
			{
				return this->setCurrent( *this->curr_value + val );
			}
			
			double DoubleRange::getMedian( void )
			{
				return ( *this->min + *this->max ) * 0.5;
			}

			double DoubleRange::getRange( void )
			{
				return *this->max - *this->min;
			}

			bool DoubleRange::isValueInRange( double val )
			{
				return (val >= *this->min && val <= *this->max);
			}

			double DoubleRange::pickRandom( void )
			{
				*this->curr_value = math::MathUtils::random( *this->min, *this->max );
				return *this->curr_value;
			}

			double DoubleRange::setCurrent( const double val )
			{
				*this->curr_value = math::MathUtils::clip(val, *this->min, *this->max);
				return *this->curr_value;
			}

			std::vector<double> DoubleRange::toVector( const double step )
			{
				std::vector<double> range;
	
				for(double i = *this->min; i < *this->max; i+=step )
				{
					range.push_back( i );
				}
	
				return range;
			}

			double DoubleRange::getAt(const double prec )
			{
				std::cerr << "The untested function DoubleRange::getAt( double prec ) has just been called. Handle with care." << std::endl;
				return *this->min + ( *this->max - *this->min - math::MathUtils::EPS) * prec;
			}

			double DoubleRange::getCurrent()
			{
				return *curr_value;
			}

			double DoubleRange::getMin() const
			{
				return *min;
			}

			double DoubleRange::getMax() const
			{
				return *max;
			}

			DoubleRange& DoubleRange::operator=( const DoubleRange &cSource )
			{
				*this->min = *cSource.min;
				*this->max = *cSource.max;
				*this->curr_value = *cSource.curr_value;
				return *this;
			}

		}
	}
}