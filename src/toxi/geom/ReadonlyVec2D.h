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


			virtual double angleBetween( Vec2D v ) = 0;
			virtual double angleBetween( Vec2D v, bool forceNormalize ) = 0;
			virtual Vec3D bisect( Vec2D p ) = 0;
			virtual int compareTo( Vec2D v ) = 0;
			virtual double cross( Vec2D v ) = 0;
			virtual double distanceTo( Vec2D v ) = 0;
			virtual double distanceToSquared( Vec2D v ) = 0;
			virtual double dot( Vec2D v ) = 0;
			virtual bool equals( Vec2D v ) = 0;
			virtual bool equalsWithTolerance(Vec2D v, double tolerance) = 0;
			virtual Vec2D getCartesian() = 0;
			virtual double getComponent(int id) = 0;
			virtual Vec2D getFloored() = 0;
			virtual Vec2D getFrac() = 0;
			virtual Vec2D getInverted() = 0;
			virtual Vec2D getLimited(double lim) = 0;
			virtual Vec2D getMapped(toxi::math::ScaleMap map) = 0;
			virtual Vec2D getNormalized() = 0;
			virtual Vec2D getNormalizedTo(double len) = 0;
			virtual Vec2D getPerpendicular() = 0;
			virtual Vec2D toPolar() = 0;
			virtual Vec2D reciprocal() = 0;
			virtual Vec2D getReflected(Vec2D normal) = 0;
			virtual Vec2D getRotated(double theta) = 0;
			virtual Vec2D getRoundedTo(double prec) = 0;
			virtual Vec2D getSignum() = 0;
			virtual double heading() = 0;
			virtual Vec2D interpolateTo(Vec2D v, double f) = 0;
			virtual Vec2D interpolateTo(Vec2D v, double f, toxi::math::InterpolateStrategy s) = 0;
			virtual bool isInCircle(Vec2D sO, double sR) = 0;
			virtual bool isInRectangle(Rect r) = 0;
			virtual bool isInTriangle(Vec2D a, Vec2D b, Vec2D c) = 0;
			virtual bool isMajorAxis(double tolerance) = 0;
			virtual bool isZeroVector() = 0;
			virtual double magnitude() = 0;
			virtual double magSquared() = 0;
			virtual Vec2D max(Vec2D v) = 0;
			virtual Vec2D min(Vec2D v) = 0;
			virtual Vec2D scale(double s) = 0;
			virtual Vec2D scale(double a, double b) = 0;
			virtual Vec2D scale(Vec2D s) = 0;
			virtual Vec2D sub(double a, double b) = 0;
			virtual Vec2D sub(Vec2D v) = 0;
			virtual Vec2D tangentNormalOfEllipse(Vec2D eO, Vec2D eR) = 0;
			virtual Vec3D to3DXY() = 0;
			virtual Vec3D to3DXZ() = 0;
			virtual Vec3D to3DYZ() = 0;
			virtual void toArray(double *a) = 0;
			virtual double x( void ) = 0;
			virtual double y( void ) = 0;
		};
	}
}

