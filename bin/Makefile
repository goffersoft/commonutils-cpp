-include $(BASEDIR)/variables.mk

LIBS := $(shell ls $(LIBDIR))
ifeq "$(LIBTYPE)" "AR"
LOCALLIBS := $(addprefix $(LIBDIR)/, $(LIBS))
else
LOCALLIBS := $(subst lib,-l,$(LIBS))
LOCALLIBS := $(subst .so, ,$(LOCALLIBS))
endif
STDLIBS := -lstdc++ -lpthread
LIBS := $(addprefix $(LIBDIR)/, $(LIBS))
LDFLAGS := -L$(LIBDIR)

all: $(LIBS) $(EXE)

ifeq "$(PLATFORM_OS)" "__OS_LINUX__"
$(EXE) : $(LIBS)	
	$(CC) $(LDFLAGS) -Wl,--start-group $(LOCALLIBS) -Wl,--end-group $(STDLIBS) -o $@
else
$(EXE) : $(LIBS)
	$(CC) $(LDFLAGS) $(LOCALLIBS) $(STDLIBS) -o $@
endif

-include $(BASEDIR)/clean.mk
