#include "Axis2D.h"

namespace toxi
{
	namespace geom
	{
		toxi::geom::Axis2D::Axis2D(  )
		{
			vector = ZERO();
		}

/*		toxi::geom::Axis2D::Axis2D( toxi::geom::Vec2D vec )
		{
			vector = vec;
		}*/


		toxi::geom::Axis2D::~Axis2D(void)
		{
		}

		toxi::geom::Vec2D * toxi::geom::Axis2D::getVector( void )
		{
			return vector;
		}


		toxi::geom::Vec2D * Axis2D::X_AXIS( void )
		{
			return new toxi::geom::Vec2D( 1, 0 );
		}

		toxi::geom::Vec2D * Axis2D::Y_AXIS( void )
		{
			return new toxi::geom::Vec2D( 0, 1 );
		}

		toxi::geom::Vec2D * Axis2D::ZERO( void )
		{
			return new toxi::geom::Vec2D( 0, 0 );
		}

		toxi::geom::Vec2D * Axis2D::MIN_VALUE( void )
		{
			return new toxi::geom::Vec2D( DBL_MIN, DBL_MIN );
		}

		toxi::geom::Vec2D * Axis2D::MAX_VALUE( void )
		{
			return new toxi::geom::Vec2D( DBL_MAX, DBL_MAX );
		}

	}
}