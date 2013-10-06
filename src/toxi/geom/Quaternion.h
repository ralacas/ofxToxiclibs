#pragma once

#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include < string >
#include < sstream >

//#include "Matrix4x4.h"
//#include "Vec3D.h"
//#include "../math/MathUtils.h"
#include "../math/InterpolateStrategy.h"
#include <vector>

namespace toxi
{
	namespace geom
	{
		class Matrix4x4;
		class Vec3D;
		class InterpolateStrategy;
		class Quaternion
		{
		public:
			Quaternion(void);
			Quaternion( const float & w, const float & x, const float & y, const float & z );
			Quaternion( const double & w, const double & x, const double & y, const double & z );
			Quaternion( const float & w, const Vec3D & v );

			~Quaternion(void);

			static Quaternion createFromAxisAngle( Vec3D axis, const float & angle );
			static Quaternion createFromEuler( const float & pitch, const float & yaw, const float & roll );
			static Quaternion createFromMatrix( const Matrix4x4 & m );
			static Quaternion getAlignmentQuat( Vec3D & dir, Vec3D & forward );

			double x, y, z, w;

			Quaternion add( const Quaternion & q );
			Quaternion addSelf( const Quaternion & q );
			double dot( const Quaternion & q );
			Quaternion getConjugate();
			Matrix4x4 getMatrix();
			Quaternion getNormalized();
			Quaternion identity();
			Quaternion interpolateTo(const Quaternion & target, const float & t );
			Quaternion interpolateTo( const Quaternion & target, const float & t, toxi::math::InterpolateStrategy & is );
			Quaternion interpolateToSelf( const Quaternion & target, const double & t );
			Quaternion interpolateToSelf( const Quaternion & target, const double & t, toxi::math::InterpolateStrategy & is );
			float magnitude( );
			Quaternion multiply( const Quaternion & q2 );
			Quaternion normalize();
			Quaternion scale( const float & t );
			Quaternion scaleSelf( const float & t );
			Quaternion set( const float & w, const float & x, const float & y, const float & z );
			Quaternion set( const float & w, const Vec3D & v );
			Quaternion set( const Quaternion & q );
			Quaternion sub( const Quaternion & q );
			Quaternion subSelf( const Quaternion & q );
			std::vector< double > toArray();
			std::vector< double > toAxisAngle();
			Matrix4x4 toMatrix4x4();
			std::string toString();

		};
	}
}

#endif
