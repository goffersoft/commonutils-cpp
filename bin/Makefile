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

$(EXE) : $(LIBS)
	$(CC) $(LDFLAGS) $(LOCALLIBS) $(STDLIBS) -o $@

-include $(BASEDIR)/clean.mk
