//---------------------------------------------------------------------------//
//!
//! \file   Data_ElectronPhotonRelaxationDataContainer_def.hpp
//! \author Alex Robinson
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

namespace Data{

// Save the data to an archive
template<typename Archive>
void ElectronPhotonRelaxationDataContainer::save( Archive& ar, 
						  const unsigned version) const
{
  ar & boost::serialization::make_nvp( "atomic_number", d_atomic_number );
  ar & boost::serialization::make_nvp( "subshells", d_subshells );
  ar & boost::serialization::make_nvp( "subshell_occupancies", 
				       d_subshell_occupancies );
  ar & boost::serialization::make_nvp( "subshell_binding_energies", 
				       d_subshell_binding_energies );
  ar & boost::serialization::make_nvp( "relaxation_transitions", 
				       d_relaxation_transitions );
  ar & boost::serialization::make_nvp( "relaxation_vacancies", 
				       d_relaxation_vacancies );
  ar & boost::serialization::make_nvp( "relaxation_particle_energies", 
				       d_relaxation_particle_energies );
  ar & boost::serialization::make_nvp( "relaxation_probabilities", 
				       d_relaxation_probabilities );
  ar & boost::serialization::make_nvp( "compton_profile_momentum_grid", 
				       d_compton_profile_momentum_grid );
  ar & boost::serialization::make_nvp( "comton_profiles", 
				       d_compton_profiles );
  ar & boost::serialization::make_nvp( "occupancy_number_momentum_grid", 
				       d_occupancy_number_momentum_grid );
  ar & boost::serialization::make_nvp( "occupancy_numbers",
				       d_occupancy_numbers );
  ar & boost::serialization::make_nvp( "waller_hartree_scattering_function_momentum_grid",
				       d_waller_hartree_scattering_function_momentum_grid );
  ar & boost::serialization::make_nvp( "waller_hartree_scattering_function",
				       d_waller_hartree_scattering_function );
  ar & boost::serialization::make_nvp( "waller_hartree_atomic_form_factor_momentum_grid",
				       d_waller_hartree_atomic_form_factor_momentum_grid );
  ar & boost::serialization::make_nvp( "waller_hartree_atomic_form_factor",
				       d_waller_hartree_atomic_form_factor );
  ar & boost::serialization::make_nvp( "photon_energy_grid",
				       d_photon_energy_grid );
  ar & boost::serialization::make_nvp( "average_photon_heating_numbers",
				       d_average_photon_heating_numbers );
  ar & boost::serialization::make_nvp( "waller_hartree_incoherent_cross_section",
				       d_waller_hartree_incoherent_cross_section );
  ar & boost::serialization::make_nvp( "waller_hartree_incoherent_cross_section_threshold_index",
				       d_waller_hartree_incoherent_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "impulse_approx_incoherent_cross_section",
				       d_impulse_approx_incoherent_cross_section );
  ar & boost::serialization::make_nvp( "impulse_approx_incoherent_cross_section_threshold_index",
				       d_impulse_approx_incoherent_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "impulse_approx_subshell_incoherent_cross_sections",
				       d_impulse_approx_subshell_incoherent_cross_sections );
  ar & boost::serialization::make_nvp( "d_impulse_approx_subshell_incoherent_cross_section_theshold_indices",
				       d_impulse_approx_subshell_incoherent_cross_section_theshold_indices );
  ar & boost::serialization::make_nvp( "waller_hartree_coherent_cross_section",
				       d_waller_hartree_coherent_cross_section );
  ar & boost::serialization::make_nvp( "waller_hartree_coherent_cross_section_threshold_index",
				       d_waller_hartree_coherent_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "pair_production_cross_section",
				       d_pair_production_cross_section );
  ar & boost::serialization::make_nvp( "pair_production_cross_section_threshold_index",
				       d_pair_production_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "photoelectric_cross_section",
				       d_photoelectric_cross_section );
  ar & boost::serialization::make_nvp( "photoelectric_cross_section_threshold_index",
				       d_photoelectric_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "subshell_photoelectric_cross_sections",
				       d_subshell_photoelectric_cross_sections );
  ar & boost::serialization::make_nvp( "subshell_photoelectric_cross_section_threshold_indices",
				       d_subshell_photoelectric_cross_section_threshold_indices );
  ar & boost::serialization::make_nvp( "waller_hartree_total_cross_section",
				       d_waller_hartree_total_cross_section );
  ar & boost::serialization::make_nvp( "impulse_approx_total_cross_section",
				       d_impulse_approx_total_cross_section );
}
  
// Load the data from an archive
template<typename Archive>
void ElectronPhotonRelaxationDataContainer::load( Archive& ar, 
						  const unsigned version )
{
  ar & boost::serialization::make_nvp( "atomic_number", d_atomic_number );
  ar & boost::serialization::make_nvp( "subshells", d_subshells );
  ar & boost::serialization::make_nvp( "subshell_occupancies", 
				       d_subshell_occupancies );
  ar & boost::serialization::make_nvp( "subshell_binding_energies", 
				       d_subshell_binding_energies );
  ar & boost::serialization::make_nvp( "relaxation_transitions", 
				       d_relaxation_transitions );
  ar & boost::serialization::make_nvp( "relaxation_vacancies", 
				       d_relaxation_vacancies );
  ar & boost::serialization::make_nvp( "relaxation_particle_energies", 
				       d_relaxation_particle_energies );
  ar & boost::serialization::make_nvp( "relaxation_probabilities", 
				       d_relaxation_probabilities );
  ar & boost::serialization::make_nvp( "compton_profile_momentum_grid", 
				       d_compton_profile_momentum_grid );
  ar & boost::serialization::make_nvp( "comton_profiles", 
				       d_compton_profiles );
  ar & boost::serialization::make_nvp( "occupancy_number_momentum_grid", 
				       d_occupancy_number_momentum_grid );
  ar & boost::serialization::make_nvp( "occupancy_numbers",
				       d_occupancy_numbers );
  ar & boost::serialization::make_nvp( "waller_hartree_scattering_function_momentum_grid",
				       d_waller_hartree_scattering_function_momentum_grid );
  ar & boost::serialization::make_nvp( "waller_hartree_scattering_function",
				       d_waller_hartree_scattering_function );
  ar & boost::serialization::make_nvp( "waller_hartree_atomic_form_factor_momentum_grid",
				       d_waller_hartree_atomic_form_factor_momentum_grid );
  ar & boost::serialization::make_nvp( "waller_hartree_atomic_form_factor",
				       d_waller_hartree_atomic_form_factor );
  ar & boost::serialization::make_nvp( "photon_energy_grid",
				       d_photon_energy_grid );
  ar & boost::serialization::make_nvp( "average_photon_heating_numbers",
				       d_average_photon_heating_numbers );
  ar & boost::serialization::make_nvp( "waller_hartree_incoherent_cross_section",
				       d_waller_hartree_incoherent_cross_section );
  ar & boost::serialization::make_nvp( "waller_hartree_incoherent_cross_section_threshold_index",
				       d_waller_hartree_incoherent_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "impulse_approx_incoherent_cross_section",
				       d_impulse_approx_incoherent_cross_section );
  ar & boost::serialization::make_nvp( "impulse_approx_incoherent_cross_section_threshold_index",
				       d_impulse_approx_incoherent_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "impulse_approx_subshell_incoherent_cross_sections",
				       d_impulse_approx_subshell_incoherent_cross_sections );
  ar & boost::serialization::make_nvp( "d_impulse_approx_subshell_incoherent_cross_section_theshold_indices",
				       d_impulse_approx_subshell_incoherent_cross_section_theshold_indices );
  ar & boost::serialization::make_nvp( "waller_hartree_coherent_cross_section",
				       d_waller_hartree_coherent_cross_section );
  ar & boost::serialization::make_nvp( "waller_hartree_coherent_cross_section_threshold_index",
				       d_waller_hartree_coherent_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "pair_production_cross_section",
				       d_pair_production_cross_section );
  ar & boost::serialization::make_nvp( "pair_production_cross_section_threshold_index",
				       d_pair_production_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "photoelectric_cross_section",
				       d_photoelectric_cross_section );
  ar & boost::serialization::make_nvp( "photoelectric_cross_section_threshold_index",
				       d_photoelectric_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "subshell_photoelectric_cross_sections",
				       d_subshell_photoelectric_cross_sections );
  ar & boost::serialization::make_nvp( "subshell_photoelectric_cross_section_threshold_indices",
				       d_subshell_photoelectric_cross_section_threshold_indices );
  ar & boost::serialization::make_nvp( "waller_hartree_total_cross_section",
				       d_waller_hartree_total_cross_section );
  ar & boost::serialization::make_nvp( "impulse_approx_total_cross_section",
				       d_impulse_approx_total_cross_section );
}

} // end Data namespace

#endif // end DATA_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_ElectronPhotonRelaxationDataContainer_def.hpp
//---------------------------------------------------------------------------//
