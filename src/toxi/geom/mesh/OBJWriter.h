#pragma once

#ifndef __OBJWRITER_H__
#define __OBJWRITER_H__

#include <string>

#include "../Vec3D.h"
//#include "Vertex.h"

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
			class Vertex;
			class Vec3D;
			class OBJWriter
			{
			public:
				OBJWriter(void);
				~OBJWriter(void);
				int getCurrVertexOffset();
				int getCurrNormalOffset();
				void newObject( std::string name );
				void vertex( toxi::geom::mesh::Vertex * v );
				void normal( toxi::geom::Vec3D * normal );
				void faceWithNormals( int a, int b, int c, int d, int e, int f );
				void face( int a, int b, int c );
				void beginSave( std::string path );
				void endSave();
			};

		}
	}
}

#endif