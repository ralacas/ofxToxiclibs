#ifndef __FLOAT_RANGE_H__
#define __FLOAT_RANGE_H__

#pragma once

namespace toxi
{
	namespace util
	{
		namespace datatypes
		{
			class FloatRange
			{
			public:
				FloatRange(void);
				~FloatRange(void);

				float min, max;
				float curr_value;
			};
		}
	}
}

#endif