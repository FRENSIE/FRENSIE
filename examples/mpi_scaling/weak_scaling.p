dagmc_mpi = "dagmc/MPI_Weak_Summary.txt"
root_mpi = "root/MPI_Weak_Summary.txt"
dagmc_openmp = "dagmc/OpenMP_Weak_Summary.txt"
#
set term postscript landscape enhanced color "Helvetica" 14
set output "weak_scaling_comparison.ps"
#
set tmargin at screen 0.98
set bmargin at screen 0.05
set lmargin at screen 0.05
set rmargin at screen 0.98
#
unset title
unset label
#
set title "Weak Scaling Comparison Study - Single Batch"
set xlabel "Number of Processes"
set ylabel "Computer Time (s)"
#
set autoscale
set xrange [1:11]
set xtics( 1, 3, 5, 7, 9, 11 )
set grid
#
plot dagmc_mpi using 1:2 with line lc rgb"black" lt 2 lw 2 title "DagMC - MPI", root_mpi using 1:2 with line  lc rgb"blue" lt 4 lw 2 title "Root - MPI", dagmc_openmp using 1:2 with line lc rgb"red" lt 2 lw 2 title "DagMC - OpenMP" 
#
unset key
#
