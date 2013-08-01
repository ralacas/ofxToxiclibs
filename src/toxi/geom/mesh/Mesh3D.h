#pragma once

#include "Vec3D.h"
#include "Vec2D.h"

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
			class Mesh3D
			{
			public:
				Mesh3D(void);
				~Mesh3D(void);

				virtual Mesh3D addFace(toxi::geom::Vec3D a, toxi::geom::Vec3D b, toxi::geom::Vec3D c);
				virtual Mesh3D addFace(toxi::geom::Vec3D a, toxi::geom::Vec3D b, toxi::geom::Vec3D c, toxi::geom::Vec2D uvA, toxi::geom::Vec2D uvB,	toxi::geom::Vec2D uvC);
				virtual Mesh3D addFace(toxi::geom::Vec3D a, toxi::geom::Vec3D b, toxi::geom::Vec3D c, toxi::geom::Vec3D n);
				virtual Mesh3D addFace(toxi::geom::Vec3D a, toxi::geom::Vec3D b, toxi::geom::Vec3D c, toxi::geom::Vec3D n,toxi::geom:: Vec2D uvA,
					toxi::geom::Vec2D uvB, toxi::geom::Vec2D uvC);
			};
		}
	}
}

