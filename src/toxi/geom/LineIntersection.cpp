#include "LineIntersection.h"



toxi::geom::LineIntersection::LineIntersection( Type type )
{
	LineIntersection( type, Line3D(), 0, 0 );
}

toxi::geom::LineIntersection::LineIntersection( Type type, Line3D line, float mua, float mub )
{
	this->type = type;
	this->line = line;
	this->coeff.push_back( mua );
	this->coeff.push_back( mub );
}

toxi::geom::LineIntersection::~LineIntersection(void)
{
}

std::vector< float > toxi::geom::LineIntersection::getCoefficients()
{
	return coeff;
}

float toxi::geom::LineIntersection::getLength()
{
	return line.getLength();
}

toxi::geom::Line3D toxi::geom::LineIntersection::getLine()
{
	return line;
}

Type toxi::geom::LineIntersection::getType()
{
	return type;
}

bool toxi::geom::LineIntersection::iIntersectionInside()
{
	return type == Type::INTERSECTING && coeff[0] >= 0 && coeff[0] <= 1
		&& coeff[1] >= 0 && coeff[1] <= 1;
}

std::string toxi::geom::LineIntersection::toString()
{
	std::stringstream ss;
	ss << "type: " << type << " line: " << line.toString();
	return ss.str();
}
