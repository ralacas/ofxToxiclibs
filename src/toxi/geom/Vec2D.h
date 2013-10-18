#pragma once

#ifndef __VEC2D_H__
#define __VEC2D_H__

#include <iostream>
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
			Vec2D( const double & _x, const double & _y );
			Vec2D( const double & theta );
			Vec2D( const Vec2D & v );
			~Vec2D(void);

			friend std::ostream& operator << (std::ostream &os, const toxi::geom::Vec2D & v) 
			{
				os << "{x:" << v.getX() << ", y:" << v.getY() << "}";
				return os;
			}
			
			//bool operator==( const Vec2D & v1 ) const;
			inline bool operator == (const Vec2D & lhs)
			{
				return ( lhs.x == this->x && lhs.y == this->y );
			}

			inline bool operator == (const Vec2D * lhs)
			{
				return ( lhs->x == this->x && lhs->y == this->y );
			}

			inline Vec2D operator=( const Vec2D & lhs )
			{
				this->x = lhs.x;
				this->y = lhs.y;
				return *this;
			}

			static enum Axis{ X, Y };

			static Vec2D X_AXIS;
			static Vec2D Y_AXIS;
			static Vec2D ZERO;
			static Vec2D MIN_VALUE;
			static Vec2D MAX_VALUE;

			double angleBetween( Vec2D & v );
			double angleBetween( Vec2D & v, const bool & forceNormalize );
			double cross( Vec2D & v );
			double distanceTo( Vec2D & v );
			double distanceToSquared( Vec2D & v );
			double dot( Vec2D & v );
			bool equalsWithTolerance(Vec2D & v, const double & tolerance);
			double getComponent(const int & id);
			double getComponent( toxi::geom::Vec2D::Axis axis );
			double heading();
			int hashCode();
			bool isInCircle(Vec2D & sO, const double & sR);
			bool isInRectangle(Rect&  r);
			bool isInTriangle(Vec2D & a, Vec2D & b, Vec2D & c);
			bool isMajorAxis( const double & tolerance);
			bool isZeroVector();
			double magnitude();
			double magSquared();
			double positiveHeading();

			// those modify the current instance
			Vec3D bisect( Vec2D & p );
			
			Vec2D abs();
			Vec2D constrain( toxi::geom::Polygon2D & poly );
			Vec2D constrain( Rect & r );
			Vec2D constrain( Vec2D & min, Vec2D & max );
			Vec2D floor( void );
			Vec2D frac( );
			Vec2D invert();
			Vec2D limit( const float & lim );
			Vec2D normalize( );
			Vec2D normalizeTo( const float & len );
			Vec2D addSelf( const double & a, const double & b);
			Vec2D addSelf( Vec2D & v );
			Vec2D subSelf( const double & a, const double & b );
			Vec2D subSelf( Vec2D & v );
			Vec2D set( const double & x, const double & y );
			Vec2D set( Vec2D  &v );
			Vec2D setComponent( Axis & id, const float & val );
			Vec2D setComponent( const int & id, const float & val );
			Vec2D perpendicular();
			Vec2D toPolar();
			Vec2D reciprocal();
			Vec2D reflect( Vec2D & normal );
			Vec2D rotate( const double & theta );
			Vec2D roundTo( const double & prec );
			Vec2D signum( );
			Vec2D interpolateTo(Vec2D & v, const double & f);
			Vec2D interpolateTo(Vec2D & v, const double & f, toxi::math::InterpolateStrategy * s);
			Vec2D interpolateToSelf( Vec2D & v, const float & f );
			Vec2D interpolateToSelf( Vec2D & v, const float & f, toxi::math::InterpolateStrategy*  s );
			Vec2D jitter( const double & j );
			Vec2D jitter( const double & jx, const double & jy );
			Vec2D jitter( Vec2D & jv );
			Vec2D tangentNormalOfEllipse(Vec2D & eO, Vec2D & eR);
			Vec2D scaleSelf( const float & s );
			Vec2D scaleSelf( Vec2D & v );
			Vec2D scaleSelf( const float & s1, const float & s2 );
			Vec2D maxSelf( Vec2D & v );
			Vec2D minSelf( Vec2D & v );
			Vec2D snapToAxis();

			Vec3D to3DXY();
			Vec3D to3DXZ();
			Vec3D to3DYZ();

			std::vector< double > toVector();

			// those return new instances
			Vec2D add( const double & x, const double & y );
			Vec2D add( toxi::geom::Vec2D & v );
			Vec2D getAbs( void );
			Vec2D getCartesian();
			Vec2D getConstrained( toxi::geom::Polygon2D & poly );
			Vec2D getConstrained( toxi::geom::Rect & rec );
			Vec2D getFloored();
			Vec2D getFrac();
			Vec2D getInverted();
			Vec2D getLimited( const double & lim );
			Vec2D getMapped( toxi::math::ScaleMap & map );
			Vec2D getNormalized();
			Vec2D getNormalizedTo(const double & len);
			Vec2D getPerpendicular();
			Vec2D getReflected(Vec2D & normal);
			Vec2D getRotated( const double & theta );
			Vec2D getRoundedTo( const double & prec );
			Vec2D getSignum();
			Vec2D scale( const double & s );
			Vec2D scale(const double & a, const double & b );
			Vec2D scale(Vec2D & s);
			Vec2D max(Vec2D & v);
			Vec2D min(Vec2D & v);
			static Vec2D min( Vec2D & v1, Vec2D & v2 );
			static Vec2D max( Vec2D & v1, Vec2D & v2 );
			Vec2D sub(const double & a, const double & b);
			Vec2D sub(const Vec2D & v) const ;
			Vec2D randomVector( void );

			const double getX() const ;
			const double getY() const ;
			

		private:
			double x;
			double y;

			std::string toString();
		};
	}
}

#endif