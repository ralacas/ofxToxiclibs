#ifndef __LINEINTERSECTION_3D_H__
#define __LINEINTERSECTION_3D_H__

#pragma once

namespace toxi
{
	namespace geom
	{
		class Line3D;
		class LineIntersection3D
		{
		public:
			static enum Type { NON_INTERSECTING, INTERSECTING };

			LineIntersection3D(void);
			LineIntersection3D( toxi::geom::LineIntersection3D::Type type );
			LineIntersection3D( toxi::geom::LineIntersection3D::Type type, Line3D line, float mua, float mub );
			~LineIntersection3D(void);
		};
	}
}

#endif