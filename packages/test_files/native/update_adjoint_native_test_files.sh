#!/bin/bash
##---------------------------------------------------------------------------##
## Test data updater
##---------------------------------------------------------------------------##

# Get the date for the table notes
today=`date`
notes="This table was generated on $today. It is for testing only!"
    
# Update adjoint Hydrogen data
printf "Updating the adjoint H native test data...\n"
rm test_aepr_1_native.xml
aepr_generator --forward_file=test_epr_1_native.xml --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=20 --adjoint_pp_edist_eval_tol=1e-3 --adjoint_pp_edist_nudge_val=1e-6 --adjoint_tp_edist_eval_tol=1e-3 --adjoint_tp_edist_nudge_val=1e-6 --adjoint_incoherent_max_e_nudge_val=0.2 --adjoint_incoherent_e_to_max_e_nudge_val=1e-5 --adjoint_incoherent_eval_tol=1e-2 --adjoint_incoherent_grid_convergence_tol=0.5 --adjoint_incoherent_grid_absolute_diff_tol=1e-42 --adjoint_incoherent_grid_dist_tol=1e-16 --cutoff_angle_cosine=0.9 --number_of_moment_preserving_angles=2 --electron_tabular_evaluation_tol=1e-6 --electron_linlinlog_interp --electron_correlated_sampling --electron_unit_based_interp --adjoint_electron_grid_convergence_tol=1e-2 --adjoint_electron_grid_absolute_diff_tol=1e-16 --adjoint_electron_dist_tol=1e-9 --adjoint_bremsstrahlung_max_e_nudge_val=0.2 --adjoint_bremsstrahlung_e_to_outgoing_e_nudge_val=1e-7 --adjoint_bremsstrahlung_eval_tol=1e-6 --adjoint_bremsstrahlung_grid_convergence_tol=0.5 --adjoint_bremsstrahlung_grid_absolute_diff_tol=1e-16 --adjoint_bremsstrahlung_dist_tol=1e-9 --adjoint_electroionization_eval_tol=1e-6 --adjoint_electroionization_grid_convergence_tol=0.5 --adjoint_electroionization_grid_absolute_diff_tol=1e-16 --adjoint_electroionization_dist_tol=1e-9 --grid_convergence_tol=1e-3 --grid_absolute_diff_tol=1e-42 --grid_absolute_dist_tol=1e-16 --notes="$notes"
if [ $? -eq 0 ]
then
    printf "adjoint H native data updated successfully!\n\n"
    mv aepr_1_native.xml test_aepr_1_native.xml
else
    printf "adjoint H native data FAILED to update!\n"
    exit 1
fi
    
# Update adjoint Carbon data
printf "Updating the adjoint C native test data...\n"
rm test_aepr_6_native.xml
aepr_generator --forward_file=test_epr_6_native.xml --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=20 --adjoint_pp_edist_eval_tol=1e-3 --adjoint_pp_edist_nudge_val=1e-6 --adjoint_tp_edist_eval_tol=1e-3 --adjoint_tp_edist_nudge_val=1e-6 --adjoint_incoherent_max_e_nudge_val=0.2 --adjoint_incoherent_e_to_max_e_nudge_val=1e-5 --adjoint_incoherent_eval_tol=1e-2 --adjoint_incoherent_grid_convergence_tol=0.5 --adjoint_incoherent_grid_absolute_diff_tol=1e-42 --adjoint_incoherent_grid_dist_tol=1e-16 --cutoff_angle_cosine=0.9 --number_of_moment_preserving_angles=2 --electron_tabular_evaluation_tol=1e-6 --electron_linlinlog_interp --electron_correlated_sampling --electron_unit_based_interp --adjoint_electron_grid_convergence_tol=1e-2 --adjoint_electron_grid_absolute_diff_tol=1e-16 --adjoint_electron_dist_tol=1e-9 --adjoint_bremsstrahlung_max_e_nudge_val=0.2 --adjoint_bremsstrahlung_e_to_outgoing_e_nudge_val=1e-7 --adjoint_bremsstrahlung_eval_tol=1e-6 --adjoint_bremsstrahlung_grid_convergence_tol=0.5 --adjoint_bremsstrahlung_grid_absolute_diff_tol=1e-16 --adjoint_bremsstrahlung_dist_tol=1e-9 --adjoint_electroionization_eval_tol=1e-6 --adjoint_electroionization_grid_convergence_tol=0.5 --adjoint_electroionization_grid_absolute_diff_tol=1e-16 --adjoint_electroionization_dist_tol=1e-9 --grid_convergence_tol=1e-3 --grid_absolute_diff_tol=1e-42 --grid_absolute_dist_tol=1e-16 --notes="$notes"
if [ $? -eq 0 ]
then
    printf "adjoint C native data updated successfully!\n\n"
    mv aepr_6_native.xml test_aepr_6_native.xml
else
    printf "adjoint C native data FAILED to update!\n"
    exit 1
fi

# Update adjoint Aluminum data
printf "Updating the adjoint Al native test data...\n"
rm test_aepr_13_native.xml
aepr_generator --forward_file=test_epr_13_native.xml --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=20 --adjoint_pp_edist_eval_tol=1e-3 --adjoint_pp_edist_nudge_val=1e-6 --adjoint_tp_edist_eval_tol=1e-3 --adjoint_tp_edist_nudge_val=1e-6 --adjoint_incoherent_max_e_nudge_val=0.2 --adjoint_incoherent_e_to_max_e_nudge_val=1e-5 --adjoint_incoherent_eval_tol=1e-2 --adjoint_incoherent_grid_convergence_tol=0.5 --adjoint_incoherent_grid_absolute_diff_tol=1e-42 --adjoint_incoherent_grid_dist_tol=1e-16 --cutoff_angle_cosine=0.9 --number_of_moment_preserving_angles=2 --electron_tabular_evaluation_tol=1e-6 --electron_linlinlog_interp --electron_correlated_sampling --electron_unit_based_interp --adjoint_electron_grid_convergence_tol=1e-2 --adjoint_electron_grid_absolute_diff_tol=1e-16 --adjoint_electron_dist_tol=1e-9 --adjoint_bremsstrahlung_max_e_nudge_val=0.2 --adjoint_bremsstrahlung_e_to_outgoing_e_nudge_val=1e-7 --adjoint_bremsstrahlung_eval_tol=1e-6 --adjoint_bremsstrahlung_grid_convergence_tol=0.5 --adjoint_bremsstrahlung_grid_absolute_diff_tol=1e-16 --adjoint_bremsstrahlung_dist_tol=1e-9 --adjoint_electroionization_eval_tol=1e-6 --adjoint_electroionization_grid_convergence_tol=0.5 --adjoint_electroionization_grid_absolute_diff_tol=1e-16 --adjoint_electroionization_dist_tol=1e-9 --grid_convergence_tol=1e-3 --grid_absolute_diff_tol=1e-42 --grid_absolute_dist_tol=1e-16 --notes="$notes"
if [ $? -eq 0 ]
then
    printf "adjoint Al native data updated successfully!\n\n"
    mv aepr_13_native.xml test_aepr_13_native.xml
else
    printf "adjoint Al native data FAILED to update!\n"
    exit 1
fi

# Update adjoint Silicon data
printf "Updating the adjoint Si native test data...\n"
rm test_aepr_14_native.xml
aepr_generator --forward_file=test_epr_14_native.xml --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=20 --adjoint_pp_edist_eval_tol=1e-3 --adjoint_pp_edist_nudge_val=1e-6 --adjoint_tp_edist_eval_tol=1e-3 --adjoint_tp_edist_nudge_val=1e-6 --adjoint_incoherent_max_e_nudge_val=0.2 --adjoint_incoherent_e_to_max_e_nudge_val=1e-5 --adjoint_incoherent_eval_tol=1e-2 --adjoint_incoherent_grid_convergence_tol=0.5 --adjoint_incoherent_grid_absolute_diff_tol=1e-42 --adjoint_incoherent_grid_dist_tol=1e-16 --cutoff_angle_cosine=1.0 --number_of_moment_preserving_angles=0 --electron_tabular_evaluation_tol=1e-6 --electron_linlinlog_interp --electron_correlated_sampling --electron_unit_based_interp --adjoint_electron_grid_convergence_tol=1e-2 --adjoint_electron_grid_absolute_diff_tol=1e-16 --adjoint_electron_dist_tol=1e-9 --adjoint_bremsstrahlung_max_e_nudge_val=0.2 --adjoint_bremsstrahlung_e_to_outgoing_e_nudge_val=1e-7 --adjoint_bremsstrahlung_eval_tol=1e-6 --adjoint_bremsstrahlung_grid_convergence_tol=0.5 --adjoint_bremsstrahlung_grid_absolute_diff_tol=1e-16 --adjoint_bremsstrahlung_dist_tol=1e-9 --adjoint_electroionization_eval_tol=1e-6 --adjoint_electroionization_grid_convergence_tol=0.5 --adjoint_electroionization_grid_absolute_diff_tol=1e-16 --adjoint_electroionization_dist_tol=1e-9 --grid_convergence_tol=1e-3 --grid_absolute_diff_tol=1e-42 --grid_absolute_dist_tol=1e-16 --notes="$notes"
if [ $? -eq 0 ]
then
    printf "adjoint Si native data updated successfully!\n\n"
    mv aepr_14_native.xml test_aepr_14_native.xml
else
    printf "adjoint Si native data FAILED to update!\n"
    exit 1
fi
    
# Update adjoint Lead data
# printf "Updating the adjoint Pb native test data...\n"
# aepr_generator --forward_file=test_epr_82_native.xml --min_photon_energy=1e-3 --max_photon_energy=20.0 --min_electron_energy=1e-5 --max_electron_energy=20 --adjoint_pp_edist_eval_tol=1e-3 --adjoint_pp_edist_nudge_val=1e-6 --adjoint_tp_edist_eval_tol=1e-3 --adjoint_tp_edist_nudge_val=1e-6 --adjoint_incoherent_max_e_nudge_val=0.2 --adjoint_incoherent_e_to_max_e_nudge_val=1e-5 --adjoint_incoherent_eval_tol=1e-2 --adjoint_incoherent_grid_convergence_tol=0.5 --adjoint_incoherent_grid_absolute_diff_tol=1e-42 --adjoint_incoherent_grid_dist_tol=1e-16 --cutoff_angle_cosine=1.0 --number_of_moment_preserving_angles=0 --electron_tabular_evaluation_tol=1e-6 --electron_linlinlog_interp --electron_correlated_sampling --electron_unit_based_interp --adjoint_electron_grid_convergence_tol=1e-2 --adjoint_electron_grid_absolute_diff_tol=1e-16 --adjoint_electron_dist_tol=1e-9 --adjoint_bremsstrahlung_max_e_nudge_val=0.2 --adjoint_bremsstrahlung_e_to_outgoing_e_nudge_val=1e-7 --adjoint_bremsstrahlung_eval_tol=1e-6 --adjoint_bremsstrahlung_grid_convergence_tol=0.5 --adjoint_bremsstrahlung_grid_absolute_diff_tol=1e-16 --adjoint_bremsstrahlung_dist_tol=1e-9 --adjoint_electroionization_eval_tol=1e-6 --adjoint_electroionization_grid_convergence_tol=0.5 --adjoint_electroionization_grid_absolute_diff_tol=1e-16 --adjoint_electroionization_dist_tol=1e-9 --grid_convergence_tol=1e-3 --grid_absolute_diff_tol=1e-42 --grid_absolute_dist_tol=1e-16 --notes="$notes"
# if [ $? -eq 0 ]
# then
#     printf "adjoint Pb native data updated successfully!\n\n"
#     mv aepr_82_native.xml test_aepr_82_native.xml
# else
#     printf "adjoint Pb native data FAILED to update!\n"
#     exit 1
# fi

