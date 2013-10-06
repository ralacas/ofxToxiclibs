#include "OBJWriter.h"


toxi::geom::mesh::OBJWriter::OBJWriter(void)
{
}


toxi::geom::mesh::OBJWriter::~OBJWriter(void)
{
}

int toxi::geom::mesh::OBJWriter::getCurrVertexOffset()
{
	throw std::exception("The method or operation is not implemented.");
}

int toxi::geom::mesh::OBJWriter::getCurrNormalOffset()
{
	throw std::exception("The method or operation is not implemented.");
}

void toxi::geom::mesh::OBJWriter::newObject( std::string name )
{
	throw std::exception("The method or operation is not implemented.");
}

void toxi::geom::mesh::OBJWriter::vertex( const toxi::geom::mesh::Vertex & v )
{
	throw std::exception("The method or operation is not implemented.");
}

void toxi::geom::mesh::OBJWriter::normal( const toxi::geom::Vec3D & normal )
{
	throw std::exception("The method or operation is not implemented.");
}

void toxi::geom::mesh::OBJWriter::faceWithNormals(  int a, int b, int c, int d, int e, int f  )
{
	throw std::exception("The method or operation is not implemented.");
}

void toxi::geom::mesh::OBJWriter::face( int a, int b, int c )
{
	throw std::exception("The method or operation is not implemented.");
}

void toxi::geom::mesh::OBJWriter::beginSave( std::string path )
{
	throw std::exception("The method or operation is not implemented.");
}

void toxi::geom::mesh::OBJWriter::endSave()
{
	throw std::exception("The method or operation is not implemented.");
}
