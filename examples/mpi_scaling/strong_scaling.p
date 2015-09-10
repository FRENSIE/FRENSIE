dagmc_mpi = "dagmc/MPI_Strong_Summary.txt"
root_mpi = "root/MPI_Strong_Summary.txt"
# dagmc_openmp = "dagmc/OpenMP_Strong_Summary.txt"
#
set terminal post eps enh color
set output "strong_scaling_comparison.ps"
#
set tmargin at screen 0.97
set bmargin at screen 0.10
set lmargin at screen 0.10
set rmargin at screen 0.95
#
unset title
unset label
#
set title "Strong Scaling Comparison Study - Hydrogen Sphere"
set xlabel "Number of Processes"
set ylabel "Computer Time (s)"
#
set xrange [1:11]
set yrange [100:1000]
set grid
#
plot dagmc_mpi using 1:2 with line lc rgb"black" lt 2 lw 1 title "DagMC - MPI",
root_mpi using 1:2 with line  lc rgb"blue" lt 2 lw 1 title "Root - MPI"
# , dagmc_openmp using 1:2 with line lc rgb"green" lt 2 lw 1 title "DagMC - OpenMP" 
#
unset key
#
