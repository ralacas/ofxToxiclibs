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
#include <DoubleRangeTest.h>

/**
 * Performs this application as start point.
 *
 * @return 	integer value including 0 in case this application terminates successfully,
 *			otherwise -1
 */
int main(void)
{
	std::ofstream outputStream("TestResult.xml", std::ofstream::out);
	CppUnit::TextTestRunner runner;
	
	runner.setOutputter(new CppUnit::XmlOutputter(&runner.result(), outputStream));
	runner.addTest(DoubleRangeTest::suite());
	runner.run();

	outputStream.close();

	std::cout << "Test suite were performend and the result were written into 'TestResult.xml'!" << std::endl;

	return EXIT_SUCCESS;
}