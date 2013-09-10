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
#include <windows.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "toxi/math/MathUtilsTest.h"
#include "toxi/util/datatypes/DoubleRangeTest.h"
#include "toxi/math/LinearInterpolationTest.h"
#include "toxi/math/ScaleMapTest.h"
#include "toxi/geom/Vec2DTest.h"
#include "HtmlOutputter.h"
#include "../toxi/main/Toxiclibs.h"

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
	Toxiclibs::init();
	runner.addTest( MathUtilsTest::suite() );
	runner.addTest( DoubleRangeTest::suite() );
	runner.addTest( LinearInterpolationTest::suite() );
	runner.addTest( ScaleMapTest::suite() );
	runner.addTest( Vec2DTest::suite() );
	runner.run();

	outputStream.close();

	std::cout << "Test suite were performend and the result were written into 'TestResult.html'!" << std::endl;

	std::cout << "Want to open the result file? y/n" << std::endl;

	char c;
	std::cin >> c;

	if( c == 'y' )
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );

		char * chromeUrl = "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe";
		char * resultsUrl = "G:\\CODE\\visual_studio_2012_workspace\\ofxToxiclibs\\ofxToxiclibs\\test\\TestResult.html";

		std::stringstream ss;
		ss << chromeUrl << " " << resultsUrl;

		std::string urlString = ss.str();

		std::cout << urlString << std::endl;

		char * url = const_cast<char *>( urlString.c_str() );

		std::cout << url << std::endl;
		// Start the child process. 
		if( !CreateProcess( NULL,   // No module name (use command line)
			url,		// Command line
			NULL,		   // Process handle not inheritable
			NULL,		   // Thread handle not inheritable
			FALSE,		  // Set handle inheritance to FALSE
			0,			  // No creation flags
			NULL,		   // Use parent's environment block
			NULL,		   // Use parent's starting directory 
			&si,			// Pointer to STARTUPINFO structure
			&pi )		   // Pointer to PROCESS_INFORMATION structure
			) 
		{
			printf( "CreateProcess failed (%d)\n", GetLastError() );
			char c;
			std::cin >> c;
			return EXIT_FAILURE;
		}

		// Wait until child process exits.
		WaitForSingleObject( pi.hProcess, INFINITE );

		// Close process and thread handles. 
		CloseHandle( pi.hProcess );
		CloseHandle( pi.hThread );
	}

	return EXIT_SUCCESS;

	
}