#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "../math/MathUtils.h"

namespace toxi
{
	namespace util
	{
		namespace datatypes
		{
			class DoubleRange
			{
			public:
				DoubleRange( double& min, double& max );
				DoubleRange( DoubleRange& copyTo );
				~DoubleRange(void);
				double adjustCurrentBy( double& val );
				double getCurrent( void );
				double getMedian( void );
				double getRange( void );
				bool isValueInRange( double& val );
				double pickRandom( void );
				double setCurrent( double& val );
				std::vector<double> toVector( double& step );


				double getAt( double& prec );
				
				
				std::string to_string( void );

				static toxi::util::datatypes::DoubleRange* fromSamples( std::vector< double >& samples );

			private:
				double min, max, curr_value;
			};

			
		}
	}
}
