ifeq "$(MAKETYPE)" "$(MAKETYPE_RECURSE)"
export SUBDIRS = 
include $(BASEDIR)/variables.mk
include $(BASEDIR)/global.mk
include $(BASEDIR)/clean.mk
else
CPPEXTRAFLAGS :=
CEXTRAFLAGS :=
-include $(BASEDIR)/common.mk
endif
