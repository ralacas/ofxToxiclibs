/**
 * HtmlOutputter - CppUnit Output Extension Module.
 *
 * This module based on the outputter interface of CppUnit (see link for more information about CppUnit).
 *
 * Copyright (C) 2013 Andy Liebke
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * @author		Andy Liebke<coding@andysmiles4games.com>
 * @file		HtmlOutputter.h
 * @version 	1.0.0 18-Jul-13
 * @version		1.1.0 25-Jul-13
 * @copyright	Copyright (c) 2013 by Andy Liebke. All rights reserved. (http://andysmiles4games.com)
 * @see			http://sourceforge.net/apps/mediawiki/cppunit/index.php?title=Main_Page
 */
#ifndef __HTML_OUTPUTTER_H__
#define __HTML_OUTPUTTER_H__

#include <cppunit/Outputter.h>
#include <cppunit/TestResultCollector.h>
#include <ostream>

/**
 * HTML Outputter Class.
 */
class HtmlOutputter : public CppUnit::Outputter
{
	public:
		/**
		 * Creates a new instance of this class by the test result collection and an output stream.
		 *
		 * @param result	- test result collection
		 * @param stream	- reference to the output stream
		 */
		HtmlOutputter(CppUnit::TestResultCollector* result, std::ostream &stream);
		
		/**
		 * Creates a new instance of this class by the test result collection, an output stream and a title for the HTML page.
		 *
		 * @param result	- test result collection
		 * @param stream	- reference to the output stream
		 * @param title		- string including title for the HTML page
		 */
		HtmlOutputter(CppUnit::TestResultCollector* result, std::ostream &stream, const std::string title);
		
		/**
		 * Removes this object from memory.
		 */
		virtual ~HtmlOutputter(void);
		
		/**
		 * Writes test results into output HTML file.
		 */
		void write(void);
		
		/**
		 * Assigns a title for this test result output page.
		 *
		 * @param title - string including title for the result HTML page
		 */
		void setTitle(const std::string title)
		{
			this->_title = title;
		}
		
		/**
		 * Assigns path to the external stylesheet.
		 *
		 * @param path - string including path to the external stylesheet
		 */
		void setStylesheetPath(const std::string path)
		{
			this->_pathStylesheet = path;
		}
		
	protected:	
		/**
		 * Writes the header part of this HTML file.
		 */
		void _writeHeader(void);	
		
		/**
		 * Writes the footer part of this HTML file.
		 */
		void _writeFooter(void);
		
		/**
		 * Writes the result list into this HTML file.
		 */
		void _writeResultList(void);
		
		/**
		 * Writes the header of the result overview list into this HTML file.
		 */
		void _writeResultListHeader(void);
		
		/**
		 * Writes a result item of the result overview list into this HTML file.
		 *
		 * @param test 		- pointer to a test case
		 * @param success	- boolean value that has the value true in case the test case run successfully
		 *					  otherwise false
		 */
		void _writeResultListItem(CppUnit::Test* test, const bool success);
		
		/**
		 * Writes the footer part of the test result overview list into this HTML file.
		 */
		void _writeResultListFooter(void);
		
		/**
		 * Checks a particular test if it's within the failure test list.
		 *
		 * @param test - test that should be tested if it's within the failure list
		 * @return boolean with value true in case that the given test is within failure list,
		 *			otherwise false
		 */
		bool _isInFailureList(CppUnit::Test* test);
		
	private:
		/**
		 * Creates new instance of this class by copy another instance.
		 *
		 * @param src - another instance to copy from
		 */
		HtmlOutputter(const HtmlOutputter &src);
		
		/**
		 * Assigns information from another instance of this class to this one.
		 *
		 * @param src - another instance to copy from
		 */
		HtmlOutputter& operator = (const HtmlOutputter &src);	
		
	private:
		/**
		 * Stores a list of the results for each test case.
		 */
		CppUnit::TestResultCollector* _result;
		
		/**
		 * Stores output stream.
		 */
		std::ostream &_stream;
		
		/**
		 * Stores string including title for the output HTML file.
		 */
		std::string _title;
		
		/**
		 * Stores path to a custome Stylesheet file.
		 */
		std::string _pathStylesheet;
};

#endif