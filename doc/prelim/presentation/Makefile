PDFTEX := pdflatex

all:
	$(PDFTEX) presentation
	$(PDFTEX) presentation
	$(PDFTEX) presentation

clean:
	-rm -f *~
	-rm -f *.log
	-rm -f *.aux
	-rm -f *.dvi
	-rm -f *.rel
	-rm -f *.bbl
	-rm -f *.blg
	-rm -f *.out
	-rm -f *.toc *.lof *.lot
	-rm -f *.bak
	-rm -f *.idx

realclean:
	-rm -f presentation.pdf