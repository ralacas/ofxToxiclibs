#pragma once

#ifndef __TRIANGLEINTERSECTOR_H__
#define __TRIANGLEINTERSECTOR_H__

namespace toxi
{
	namespace geom
	{
		class Triangle3D;
		class IsectData3D;
		class Ray3D;
		class TriangleIntersector :
			public toxi::geom::Intersector3D
		{
		public:
			TriangleIntersector(void);
			TriangleIntersector( Triangle3D t );
			~TriangleIntersector(void);

			Triangle3D * triangle;

			IsectData3D getIntersectionData();
			Triangle3D getTriangle();
			bool intersectsRay( Ray3D ray );
			TriangleIntersector setTriangle( Triangle3D tri );

		private:
			IsectData3D * isectData;
		};
	}
}

#endif