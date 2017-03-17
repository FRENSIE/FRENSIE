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
       d) cross_section_directory=${OPTARG};;
   esac
done

if [ -d "$cross_section_directory" ]; then
    
    # Update Hydrogen data
    printf "Updating the H native test data...\n"
    epr_generator --cross_sec_dir=$cross_section_directory --cross_sec_alias=H --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=1e5 --occupation_num_tol=1e-3 --subshell_incoherent_tol=1e-3 --grid_convergence_tol=1e-3 --grid_absolute_diff_tol=1e-80 --grid_absolute_dist_tol=1e-18 --tabular_evaluation_tol=1e-15 --cutoff_angle_cosine=0.9 --number_of_moment_preserving_angles=1.0 --notes="$notes"
    if [ $? -eq 0 ]
    then
        printf "H native data updated successfully!\n\n"
        mv epr_1_native.xml test_epr_1_native.xml
    else
        printf "H native data FAILED to update!\n"
        exit 1
    fi
    
    # Update Carbon data
    printf "Updating the C native test data...\n"
    epr_generator --cross_sec_dir=$cross_section_directory --cross_sec_alias=C --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=1e5 --occupation_num_tol=1e-3 --subshell_incoherent_tol=1e-3 --grid_convergence_tol=1e-3 --grid_absolute_diff_tol=1e-70 --grid_absolute_dist_tol=1e-18 --tabular_evaluation_tol=1e-15 --cutoff_angle_cosine=1.0 --number_of_moment_preserving_angles=0.0 --notes="$notes"
    if [ $? -eq 0 ]
    then
        printf "C native data updated successfully!\n\n"
        mv epr_6_native.xml test_epr_6_native.xml
    else
        printf "C native data FAILED to update!\n"
        exit 1
    fi
    
    # Update Aluminum data
    printf "Updating the Al native test data...\n"
    epr_generator --cross_sec_dir=$cross_section_directory --cross_sec_alias=Al --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=1e5 --occupation_num_tol=1e-3 --subshell_incoherent_tol=1e-3 --grid_convergence_tol=1e-3 --grid_absolute_diff_tol=1e-60 --grid_absolute_dist_tol=1e-18 --tabular_evaluation_tol=1e-15 --cutoff_angle_cosine=0.9 --number_of_moment_preserving_angles=2.0 --notes="$notes"
    if [ $? -eq 0 ]
    then
        printf "Al native data updated successfully!\n\n"
        mv epr_13_native.xml test_epr_13_native.xml
    else
        printf "Al native data FAILED to update!\n"
        exit 1
    fi
    
    # Update Silicon data
    printf "Updating the Si native test data...\n"
    epr_generator --cross_sec_dir=$cross_section_directory --cross_sec_alias=Si --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=1e5 --occupation_num_tol=1e-3 --subshell_incoherent_tol=1e-3 --grid_convergence_tol=1e-3 --grid_absolute_diff_tol=1e-60 --grid_absolute_dist_tol=1e-18 --tabular_evaluation_tol=1e-15 --cutoff_angle_cosine=0.9 --number_of_moment_preserving_angles=1.0 --notes="$notes"
    if [ $? -eq 0 ]
    then
        printf "Si native data updated successfully!\n\n"
        mv epr_14_native.xml test_epr_14_native.xml
    else
        printf "Si native data FAILED to update!\n"
        exit 1
    fi
    
    # Update Lead data
    printf "Updating the Pb native test data...\n"
    epr_generator --cross_sec_dir=$cross_section_directory --cross_sec_alias=Pb --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=1e5 --occupation_num_tol=1e-3 --subshell_incoherent_tol=1e-3 --grid_convergence_tol=1e-3 --grid_absolute_diff_tol=1e-50 --grid_absolute_dist_tol=1e-18 --tabular_evaluation_tol=1e-15 --cutoff_angle_cosine=0.9 --number_of_moment_preserving_angles=2.0 --notes="$notes"
    if [ $? -eq 0 ]
    then
        printf "Pb native data updated successfully!\n\n"
        mv epr_82_native.xml test_epr_82_native.xml
    else
        printf "Pb native data FAILED to update!\n"
        exit 1
    fi
else
    printf "\nERROR: Invalid cross section directory!\n"
    printf "  update_native_test_files.sh -d cross_sectin_directory\n\n"
fi
