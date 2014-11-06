export SRCDIRNAME=src
export EXEDIRNAME=bin
export OBJDIRNAME=obj
export LIBDIRNAME=lib
export INCLUDEDIRNAME=inc
export APPCCBASEDIR=/Users/peaswar/Documents/cc/commonutils-cpp

export LIBTYPE := AR
#export LIBTYPE := SO

export APPBASEDIR=$(APPCCBASEDIR)
export BASEDIR=$(APPBASEDIR)
export SRCDIR=$(BASEDIR)/$(SRCDIRNAME)
export OBJDIR=$(BASEDIR)/$(OBJDIRNAME)
export INCDIR=$(BASEDIR)/$(INCLUDEDIRNAME)
export EXEDIR=$(BASEDIR)/$(EXEDIRNAME)


export OBJDIR := $(subst $(SRCDIRNAME),$(OBJDIRNAME),$(shell pwd))
export LIBDIR := $(BASEDIR)/$(LIBDIRNAME)

export LIBNAME := $(subst /, ,$(shell pwd))
export LIBNAME := $(lastword $(LIBNAME))
export LIBNAME := $(addprefix lib,$(LIBNAME))
export LIBNAME := $(LIBNAME)
export SOLIBNAME := $(LIBDIR)/$(LIBNAME).so
export ARLIBNAME := $(LIBDIR)/$(LIBNAME).ar
ifeq "$(LIBTYPE)" "AR"
export LIBNAME := $(ARLIBNAME)
else
export LIBNAME := $(SOLIBNAME)
endif

export EXE := run.exe
export MV=mv -f
export RM=-@rm -rf
export ECHO=echo
export MKDIR=@mkdir -p
export CC=gcc
export INCFLAGS= -I$(INCDIR) \
		 -I$(SRCDIR)/com/goffersoft/core/ \

export SOCFLAGS = -fPIC -Wall $(INCFLAGS)
export SOCPPFLAGS = -fPIC -Wall $(INCFLAGS)
export ARCFLAGS = -Wall $(INCFLAGS)
export ARCPPFLAGS = -Wall $(INCFLAGS)
export PLATFORM_OS = -D__OS_LINUX__
export DEBUG_FLAGS = -DDEBUG -g

ifeq "$(LIBTYPE)" "AR"
export CFLAGS := $(ARCFLAGS) $(PLATFORM_OS) $(DEBUG_FLAGS)
export CPPFLAGS := $(ARCPPFLAGS) $(PLATFORM_OS) $(DEBUG_FLAGS)
else
export CFLAGS := $(SOCFLAGS) $(PLATFORM_OS) $(DEBUG_FLAGS)
export CPPFLAGS := $(SOCPPFLAGS) $(PLATFORM_OS) $(DEBUG_FLAGS)
endif

export CPPSRCS := $(wildcard *.cpp)
export CSRCS := $(wildcard *.c)
export SRCS := $(SRCS) $(CPPSRCS)
export CPPOBJS := $(CPPSRCS:.cpp=.o)
export COBJS := $(CSRCS:.c=.o)
export OBJS := $(addprefix $(OBJDIR)/, $(CPPOBJS) $(COBJS))

