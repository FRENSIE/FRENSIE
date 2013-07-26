ti1 = "AMOS"
ti2 = "FACEMC"
file1 = "/home/alex/research/transport/FACEMC/doc/prelim/presentation/figures/irradiator_flux_spec_data_amos"
file2 = "/home/alex/research/transport/FACEMC/doc/prelim/presentation/figures/irradiator_flux_spec_data_facemc"
set terminal post eps enh color
set output "facemc_amos_irradiator_comp.eps"
#set multiplot layout 1, 2
set title "Irradiator Facility Photon Flux Spectrum at 50 cm"
set xlabel "Energy (keV)"
set ylabel "d{/Symbol f}/dE (per source particle)"
set logscale y
set format x "%2.1f"
set format y "10^{%L}"
set yrange[1e-12:1e-4]
set key at 700,3.5e-4
set grid
plot file2 using ($1*1000):($2/2) with line lc rgb"black" lt 1 lw 2 title ti2, file1 using 1:2 with lines lc rgb"red" lt 1 lw 2 title ti1
