#include "Face.h"


toxi::geom::mesh::Face::Face(void)
{
}


toxi::geom::mesh::Face::~Face(void)
{
}

toxi::geom::Triangle3D toxi::geom::mesh::Face::toTriangle()
{
	return Triangle3D( a, b, c );
}
