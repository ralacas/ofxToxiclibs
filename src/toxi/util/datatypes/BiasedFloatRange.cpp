#include "BiasedFloatRange.h"


toxi::util::datatypes::BiasedFloatRange::BiasedFloatRange(void)
	: bias( 0.5f ),
	  standardDeviation( bias * 0.5f )
{
}

toxi::util::datatypes::BiasedFloatRange::BiasedFloatRange( float min, float max, float bias, float sd )
	: bias( 0.5f ),
	standardDeviation( bias * 0.5f )
{

}


toxi::util::datatypes::BiasedFloatRange::~BiasedFloatRange(void)
{
}

float toxi::util::datatypes::BiasedFloatRange::pickRandom( void )
{
	// TODO: Java#s random class nextGaussian()
	do {
		curr_value = (float) (0.0 * standardDeviation * (max - min))
			+ bias;
	} while (curr_value < min || curr_value >= max);
	return curr_value;
}
