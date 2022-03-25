DOXYGEN=C:/cppdev/doxygen-1.8.13/doxygen.exe
DOXYCFG=Doxyfile
DOXYOUT=doxygen/html/
DOXYINDEX=index.html

CLOC=C:/cppdev/cloc-1.64/cloc.exe
CLOCDIR=src/

doxygen-build:
	$(DOXYGEN) -s $(DOXYCFG)

doxygen-open:
	start $(DOXYOUT)$(DOXYINDEX) &

cloc:
	$(CLOC) $(CLOCDIR)
