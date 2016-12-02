#!/bin/bash

## Validation runs comparing 

## Run mcnp5
/home/software/mcnp6.1.1/bin/./mcnp611_linux_x86_64_omp i=h2o_sphere.i n=h2o_sphere_results_ tasks 12

## Run facemc using root geometry
.././facemc --sim_info=h2o_sphere_hist.xml --geom_def=h2o_sphere_geom_root.xml --mat_def=h2o_sphere_mat.xml --resp_def=h2o_sphere_response.xml --est_def=h2o_sphere_est.xml --src_def=h2o_sphere_src.xml --cross_sec_dir=/home/software/mcnpdata --simulation_name=h2o_sphere_root.h5 --threads=12

## Run facemc using Cubit geometry
.././facemc --sim_info=h2o_sphere_hist.xml --geom_def=h2o_sphere_geom_cub.xml --mat_def=h2o_sphere_mat.xml --resp_def=h2o_sphere_response.xml --est_def=h2o_sphere_est.xml --src_def=h2o_sphere_src.xml --cross_sec_dir=/home/software/mcnpdata --simulation_name=h2o_sphere_root.h5 --threads=12
