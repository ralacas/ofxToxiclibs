#include "Face.h"


toxi::geom::mesh::Face::Face(void)
{
	//TODO implement this
}


toxi::geom::mesh::Face::~Face(void)
{
}

toxi::geom::Triangle3D toxi::geom::mesh::Face::toTriangle()
{
	return toxi::geom::Triangle3D( a, b, c );
}
