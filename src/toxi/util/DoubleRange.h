#ifndef __DOUBLE_RANGE_H__
#define __DOUBLE_RANGE_H__

#ifdef _WIN32
	#pragma once
#endif

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
					DoubleRange( const DoubleRange& copyFrom );
					~DoubleRange( void );
					
					double adjustCurrentBy( double& val );
					double getMedian( void ) const;
					double getRange( void ) const;
					bool isValueInRange( double& val );
					double pickRandom( void );
					double setCurrent( const double val );
					double getAt( const double prec ) const;
					DoubleRangeVector toVector( const double step ) const;
					std::string toString( void ) const;

					static DoubleRange* fromSamples( DoubleRangeVector& samples );
				
					double getCurrent( void ) const
					{
						return this->curr_value;
					}

					double getMin( );
					double getMax( );
				
				private:
					double min;
					double max;
					double curr_value;
			};
		}
	}
}

#endif