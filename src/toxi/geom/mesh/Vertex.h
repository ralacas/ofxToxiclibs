#pragma once

#ifndef _VERTEX_H__
#define _VERTEX_H__

#include < string >

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
			class Vec3D;
			class Vertex: public toxi::geom::Vec3D
			{
			public:
				Vertex(void);
				Vertex( toxi::geom::Vec3D v, int id );
				~Vertex(void);

				void addFaceNormal( toxi::geom::Vec3D n );
				void clearNormal( );
				void computeNormal( );
				std::string toString( );

				toxi::geom::Vec3D normal;
				int id;
			};
		}
	}
}

#endif