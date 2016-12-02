#!/bin/bash
## chmod +x *.sh

## Validation runs comparing 

## Run mcnp5
#/home/software/mcnp6.1.1/bin/./mcnp611_linux_x86_64_omp i=al.i n=al_results_ tasks 12

## Run facemc using root geometry
.././facemc --sim_info=al_hist.xml --geom_def=al_geom_root.xml --mat_def=al_mat.xml --resp_def=al_response.xml --est_def=al_est_root.xml --src_def=al_src.xml --cross_sec_dir=/home/software/mcnpdata --simulation_name=al_root.h5 --threads=12

## Run facemc using Cubit geometry
#.././facemc --sim_info=al_hist.xml --geom_def=al_geom_cub.xml --mat_def=al_mat.xml --resp_def=al_response.xml --est_def=al_est_dag.xml --src_def=al_src.xml --cross_sec_dir=/home/software/mcnpdata --simulation_name=al_dag.h5 --threads=12

python ~/software/frensie/bin/edump.py -f al_root.h5 -e 4 -i total -b Energy > root_tl.out
#python ~/software/frensie/bin/edump.py -f al_dag.h5 -e 4 -i total -b Energy > dag_tl.out
python ~/software/frensie/bin/data_combiner.py -m mcnp_tl.out -f root_tl.out -o combined_tl_root.out
#python ~/software/frensie/bin/data_combiner.py -m mcnp_tl.out -f dag_tl.out -o combined_tl_dag.out
gnuplot plot_agreement.p
