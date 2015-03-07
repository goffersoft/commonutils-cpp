commonutils-cpp
===============

Create a common framework for c++ 


Before running make do the following
1) export BASEDIR=<path_to_this_dir>
2) change PLATFORM_OS (in $BASEDIR/variable.mk) to
    a) __OS__LINUX__ for all flavors of LINUX
    b) __OS__MAC__ for MAC (currently cannot create dylib in shared generation mode' --> SO_EXETYPE_SO)
    c) currently not compatible with CYGWIN

Using the google style guide for c/c++ code
http://google-styleguide.googlecode.com/svn/trunk/cppguide.html

all cpp file end with .cc
all c files end with .c
all header files end with .h
