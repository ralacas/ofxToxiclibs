/**
 * @mainpage ofxToxicLibs - Test Cases Application.
 *
 * @author		Andy Liebke<coding@andysmiles4games.com>
 * @version 	1.0.0 07-Jul-13
 * @copyright	Copyright (c) 2013 by Andy Liebke. All rights reserved. (http://www.andysmiles4games.com)
 */
 
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "toxi/util/datatypes/DoubleRangeTest.h"
#include "toxi/geom/Vec2DTest.h"
#include "HtmlOutputter.h"

/**
 * Performs this application as start point.
 *
 * @return 	integer value including 0 in case this application terminates successfully,
 *			otherwise -1
 */
int main(void)
{
	std::ofstream outputStream("test/TestResult.html", std::ofstream::out);
	CppUnit::TextTestRunner runner;
	
	HtmlOutputter * hmtlOutputter = new HtmlOutputter( &runner.result(), outputStream, "OFXTOXICLIBS TESTSUITE" );
	hmtlOutputter->setStylesheetPath( "Style.css" );

	//runner.setOutputter(new CppUnit::XmlOutputter(&runner.result(), outputStream));
	runner.setOutputter( hmtlOutputter );
	runner.addTest(DoubleRangeTest::suite());
	runner.addTest(Vec2DTest::suite() );
	runner.run();

	outputStream.close();

	std::cout << "Test suite were performend and the result were written into 'TestResult.xml'!" << std::endl;

	char c;
	std::cin >> c;

	return EXIT_SUCCESS;

	
}