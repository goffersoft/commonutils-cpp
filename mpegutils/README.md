MPEG Utils
==========

Before running make do the following
1) export BASEDIR=<path_to_this_dir>

2) change PLATFORM_OS (in $BASEDIR/variable.mk) to
    a) __OS__LINUX__ for all flavors of LINUX
    b) __OS__MAC__ for MAC (currently cannot create 
       dylib in shared generation mode' --> SO_EXETYPE_SO)
    c) currently not compatible with CYGWIN

3) there are 2 directories that can be used to add external
   libraries and source code
    a) commonutils-cpp/ext --> external libraries that are
       common to all projects
    b) commonutils-cpp/<projname>/ext --> external libraries
       that are needed for a specific project
    c) change variables.mk -->  EXTINCFLAGS to add include dirs 
    d) change bin/Makefile -->  EXTLDFLAGS to add lib dirs
    e) change bin/Makefile -->  EXTLIBS to link external libs
    f) the following two helper variables are defined in variables.mk
       i) EXTDIR --> points to commonutils-cpp/ext
      ii) EXTLOCALDIR --> points to commonutils-cpp/<proj-name>/ext

4) Install boost 
    a) Download the boost tarball(linux and mac) and copy to $(EXTDIR)
    b) cd $(EXTDIR) 
    c) tar -xvf <boost tar ball>
    d) cd to <boost directory> 
    e) ./bootstrap.sh
    f) ./b2 --> takes a long time
    g) after all this the .so's and .a's should be generated
    h) add/remove libraries as is required to/from EXTLIBS variable.
    i) the required libraries have been added for boost logging to EXTLIBS.
    j) before running the executable set 
        i) linux - LD_LIBRARY_PATH to point to $(EXTLIB)/<boost_dir>/stage/lib
       ii) mac - DYLD_LIBRARY_PATH to point to $(EXTLIB)/<boost_dir>/stage/lib
    k) step j is required because BOOST_LOG_DYN_LINK flag is set at compile time
       and apprently is needed for some of the boost libraries.

Using the google style guide for c/c++ code
http://google-styleguide.googlecode.com/svn/trunk/cppguide.html

all cpp file end with .cc
all c files end with .c
all header files end with .h
