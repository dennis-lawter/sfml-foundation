DOXYGEN=doxygen
DOXYCFG=Doxyfile
DOXYOUT=doxygen/html/
DOXYINDEX=index.html

CLOC=cloc
CLOCDIR=src/

doxygen-build:
	$(DOXYGEN) -s $(DOXYCFG)

doxygen-open:
	echo "execute: xdg-open $(DOXYOUT)$(DOXYINDEX)"

cloc:
	$(CLOC) $(CLOCDIR)
