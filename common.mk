-include $(BASEDIR)/variables.mk

all: $(OBJS) $(LIBNAME)

ifeq "$(LIBTYPE)" "AR"
$(LIBNAME) : $(OBJS)
	$(AR) -rcs $(LIBNAME) $(OBJS)
else
$(LIBNAME) : $(OBJS)
	$(CC) -shared -o $(LIBNAME) -fPIC $(OBJS)
endif

$(OBJS): | $(OBJDIR) $(LIBDIR)

# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)


# more complicated dependency computation, so all prereqs listed
# will also become command-less, prereq-less targets
#   sed:    add $(OBJDIR) as prefix (everything beofrecolon)
#   sed:    strip the target (everything before colon)
#   sed:    remove any continuation backslashes
#   fmt -1: list words one per line
#   sed:    strip leading spaces
#   sed:    add trailingcolons
$(OBJDIR)/%.o: %.cpp
	$(CC) -c $(CPPFLAGS) $(CPPEXTRAFLAGS) $< -o $@
	@$(CC) -MM $(CPPFLAGS) $(CPPEXTRAFLAGS) $< > $(OBJDIR)/$*.d
	@mv -f $(OBJDIR)/$*.d $(OBJDIR)/$*.d.tmp
	@sed -e 's|.*:|$(OBJDIR)/$*.o:|' < $(OBJDIR)/$*.d.tmp > $(OBJDIR)/$*.d
	@cp -f $(OBJDIR)/$*.d $(OBJDIR)/$*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $(OBJDIR)/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $(OBJDIR)/$*.d
	@rm -f $(OBJDIR)/$*.d.tmp



# more complicated dependency computation, so all prereqs listed
# will also become command-less, prereq-less targets
#   sed:    add $(OBJDIR) as prefix (everything beofrecolon)
#   sed:    strip the target (everything before colon)
#   sed:    remove any continuation backslashes
#   fmt -1: list words one per line
#   sed:    strip leading spaces
#   sed:    add trailingcolons
$(OBJDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CEXTRAFLAGS) $< -o $@
	@$(CC) -MM $(CPPFLAGS) $(CPPEXTRAFLAGS) $< > $(OBJDIR)/$*.d
	@mv -f $(OBJDIR)/$*.d $(OBJDIR)/$*.d.tmp
	@sed -e 's|.*:|$(OBJDIR)/$*.o:|' < $(OBJDIR)/$*.d.tmp > $(OBJDIR)/$*.d
	@cp -f $(OBJDIR)/$*.d $(OBJDIR)/$*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $(OBJDIR)/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $(OBJDIR)/$*.d
	@rm -f $(OBJDIR)/$*.d.tmp

-include $(BASEDIR)/clean.mk
