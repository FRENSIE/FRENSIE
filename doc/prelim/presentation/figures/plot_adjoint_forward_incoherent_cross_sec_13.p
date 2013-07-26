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
set style line 1 lt 1 lw 1 lc rgb"black"
set style arrow 1 head nofilled size screen 0.015, 20, 20 ls 1
set arrow 1 from 2.0,9 to 0.35,5 as 1 front
set arrow 2 from 1.2,18.5 to 0.34,16 as 1 front
set label 1 "Incoherent" at 3e-2, 5.5
set label 2 "    Adjoint\n Incoherent" at 4.5e-2, 12
set label 3 "Em = 1 MeV" at 2.1,9
set label 4 "Em = 10 MeV" at 1.3, 18.5
set label 5 "Em = 20 MeV" at 0.33, 24
set label 6 "Aluminum" at 3.0, 27.5
plot file1 using 1:2  with line lc rgb"black" lt 1 lw 1, file2 using 1:2 with line lc rgb"red" lt 2 lw 1, file3 using 1:2 with line lc rgb"red" lt 4 lw 1, file4 using 1:2 with line lc rgb"red" lt 5 lw 1