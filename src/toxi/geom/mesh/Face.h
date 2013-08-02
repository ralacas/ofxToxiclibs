#pragma once

#include "Vertex.h"
#include "..\Vec2D.h"
#include "..\Vec3D.h"
#include "..\Triangle3D.h"
#include < vector >
#include < string >
namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
			class Face
			{
			public:
				Face( Vertex a, Vertex b, Vertex c );
				Face( Vertex a, Vertex b, Vertex c, Vec2D uvA, Vec2D uvB, Vec2D uvC );
				~Face(void);

				Vertex a, b, c;
				Vec2D uvA, uvB, uvC;
				Vec3D normal;

				void computeNormal();
				void flipVertexOrder();
				Vec3D getCentroid( );
				Vertex* getVertices( );
				std::string toString( );
				toxi::geom::Triangle3D toTriangle( );
				
			};
		}
	}
}


