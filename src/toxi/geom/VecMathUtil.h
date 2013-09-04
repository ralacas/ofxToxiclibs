#pragma once

#ifndef __VECMATHUTIL_H__
#define __VECMATHUTIL_H__

namespace toxi
{
	namespace geom 
	{
		class VecMathUtil
		{
		public:
			VecMathUtil(void);
			~VecMathUtil(void);

			static long doubleToLongBits( double d );
			static int floatToIntBits( float f );
		};
	}
}

#endif