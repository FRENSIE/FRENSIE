#!/bin/bash

## Validation runs comparing 

## Run mcnp5
##/home/software/mcnp6.1.1/bin/./mcnp611_linux_x86_64_omp i=bare.i n=bare_results_ tasks 12

## Run facemc using root geometry
#.././facemc --sim_info=bare_hist.xml --geom_def=bare_geom_root.xml --mat_def=bare_mat.xml --resp_def=bare_response.xml --est_def=bare_est.xml --src_def=bare_src.xml --cross_sec_dir=/home/software/mcnpdata --simulation_name=bare_root.h5 --threads=12

## Run facemc using Cubit geometry
#.././facemc --sim_info=bare_hist.xml --geom_def=bare_geom_cub.xml --mat_def=bare_mat.xml --resp_def=bare_response.xml --est_def=bare_est.xml --src_def=bare_src.xml --cross_sec_dir=/home/software/mcnpdata --simulation_name=bare_dag.h5 --threads=12

python ~/software/frensie/bin/edump.py -f bare_root.h5 -e 4 -i total -b Energy > root_tl_n.out
python ~/software/frensie/bin/edump.py -f bare_dag.h5 -e 4 -i total -b Energy > dag_tl_n.out
python ~/software/frensie/bin/edump.py -f bare_root.h5 -e 14 -i total -b Energy > root_tl_p.out
python ~/software/frensie/bin/edump.py -f bare_dag.h5 -e 14 -i total -b Energy > dag_tl_p.out
python ~/software/frensie/bin/data_combiner.py -m mcnp_tl_n.out -f root_tl_n.out -o combined_tl_n_root.out
python ~/software/frensie/bin/data_combiner.py -m mcnp_tl_n.out -f dag_tl_n.out -o combined_tl_n_dag.out
python ~/software/frensie/bin/data_combiner.py -m mcnp_tl_p.out -f root_tl_p.out -o combined_tl_p_root.out
python ~/software/frensie/bin/data_combiner.py -m mcnp_tl_p.out -f dag_tl_p.out -o combined_tl_p_dag.out
