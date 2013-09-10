#pragma once

#ifndef __DOUBLE_RANGE_H__
#define __DOUBLE_RANGE_H__

#include <vector>
#include <string>

namespace toxi
{
	namespace util
	{
		namespace datatypes
		{
			typedef std::vector<double> DoubleRangeVector;
			
			class DoubleRange
			{
				public:
					DoubleRange( void );
					DoubleRange( const double min, const double max );
					DoubleRange( DoubleRangeVector* samples );
					DoubleRange( const DoubleRange& copyFrom );
					~DoubleRange( void );
					
					double adjustCurrentBy( double val );
					double getMedian( void );
					double getRange( void );
					bool isValueInRange( double val );
					double pickRandom( void );
					double setCurrent( double val );
					double getAt( double prec );
					DoubleRangeVector toVector( double step );
					std::string toString( void ) const;
				
					double getCurrent( void );
					double getMin( void );
					double getMax( void );
				
				private:
					double * min;
					double * max;
					double * curr_value;
			};
		}
	}
}

#endif