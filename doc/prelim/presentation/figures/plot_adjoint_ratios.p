# Gnuplot for plotting mesh tallies
set terminal post eps enh color
set output "3dout.eps"
#set lmargin at screen 0.175
#set rmargin at screen 0.9
set bmargin at screen 0.25
set tmargin at screen 0.8
set ticslevel 0
set xlabel "X [cm]"
set ylabel "Y [cm]" offset 3,-1
unset zlabel
set format z "%.1f"
set style line 1 lt 1 lw 1 lc rgb"black"
set pm3d depthorder hidden3d 1
set palette rgbformulae 22,13,-31
set size square
set view 55,135
unset key
unset colorbox
set style line 2 lt 1 lw 4
set style arrow 1 head nofilled size screen 0.025, 20, 45 ls 2
set arrow from 0.0,3.0,20.0 to 3.11,4.1,10.0 as 1 front
set label 1 "Ideal Position" at 0.0,3.1,20.5
#adjoint ratio data
set title "Adjoint Ratio Distribution" offset 0,4.5
splot "dataslices_slice5" using 1:2:(($10/10+$11/10+$12)/($9/10)):(($10/10+$11/10+$12)/($9/10)) with pm3d