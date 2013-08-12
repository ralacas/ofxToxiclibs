#pragma once

#include "Intersector3D.h"

namespace toxi
{
	namespace geom
	{
		class TriangleIntersector :
			public toxi::geom::Intersector3D
		{
		public:
			TriangleIntersector(void);
			TriangleIntersector( Triangle3D t );
			~TriangleIntersector(void);

			Triangle3D triangle;

			IsectData3D getIntersectionData();
			Triangle3D getTriangle();
			bool intersectsRay( Ray3D ray );
			TriangleIntersector setTriangle( Triangle3D tri );

		private:
			IsectData3D isectData;
		};
	}
}


