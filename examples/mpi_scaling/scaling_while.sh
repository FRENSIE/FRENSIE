#!/bin/bash

# -----------------------------------------------------------------------------
# Root Scaling Tests
# -----------------------------------------------------------------------------

cd root

# Strong Scaling Tests
# -----------------------------------------------------------------------------

echo ------------------------ ROOT STRONG SCALING TESTS -----------------------

echo ROOT - MPI - 10 Worker Cores - 1e6 Par
mpiexec -n 11 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_10.txt 2>&1

while pgrep "facemc-mpi" > /dev/null; do
    sleep 5
done

echo ROOT - MPI - 11 Worker Cores - 1e6 Par
mpiexec -n 12 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_11.txt 2>&1
