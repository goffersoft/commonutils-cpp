ifndef SUBDIRS
SUBDIRS := $(shell ls -d */ 2>/dev/null)
endif

FILES := $(shell ls *.cc *.c 2>/dev/null)

ifeq ("$(SUBDIRS)", "-")
SUBDIRS := $(shell pwd)
else
ifeq ($(FILES),)
SUBDIRS := $(addprefix $(shell pwd)/, $(SUBDIRS))
else
SUBDIRS := $(shell pwd) $(addprefix $(shell pwd)/, $(SUBDIRS))
endif
endif

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	@echo $(SUBDIRS)
	@if [ "$@" = "$(PWD)" ]; then \
		$(MAKE) -C $@ MAKETYPE=$(MAKETYPE_NORECURSE); \
	else \
		$(MAKE) -C $@ MAKETYPE=$(MAKETYPE_RECURSE); \
	fi
