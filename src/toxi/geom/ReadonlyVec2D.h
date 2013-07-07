#pragma once

#include "Vec2D.h"
#include "Vec3D.h"
#include "Axis2D.h"
#include "../math/ScaleMap.h"
#include "../math/InterpolateStrategy.h"
#include "../util/Rect.h"

namespace toxi
{
	namespace geom
	{
		class ReadonlyVec2D
		{
		public:
			ReadonlyVec2D( void );
			ReadonlyVec2D( int x, int y );
			ReadonlyVec2D( ReadonlyVec2D& v );
			~ReadonlyVec2D( void );


			virtual float angleBetween( Vec2D v ) = 0;
			virtual float angleBetween( Vec2D v, bool forceNormalize ) = 0;
			virtual Vec3D bisect( Vec2D p ) = 0;
			virtual int compareTo( Vec2D v ) = 0;
			virtual float cross( Vec2D v ) = 0;
			virtual float distanceTo( Vec2D v ) = 0;
			virtual float distanceToSquared( Vec2D v ) = 0;
			virtual float dot( Vec2D v ) = 0;
			virtual bool equals( Vec2D v ) = 0;
			virtual bool equalsWithTolerance(Vec2D v, float tolerance) = 0;
			virtual Vec2D getCartesian() = 0;
			virtual float getComponent(int id) = 0;
			virtual Vec2D getFloored() = 0;
			virtual Vec2D getFrac() = 0;
			virtual Vec2D getInverted() = 0;
			virtual Vec2D getLimited(float lim) = 0;
			virtual Vec2D getMapped(toxi::math::ScaleMap map) = 0;
			virtual Vec2D getNormalized() = 0;
			virtual Vec2D getNormalizedTo(float len) = 0;
			virtual Vec2D getPerpendicular() = 0;
			virtual Vec2D getPolar() = 0;
			virtual Vec2D getReciprocal() = 0;
			virtual Vec2D getReflected(Vec2D normal) = 0;
			virtual Vec2D getRotated(float theta) = 0;
			virtual Vec2D getRoundedTo(float prec) = 0;
			virtual Vec2D getSignum() = 0;
			virtual float heading() = 0;
			virtual Vec2D interpolateTo(Vec2D v, float f) = 0;
			virtual Vec2D interpolateTo(Vec2D v, float f, toxi::math::InterpolateStrategy s) = 0;
			virtual bool isInCircle(Vec2D sO, float sR) = 0;
			virtual bool isInRectangle(Rect r) = 0;
			virtual bool isInTriangle(Vec2D a, Vec2D b, Vec2D c) = 0;
			virtual bool isMajorAxis(float tolerance) = 0;
			virtual bool isZeroVector() = 0;
			virtual float magnitude() = 0;
			virtual float magSquared() = 0;
			virtual Vec2D max(Vec2D v) = 0;
			virtual Vec2D min(Vec2D v) = 0;
			virtual Vec2D scale(float s) = 0;
			virtual Vec2D scale(float a, float b) = 0;
			virtual Vec2D scale(Vec2D s) = 0;
			virtual Vec2D sub(float a, float b) = 0;
			virtual Vec2D sub(Vec2D v) = 0;
			virtual Vec2D tangentNormalOfEllipse(Vec2D eO, Vec2D eR) = 0;
			virtual Vec3D to3DXY() = 0;
			virtual Vec3D to3DXZ() = 0;
			virtual Vec3D to3DYZ() = 0;
			virtual void toArray(float *a) = 0;
			virtual float x( void ) = 0;
			virtual float y( void ) = 0;
		};
	}
}

