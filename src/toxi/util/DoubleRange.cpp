#include <toxi/util/DoubleRange.h>
#include <toxi/math/MathUtils.h>
#include <sstream>
#include <iostream>
#include <cfloat>

namespace toxi
{
	namespace util
	{
		namespace datatypes
		{
			DoubleRange::DoubleRange( void ) :
				min(0.0),
				max(0.0),
				curr_value(0.0)
			{
			}

			DoubleRange::DoubleRange( const double min, const double max ) :
				min((min > max) ? max : min),
				max((min > max) ? min : max),
				curr_value(this->min)
			{
#ifdef DEBUG
				std::cout << "toxi::util::datatypes::DoubleRange::DoubleRange" << std::endl;
				std::cout << "min: " << min << " max: " << max << std::endl;
#endif
				//this->min = ;
				/*this->max = ;
				this->curr_value = this->min;*/

#ifdef DEBUG	
				std::cout << "min: " << this->min << " max: " << this->max << std::endl;
#endif
			}

			DoubleRange::DoubleRange(const DoubleRange& copyFrom ) :
				min(copyFrom.min),
				max(copyFrom.max),
				curr_value(copyFrom.curr_value)
			{
			}

			DoubleRange::~DoubleRange(void)
			{
				this->min = 0.0;
				this->max = 0.0;
				this->curr_value = 0.0;
			}

			std::string DoubleRange::toString( void ) const
			{
				std::stringstream strContent;
				
				strContent << "DoubleRange: " << this->min << " -> " << this->max;
				
				return strContent.str();
			}

			double DoubleRange::adjustCurrentBy( double& val )
			{
				return this->setCurrent(this->curr_value + val);
			}


			double DoubleRange::getMedian( void ) const
			{
				return ( this->min + this->max ) * 0.5;
			}

			double DoubleRange::getRange( void ) const
			{
				return this->max - this->min;
			}

			bool DoubleRange::isValueInRange( double& val )
			{
				return (val >= this->min && val <= this->max);
			}

			double DoubleRange::pickRandom( void )
			{
				this->curr_value = math::MathUtils::random( this->min, this->max );
				return this->curr_value;
			}

			double DoubleRange::setCurrent( const double val )
			{
				this->curr_value = math::MathUtils::clip(val, this->min, this->max);
				return this->curr_value;
			}

			std::vector<double> DoubleRange::toVector( const double step ) const
			{
				std::vector<double> range;
	
				for(double i=this->min; i < this->max; i+=step )
				{
					range.push_back( i );
				}
	
				return range;
			}

			double DoubleRange::getAt(const double prec ) const
			{
				return this->min + (this->max - this->min - math::MathUtils::EPS) * prec;
			}

			DoubleRange* DoubleRange::fromSamples( DoubleRangeVector& samples )
			{
				// this is a perfect example why u should always use this->min instead of only min => because u can't say which one is your
				// local variable and which one is the class property ;)
				double min = DBL_MIN;
				double max = DBL_MAX;

				for( DoubleRangeVector::iterator it = samples.begin(); it < samples.end(); ++it )
				{
					min = math::MathUtils::min(min, *it);
					max = math::MathUtils::max(max, *it);
				}

				return new DoubleRange( min, max );
			}
		}
	}
}