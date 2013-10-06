#pragma once

#ifndef __STLWRITER_H__
#define __STLWRITER_H__

#include <string>

//#include "../Vec3D.h"
#include "Vertex.h"

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
			class STLWriter
			{
			public:
				STLWriter(void);
				~STLWriter(void);
				void beginSave( std::string path, int numFaces );
				void endSave();
				void setScale( const toxi::geom::Vec3D & v );
				void face( const toxi::geom::mesh::Vertex & a, const toxi::geom::mesh::Vertex & b, const toxi::geom::mesh::Vertex & c, const toxi::geom::Vec3D & normal, const int & type);

				static const int DEFAULT_RGB = 1;
			};

		}
	}
}

#endif