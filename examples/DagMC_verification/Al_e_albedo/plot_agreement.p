set terminal post eps enh color
set output "plot_tl.eps"
set title "Cell Tally Flux for Subcritical Bare Reactor Problem"
set multiplot layout 2,1 rowsfirst
set tmargin at screen 0.85
set bmargin at screen 0.47
set lmargin at screen 0.12
set rmargin at screen 0.95
unset xlabel
set ylabel "Neutron Flux Spectrum"
set logscale x
set logscale y
set format x ""
set format y "%4.3e"
set grid
#set xrange[0.0718:0.1]
#set xrange[0.0718:0.075]
set xrange[1.0e-3:0.005]
set xtics( 1.0e-3, 2.0e-3, 4.0e-3, 5.0e-3)
#set yrange[0.0:60]
#set yrange[0.0:20]
plot "combined_tl_dag.out" using 1:2 with line lc rgb"black" lt 4 lw 1 title "MCNP6", "combined_tl_dag.out" using 1:4 with line lc rgb"red" lt 2 lw 1 title "FRENSIE using Dag", "combined_tl_root.out" using 1:4 with line lc rgb"blue" lt 3 lw 1 title "FRENSIE using Root",
#
set tmargin at screen 0.47
set bmargin at screen 0.1
set lmargin at screen 0.12
set rmargin at screen 0.95
unset key
unset title
set format x "%3.2e"
set format y "%3.2f"
set xlabel "Energy (MeV)"
set ylabel "C/E"
set yrange[0.90:1.10]
set ytics( '' 0.90, 0.95, 1.0, 1.05, '' 1.10 )
#set arrow from 1e-3,1.0 to 10.0,1.0 nohead lc rgb"red" lt 2 lw 1
plot "combined_tl_dag.out" using 1:($4/$2) with points lc rgb"red" pt 7 ps 0.25, "combined_tl_dag.out" using 1:($4/$2):6 with error lc rgb"red" lt 1 lw 1 pt 7 ps 0.25, "combined_tl_root.out" using 1:($4/$2) with points lc rgb"blue" pt 7 ps 0.25, "combined_tl_root.out" using 1:($4/$2):6 with error lc rgb"blue" lt 1 lw 1 pt 7 ps 0.25
unset multiplot
