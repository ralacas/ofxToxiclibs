#pragma once

#include "../Vec3D.h"
#include "../Vec2D.h"

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

				virtual Mesh3D* addFace(toxi::geom::Vec3D a, toxi::geom::Vec3D b, toxi::geom::Vec3D c) = 0;
				virtual Mesh3D* addFace(toxi::geom::Vec3D a, toxi::geom::Vec3D b, toxi::geom::Vec3D c, toxi::geom::Vec2D uvA, toxi::geom::Vec2D uvB,	toxi::geom::Vec2D uvC) = 0;
				virtual Mesh3D* addFace(toxi::geom::Vec3D a, toxi::geom::Vec3D b, toxi::geom::Vec3D c, toxi::geom::Vec3D n) = 0;
				virtual Mesh3D* addFace(toxi::geom::Vec3D a, toxi::geom::Vec3D b, toxi::geom::Vec3D c, toxi::geom::Vec3D n,toxi::geom:: Vec2D uvA,
					toxi::geom::Vec2D uvB, toxi::geom::Vec2D uvC) = 0;
			};
		}
	}
}

