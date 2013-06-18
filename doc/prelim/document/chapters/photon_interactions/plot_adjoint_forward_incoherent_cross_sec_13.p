file1 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/incoherent_cross_section-13"
file2 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/adjoint_incoherent_cross_section_13-20MeV"
file3 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/adjoint_incoherent_cross_section_13-10MeV"
file4 = "/home/alex/research/transport/FACEMC/doc/prelim/document/chapters/photon_interactions/adjoint_incoherent_cross_section_13-1MeV"
set terminal post eps enh color
set output "adjoint_and_forward_incoherent_cross_section-13.eps"
set xlabel "Energy (MeV)"
set ylabel "Barns"
set logscale x
set format x "10^{%L}"
#set format y "10^{%L}"
unset key
set grid
set xrange[1e-3:20]
set label 1 "Incoherent" at 3e-2, 5.5
set label 2 "    Adjoint\n Incoherent" at 4.5e-2, 12
plot file1 using 1:2  with line lc rgb"black" lt 1 lw 1, file2 using 1:2 with line lc rgb"red" lt 2 lw 1, file3 using 1:2 with line lc rgb"red" lt 4 lw 1, file4 using 1:2 with line lc rgb"red" lt 5 lw 1