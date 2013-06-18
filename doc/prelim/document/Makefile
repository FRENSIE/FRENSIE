TEX    := latex
BIB    := bibtex
PDFTEX := pdflatex
PDF    := dvipdf

chap_intro = chapters/introduction
chap_mcb = chapters/monte_carlo_background
chap_rwpd = chapters/random_walk_process_derivation
chap_arwpd = chapters/adjoint_random_walk_process_derivation
chap_pi = chapters/photon_interactions
chap_ni = chapters/neutron_interactions

all: Kahn_Koblinger_sampling_eff_no_binding.pdf Kahn_Koblinger_sampling_eff.pdf Persliden_experimental_sampling_method_eff.pdf adjoint_and_forward_incoherent_cross_section-13.pdf adjoint_KN_sampling_method_eff.pdf adjoint_weight_factor.pdf
	$(PDFTEX) dissertation
	-$(BIB) dissertation
	$(PDFTEX) dissertation
	$(PDFTEX) dissertation
	$(PDFTEX) dissertation

# Photon interaction figures
Kahn_Koblinger_sampling_eff_no_binding.pdf: $(chap_pi)/plot_kahn_koblinger_sampling_eff_no_binding.p
	gnuplot $(chap_pi)/plot_kahn_koblinger_sampling_eff_no_binding.p
	epstopdf Kahn_Koblinger_sampling_eff_no_binding.eps
	mv Kahn_Koblinger_sampling_eff_no_binding.pdf $(chap_pi)/.

Kahn_Koblinger_sampling_eff.pdf: $(chap_pi)/plot_kahn_koblinger_sampling_eff.p
	gnuplot $(chap_pi)/plot_kahn_koblinger_sampling_eff.p
	epstopdf Kahn_Koblinger_sampling_eff.eps
	mv Kahn_Koblinger_sampling_eff.pdf $(chap_pi)/.

Persliden_experimental_sampling_method_eff.pdf: $(chap_pi)/plot_coherent_sampling_eff.p
	gnuplot $(chap_pi)/plot_coherent_sampling_eff.p
	epstopdf Persliden_experimental_sampling_method_eff.eps
	mv Persliden_experimental_sampling_method_eff.pdf $(chap_pi)/.

adjoint_and_forward_incoherent_cross_section-13.pdf: $(chap_pi)/plot_adjoint_forward_incoherent_cross_sec_13.p
	gnuplot $(chap_pi)/plot_adjoint_forward_incoherent_cross_sec_13.p
	epstopdf adjoint_and_forward_incoherent_cross_section-13.eps
	mv adjoint_and_forward_incoherent_cross_section-13.pdf $(chap_pi)/.

adjoint_KN_sampling_method_eff.pdf: $(chap_pi)/plot_adjoint_incoherent_sampling_eff.p
	gnuplot $(chap_pi)/plot_adjoint_incoherent_sampling_eff.p
	epstopdf adjoint_KN_sampling_method_eff.eps
	mv adjoint_KN_sampling_method_eff.pdf $(chap_pi)/.

adjoint_weight_factor.pdf: $(chap_pi)/plot_adjoint_weight_factor.p
	gnuplot $(chap_pi)/plot_adjoint_weight_factor.p
	epstopdf adjoint_weight_factor.eps
	mv adjoint_weight_factor.pdf $(chap_pi)/.

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