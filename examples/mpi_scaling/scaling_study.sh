#!/bin/bash

# -----------------------------------------------------------------------------
# Root Scaling Tests
# -----------------------------------------------------------------------------

cd root

# Strong Scaling Tests
# -----------------------------------------------------------------------------

echo ------------------------ ROOT STRONG SCALING TESTS -----------------------

echo ROOT - MPI - 1 Worker Core - 1e6 Par
mpiexec -n 2 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_1.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 2 Worker Cores - 1e6 Par
mpiexec -n 3 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_2.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 3 Worker Cores - 1e6 Par
mpiexec -n 4 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_3.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 4 Worker Cores - 1e6 Par
mpiexec -n 5 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_4.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 5 Worker Cores - 1e6 Par
mpiexec -n 6 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_5.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 6 Worker Cores - 1e6 Par
mpiexec -n 7 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_6.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 7 Worker Cores - 1e6 Par
mpiexec -n 8 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_7.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 8 Worker Cores - 1e6 Par
mpiexec -n 9 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_8.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 9 Worker Cores - 1e6 Par
mpiexec -n 10 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_9.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 10 Worker Cores - 1e6 Par
mpiexec -n 11 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_10.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 11 Worker Cores - 1e6 Par
mpiexec -n 12 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_11.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

# Weak Scaling Tests
# -----------------------------------------------------------------------------

echo ------------------------ ROOT WEAK SCALING TESTS -----------------------

echo ROOT - MPI - 1 Worker Core - 1e5 Par
mpiexec -n 2 ./facemc-mpi --sim_info="sim_info_1e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_1.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 2 Worker Cores - 2e5 Par
mpiexec -n 3 ./facemc-mpi --sim_info="sim_info_2e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_2.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 3 Worker Cores - 3e5 Par
mpiexec -n 4 ./facemc-mpi --sim_info="sim_info_3e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_3.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 4 Worker Cores - 4e5 Par
mpiexec -n 5 ./facemc-mpi --sim_info="sim_info_4e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_4.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 5 Worker Cores - 5e5 Par
mpiexec -n 6 ./facemc-mpi --sim_info="sim_info_5e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_5.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 6 Worker Cores - 6e5 Par
mpiexec -n 7 ./facemc-mpi --sim_info="sim_info_6e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_6.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 7 Worker Cores - 7e5 Par
mpiexec -n 8 ./facemc-mpi --sim_info="sim_info_7e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_7.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 8 Worker Cores - 8e5 Par
mpiexec -n 9 ./facemc-mpi --sim_info="sim_info_8e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_8.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 9 Worker Cores - 9e5 Par
mpiexec -n 10 ./facemc-mpi --sim_info="sim_info_9e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_9.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 10 Worker Cores - 10e5 Par
mpiexec -n 11 ./facemc-mpi --sim_info="sim_info_10e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_10.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo ROOT - MPI - 11 Worker Cores - 11e5 Par
mpiexec -n 12 ./facemc-mpi --sim_info="sim_info_11e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_11.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

# -----------------------------------------------------------------------------
# DagMC Scaling Tests
# -----------------------------------------------------------------------------

cd ../dagmc

# Strong Scaling Tests
# -----------------------------------------------------------------------------

echo ------------------------ DAGMC STRONG SCALING TESTS -----------------------

# MPI

echo DAGMC - MPI - 1 Worker Core - 1e6 Par
mpiexec -n 2 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_1.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 2 Worker Cores - 1e6 Par
mpiexec -n 3 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_2.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 3 Worker Cores - 1e6 Par
mpiexec -n 4 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_3.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 4 Worker Cores - 1e6 Par
mpiexec -n 5 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_4.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 5 Worker Cores - 1e6 Par
mpiexec -n 6 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_5.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 6 Worker Cores - 1e6 Par
mpiexec -n 7 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_6.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 7 Worker Cores - 1e6 Par
mpiexec -n 8 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_7.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 8 Worker Cores - 1e6 Par
mpiexec -n 9 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_8.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 9 Worker Cores - 1e6 Par
mpiexec -n 10 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_9.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 10 Worker Cores - 1e6 Par
mpiexec -n 11 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_10.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 11 Worker Cores - 1e6 Par
mpiexec -n 12 ./facemc-mpi --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Strong_11.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

# OpenMP

echo DAGMC - OpenMP - 1 Worker Core - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=1 > OpenMP_Strong_1.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 2 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=2 > OpenMP_Strong_2.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 3 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=3 > OpenMP_Strong_3.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 4 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=4 > OpenMP_Strong_4.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 5 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=5 > OpenMP_Strong_5.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 6 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=6 > OpenMP_Strong_6.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 7 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=7 > OpenMP_Strong_7.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 8 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=8 > OpenMP_Strong_8.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 9 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=9 > OpenMP_Strong_9.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 10 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=10 > OpenMP_Strong_10.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 11 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=11 > OpenMP_Strong_11.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

# Weak Scaling Tests
# -----------------------------------------------------------------------------

echo ------------------------ DAGMC WEAK SCALING TESTS -----------------------

echo DAGMC - MPI - 1 Worker Core - 1e5 Par
mpiexec -n 2 ./facemc-mpi --sim_info="sim_info_1e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_1.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 2 Worker Cores - 2e5 Par
mpiexec -n 3 ./facemc-mpi --sim_info="sim_info_2e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_2.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 3 Worker Cores - 3e5 Par
mpiexec -n 4 ./facemc-mpi --sim_info="sim_info_3e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_3.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 4 Worker Cores - 4e5 Par
mpiexec -n 5 ./facemc-mpi --sim_info="sim_info_4e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_4.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 5 Worker Cores - 5e5 Par
mpiexec -n 6 ./facemc-mpi --sim_info="sim_info_5e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_5.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 6 Worker Cores - 6e5 Par
mpiexec -n 7 ./facemc-mpi --sim_info="sim_info_6e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_6.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 7 Worker Cores - 7e5 Par
mpiexec -n 8 ./facemc-mpi --sim_info="sim_info_7e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_7.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 8 Worker Cores - 8e5 Par
mpiexec -n 9 ./facemc-mpi --sim_info="sim_info_8e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_8.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 9 Worker Cores - 9e5 Par
mpiexec -n 10 ./facemc-mpi --sim_info="sim_info_9e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_9.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 10 Worker Cores - 10e5 Par
mpiexec -n 11 ./facemc-mpi --sim_info="sim_info_10e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_10.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - MPI - 11 Worker Cores - 11e5 Par
mpiexec -n 12 ./facemc-mpi --sim_info="sim_info_11e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" > MPI_Weak_11.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

# OpenMP

echo DAGMC - OpenMP - 1 Worker Core - 1e6 Par
./facemc --sim_info="sim_info_1e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=1 > OpenMP_Weak_1.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 2 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_2e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=2 > OpenMP_Weak_2.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 3 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_3e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=3 > OpenMP_Weak_3.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 4 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_4e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=4 > OpenMP_Weak_4.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 5 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_5e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=5 > OpenMP_Weak_5.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 6 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_6e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=6 > OpenMP_Weak_6.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 7 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_7e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=7 > OpenMP_Weak_7.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 8 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_8e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=8 > OpenMP_Weak_8.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 9 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_9e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=9 > OpenMP_Weak_9.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 10 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_10e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=10 > OpenMP_Weak_10.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

echo DAGMC - OpenMP - 11 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_11e5.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=11 > OpenMP_Weak_11.txt 2>&1

while [ pgrep "facemc-mpi" > /dev/null -o pgrep "facemc" > /dev/null -o "ctest" > /dev/null ]; do
    sleep 5
done

