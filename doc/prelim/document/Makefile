TEX    := latex
BIB    := bibtex
PDFTEX := pdflatex
PDF    := dvipdf

chap_intro = chapters/introduction

all: 
	$(PDFTEX) dissertation
	-$(BIB) dissertation
	$(PDFTEX) dissertation
	$(PDFTEX) dissertation
	$(PDFTEX) dissertation

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
	-rm -f $(chap_intro)/*.pdf $(chap_intro)/*.pdftex_t $(chap_intro)/*.bak
	-rm -f $(chap_intro)/*.aux
	-rm -f TAGS

realclean: clean
	-rm -f dissertation.pdf