#pragma once

#ifndef __VEC2D_H__
#define __VEC2D_H__

#include <math.h>
#include "../math/ScaleMap.h"

namespace toxi
{
	namespace geom
	{
		class Vec3D;
		class ScaleMap;
		class Rect;
		class Polygon2D;
		class InterpolateStrategy;
		class VecMathUtil;
		class Vec2D
		{
		public:
			Vec2D();
			Vec2D( double _x, double _y );
			Vec2D( float theta );
			Vec2D( const Vec2D & v );
			~Vec2D(void);

			static enum Axis{ X, Y };

			bool operator==( const Vec2D v1 );

			static Vec2D X_AXIS;
			static Vec2D Y_AXIS;
			static Vec2D ZERO;
			static Vec2D MIN_VALUE;
			static Vec2D MAX_VALUE;

			 Vec2D add( double x, double y );
			 Vec2D add( toxi::geom::Vec2D v );

			 Vec2D randomVector( void );
			 Vec2D abs();
			 Vec2D getAbs( void );

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
			 double getComponent( toxi::geom::Vec2D::Axis axis );
			 Vec2D constrain( toxi::geom::Polygon2D * poly );
			 Vec2D constrain(Rect * r);
			 Vec2D constrain( Vec2D min, Vec2D max );
			 Vec2D getConstrained( toxi::geom::Polygon2D * poly );
			 Vec2D getConstrained( toxi::geom::Rect * rec );
			 Vec2D floor( void );
			 Vec2D getFloored();
			 Vec2D frac( );
			 Vec2D getFrac();
			 Vec2D invert();
			 Vec2D getInverted();
			 Vec2D limit( float lim );
			 Vec2D getLimited( double lim );
			 Vec2D getMapped( toxi::math::ScaleMap map );
			 Vec2D normalize( );
			 Vec2D normalizeTo( float len );
			 Vec2D addSelf( double a, double b);
			 Vec2D addSelf( Vec2D v );
			 Vec2D subSelf( double a, double b );
			 Vec2D subSelf( Vec2D v );
			 Vec2D set( double x, double y );
			 Vec2D set( Vec2D v );
			 Vec2D setComponent( Axis id, float val );
			 Vec2D setComponent( int id, float val );
			 Vec2D getNormalized();
			 Vec2D getNormalizedTo(double len);
			 Vec2D perpendicular();
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
			 int hashCode();
			 Vec2D interpolateTo(Vec2D v, double f);
			 Vec2D interpolateTo(Vec2D v, double f, toxi::math::InterpolateStrategy s);
			 Vec2D interpolateToSelf( Vec2D v, float f );
			 Vec2D interpolateToSelf( Vec2D v, float f, toxi::math::InterpolateStrategy s );
			 bool isInCircle(Vec2D sO, double sR);
			 bool isInRectangle(Rect r);
			 bool isInTriangle(Vec2D a, Vec2D b, Vec2D c);
			 bool isMajorAxis(double tolerance);
			 bool isZeroVector();
			 Vec2D jitter( float j );
			 Vec2D jitter( float jx, float jy );
			 Vec2D jitter( Vec2D jv );
			 double magnitude();
			 double magSquared();
			 Vec2D max(Vec2D v);
			 Vec2D min(Vec2D v);
			 static Vec2D min( Vec2D v1, Vec2D v2 );
			 static Vec2D max( Vec2D v1, Vec2D v2 );
			 Vec2D scale(double s);
			 Vec2D scale(double a, double b);
			 Vec2D scale(Vec2D s);
			 Vec2D sub(double a, double b);
			 Vec2D sub(Vec2D v);
			 Vec2D tangentNormalOfEllipse(Vec2D eO, Vec2D eR);
			 Vec3D to3DXY();
			 Vec3D to3DXZ();
			 Vec3D to3DYZ();
			 std::vector< float > toVector();
			 std::string toString();

			 static Vec2D fromTheta( float theta );
			 Vec2D scaleSelf( float s );
			 Vec2D scaleSelf( Vec2D v );
			 Vec2D scaleSelf( float s1, float s2 );
			 Vec2D maxSelf( Vec2D v );
			 Vec2D minSelf( Vec2D v );
			 float positiveHeading();
			 Vec2D snapToAxis();

			double x;
			double y;
		};
	}
}

#endif