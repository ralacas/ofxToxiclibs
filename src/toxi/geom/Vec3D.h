#pragma once

#ifndef __VEC3D_H__
#define __VEC3D_H__

#include <string>
#include <iostream>
#include <sstream>

#include "Axis3D.h"
#include "Vec2D.h"
#include "Vec4D.h"
#include "VecMathUtil.h"

#include "../math/InterpolateStrategy.h"
#include "../math/MathUtils.h"
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
			Vec3D( int x, int y, int z );
			Vec3D( float x, float y, float z );
			Vec3D( double x, double y, double z );
			~Vec3D(void);

			Vec3D add(double a, double b, double c);

			Vec3D * add(Vec3D * v);
			Vec3D addSelf( float a, float b, float c );
			Vec3D addSelf( Vec3D * v );
			float angleBetween(Vec3D * v);
			float angleBetween(Vec3D * v, bool forceNormalize);
			int compareTo(Vec3D * v);
			Vec3D copy();
			Vec3D cross(Vec3D * v);
			Vec3D crossInto(Vec3D * v);
			float distanceTo(Vec3D * v);
			float distanceToSquared(Vec3D * v);
			float dot(Vec3D * v);
			bool equals(Vec3D * obj);
			bool equalsWithTolerance(Vec3D *v, float tolerance);
			Vec3D getAbs();
			Vec3D getCartesian();
			toxi::geom::Axis3D * getClosestAxis();
			float getComponent(toxi::geom::Axis3D * id);
			float getComponent(int id);
			Vec3D getConstrained( AABB * box);
			Vec3D constrain(AABB * box);
			Vec3D constrain(Vec3D * min, Vec3D * max);
			Vec3D getFloored();
			Vec3D getFrac();
			Vec3D getInverted();
			Vec3D getLimited(float lim);
			Vec3D getMapped( toxi::math::ScaleMap * map);
			Vec3D getNormalized();
			Vec3D getNormalizedTo(float len);
			Vec3D normalize( void );
			Vec3D normalizeTo( double len );
			Vec3D getReciprocal();
			Vec3D reciprocal();
			Vec3D getReflected(Vec3D * normal);
			Vec3D reflect( Vec3D * normal );
			Vec3D getRotatedAroundAxis(Vec3D * axis, float theta);
			Vec3D rotateAroundAxis( Vec3D* axis, float theta );
			Vec3D getRotatedX(float theta);
			Vec3D rotateX( float theta );
			Vec3D rotateY( float theta );
			Vec3D rotateZ( float theta );
			Vec3D getRotatedY(float theta);
			Vec3D getRotatedZ(float theta);
			Vec3D getRoundedTo(float prec);
			Vec3D roundTo( float perc );
			Vec3D getSignum();
			Vec3D signum();
			Vec3D getSpherical();
			Vec3D toSpherical();
			float headingXY();
			float headingXZ();
			float headingYZ();
			Vec3D interpolateTo(Vec3D * v, float f);
			Vec3D interpolateTo(toxi::geom::Vec3D * v, float f, toxi::math::InterpolateStrategy * s);
			bool isInAABB( AABB * box );
			bool isInAABB(Vec3D * boxOrigin, Vec3D * boxExtent);
			bool isMajorAxis(float tolerance);
			bool isZeroVector();
			float magnitude();
			float magSquared();
			Vec3D scale(float s);
			Vec3D scale(float a, float b, float c);
			Vec3D scale(Vec3D * s);
			Vec3D scaleSelf( float s );
			Vec3D sub(float a, float b, float c);
			Vec3D sub(Vec3D * v);
			Vec2D to2DXY();
			Vec2D to2DXZ();
			Vec2D to2DYZ();
			Vec4D to4D();
			Vec4D to4D(float w);
			void toArray(float& arr);
			void toArray4(float& arr, float w);

			static Vec3D * min( Vec3D * a, Vec3D * b );
			static Vec3D * max( Vec3D * a, Vec3D * b );
			static Vec3D max_value( );
			static Vec3D min_value( );
			Vec3D minSelf( Vec3D * v );
			Vec3D maxSelf( Vec3D * v );

			Vec3D set( Vec3D * v );
			Vec3D set( float x, float y, float z );
			Vec3D set( double x, double y, double z );

			static Vec3D X_AXIS( );
			static Vec3D Y_AXIS( );
			static Vec3D Z_AXIS( );

			std::string toString( );
			Vec3D clear();
			Vec3D crossSelf( Vec3D * v );
			Vec3D subSelf( float a, float b, float c);
			Vec3D subSelf( Vec3D * _v );
			int hashCode();
			Vec3D invert();
			Vec3D interpolateToSelf( Vec3D * v, float f );
			Vec3D limit( float lim );

			float x;
			float y;
			float z;
		};


	}
}

#endif