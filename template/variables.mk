export BASEDIR ?= $(shell pwd)

ifneq ($(findstring $(BASEDIR), $(shell pwd)), $(BASEDIR))
$(info BASEDIR=$(BASEDIR) is not set correctly )
$(error make sure BASEDIR is set correctly before running make!!)
endif

export PLATFORM_LINUX = __OS_LINUX__
export PLATFORM_MAC = __OS_MAC__
#export PLATFORM_OS = $(PLATFORM_LINUX)
export PLATFORM_OS = $(PLATFORM_MAC)

#export INCLUDE_BOOST = 1
export BOOSTDIRNAME = boost_1_57_0


export MAKETYPE_RECURSE = RECURSE
export MAKETYPE_NORECURSE = NORECURSE
export MAKETYPE := $(MAKETYPE_RECURSE) 

export LIBTYPE_AR = "AR"
export LIBTYPE_SO = "SO"
#export LIBTYPE = $(LIBTYPE_AR)
export LIBTYPE = $(LIBTYPE_SO)

export SO_EXETYPE_SO = "SO"
export SO_EXETYPE_EXE = "EXE"
#export SO_EXETYPE = $(SO_EXETYPE_SO)
export SO_EXETYPE = $(SO_EXETYPE_EXE)

export SRCDIRNAME = src
export TESTDIRNAME = test
export BINDIRNAME = bin
export OBJDIRNAME = obj
export LIBDIRNAME = lib
export INCLUDEDIRNAME = inc
export EXTDIRNAME = ext

export SRCDIR = $(BASEDIR)/$(SRCDIRNAME)
export INCDIR = $(BASEDIR)/$(INCLUDEDIRNAME)
export BINDIR = $(BASEDIR)/$(BINDIRNAME)
export LIBDIR = $(BASEDIR)/$(LIBDIRNAME)
export EXTDIR = $(BASEDIR)/../$(EXTDIRNAME)
export EXTLOCALDIR = $(BASEDIR)/$(EXTDIRNAME)
ifeq ($(findstring $(SRCDIRNAME), $(shell pwd)), $(SRCDIRNAME))
export OBJDIR = $(subst $(SRCDIRNAME),$(OBJDIRNAME)/$(SRCDIRNAME),$(shell pwd))
else
export OBJDIR = $(subst $(TESTDIRNAME),$(OBJDIRNAME)/$(TESTDIRNAME),$(shell pwd))
endif

export TMP := $(subst /,_,$(BASEDIR))
export LIBNAME := $(subst /,_,$(shell pwd))
export LIBNAME := $(subst $(TMP),lib,$(LIBNAME))
export LIBNAME := $(lastword $(LIBNAME))
export SOLIBNAME = $(LIBDIR)/$(LIBNAME).so
export DYLIBNAME = $(LIBDIR)/$(LIBNAME).dylib
export ARLIBNAME = $(LIBDIR)/$(LIBNAME).ar

export EXE = $(subst /, ,$(BASEDIR))
export EXE := $(lastword $(EXE))
export MV = mv -f
#export RM = -@rm -rf
export ECHO = echo
export MKDIR = @mkdir -p
export CC = gcc
export AR = ar

export EXTINCFLAGS = -I$(EXTDIR)/$(BOOSTDIRNAME)
export INCFLAGS ?= -I$(INCDIR) \
                   $(addprefix -I$(SRCDIR),$(subst $(SRCDIR), \
                     ,${shell find ${SRCDIR} -type d -print})) \
                   $(EXTINCFLAGS)

export CCFLAGS = -Wall $(INCFLAGS) -D$(PLATFORM_OS) -DBOOST_LOG_DYN_LINK -std=c++11
export SOCFLAGS = -fPIC
export SOCPPFLAGS = -fPIC
export ARCFLAGS = 
export ARCPPFLAGS =
export DEBUG_FLAGS = -DDEBUG -g

export CPPSRCS = $(wildcard *.cc)
export CSRCS = $(wildcard *.c)
export SRCS := $(SRCS) $(CPPSRCS)
export CPPOBJS = $(CPPSRCS:.cc=.o)
export COBJS = $(CSRCS:.c=.o)
export OBJS = $(addprefix $(OBJDIR)/, $(CPPOBJS) $(COBJS))

ifeq "$(LIBTYPE)" "$(LIBTYPE_AR)"
export CFLAGS = $(CCFLAGS) $(ARCFLAGS) $(DEBUG_FLAGS)
export CPPFLAGS = $(CCFLAGS) $(ARCPPFLAGS) $(DEBUG_FLAGS)
export LIBNAME := $(ARLIBNAME)
export LIBTOOL = $(AR)
export LIBOPTS = -rcs
else
export CFLAGS = $(CCFLAGS) $(SOCFLAGS) $(DEBUG_FLAGS)
export CPPFLAGS = $(CCFLAGS) $(SOCPPFLAGS) $(DEBUG_FLAGS)
ifeq "$(PLATFORM_OS)" "$(PLATFORM_LINUX)"
export LIBNAME := $(ARLIBNAME)
export LIBTOOL = $(AR)
export LIBOPTS = -rcs
else
ifeq "$(PLATFORM_OS)" "$(PLATFORM_MAC)"
export LIBNAME := $(DYLIBNAME)
export LIBTOOL = $(CC)
export LIBOPTS = -shared -dynamiclib -undefined suppress -flat_namespace -fPIC -o
else
export LIBNAME := $(SOLIBNAME)
export LIBTOOL = $(CC)
export LIBOPTS = -shared -fPIC -o
endif
endif
endif
