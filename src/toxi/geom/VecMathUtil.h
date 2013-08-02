#pragma once

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

