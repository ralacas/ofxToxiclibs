#pragma once

#ifndef __FACE_H__
#define __FACE_H__

#include < vector >
#include < string >

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
			class Vertex;
			class Triangle3D;
			class Vec2D;
			class Vec3D;
			class Face
			{
			public:
				Face( void );
				Face( Vertex a, Vertex b, Vertex c );
				Face( Vertex a, Vertex b, Vertex c, Vec2D uvA, Vec2D uvB, Vec2D uvC );
				~Face(void);

				toxi::geom::mesh::Vertex *a, *b, *c;
				toxi::geom::Vec2D uvA, uvB, uvC;
				toxi::geom::Vec3D normal;

				void computeNormal();
				void flipVertexOrder();
				toxi::geom::Vec3D getCentroid( );
				Vertex* getVertices( );
				std::string toString( );
				toxi::geom::Triangle3D toTriangle( );
				
			};
		}
	}
}

#endif
