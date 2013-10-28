#pragma once

#ifndef __VEC3D_TEST_H__
#define __VEC3D_TEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class Vec3DTest : public CppUnit::TestFixture
{

public:
	CPPUNIT_TEST_SUITE( Vec3DTest );

	CPPUNIT_TEST( contructorTest );
	CPPUNIT_TEST( equalsOperatorOverloadTest );
	CPPUNIT_TEST( staticAxisTest );
	CPPUNIT_TEST( minMaxTest );
	CPPUNIT_TEST( minMaxValueTest );
	CPPUNIT_TEST( crossTest );

	CPPUNIT_TEST_SUITE_END();

public:

	void contructorTest( void );
	void equalsOperatorOverloadTest( void );
	void staticAxisTest( void );
	void minMaxTest( void );
	void minMaxValueTest( void );
	void crossTest( void );

	
	bool isRightAroundThis( double val, double goal );

};

#endif