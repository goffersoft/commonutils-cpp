.PHONY : clean
clean : 
	rm -rf $(LIBDIR)/*
	rm -rf $(BASEDIR)/$(OBJDIRNAME)/*
	rm -rf $(BINDIR)/$(EXE)
	rm -rf $(BINDIR)/lib$(EXE).*

.PHONY : cleanlocal
ifeq ($(findstring $(BASEDIR), $(shell pwd)), $(BASEDIR))
ifeq ($(findstring $(SRCDIRNAME), $(shell pwd)), $(SRCDIRNAME))
cleanlocal : 
	rm -f $(LIBNAME)
	rm -rf $(OBJDIR)
else
ifeq ($(findstring $(TESTDIRNAME), $(shell pwd)), $(TESTDIRNAME))
cleanlocal : 
	rm -f $(LIBNAME)
	rm -rf $(OBJDIR)
else
ifeq "$(shell pwd)" "$(BINDIR)"
cleanlocal :
	rm -f $(EXE)
	rm -f lib$(EXE).*
endif
endif
endif
endif
