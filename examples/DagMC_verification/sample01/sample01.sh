#!/bin/bash

## Validation runs comparing 

## Run mcnp5
mcnp5 i=sample01.i n=sample01. tasks 12

## Run facemc using root geometry
./facemc --sim_info=sample01_hist.xml --geom_def=sample01_geom_root.xml --mat_def=sample01_mat.xml --resp_def=sample01_response.xml --est_def=sample01_est.xml --src_def=sample01_src.xml --cross_sec_dir=/home/software/mcnpdata --threads=12

## Run facemc using Cubit geometry
./facemc --sim_info=sample01_hist.xml --geom_def=sample01_geom_cub.xml --mat_def=sample01_mat.xml --resp_def=sample01_response.xml --est_def=sample01_est.xml --src_def=sample01_src.xml --cross_sec_dir=/home/software/mcnpdata --threads=12
