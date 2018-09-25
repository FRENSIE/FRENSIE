#!/bin/bash
##---------------------------------------------------------------------------##
## Generate native epr data files
##---------------------------------------------------------------------------##

# Set data directory path
endl_data_dir=./endldata
native_data_dir=./native

while getopts d: options
do case "${option}"
   in
       d) cross_section_directory=${OPTARG};;
   esac
done

if [ -d "$cross_section_directory" ]; then
    cd $cross_section_directory

    if[ -d "$endl_data_dir" ]; then
        cd $endl_data_dir

        if[ ! -d "$native_data_dir" ]; then
            mkdir "$native_data_dir"
        fi

        cd "$native_data_dir"

        if[ ! -d ./epr ]; then
            mkdir epr
        fi

        # Set the generation notes
        notes="Generated on `date +%Y-%m-%d` using generate_native_epr.sh"

        printf "Generatring Z=1 data: \n"

        native_endl_to_native_epr.py --endl_file_name=../../endldata/endl_native_1.xml --output_file_name="epr_native_1.xml" --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=1e5 --occupation_number_eval_tol=1e-3 --subshell_incoherent_eval_tol=1e-3 --photon_grid_convergence_tol=1e-3 --electron_grid_convergence_tol=1e-3 --photon_grid_abs_diff_tol=1e-80 --electron_grid_abs_diff_tol=1e-80 --photon_grid_dist_tol=1e-18 --electron_grid_dist_tol=1e-18 --tabular_evaluation_tol=1e-15 --cutoff_angle_cosine=0.9 --num_moment_preserving_angles=1 --overwrite --notes="$notes"
        
        printf "done \n"
    else
        printf "ERROR: The endl data directory does not exist yet!\n"
        printf "  generator_native_epr.sh -d cross_section_directory\n"
    fi

else
    printf "ERROR: Invalid cross_section_directory!\n"
    printf "  generator_native_epr.sh -d cross_section_directory\n"
fi
