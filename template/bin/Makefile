-include $(BASEDIR)/variables.mk

LIBS = $(shell ls $(LIBDIR))
LOCALLIBS := $(addprefix $(LIBDIR)/, $(LIBS))
EXENAME = $(EXE)
EXTLDFLAGS = -L$(EXTLIBDIR)/$(BOOSTDIRNAME)/stage/lib
LDFLAGS = $(INCFLAGS) -L$(LIBDIR) $(EXTLDFLAGS)

ifeq "$(LIBTYPE)" "$(LIBTYPE_AR)"
ifeq "$(PLATFORM_OS)" "$(PLATFORM_LINUX)"
LOCALLIBS := -Wl,--start-group $(LOCALLIBS) -Wl,--end-group
endif
else
ifeq "$(SO_EXETYPE)" "$(SO_EXETYPE_SO)"
EXENAME = lib$(EXE).so
LDFLAGS := -shared $(LDFLAGS)
endif
ifeq "$(PLATFORM_OS)" "$(PLATFORM_LINUX)"
LOCALLIBS := -Wl,--whole-archive $(LOCALLIBS) -Wl,--no-whole-archive
else
ifeq "$(PLATFORM_OS)" "$(PLATFORM_MAC)"
LOCALLIBS = $(subst .dylib, ,$(LIBS))
LOCALLIBS := $(subst lib,-l,$(LOCALLIBS))
ifeq "$(SO_EXETYPE)" "$(SO_EXETYPE_SO)"
EXENAME = lib$(EXE).dylib
endif
else
LOCALLIBS = $(subst lib,-l,$(LIBS))
LOCALLIBS := $(subst .so, ,$(LOCALLIBS))
endif
endif
endif
STDLIBS = -lstdc++ -lpthread
EXTLIBS = 
LIBS := $(addprefix $(LIBDIR)/, $(LIBS))

all: $(LIBS) $(EXENAME)

$(EXENAME) : $(LIBS)
	$(CC) -o $(EXENAME) $(LDFLAGS) $(LOCALLIBS) $(STDLIBS) $(EXTLIBS)

-include $(BASEDIR)/clean.mk
