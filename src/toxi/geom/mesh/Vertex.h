#pragma once

#include "..\Vec3D.h"
#include < string >

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
			class Vertex: public Vec3D
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


