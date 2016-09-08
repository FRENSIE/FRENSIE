file1 = "agreement.data"
Ein = 0.1
me = 0.51099891013
E(mu) = Ein/(1+Ein/me*(1-mu))
dmudE(mu) = me/(E(mu)*E(mu))
set terminal post eps enh color
set output "facemc_mcnp_flux_agreement.eps"
#set output "facemc_mcnp_current_agreement.eps"
set multiplot layout 2,1 rowsfirst
set tmargin at screen 0.97
set bmargin at screen 0.53
set lmargin at screen 0.10
set rmargin at screen 0.95
unset title
unset xlabel
#set ylabel "Flux Spectrum"
set ylabel "Current Spectrum"
set logscale x
#set logscale y
set format x ""
set format y "%2.1e"
#set format y "10^{%L}"
set grid
#set xrange[0.0718:0.1]
#set xrange[0.0718:0.075]
set xrange[1e-11:1.0]
#set yrange[0.0:60]
#set yrange[0.0:20]
# set arrow from 0.24913,1e-8 to 0.24913,1e-1 nohead lc rgb"blue" lt 2 lw 0.5
# set arrow from 0.1703,1e-8 to 0.1703,1e-1 nohead lc rgb"blue" lt 4 lw 0.5
plot "combined_flux_root_mcnp.txt" using 1:2 with line lc rgb"black" lt 4 lw 1 title "MCNP6", "combined_flux_root_mcnp.txt" using 1:4 with line lc rgb"red" lt 2 lw 1 title "FACEMC-Root", "combined_flux_dag_mcnp.txt" using 1:4 with line lc rgb"blue" lt 2 lw 1 title "FACEMC-DagMC"
#, "dist.txt" using (E($1)):($2*dmudE($1)) with line lc rgb"blue" lt 1 lw 1
#
set tmargin at screen 0.53
set bmargin at screen 0.1
set lmargin at screen 0.10
set rmargin at screen 0.95
unset key
set format x "10^{%L}"
set format y "%3.2f"
set xlabel "Energy (MeV)"
set ylabel "C/E"
set yrange[0.98:1.02]
set ytics( '' 0.98, 0.99, 1.0, 1.01, '' 1.02 )
#set arrow from 1e-3,1.0 to 10.0,1.0 nohead lc rgb"red" lt 4 lw 1
plot "combined_flux_root_mcnp.txt" using 1:($4/$2) with points lc rgb"red" pt 7 ps 0.25, "combined_flux_root_mcnp.txt" using 1:($4/$2):6 with error lc rgb"red" lt 1 lw 1 pt 7 ps 0.25, "combined_flux_dag_mcnp.txt" using 1:($4/$2) with points lc rgb"blue" pt 7 ps 0.25, "combined_flux_dag_mcnp.txt" using 1:($4/$2):6 with error lc rgb"blue" lt 1 lw 1 pt 7 ps 0.25
#
unset multiplot
