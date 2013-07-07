# /**
#  * C++ Library Project Makefile.
#  * 
#  * LICENSE FOR THIS MAKEFILE:
#  *	
#  *	The MIT License (MIT)
#  *
#  *	Copyright (c) 2013 by Andy Liebke. All rights reserved.
#  *
#  *	Permission is hereby granted, free of charge, to any person obtaining a copy
#  * 	of this software and associated documentation files (the "Software"), to deal
#  *	in the Software without restriction, including without limitation the rights
#  *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  *	copies of the Software, and to permit persons to whom the Software is
#  *	furnished to do so, subject to the following conditions:
#  *
#  *	The above copyright notice and this permission notice shall be included in
#  *	all copies or substantial portions of the Software.
#  *
#  *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#  *	THE SOFTWARE.
#  *
#  * @author	Andy Liebke<coding@andysmiles4games.com>	
#  * @version 	1.0.0 20-May-13
#  * @version	1.0.1 27-May-13
#  * @version	1.0.2 30-May-13
#  * @version	1.1.0 31-May-13
#  * @version	1.2.0 08-Jun-13
#  * @version	1.2.1 09-Jun-13
#  * @version	1.3.0 16-Jun-13
#  * @version	1.3.1 20-Jun-13
#  * @version	1.4.0 22-Jun-13
#  * @version	1.5.0 23-Jun-13
#  * @version	1.5.1 27-Jun-13
#  * @version	1.5.2 29-Jun-13
#  * @version	1.6.0 07-Jul-13
#  * @copyright	Copyright (c) 2013 by Andy Liebke. All rights reserved.
#  */

LIB_TITLE = ofxToxiclibs
LIST_OBJECTS = 	Build/toxi/util/DoubleRange.o \
				Build/toxi/math/MathUtils.o

DEBUG_SETTINGS =  -g -D_DEBUG
COMMON_SETTINGS = $(DEBUG_SETTINGS) -Wall -pedantic-errors -Weffc++ -ansi -std=c++98 -I src/

.PHONY: build
build: $(LIST_OBJECTS)
	g++ -shared -fPIC -o lib$(LIB_TITLE).a $^
	mkdir -p ./Lib
	mv ./lib$(LIB_TITLE).a ./Lib/lib$(LIB_TITLE).a
	
Build/%.o: src/%.cpp
	mkdir -p $(dir $@)
	g++ $(COMMON_SETTINGS) -c $^ -o $@ 

.PHONY: clean
clean:
	rm -rf ./Build
	rm -rf ./Lib