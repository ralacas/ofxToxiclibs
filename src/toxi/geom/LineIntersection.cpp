#include "LineIntersection.h"
#include "Line2D.h"


toxi::geom::LineIntersection::LineIntersection( Type type, Vec2D*  pos )
{
	LineIntersection( type, *pos, 0, 0 );
}

toxi::geom::LineIntersection::LineIntersection( Type type, Vec2D line, float mua, float mub )
{
	this->type = type;
	this->line = & line;
	this->coeff.push_back( mua );
	this->coeff.push_back( mub );
}

toxi::geom::LineIntersection::LineIntersection( enum Type type )
{
	LineIntersection( type, Vec2D(), 0, 0 );
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
	//return line->getLength();
	return 0;
}

toxi::geom::Vec2D * toxi::geom::LineIntersection::getLine()
{
	return line;
}

toxi::geom::LineIntersection::Type toxi::geom::LineIntersection::getType()
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
	ss << "type: " << type << " line: " << line;
	return ss.str();
}

toxi::geom::Vec2D toxi::geom::LineIntersection::getPos()
{
	return line != nullptr ? *line : Vec2D();
}
