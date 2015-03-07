.PHONY : clean
clean : 
	rm -rf $(LIBDIR)/*
	rm -rf $(BASEDIR)/$(OBJDIRNAME)/*
	rm -rf $(BINDIR)/$(EXE)
	rm -rf $(BINDIR)/lib$(EXE).*

.PHONY : cleanlocal
ifneq "$(shell pwd)" "$(BINDIR)"
cleanlocal : 
	rm -f $(LIBNAME)
	rm -rf $(OBJDIR)
else
cleanlocal :
	rm -f $(EXE)
	rm -f lib$(EXE).*
endif
