#ifndef __MATH_UTILS_TEST_H__
#define __MATH_UTILS_TEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include < cmath >


/**
 * Test Suite for the MathUtils module.
 */
class MathUtilsTest : public CppUnit::TestFixture
{
	public:
		CPPUNIT_TEST_SUITE( MathUtilsTest );
		CPPUNIT_TEST( absInt );
		CPPUNIT_TEST( absFloat );
		CPPUNIT_TEST( absDouble );
		CPPUNIT_TEST( ceilPowerOf2 );
		CPPUNIT_TEST( floorPowerOf2 );
		CPPUNIT_TEST( clipInt );
		CPPUNIT_TEST( clipLong );
		CPPUNIT_TEST( clipFloat );
		CPPUNIT_TEST( clipDouble );
		CPPUNIT_TEST( clipNormalizedInt );
		CPPUNIT_TEST( clipNormalizedLong );
		CPPUNIT_TEST( clipNormalizedFloat );
		CPPUNIT_TEST( clipNormalizedDouble );
		CPPUNIT_TEST( cos );
		CPPUNIT_TEST( sin );
		CPPUNIT_TEST( radians );
		CPPUNIT_TEST( degree );
		CPPUNIT_TEST_SUITE_END();
		
	public:	
		/**
		 * Tests the construktor method.
		 */
		void absInt(void);
		void absFloat( void );
		void absDouble( void );

		void ceilPowerOf2( void );
		void floorPowerOf2( void );

		void clipInt( void );
		void clipLong( void );
		void clipFloat( void );
		void clipDouble( void );

		void clipNormalizedInt( void );
		void clipNormalizedLong( void );
		void clipNormalizedFloat( void );
		void clipNormalizedDouble( void );

		void cos( void );
		void sin( void );

		void radians( void );
		void degree( void );
};

#endif