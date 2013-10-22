#pragma once

#ifndef __VEC3D_H__
#define __VEC3D_H__

#include <string>
#include <iostream>
#include <sstream>
#include "../math/ScaleMap.h"

namespace toxi
{
	namespace geom
	{
		class AABB;
		class Axis3D;
		class Vec2D;
		class MathUtils;
		class ScaleMap;
		//class InterpolateStrategy;
		class Vec4D;
		class Vec3D
		{
		public:
			Vec3D(void);
			Vec3D( const int & x, const int & y, const int & z );
			Vec3D( const float & x, const float & y, const float & z );
			Vec3D( const double & x, const double & y, const double & z );
			~Vec3D(void);

			friend std::ostream& operator << (std::ostream &os, const toxi::geom::Vec3D & v) 
			{
				os << "{x:" << v.getX() << ", y:" << v.getY() << ", z:" << v.getZ() << "}";
				return os;
			}

			Vec3D add(const double & a, const double & b, const double & c);

			Vec3D add(const Vec3D & v);
			Vec3D addSelf( const float & a, const float & b, const float & c );
			Vec3D addSelf( const Vec3D & v );
			float angleBetween(const Vec3D & v);
			float angleBetween( Vec3D & v, const bool & forceNormalize);
			int compareTo(const Vec3D & v);
			Vec3D copy();
			Vec3D cross( const Vec3D & v);
			Vec3D crossInto(const Vec3D & v);
			double distanceTo( const Vec3D & v);
			double distanceToSquared(const Vec3D & v);
			float dot( const Vec3D & v ) const;
			bool equals(const Vec3D & obj);
			bool equalsWithTolerance(const Vec3D & v, const float & tolerance);
			Vec3D getAbs();
			Vec3D getCartesian();
			toxi::geom::Axis3D getClosestAxis();
			double getComponent(const toxi::geom::Axis3D & id);
			double getComponent(const int & id);
			Vec3D getConstrained( const AABB & box);
			Vec3D constrain(const AABB & box);
			Vec3D constrain(const Vec3D & min, const Vec3D & max);
			Vec3D getFloored();
			Vec3D getFrac();
			Vec3D getInverted();
			Vec3D getLimited(const float & lim);
			Vec3D getMapped( const toxi::math::ScaleMap & map);
			Vec3D getNormalized();
			Vec3D getNormalizedTo(const float & len);
			Vec3D normalize( void );
			Vec3D normalizeTo( const double & len );
			Vec3D getReciprocal();
			Vec3D reciprocal();
			Vec3D getReflected(const Vec3D & normal);
			Vec3D reflect( const Vec3D & normal );
			Vec3D getRotatedAroundAxis(const Vec3D & axis, const float & theta);
			Vec3D rotateAroundAxis( const Vec3D & axis, const float & theta );
			Vec3D getRotatedX(const float & theta);
			Vec3D rotateX( const float & theta );
			Vec3D rotateY( const float & theta );
			Vec3D rotateZ( const float & theta );
			Vec3D getRotatedY(const float & theta);
			Vec3D getRotatedZ(const float & theta);
			Vec3D getRoundedTo(const float & prec);
			Vec3D roundTo( const double & perc );
			Vec3D getSignum();
			Vec3D signum();
			Vec3D getSpherical();
			Vec3D toSpherical();
			float headingXY();
			float headingXZ();
			float headingYZ();
			Vec3D interpolateTo(const Vec3D & v, const double & f);
			Vec3D interpolateTo(const toxi::geom::Vec3D & v, const double & f, toxi::math::InterpolateStrategy * s);
			bool isInAABB( const AABB & box );
			bool isInAABB(const Vec3D & boxOrigin, const Vec3D & boxExtent);
			bool isMajorAxis(const float & tolerance);
			bool isZeroVector() const;
			float magnitude();
			float magSquared() const;
			Vec3D scale(const float & s) const ;
			Vec3D scale(const float & a, const float & b, const float & c) const ;
			Vec3D scale(const Vec3D & s)const ;
			Vec3D scaleSelf( const float & s );
			Vec3D sub(const float & a, const float & b, const float & c);
			Vec3D sub(const Vec3D & v);
			Vec2D to2DXY();
			Vec2D to2DXZ();
			Vec2D to2DYZ();
			Vec4D to4D();
			Vec4D to4D(const double & w);
			void toArray(const float & arr);
			void toArray4(const float & arr, const float & w);

			static Vec3D min( const Vec3D & a, const Vec3D & b );
			static Vec3D max( const Vec3D & a, const Vec3D & b );
			static Vec3D max_value( );
			static Vec3D min_value( );
			Vec3D minSelf( const Vec3D & v );
			Vec3D maxSelf( const Vec3D & v );

			Vec3D set( const Vec3D & v );
			Vec3D set( const float & x, const float & y, const float & z );
			Vec3D set( const double & x, const double & y, const double & z );

			static Vec3D X_AXIS( );
			static Vec3D Y_AXIS( );
			static Vec3D Z_AXIS( );

			double getX() const;
			double getY() const;
			double getZ() const;

			void setX( const double & _x);
			void setY( const double & _y );
			void setZ( const double & _z );

			Vec3D clear();
			Vec3D crossSelf( const Vec3D & v );
			Vec3D subSelf( const float & a, const float & b, const float & c);
			Vec3D subSelf( const Vec3D & _v );
			int hashCode();
			Vec3D invert();
			Vec3D interpolateToSelf( const Vec3D & v, const float & f );
			Vec3D limit( float lim );

			//TODO
			bool operator<( const toxi::geom::Vec3D &rhs) const
			{
				return false;
			}

			bool operator>( const toxi::geom::Vec3D &rhs) const
			{
				return true;
			}
			

		private:
			double x;
			double y;
			double z;
		};


	}
}

#endif