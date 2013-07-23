ti1 = "FACEMC-Forward"
ti2 = "FACEMC-Adjoint"
set terminal post eps enh color
set output "photon_spectrum_validation_comparison.eps"
set xlabel "Energy (keV)"
set ylabel "d{/Symbol f}/dE (per source particle)"
set logscale y
set format x "%2.1f"
set format y "10^{%L}"
set yrange[1e-9:1e-3]
set key center top
set grid
set label 1 "10 cm" at 400,8e-7
set label 2 "20 cm" at 400,2e-7
set label 3 "30 cm" at 400,7e-8
set label 4 "40 cm" at 400,2.5e-8
set label 5 "50 cm" at 400,9e-9
plot "validation_results/forbindata-10cm" using ($1*1000):2 with line lc rgb"black" lt 1 lw 1 title ti1, "validation_results/forbindata-20cm" using($1*1000):($2/5) with line lc rgb"black" lt 1 lw 1 notitle, "validation_results/forbindata-30cm" using ($1*1000):($2/5) with line lc rgb"black" lt 1 lw 1 notitle, "validation_results/forbindata-40cm" using ($1*1000):($2/5) with line lc rgb"black" lt 1 lw 1 notitle, "validation_results/forbindata-50cm" using ($1*1000):($2/5) with line lc rgb"black" lt 1 lw 1 notitle, "validation_results/adjbindata-10cm" using ($1*1000):2 with line lc rgb"red" lt 1 lw 1 title ti2, "validation_results/adjbindata-20cm" using($1*1000):($2/5) with line lc rgb"red" lt 1 lw 1 notitle, "validation_results/adjbindata-30cm" using ($1*1000):($2/5) with line lc rgb"red" lt 1 lw 1 notitle, "validation_results/adjbindata-40cm" using ($1*1000):($2/5) with line lc rgb"red" lt 1 lw 1 notitle, "validation_results/adjbindata-50cm" using ($1*1000):($2/5) with line lc rgb"red" lt 1 lw 1 notitle
