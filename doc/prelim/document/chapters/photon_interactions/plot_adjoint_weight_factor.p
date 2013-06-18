file1 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/adjoint_weight_factor_13-20MeV"
file2 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/adjoint_weight_factor_82-20MeV"
set terminal post eps enh color
set output "adjoint_weight_factor.eps"
set xlabel "Energy (MeV)"
set ylabel "Weight"
set logscale x
set format x "10^{%L}"
unset key
set grid
set xrange[1e-3:20]
set label 1 "Al" at 3.5e-1, 4.5
set label 2 "Pb" at 2.5e-1, 1.3
plot file1 using 1:2 with line lc rgb"black" lt 1 lw 1, file2 using 1:2 with line lc rgb"red" lt 2 lw 1