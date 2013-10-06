#pragma once

#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <random>
#include <algorithm>

namespace toxi
{
	namespace util
	{
		class Random
		{

		private:
			std::random_device rnd_dev;
			//std::default_random_engine dre;

		public:
			Random( void );
			~Random(void);

			static double getRandom( double min, double max );
			static double getRandom( long min, long max );
		};
	}
}

#endif