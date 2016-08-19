//---------------------------------------------------------------------------//
//!
//! \file   Data_ElectronPhotonRelaxationDataContainer_def.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The native electron-photon-relaxation data container template defs.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_DEF_HPP
#define DATA_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_DEF_HPP

// Boost Includes
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>

// FRENSIE Includes
#include "Data_DataContainerHelpers.hpp"

namespace Data{

// Save the data to an archive
template<typename Archive>
void ElectronPhotonRelaxationDataContainer::save( Archive& ar,
						  const unsigned version) const
{
  // Notes
  DATA_MAKE_NVP_DEFAULT( ar, notes );
  
  // Table Data
  DATA_MAKE_NVP_DEFAULT( ar, atomic_number );
  DATA_MAKE_NVP_DEFAULT( ar, min_photon_energy );
  DATA_MAKE_NVP_DEFAULT( ar, max_photon_energy );
  DATA_MAKE_NVP_DEFAULT( ar, min_electron_energy );
  DATA_MAKE_NVP_DEFAULT( ar, max_electron_energy );
  DATA_MAKE_NVP_DEFAULT( ar, occupation_number_evaluation_tolerance );
  DATA_MAKE_NVP_DEFAULT( ar, subshell_incoherent_evaluation_tolerance );
  DATA_MAKE_NVP_DEFAULT( ar, photon_threshold_energy_nudge_factor );
  DATA_MAKE_NVP_DEFAULT( ar, cutoff_angle_cosine );
  DATA_MAKE_NVP_DEFAULT( ar, number_of_moment_preserving_angles );
  DATA_MAKE_NVP_DEFAULT( ar, grid_convergence_tol );
  DATA_MAKE_NVP_DEFAULT( ar, grid_absolute_diff_tol );
  DATA_MAKE_NVP_DEFAULT( ar, grid_distance_tol );

  // Relaxation Data
  DATA_MAKE_NVP_DEFAULT( ar, subshells );
  DATA_MAKE_NVP_DEFAULT( ar, subshell_occupancies );
  DATA_MAKE_NVP_DEFAULT( ar, subshell_binding_energies );
  DATA_MAKE_NVP_DEFAULT( ar, relaxation_transitions );
  DATA_MAKE_NVP_DEFAULT( ar, relaxation_vacancies );
  DATA_MAKE_NVP_DEFAULT( ar, relaxation_particle_energies );
  DATA_MAKE_NVP_DEFAULT( ar, relaxation_probabilities );

  // Photon Data
  DATA_MAKE_NVP_DEFAULT( ar, compton_profile_momentum_grids );
  DATA_MAKE_NVP_DEFAULT( ar, compton_profiles );
  DATA_MAKE_NVP_DEFAULT( ar, occupation_number_momentum_grids );
  DATA_MAKE_NVP_DEFAULT( ar, occupation_numbers );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_scattering_function_momentum_grid );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_scattering_function );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_atomic_form_factor_momentum_grid );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_atomic_form_factor );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_squared_atomic_form_factor_squared_momentum_grid );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_squared_atomic_form_factor );
  DATA_MAKE_NVP_DEFAULT( ar, photon_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, average_photon_heating_numbers );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_incoherent_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_incoherent_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, impulse_approx_incoherent_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, impulse_approx_incoherent_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, impulse_approx_subshell_incoherent_cross_sections );
  DATA_MAKE_NVP_DEFAULT( ar, impulse_approx_subshell_incoherent_cross_section_threshold_indices );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_coherent_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_coherent_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, pair_production_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, pair_production_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, triplet_production_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, triplet_production_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, photoelectric_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, photoelectric_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, subshell_photoelectric_cross_sections );
  DATA_MAKE_NVP_DEFAULT( ar, subshell_photoelectric_cross_section_threshold_indices );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_total_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, impulse_approx_total_cross_section );
  // Electron Data
  DATA_MAKE_NVP_DEFAULT( ar, angular_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, cutoff_elastic_angles );
  DATA_MAKE_NVP_DEFAULT( ar, cutoff_elastic_pdf );
  DATA_MAKE_NVP_DEFAULT( ar, screened_rutherford_normalization_constant );
  DATA_MAKE_NVP_DEFAULT( ar, moliere_screening_constant );
  DATA_MAKE_NVP_DEFAULT( ar, moment_preserving_elastic_discrete_angles );
  DATA_MAKE_NVP_DEFAULT( ar, moment_preserving_elastic_weights );
  DATA_MAKE_NVP_DEFAULT( ar, electroionization_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, electroionization_recoil_energy );
  DATA_MAKE_NVP_DEFAULT( ar, electroionization_recoil_pdf );
  DATA_MAKE_NVP_DEFAULT( ar, bremsstrahlung_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, bremsstrahlung_photon_energy );
  DATA_MAKE_NVP_DEFAULT( ar, bremsstrahlung_photon_pdf );
  DATA_MAKE_NVP_DEFAULT( ar, atomic_excitation_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, atomic_excitation_energy_loss );
  DATA_MAKE_NVP_DEFAULT( ar, electron_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, cutoff_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, cutoff_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, screened_rutherford_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, screened_rutherford_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, total_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, total_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, moment_preserving_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, moment_preserving_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, electroionization_subshell_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, electroionization_subshell_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, bremsstrahlung_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, bremsstrahlung_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, atomic_excitation_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, atomic_excitation_cross_section_threshold_index );
}

// Load the data from an archive
template<typename Archive>
void ElectronPhotonRelaxationDataContainer::load( Archive& ar,
						  const unsigned version )
{
  // Notes
  DATA_MAKE_NVP_DEFAULT( ar, notes );
  
  // Table Data
  DATA_MAKE_NVP_DEFAULT( ar, atomic_number );
  DATA_MAKE_NVP_DEFAULT( ar, min_photon_energy );
  DATA_MAKE_NVP_DEFAULT( ar, max_photon_energy );
  DATA_MAKE_NVP_DEFAULT( ar, min_electron_energy );
  DATA_MAKE_NVP_DEFAULT( ar, max_electron_energy );
  DATA_MAKE_NVP_DEFAULT( ar, occupation_number_evaluation_tolerance );
  DATA_MAKE_NVP_DEFAULT( ar, subshell_incoherent_evaluation_tolerance );
  DATA_MAKE_NVP_DEFAULT( ar, photon_threshold_energy_nudge_factor );
  DATA_MAKE_NVP_DEFAULT( ar, cutoff_angle_cosine );
  DATA_MAKE_NVP_DEFAULT( ar, number_of_moment_preserving_angles );
  DATA_MAKE_NVP_DEFAULT( ar, grid_convergence_tol );
  DATA_MAKE_NVP_DEFAULT( ar, grid_absolute_diff_tol );
  DATA_MAKE_NVP_DEFAULT( ar, grid_distance_tol );

  // Relaxation Data
  DATA_MAKE_NVP_DEFAULT( ar, subshells );
  DATA_MAKE_NVP_DEFAULT( ar, subshell_occupancies );
  DATA_MAKE_NVP_DEFAULT( ar, subshell_binding_energies );
  DATA_MAKE_NVP_DEFAULT( ar, relaxation_transitions );
  DATA_MAKE_NVP_DEFAULT( ar, relaxation_vacancies );
  DATA_MAKE_NVP_DEFAULT( ar, relaxation_particle_energies );
  DATA_MAKE_NVP_DEFAULT( ar, relaxation_probabilities );

  // Photon Data
  DATA_MAKE_NVP_DEFAULT( ar, compton_profile_momentum_grids );
  DATA_MAKE_NVP_DEFAULT( ar, compton_profiles );
  DATA_MAKE_NVP_DEFAULT( ar, occupation_number_momentum_grids );
  DATA_MAKE_NVP_DEFAULT( ar, occupation_numbers );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_scattering_function_momentum_grid );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_scattering_function );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_atomic_form_factor_momentum_grid );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_atomic_form_factor );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_squared_atomic_form_factor_squared_momentum_grid );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_squared_atomic_form_factor );
  DATA_MAKE_NVP_DEFAULT( ar, photon_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, average_photon_heating_numbers );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_incoherent_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_incoherent_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, impulse_approx_incoherent_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, impulse_approx_incoherent_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, impulse_approx_subshell_incoherent_cross_sections );
  DATA_MAKE_NVP_DEFAULT( ar, impulse_approx_subshell_incoherent_cross_section_threshold_indices );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_coherent_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_coherent_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, pair_production_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, pair_production_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, triplet_production_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, triplet_production_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, photoelectric_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, photoelectric_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, subshell_photoelectric_cross_sections );
  DATA_MAKE_NVP_DEFAULT( ar, subshell_photoelectric_cross_section_threshold_indices );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_total_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, impulse_approx_total_cross_section );
  // Electron Data
  DATA_MAKE_NVP_DEFAULT( ar, angular_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, cutoff_elastic_angles );
  DATA_MAKE_NVP_DEFAULT( ar, cutoff_elastic_pdf );
  DATA_MAKE_NVP_DEFAULT( ar, screened_rutherford_normalization_constant );
  DATA_MAKE_NVP_DEFAULT( ar, moliere_screening_constant );
  DATA_MAKE_NVP_DEFAULT( ar, moment_preserving_elastic_discrete_angles );
  DATA_MAKE_NVP_DEFAULT( ar, moment_preserving_elastic_weights );
  DATA_MAKE_NVP_DEFAULT( ar, electroionization_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, electroionization_recoil_energy );
  DATA_MAKE_NVP_DEFAULT( ar, electroionization_recoil_pdf );
  DATA_MAKE_NVP_DEFAULT( ar, bremsstrahlung_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, bremsstrahlung_photon_energy );
  DATA_MAKE_NVP_DEFAULT( ar, bremsstrahlung_photon_pdf );
  DATA_MAKE_NVP_DEFAULT( ar, atomic_excitation_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, atomic_excitation_energy_loss );
  DATA_MAKE_NVP_DEFAULT( ar, electron_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, cutoff_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, cutoff_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, screened_rutherford_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, screened_rutherford_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, total_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, total_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, moment_preserving_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, moment_preserving_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, electroionization_subshell_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, electroionization_subshell_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, bremsstrahlung_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, bremsstrahlung_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, atomic_excitation_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, atomic_excitation_cross_section_threshold_index );
}

} // end Data namespace

#endif // end DATA_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_ElectronPhotonRelaxationDataContainer_def.hpp
//---------------------------------------------------------------------------//
