#pragma once

#include <math.h>
#include "../math/MathUtils.h"
#include "Vec3D.h"

namespace toxi
{
	namespace geom
	{
		class Vec2D
		{
		public:
			Vec2D();
			Vec2D( double _x, double _y );
			~Vec2D(void);

			 Vec2D add( double x, double y );
			 Vec2D add( toxi::geom::Vec2D v );
			 double angleBetween( Vec2D v );
			 double angleBetween( Vec2D v, bool forceNormalize );
			 Vec3D bisect( Vec2D p );
			 int compareTo( Vec2D v );
			 double cross( Vec2D v );
			 double distanceTo( Vec2D v );
			 double distanceToSquared( Vec2D v );
			 double dot( Vec2D v );
			 bool equals( Vec2D v );
			 bool equalsWithTolerance(Vec2D v, double tolerance);
			 Vec2D getCartesian();
			 double getComponent(int id);
			 Vec2D constrain(toxi::geom::Rect r);
			 Vec2D floor( void );
			 Vec2D getFloored();
			 Vec2D frac( );
			 Vec2D getFrac();
			 Vec2D getInverted();
			 Vec2D getLimited( double lim );
			 Vec2D getMapped( toxi::math::ScaleMap map );
			 Vec2D normalize( );
			 Vec2D subSelf( double a, double b );
			 Vec2D subSelf( Vec2D *v );
			 Vec2D set( double x, double y );
			 Vec2D set( Vec2D v );
			 Vec2D getNormalized();
			 Vec2D getNormalizedTo(double len);
			 Vec2D getPerpendicular();
			 Vec2D toPolar();
			 Vec2D reciprocal();
			 Vec2D reflect( Vec2D normal );
			 Vec2D getReflected(Vec2D normal);
			 Vec2D rotate( double theta );
			 Vec2D getRotated(double theta);
			 Vec2D roundTo( double prec );
			 Vec2D getRoundedTo(double prec);
			 Vec2D signum( );
			 Vec2D getSignum();
			 double heading();
			 Vec2D interpolateTo(Vec2D v, double f);
			 Vec2D interpolateTo(Vec2D v, double f, toxi::math::InterpolateStrategy s);
			 bool isInCircle(Vec2D sO, double sR);
			 bool isInRectangle(Rect r);
			 bool isInTriangle(Vec2D a, Vec2D b, Vec2D c);
			 bool isMajorAxis(double tolerance);
			 bool isZeroVector();
			 double magnitude();
			 double magSquared();
			 Vec2D max(Vec2D v);
			 Vec2D min(Vec2D v);
			 Vec2D scale(double s);
			 Vec2D scale(double a, double b);
			 Vec2D scale(Vec2D s);
			 Vec2D sub(double a, double b);
			 Vec2D sub(Vec2D v);
			 Vec2D tangentNormalOfEllipse(Vec2D eO, Vec2D eR);
			 Vec3D to3DXY();
			 Vec3D to3DXZ();
			 Vec3D to3DYZ();
			 double* toArray(double a);
			 double x( void );
			 double y( void );

			double x;
			double y;
		};
	}
}
