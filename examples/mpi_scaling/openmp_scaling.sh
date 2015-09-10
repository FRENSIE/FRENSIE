#!/bin/bash

# -----------------------------------------------------------------------------
# Root Scaling Tests
# -----------------------------------------------------------------------------

cd dagmc

# Strong Scaling Tests
# -----------------------------------------------------------------------------

echo DAGMC - OpenMP - 1 Worker Core - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=1 > OpenMP_Strong_1.txt 2>&1

echo DAGMC - OpenMP - 2 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=2 > OpenMP_Strong_2.txt 2>&1

echo DAGMC - OpenMP - 3 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=3 > OpenMP_Strong_3.txt 2>&1

echo DAGMC - OpenMP - 4 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=4 > OpenMP_Strong_4.txt 2>&1

echo DAGMC - OpenMP - 5 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=5 > OpenMP_Strong_5.txt 2>&1

echo DAGMC - OpenMP - 6 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=6 > OpenMP_Strong_6.txt 2>&1

echo DAGMC - OpenMP - 7 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=7 > OpenMP_Strong_7.txt 2>&1

echo DAGMC - OpenMP - 8 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=8 > OpenMP_Strong_8.txt 2>&1

echo DAGMC - OpenMP - 9 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=9 > OpenMP_Strong_9.txt 2>&1

echo DAGMC - OpenMP - 10 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=10 > OpenMP_Strong_10.txt 2>&1

echo DAGMC - OpenMP - 11 Worker Cores - 1e6 Par
./facemc --sim_info="sim_info_1e6.xml" --geom_def="h_sphere_geom.xml" --src_def="h_sphere_source.xml" --resp_def="h_sphere_rsp_fn.xml" --est_def="h_sphere_est.xml" --mat_def="h_sphere_mat.xml" --cross_sec_dir="/home/software/mcnpdata" --threads=11 > OpenMP_Strong_11.txt 2>&1
