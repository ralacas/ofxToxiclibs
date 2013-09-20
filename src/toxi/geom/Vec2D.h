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
			Vec2D( double theta );
			Vec2D( const Vec2D & v );
			~Vec2D(void);
			
			//bool operator==( const Vec2D & v1 ) const;
			inline bool operator == (const Vec2D & lhs)
			{
				return ( *lhs.x == *this->x && *lhs.y == *this->y );
			}

			inline bool operator == (const Vec2D * lhs)
			{
				return ( *lhs->x == *this->x && *lhs->y == *this->y );
			}

			inline Vec2D operator=( const Vec2D & lhs )
			{
				// TODO this isnt right yet
				std::cout << ".operator=" << std::endl;
				*this->x = *lhs.x;
				*this->y = *lhs.y;
				return *this;
			}

			static enum Axis{ X, Y };

			static Vec2D X_AXIS;
			static Vec2D Y_AXIS;
			static Vec2D ZERO;
			static Vec2D MIN_VALUE;
			static Vec2D MAX_VALUE;

			double angleBetween( Vec2D * v );
			double angleBetween( Vec2D * v, bool forceNormalize );
			double cross( Vec2D * v );
			double distanceTo( Vec2D * v );
			double distanceToSquared( Vec2D * v );
			double dot( Vec2D * v );
			bool equalsWithTolerance(Vec2D * v, double tolerance);
			double getComponent(int id);
			double getComponent( toxi::geom::Vec2D::Axis axis );
			double heading();
			int hashCode();
			bool isInCircle(Vec2D * sO, double sR);
			bool isInRectangle(Rect*  r);
			bool isInTriangle(Vec2D * a, Vec2D * b, Vec2D * c);
			bool isMajorAxis(double tolerance);
			bool isZeroVector();
			double magnitude();
			double magSquared();
			float positiveHeading();

			// those modify the current instance
			Vec3D * bisect( Vec2D * p );
			
			Vec2D * abs();
			Vec2D * constrain( toxi::geom::Polygon2D * poly );
			Vec2D * constrain( Rect * r );
			Vec2D * constrain( Vec2D * min, Vec2D * max );
			Vec2D * floor( void );
			Vec2D * frac( );
			Vec2D * invert();
			Vec2D * limit( float lim );
			Vec2D * normalize( );
			Vec2D * normalizeTo( float len );
			Vec2D * addSelf( double a, double b);
			Vec2D * addSelf( Vec2D * v );
			Vec2D * subSelf( double a, double b );
			Vec2D * subSelf( Vec2D * v );
			Vec2D * set( double x, double y );
			Vec2D * set( Vec2D  *v );
			Vec2D * setComponent( Axis * id, float val );
			Vec2D * setComponent( int id, float val );
			Vec2D * perpendicular();
			Vec2D * toPolar();
			Vec2D * reciprocal();
			Vec2D * reflect( Vec2D * normal );
			Vec2D * rotate( double theta );
			Vec2D * roundTo( double prec );
			Vec2D * signum( );
			Vec2D * interpolateTo(Vec2D * v, double f);
			Vec2D * interpolateTo(Vec2D * v, double f, toxi::math::InterpolateStrategy s);
			Vec2D * interpolateToSelf( Vec2D * v, float f );
			Vec2D * interpolateToSelf( Vec2D * v, float f, toxi::math::InterpolateStrategy s );
			Vec2D * jitter( float j );
			Vec2D * jitter( float jx, float jy );
			Vec2D * jitter( Vec2D * jv );
			Vec2D * tangentNormalOfEllipse(Vec2D * eO, Vec2D * eR);
			Vec2D * scaleSelf( float s );
			Vec2D * scaleSelf( Vec2D * v );
			Vec2D * scaleSelf( float s1, float s2 );
			Vec2D * maxSelf( Vec2D * v );
			Vec2D * minSelf( Vec2D * v );
			Vec2D * snapToAxis();

			Vec3D * to3DXY();
			Vec3D * to3DXZ();
			Vec3D * to3DYZ();

			std::vector< float > toVector();
			std::string toString();

			// those return new instances
			Vec2D * add( double x, double y );
			Vec2D * add( toxi::geom::Vec2D * v );
			Vec2D * getAbs( void );
			Vec2D * getCartesian();
			Vec2D * getConstrained( toxi::geom::Polygon2D * poly );
			Vec2D * getConstrained( toxi::geom::Rect * rec );
			Vec2D * getFloored();
			Vec2D * getFrac();
			Vec2D * getInverted();
			Vec2D * getLimited( double lim );
			Vec2D * getMapped( toxi::math::ScaleMap * map );
			Vec2D * getNormalized();
			Vec2D * getNormalizedTo(double len);
			Vec2D * getPerpendicular();
			Vec2D * getReflected(Vec2D * normal);
			Vec2D * getRotated(double theta);
			Vec2D * getRoundedTo(double prec);
			Vec2D * getSignum();
			Vec2D * scale(double s);
			Vec2D * scale(double a, double b);
			Vec2D * scale(Vec2D * s);
			Vec2D * max(Vec2D * v);
			Vec2D * min(Vec2D * v);
			static Vec2D * min( Vec2D * v1, Vec2D * v2 );
			static Vec2D * max( Vec2D * v1, Vec2D * v2 );
			Vec2D * sub(double a, double b);
			Vec2D * sub(Vec2D * v);
			Vec2D * randomVector( void );

			double getX();
			double getY();

		private:
			double * x;
			double * y;
		};
	}
}

#endif