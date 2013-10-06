#pragma once

#ifndef _VERTEX_H__
#define _VERTEX_H__

#include < string >

#include "../Vec3D.h"

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
				Vertex( Vec3D v, int id );
				~Vertex(void);

				void addFaceNormal( const Vec3D & n );
				void clearNormal( );
				void computeNormal( );
				std::string toString( );

				Vec3D normal;
				int id;
			};
		}
	}
}

#endif