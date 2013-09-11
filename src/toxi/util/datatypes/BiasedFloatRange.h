#ifndef __BIASED_FLOAT_RANGE_H__
#define __BIASED_FLOAT_RANGE_H__

#pragma once

#include "FloatRange.h"

namespace toxi
{
	namespace util
	{
		namespace datatypes
		{
			class BiasedFloatRange : public FloatRange
			{
			public:
				BiasedFloatRange(void);
				BiasedFloatRange( float min, float max, float bias, float sd );
				~BiasedFloatRange(void);

				float bias;
				float standardDeviation;

				float pickRandom( void );
			};

		}
	}
}

#endif