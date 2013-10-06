#include "Random.h"
#include <ctime>

toxi::util::Random::Random(void) 
{
	
}


toxi::util::Random::~Random(void)
{
	
}

double toxi::util::Random::getRandom( double min, double max )
{
	std::random_device rnd_dev;
	//dre.seed( std::time(0) );
	std::uniform_real_distribution<double> dr( min, max );
	return dr( rnd_dev );
}

double toxi::util::Random::getRandom( long min, long max )
{
	std::random_device rnd_dev;
	//dre.seed( std::time(0) );
	std::uniform_real_distribution<double> dr( min, max );
	return dr( rnd_dev );
}
