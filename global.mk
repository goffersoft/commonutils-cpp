ifndef SUBDIRS
	SUBDIRS = $(shell ls -d */)
endif

SUBDIRS := $(addprefix $(shell pwd)/, $(SUBDIRS))

.PHONY: subdirs $(SUBDIRS)
     
subdirs: $(SUBDIRS)
     
$(SUBDIRS):
	@echo $(SUBDIRS)
	$(MAKE) -C $@
