#pragma once

#include < string >
#include < sstream >
#include "Vec3D.h"
#include "../math/MathUtils.h"
#include "Matrix4x4.h"
#include "../math/InterpolateStrategy.h"

namespace toxi
{
	namespace geom
	{
		class Matrix4x4;
		class Quaternion
		{
		public:
			Quaternion(void);
			Quaternion( float w, float x, float y, float z );
			Quaternion( float w, Vec3D v );

			~Quaternion(void);

			static Quaternion createFromAxisAngle( Vec3D axis, float angle );
			static Quaternion createFromEuler( float pitch, float yaw, float roll );
			static Quaternion createFromMatrix( Matrix4x4 m );
			static Quaternion getAlignmentQuat( Vec3D dir, Vec3D forward );

			float x, y, z, w;

			Quaternion add( Quaternion q );
			Quaternion addSelf( Quaternion q );
			float dot( Quaternion q );
			Quaternion getConjugate();
			Matrix4x4 getMatrix();
			Quaternion getNormalized();
			Quaternion identity();
			Quaternion interpolateTo( Quaternion target, float t );
			Quaternion interpolateTo( Quaternion target, float t, toxi::geom::InterpolateStrategy *is );
			Quaternion interpolateToSelf( Quaternion target, double t );
			Quaternion interpolateToSelf( Quaternion target, double t, toxi::geom::InterpolateStrategy * is );
			float magnitude( );
			Quaternion multiply( Quaternion q2 );
			Quaternion normalize();
			Quaternion scale( float t );
			Quaternion scaleSelf( float t );
			Quaternion set( float w, float x, float y, float z );
			Quaternion set( float w, Vec3D v );
			Quaternion set( Quaternion q );
			Quaternion sub( Quaternion q );
			Quaternion subSelf( Quaternion q );
			float * toArray();
			float * toAxisAngle();
			Matrix4x4 toMatrix4x4();
			std::string toString();

		};
	}
}


