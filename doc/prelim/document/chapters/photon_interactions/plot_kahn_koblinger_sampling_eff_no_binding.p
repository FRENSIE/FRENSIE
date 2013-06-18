file1 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/kahn-effdata-nobe"
file2 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/kk-effdata-nobe"
label1 = "Kahn's Method"
label2 = "Combined Method"
set terminal post eps enh color
set output "Kahn_Koblinger_sampling_eff_no_binding.eps"
set xlabel "Energy (MeV)"
set ylabel "Efficiency"
set logscale x
set format x "10^{%L}"
set format y "%2.1f"
#set key at .1, 0.9
unset key
set grid
set xrange[1e-3:20]
set yrange[0.4:1.01]
set label 1 "Kahn" at 2, 0.71
set label 2 "Combined" at 2, 0.91
plot file1 using 1:2 with line lc rgb"black" lt 1 lw 1 title label1, file2 using 1:2 with line lc rgb"red" lt 2 lw 1 title label2
