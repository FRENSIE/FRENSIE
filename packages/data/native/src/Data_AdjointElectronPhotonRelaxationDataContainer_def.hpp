//---------------------------------------------------------------------------//
//!
//! \file   Data_AdjointElectronPhotonRelaxationDataContainer_def.hpp
//! \author Luke Kersting
//! \brief  The native adjoint electron-photon-relaxation data container template defs.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_DEF_HPP
#define DATA_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_DEF_HPP

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
void AdjointElectronPhotonRelaxationDataContainer::save( Archive& ar,
						  const unsigned version) const
{
  // Table Data
  DATA_MAKE_NVP_DEFAULT( atomic_number );
  DATA_MAKE_NVP_DEFAULT( min_photon_energy );
  DATA_MAKE_NVP_DEFAULT( max_photon_energy );
  DATA_MAKE_NVP_DEFAULT( min_electron_energy );
  DATA_MAKE_NVP_DEFAULT( max_electron_energy );
  DATA_MAKE_NVP_DEFAULT( cutoff_angle_cosine );
  DATA_MAKE_NVP_DEFAULT( number_of_adjoint_moment_preserving_angles );
  DATA_MAKE_NVP_DEFAULT( grid_convergence_tol );
  DATA_MAKE_NVP_DEFAULT( grid_absolute_diff_tol );
  DATA_MAKE_NVP_DEFAULT( grid_distance_tol );

  // Relaxation Data
  DATA_MAKE_NVP_DEFAULT( subshells );
  DATA_MAKE_NVP_DEFAULT( subshell_occupancies );
  DATA_MAKE_NVP_DEFAULT( subshell_binding_energies );

  // Photon Data
  DATA_MAKE_NVP_DEFAULT( compton_profile_momentum_grids );
  DATA_MAKE_NVP_DEFAULT( compton_profiles );
  DATA_MAKE_NVP_DEFAULT( occupation_number_momentum_grids );
  DATA_MAKE_NVP_DEFAULT( occupation_numbers );
  DATA_MAKE_NVP_DEFAULT( waller_hartree_scattering_function_momentum_grid );
  DATA_MAKE_NVP_DEFAULT( waller_hartree_scattering_function );
  DATA_MAKE_NVP_DEFAULT( waller_hartree_atomic_form_factor_momentum_grid );
  DATA_MAKE_NVP_DEFAULT( waller_hartree_atomic_form_factor );
  DATA_MAKE_NVP_DEFAULT( adjoint_photon_energy_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_waller_hartree_incoherent_max_energy_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_waller_hartree_incoherent_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_impulse_approx_subshell_incoherent_max_energy_grids );
  DATA_MAKE_NVP_DEFAULT( adjoint_impulse_approx_subshell_incoherent_cross_sections );
  DATA_MAKE_NVP_DEFAULT( waller_hartree_coherent_cross_sections );
  DATA_MAKE_NVP_DEFAULT( adjoint_pair_production_energy_distribution_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_pair_production_energy_distribution );
  DATA_MAKE_NVP_DEFAULT( adjoint_pair_production_norm_constant_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_pair_production_norm_constant );
  DATA_MAKE_NVP_DEFAULT( photon_energy_grid );
  DATA_MAKE_NVP_DEFAULT( waller_hartree_total_cross_section );
  DATA_MAKE_NVP_DEFAULT( impulse_approx_total_cross_section );
  
  // Electron Data
  DATA_MAKE_NVP_DEFAULT( adjoint_angular_energy_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_cutoff_elastic_angles );
  DATA_MAKE_NVP_DEFAULT( adjoint_cutoff_elastic_pdf );
  DATA_MAKE_NVP_DEFAULT( adjoint_moment_preserving_elastic_discrete_angles );
  DATA_MAKE_NVP_DEFAULT( djoint_moment_preserving_elastic_weights );
  DATA_MAKE_NVP_DEFAULT( adjoint_electroionization_energy_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_electroionization_recoil_energy );
  DATA_MAKE_NVP_DEFAULT( adjoint_electroionization_recoil_pdf );
  DATA_MAKE_NVP_DEFAULT( adjoint_bremsstrahlung_energy_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_bremsstrahlung_photon_energy );
  DATA_MAKE_NVP_DEFAULT( adjoint_bremsstrahlung_photon_pdf );
  DATA_MAKE_NVP_DEFAULT( adjoint_atomic_excitation_energy_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_atomic_excitation_energy_gain );
  DATA_MAKE_NVP_DEFAULT( adjoint_electron_energy_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_cutoff_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_cutoff_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( adjoint_screened_rutherford_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_screened_rutherford_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( adjoint_total_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_total_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( adjoint_moment_preserving_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_moment_preserving_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( adjoint_electroionization_subshell_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_electroionization_subshell_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( adjoint_bremsstrahlung_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_bremsstrahlung_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( adjoint_atomic_excitation_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_atomic_excitation_cross_section_threshold_index );
}

// Load the data from an archive
template<typename Archive>
void AdjointElectronPhotonRelaxationDataContainer::load( Archive& ar,
						  const unsigned version )
{
  // Table Data
  DATA_MAKE_NVP_DEFAULT( atomic_number );
  DATA_MAKE_NVP_DEFAULT( min_photon_energy );
  DATA_MAKE_NVP_DEFAULT( max_photon_energy );
  DATA_MAKE_NVP_DEFAULT( min_electron_energy );
  DATA_MAKE_NVP_DEFAULT( max_electron_energy );
  DATA_MAKE_NVP_DEFAULT( cutoff_angle_cosine );
  DATA_MAKE_NVP_DEFAULT( number_of_adjoint_moment_preserving_angles );
  DATA_MAKE_NVP_DEFAULT( grid_convergence_tol );
  DATA_MAKE_NVP_DEFAULT( grid_absolute_diff_tol );
  DATA_MAKE_NVP_DEFAULT( grid_distance_tol );

  // Relaxation Data
  DATA_MAKE_NVP_DEFAULT( subshells );
  DATA_MAKE_NVP_DEFAULT( subshell_occupancies );
  DATA_MAKE_NVP_DEFAULT( subshell_binding_energies );

  // Photon Data
  DATA_MAKE_NVP_DEFAULT( compton_profile_momentum_grids );
  DATA_MAKE_NVP_DEFAULT( compton_profiles );
  DATA_MAKE_NVP_DEFAULT( occupation_number_momentum_grids );
  DATA_MAKE_NVP_DEFAULT( occupation_numbers );
  DATA_MAKE_NVP_DEFAULT( waller_hartree_scattering_function_momentum_grid );
  DATA_MAKE_NVP_DEFAULT( waller_hartree_scattering_function );
  DATA_MAKE_NVP_DEFAULT( waller_hartree_atomic_form_factor_momentum_grid );
  DATA_MAKE_NVP_DEFAULT( waller_hartree_atomic_form_factor );
  DATA_MAKE_NVP_DEFAULT( adjoint_photon_energy_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_waller_hartree_incoherent_max_energy_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_waller_hartree_incoherent_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_impulse_approx_subshell_incoherent_max_energy_grids );
  DATA_MAKE_NVP_DEFAULT( adjoint_impulse_approx_subshell_incoherent_cross_sections );
  DATA_MAKE_NVP_DEFAULT( waller_hartree_coherent_cross_sections );
  DATA_MAKE_NVP_DEFAULT( adjoint_pair_production_energy_distribution_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_pair_production_energy_distribution );
  DATA_MAKE_NVP_DEFAULT( adjoint_pair_production_norm_constant_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_pair_production_norm_constant );
  DATA_MAKE_NVP_DEFAULT( photon_energy_grid );
  DATA_MAKE_NVP_DEFAULT( waller_hartree_total_cross_section );
  DATA_MAKE_NVP_DEFAULT( impulse_approx_total_cross_section );

  // Electron Data
  DATA_MAKE_NVP_DEFAULT( adjoint_angular_energy_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_cutoff_elastic_angles );
  DATA_MAKE_NVP_DEFAULT( adjoint_cutoff_elastic_pdf );
  DATA_MAKE_NVP_DEFAULT( adjoint_moment_preserving_elastic_discrete_angles );
  DATA_MAKE_NVP_DEFAULT( adjoint_moment_preserving_elastic_weights );
  DATA_MAKE_NVP_DEFAULT( adjoint_electroionization_energy_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_electroionization_recoil_energy );
  DATA_MAKE_NVP_DEFAULT( adjoint_electroionization_recoil_pdf );
  DATA_MAKE_NVP_DEFAULT( adjoint_bremsstrahlung_energy_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_bremsstrahlung_photon_energy );
  DATA_MAKE_NVP_DEFAULT( adjoint_bremsstrahlung_photon_pdf );
  DATA_MAKE_NVP_DEFAULT( adjoint_atomic_excitation_energy_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_atomic_excitation_energy_gain );
  DATA_MAKE_NVP_DEFAULT( adjoint_electron_energy_grid );
  DATA_MAKE_NVP_DEFAULT( adjoint_cutoff_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_cutoff_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( adjoint_screened_rutherford_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_screened_rutherford_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( adjoint_total_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_total_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( adjoint_moment_preserving_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_moment_preserving_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( adjoint_electroionization_subshell_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_electroionization_subshell_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( adjoint_bremsstrahlung_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_bremsstrahlung_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( adjoint_atomic_excitation_cross_section );
  DATA_MAKE_NVP_DEFAULT( adjoint_atomic_excitation_cross_section_threshold_index );
}

} // end Data namespace

#endif // end DATA_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_AdjointElectronPhotonRelaxationDataContainer_def.hpp
//---------------------------------------------------------------------------//
