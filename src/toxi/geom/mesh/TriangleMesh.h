#pragma once

#include < string >
#include < vector >
#include "Face.h"

namespace toxi 
{
	namespace geom
	{
		namespace mesh
		{
			class TriangleMesh : Mesh3D
			{
			public:
				TriangleMesh( void );
				~TriangleMesh( void );
				static int DEFAULT_NUM_VERTICES;
				static int DEFAULT_NUN_FACES;
				static int DEFAULT_STRIDE;

				std::string name;
				std::vector< Face > faces;

			private:
				
			};
		}
	}
}