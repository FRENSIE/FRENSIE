#!/bin/bash
##---------------------------------------------------------------------------##
## Test data updater
##---------------------------------------------------------------------------##

# Get the date for the table notes
today=`date`
notes="This table was generated on $today. It is for testing only!"

# Set the data directory path.
while getopts d: option
do case "${option}"
   in
       d) database_directory=${OPTARG};;
   esac
done

if [ -d "$database_directory" ]; then

    # Update Hydrogen data
    printf "Updating the H native test data...\n"
    native_endl_to_native_epr.py --endl_file_name="$database_directory/endldata/endl_native_1.xml" --ace_table_name="1000.14p" --db_nam="$database_directory/database.xml" --output_file_name="test_epr_1_native.xml" --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=1e5 --photon_grid_convergence_tol=1e-3 --photon_grid_abs_diff_tol=1e-80 --photon_grid_dist_tol=1e-18 --electron_grid_convergence_tol=1e-3 --electron_grid_abs_diff_tol=1e-80 --electron_grid_dist_tol=1e-18 --occupation_number_eval_tol=1e-3 --subshell_incoherent_eval_tol=1e-3 --tabular_evaluation_tol=1e-15 --cutoff_angle_cosine=0.9 --num_moment_preserving_angles=1 --overwrite --notes="$notes"
    if [ $? -eq 0 ]
    then
        printf "H native data updated successfully!\n\n"
    else
        printf "H native data FAILED to update!\n"
        exit 1
    fi

    # Update Carbon data
    printf "Updating the C native test data...\n"
    native_endl_to_native_epr.py --endl_file_name="$database_directory/endldata/endl_native_6.xml" --ace_table_name="6000.14p" --db_nam="$database_directory/database.xml" --output_file_name="test_epr_6_native.xml" --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=1e5 --photon_grid_convergence_tol=1e-3 --photon_grid_abs_diff_tol=1e-70 --photon_grid_dist_tol=1e-18 --electron_grid_convergence_tol=1e-3 --electron_grid_abs_diff_tol=1e-70 --electron_grid_dist_tol=1e-18 --occupation_number_eval_tol=1e-3 --subshell_incoherent_eval_tol=1e-3 --tabular_evaluation_tol=1e-15 --cutoff_angle_cosine=1.0 --num_moment_preserving_angles=0 --overwrite --notes="$notes"
    if [ $? -eq 0 ]
    then
        printf "C native data updated successfully!\n\n"
    else
        printf "C native data FAILED to update!\n"
        exit 1
    fi

    # Update Aluminum data
    printf "Updating the Al native test data...\n"
    native_endl_to_native_epr.py --endl_file_name="$database_directory/endldata/endl_native_13.xml" --ace_table_name="13000.14p" --db_nam="$database_directory/database.xml" --output_file_name="test_epr_13_native.xml" --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=1e5 --photon_grid_convergence_tol=1e-3 --photon_grid_abs_diff_tol=1e-60 --photon_grid_dist_tol=1e-18 --electron_grid_convergence_tol=1e-3 --electron_grid_abs_diff_tol=1e-60 --electron_grid_dist_tol=1e-18 --occupation_number_eval_tol=1e-3 --subshell_incoherent_eval_tol=1e-3 --tabular_evaluation_tol=1e-15 --cutoff_angle_cosine=0.9 --num_moment_preserving_angles=2 --overwrite --notes="$notes"
    if [ $? -eq 0 ]
    then
        printf "Al native data updated successfully!\n\n"
    else
        printf "Al native data FAILED to update!\n"
        exit 1
    fi

    # Update Silicon data
    printf "Updating the Si native test data...\n"
    native_endl_to_native_epr.py --endl_file_name="$database_directory/endldata/endl_native_14.xml" --ace_table_name="14000.14p" --db_nam="$database_directory/database.xml" --output_file_name="test_epr_14_native.xml" --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=1e5 --photon_grid_convergence_tol=1e-3 --photon_grid_abs_diff_tol=1e-60 --photon_grid_dist_tol=1e-18 --electron_grid_convergence_tol=1e-3 --electron_grid_abs_diff_tol=1e-60 --electron_grid_dist_tol=1e-18 --occupation_number_eval_tol=1e-3 --subshell_incoherent_eval_tol=1e-3 --tabular_evaluation_tol=1e-15 --cutoff_angle_cosine=0.9 --num_moment_preserving_angles=1 --overwrite --notes="$notes"
    if [ $? -eq 0 ]
    then
        printf "Si native data updated successfully!\n\n"
    else
        printf "Si native data FAILED to update!\n"
        exit 1
    fi

    # Update Lead data
    printf "Updating the Pb native test data...\n"
    native_endl_to_native_epr.py --endl_file_name="$database_directory/endldata/endl_native_82.xml" --ace_table_name="82000.14p" --db_nam="$database_directory/database.xml" --output_file_name="test_epr_82_native.xml" --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=1e5 --photon_grid_convergence_tol=1e-3 --photon_grid_abs_diff_tol=1e-50 --photon_grid_dist_tol=1e-18 --electron_grid_convergence_tol=1e-3 --electron_grid_abs_diff_tol=1e-50 --electron_grid_dist_tol=1e-18 --occupation_number_eval_tol=1e-3 --subshell_incoherent_eval_tol=1e-3 --tabular_evaluation_tol=1e-15 --cutoff_angle_cosine=0.9 --num_moment_preserving_angles=2 --overwrite --notes="$notes"
    if [ $? -eq 0 ]
    then
        printf "Pb native data updated successfully!\n\n"
    else
        printf "Pb native data FAILED to update!\n"
        exit 1
    fi
else
    printf "\nERROR: Invalid cross section directory!\n"
    printf "  update_native_test_files.sh -d cross_sectin_directory\n\n"
fi
