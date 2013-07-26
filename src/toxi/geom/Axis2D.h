#pragma once

#include "Vec2D.h"

namespace toxi
{
	namespace geom
	{
		class Axis2D
		{
		public:
			Axis2D( void );
			//Axis2D( Vec2D v );
			~Axis2D( void );

			Vec2D* getVector( void );
			static Vec2D X_AXIS( void );
			static Vec2D Y_AXIS( void );;
			static Vec2D ZERO( void );
			static Vec2D MIN_VALUE( void );
			static Vec2D MAX_VALUE( void );

		private:
			Vec2D vector;
		};


	}
}
