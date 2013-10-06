#pragma once

#ifndef __FACE_H__
#define __FACE_H__

#include < vector >
#include < string >

#include "../Triangle3D.h"
#include "../Vec2D.h"
#include "Vertex.h"

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
			class Vertex;
			class Vec2D;
			class toxi::geom::Triangle3D;
			class Face
			{
			public:
				Face( void );
				Face(  toxi::geom::mesh::Vertex & a,  toxi::geom::mesh::Vertex & b, toxi::geom::mesh::Vertex & c );
				Face( toxi::geom::mesh::Vertex & a, toxi::geom::mesh::Vertex & b, toxi::geom::mesh::Vertex & c, const toxi::geom::Vec2D & uvA, const toxi::geom::Vec2D & uvB, const toxi::geom::Vec2D & uvC );
				~Face(void);

				toxi::geom::mesh::Vertex a, b, c;
				toxi::geom::Vec2D uvA, uvB, uvC;
				toxi::geom::Vec3D normal;

				void computeNormal();
				void flipVertexOrder();
				toxi::geom::Vec3D getCentroid( );
				std::vector< Vertex >  getVertices( );
				std::string toString( );
				toxi::geom::Triangle3D toTriangle( );
				
			};
		}
	}
}

#endif
