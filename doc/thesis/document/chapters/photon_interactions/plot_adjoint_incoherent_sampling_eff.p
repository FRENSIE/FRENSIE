file1 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/adjeffdata-nobe"
file2 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/adjeffdata-13"
file3 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/adjeffdata-82"
set terminal post eps enh color
set output "adjoint_KN_sampling_method_eff.eps"
set xlabel "Energy (MeV)"
set ylabel "Efficiency"
set logscale x
set format x "10^{%L}"
set format y "%2.2f"
unset key
set grid
set xrange[1e-3:20]
set label 1 "Free Electron" at 5e-2, 0.97
set label 2 "Al" at 1.5e-2, 0.92
set label 3 "Pb" at 3.5e-2, 0.86
plot file1 using 1:2 with line lc rgb"black" lt 1 lw 1, file2 using 1:2 with line lc rgb"red" lt 2 lw 1, file3 using 1:2 with line lc rgb"blue" lt 5 lw 1