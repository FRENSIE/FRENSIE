DOXYGEN := doxygen

html_doc_loc = html
latex_doc_loc = latex

all: 
	make clean
	$(DOXYGEN) Doxyfile
	ln -s $(html_doc_loc)/index.html .
	cd $(latex_doc_loc); make pdf
	cp $(latex_doc_loc)/refman.pdf .

clean: 
	-rm -f *~
	-rm -f *.html
	-rm -f *.pdf
	-rm -f *.log
	-rm -R -f html
	-rm -R -f latex
	-rm -f test.prof