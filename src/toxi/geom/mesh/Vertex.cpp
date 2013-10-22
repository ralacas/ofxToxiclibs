#include "Vertex.h"


toxi::geom::mesh::Vertex::Vertex(void) :
	normal()
{
	//TODO: call super constructor
}

toxi::geom::mesh::Vertex::Vertex( toxi::geom::Vec3D v, int id )
{
	//TODO: call super constructor
	this->id = id;
}


toxi::geom::mesh::Vertex::~Vertex(void)
{
}

void toxi::geom::mesh::Vertex::addFaceNormal( const toxi::geom::Vec3D & n )
{
	normal.addSelf( n );
}

void toxi::geom::mesh::Vertex::clearNormal()
{
	normal.clear( );
}

void toxi::geom::mesh::Vertex::computeNormal()
{
	normal.normalize();
}

std::string toxi::geom::mesh::Vertex::toString()
{
	std::stringstream ss;
	ss << id << ": p: " << *this << " n: " << normal;
	return ss.str();
}
