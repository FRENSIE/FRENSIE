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

all: Kahn_Koblinger_sampling_eff_no_binding.pdf Kahn_Koblinger_sampling_eff.pdf Persliden_experimental_sampling_method_eff.pdf adjoint_and_forward_incoherent_cross_section-13.pdf adjoint_KN_sampling_method_eff.pdf adjoint_weight_factor.pdf lab_and_cm_scattering_angles.pdf incoming_outgoing_energies_cm_angle.pdf incoming_outgoing_energies_lab_angle.pdf
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
	rm Kahn_Koblinger_sampling_eff_no_binding.eps

Kahn_Koblinger_sampling_eff.pdf: $(chap_pi)/plot_kahn_koblinger_sampling_eff.p
	gnuplot $(chap_pi)/plot_kahn_koblinger_sampling_eff.p
	epstopdf Kahn_Koblinger_sampling_eff.eps
	mv Kahn_Koblinger_sampling_eff.pdf $(chap_pi)/.
	rm Kahn_Koblinger_sampling_eff.eps

Persliden_experimental_sampling_method_eff.pdf: $(chap_pi)/plot_coherent_sampling_eff.p
	gnuplot $(chap_pi)/plot_coherent_sampling_eff.p
	epstopdf Persliden_experimental_sampling_method_eff.eps
	mv Persliden_experimental_sampling_method_eff.pdf $(chap_pi)/.	
	rm Persliden_experimental_sampling_method_eff.eps

adjoint_and_forward_incoherent_cross_section-13.pdf: $(chap_pi)/plot_adjoint_forward_incoherent_cross_sec_13.p
	gnuplot $(chap_pi)/plot_adjoint_forward_incoherent_cross_sec_13.p
	epstopdf adjoint_and_forward_incoherent_cross_section-13.eps
	mv adjoint_and_forward_incoherent_cross_section-13.pdf $(chap_pi)/.	
	rm adjoint_and_forward_incoherent_cross_section-13.eps

adjoint_KN_sampling_method_eff.pdf: $(chap_pi)/plot_adjoint_incoherent_sampling_eff.p
	gnuplot $(chap_pi)/plot_adjoint_incoherent_sampling_eff.p
	epstopdf adjoint_KN_sampling_method_eff.eps
	mv adjoint_KN_sampling_method_eff.pdf $(chap_pi)/.
	rm adjoint_KN_sampling_method_eff.eps

adjoint_weight_factor.pdf: $(chap_pi)/plot_adjoint_weight_factor.p
	gnuplot $(chap_pi)/plot_adjoint_weight_factor.p
	epstopdf adjoint_weight_factor.eps
	mv adjoint_weight_factor.pdf $(chap_pi)/.
	rm adjoint_weight_factor.eps

lab_and_cm_scattering_angles.pdf: $(chap_ni)/plot_angles.p
	gnuplot $(chap_ni)/plot_angles.p
	epstopdf lab_and_cm_scattering_angles.eps
	mv lab_and_cm_scattering_angles.pdf $(chap_ni)/.
	rm lab_and_cm_scattering_angles.eps
	sed -i 's/lab_and_cm_scattering_angles/chapters\/neutron_interactions\/lab_and_cm_scattering_angles.pdf/g' lab_and_cm_scattering_angles.tex
	mv lab_and_cm_scattering_angles.tex $(chap_ni)/.

incoming_outgoing_energies_cm_angle.pdf: $(chap_ni)/plot_energies_cm.p
	gnuplot $(chap_ni)/plot_energies_cm.p
	epstopdf incoming_outgoing_energies_cm_angle.eps
	mv incoming_outgoing_energies_cm_angle.pdf $(chap_ni)/.
	rm incoming_outgoing_energies_cm_angle.eps
	sed -i 's/incoming_outgoing_energies_cm_angle/chapters\/neutron_interactions\/incoming_outgoing_energies_cm_angle.pdf/g' incoming_outgoing_energies_cm_angle.tex
	mv incoming_outgoing_energies_cm_angle.tex $(chap_ni)/.

incoming_outgoing_energies_lab_angle.pdf: $(chap_ni)/plot_energies_lab.p
	gnuplot $(chap_ni)/plot_energies_lab.p
	epstopdf incoming_outgoing_energies_lab_angle.eps
	mv incoming_outgoing_energies_lab_angle.pdf $(chap_ni)/.
	rm incoming_outgoing_energies_lab_angle.eps
	sed -i 's/incoming_outgoing_energies_lab_angle/chapters\/neutron_interactions\/incoming_outgoing_energies_lab_angle.pdf/g' incoming_outgoing_energies_lab_angle.tex
	mv incoming_outgoing_energies_lab_angle.tex $(chap_ni)/.

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