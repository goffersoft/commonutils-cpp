.PHONY : clean
clean : 
	rm -rf $(LIBDIR)
	rm -rf $(BASEDIR)/$(OBJDIRNAME)
	rm -rf $(EXEDIR)/$(EXE)

.PHONY : cleanlocal
cleanlocal : 
	rm -f $(LIBNAME)
	rm -rf $(OBJDIR)
