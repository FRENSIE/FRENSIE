file1 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/exp-effdata-13"
file2 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/exp-effdata-82"
file3 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/persliden-effdata-13"
file4 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/persliden-effdata-82"
set terminal post eps enh color
set output "Persliden_experimental_sampling_method_eff.eps"
set xlabel "Energy (MeV)"
set ylabel "Efficiency"
set logscale x
set format x "10^{%L}"
set format y "%2.1f"
unset key
set grid
set xrange[1e-3:20]
set label 1 "Al" at 6e-3, 0.43
set label 2 "Pb" at 2e-2, 0.45
set label 3 "   Probability mixing and \nInverse CDF with rejection" at 0.09, 0.25
set label 4 "Al" at 2e-2, .93
set label 5 "Pb" at 4e-2, .86
set label 6 "Persliden" at 0.1, .82
plot file1 using 1:2 with line lc rgb"black" lt 1 lw 1, file2 using 1:2 with line lc rgb"red" lt 1 lw 1, file3 using 1:2 with line lc rgb"black" lt 2 lw 1, file4 using 1:2 with line lc rgb"red" lt 2 lw 1