#include "Face.h"


toxi::geom::mesh::Face::Face(void)
{
	this->a = 0;
	this->b = 0;
	this->c = 0;
	normal = new toxi::geom::Vec3D();
	a->addFaceNormal(normal);
	b->addFaceNormal(normal);
	c->addFaceNormal(normal);
}

toxi::geom::mesh::Face::Face( Vertex * a, Vertex * b, Vertex * c )
{
	this->a = a;
	this->b = b;
	this->c = c;
	normal = &a->sub(c).crossSelf(&a->sub(b)).normalize();
	a->addFaceNormal(normal);
	b->addFaceNormal(normal);
	c->addFaceNormal(normal);
}

toxi::geom::mesh::Face::Face( Vertex * a, Vertex * b, Vertex * c, Vec2D * uvA, Vec2D * uvB, Vec2D * uvC )
{
	this->a = a;
	this->b = b;
	this->c = c;
	normal = &a->sub(c).crossSelf(&a->sub(b)).normalize();
	a->addFaceNormal(normal);
	b->addFaceNormal(normal);
	c->addFaceNormal(normal);

	this->uvA = uvA;
	this->uvB = uvB;
	this->uvC = uvC;
}

toxi::geom::mesh::Face::~Face(void)
{
	delete normal;
}

toxi::geom::Triangle3D * toxi::geom::mesh::Face::toTriangle()
{
	return new toxi::geom::Triangle3D( *a, *b, *c );
}

void toxi::geom::mesh::Face::computeNormal()
{
	normal = &a->sub(c).crossSelf(&a->sub(b)).normalize();
}

void toxi::geom::mesh::Face::flipVertexOrder()
{
	Vertex * t = a;
	a = b;
	b = t;
	normal->invert();
	delete t;
}

toxi::geom::Vec3D * toxi::geom::mesh::Face::getCentroid()
{
	return &a->add(b)->addSelf(c).scale(1.0 / 3);
}

std::vector< toxi::geom::mesh::Vertex * >  toxi::geom::mesh::Face::getVertices()
{
	std::vector< toxi::geom::mesh::Vertex *>  verts;
	verts.push_back( a );
	verts.push_back( b );
	verts.push_back( c );
	return verts;
}

std::string toxi::geom::mesh::Face::toString()
{
	std::stringstream ss;
	ss << "toxi::geom::mesh::Face: a:" << a->toString() << " b:" << b->toString() << " c:" << c->toString();
}
