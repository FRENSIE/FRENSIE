file1 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/kk-effdata-nobe"
file2 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/kk-effdata-13"
file3 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/kk-effdata-82"
set terminal post eps enh color
set output "Kahn_Koblinger_sampling_eff.eps"
set xlabel "Energy (MeV)"
set ylabel "Efficiency"
set logscale x
set format x "10^{%L}"
set format y "%2.1f"
unset key
set grid
set xrange[1e-3:2]
set yrange[0.5:1.01]
set label 1 "Free Electron" at 2e-2, .78
set label 2 "Al" at 3e-2, 0.73
set label 3 "Pb" at 3e-2, 0.64
plot file1 using 1:2 with line lc rgb"black" lt 1 lw 1, file2 using 1:2 with line lc rgb"red" lt 2 lw 1, file3 using 1:2 with line lc rgb"blue" lt 5 lw 1