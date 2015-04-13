ifeq "$(MAKETYPE)" "$(MAKETYPE_RECURSE)"
#SUBDIRS = <blank>  compile all sub-directories
#SUBDIRS = dir1 dir2 <dir3 ...>  --> compile specified sub-directories
#SUBDIRS = - donot compile any sub-directories
export SUBDIRS = core
include $(BASEDIR)/variables.mk
include $(BASEDIR)/global.mk
include $(BASEDIR)/clean.mk
else
CPPEXTRAFLAGS :=
CEXTRAFLAGS :=
-include $(BASEDIR)/common.mk
endif
