//---------------------------------------------------------------------------//
//!
//! \file   Data_ElectronPhotonRelaxationContainer_def.hpp
//! \author Alex Robinson
//! \brief  The native electron-photon-relaxation data container template defs.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ELECTRON_PHOTON_RELAXATION_CONTAINER_DEF_HPP
#define DATA_ELECTRON_PHOTON_RELAXATION_CONTAINER_DEF_HPP

// Boost Includes
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>

namespace Data{

// Save the data to an archive
template<typename Archive>
void ElectronPhotonRelaxationContainer::save( Archive& ar, 
					      const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_atomic_number );
  ar & BOOST_SERIALIZATION_NVP( d_subshells );
  ar & BOOST_SERIALIZATION_NVP( d_subshell_occupancies );
  ar & BOOST_SERIALIZATION_NVP( d_subshell_binding_energies );
  ar & BOOST_SERIALIZATION_NVP( d_relaxation_transitions );
  ar & BOOST_SERIALIZATION_NVP( d_relaxation_vacancies );
  ar & BOOST_SERIALIZATION_NVP( d_relaxation_particle_energies );
  ar & BOOST_SERIALIZATION_NVP( d_relaxation_cdf );
  ar & BOOST_SERIALIZATION_NVP( d_compton_profile_momentum_grids );
  ar & BOOST_SERIALIZATION_NVP( d_compton_profiles );
  ar & BOOST_SERIALIZATION_NVP( d_occupancy_number_momentum_grids );
  ar & BOOST_SERIALIZATION_NVP( d_occupancy_numbers );
  ar & BOOST_SERIALIZATION_NVP( d_waller_hartree_scattering_function_momentum_grid );
  ar & BOOST_SERIALIZATION_NVP( d_waller_hartree_scattering_function );
  ar & BOOST_SERIALIZATION_NVP( d_waller_hartree_atomic_form_factor_momentum_grid );
  ar & BOOST_SERIALIZATION_NVP( d_waller_hartree_atomic_form_factor );
  ar & BOOST_SERIALIZATION_NVP( d_photon_energy_grid );
  ar & BOOST_SERIALIZATION_NVP( d_average_photon_heating_numbers );
  ar & BOOST_SERIALIZATION_NVP( d_waller_hartree_incoherent_cross_section );
  ar & BOOST_SERIALIZATION_NVP( d_waller_hartree_incoherent_cross_section_threshold_index );
  ar & BOOST_SERIALIZATION_NVP( d_impulse_approx_incoherent_cross_section );
  ar & BOOST_SERIALIZATION_NVP( d_impulse_approx_incoherent_cross_section_threshold_index );
  ar & BOOST_SERIALIZATION_NVP( d_impulse_approx_subshell_incoherent_cross_sections );
  ar & BOOST_SERIALIZATION_NVP( d_impulse_approx_subshell_incoherent_cross_section_threshold_indices );
  ar & BOOST_SERIALIZATION_NVP( d_waller_hartree_coherent_cross_section );
  ar & BOOST_SERIALIZATION_NVP( d_waller_hartree_coherent_cross_section_threshold_index );
  ar & BOOST_SERIALIZATION_NVP( d_pair_production_cross_section );
  ar & BOOST_SERIALIZATION_NVP( d_pair_production_cross_section_threshold_index );
  ar & BOOST_SERIALIZATION_NVP( d_photoelectric_cross_section );
  ar & BOOST_SERIALIZATION_NVP( d_photoelectric_cross_section_threshold_index );
  ar & BOOST_SERIALIZATION_NVP( d_subshell_photoelectric_cross_sections );
  ar & BOOST_SERIALIZATION_NVP( d_subshell_photoelectric_cross_section_threshold_indices );
  ar & BOOST_SERIALIZATION_NVP( d_waller_hartree_total_cross_section );
  ar & BOOST_SERIALIZATION_NVP( d_impulse_approx_total_cross_section );
}
  
// Load the data from an archive
template<typename Archive>
void ElectronPhotonRelaxationContainer::load( Archive& ar, 
					      const unsigned version )
{
  ar & d_atomic_number;
  ar & d_subshells;
  ar & d_subshell_occupancies;
  ar & d_subshell_binding_energies;
  ar & d_relaxation_transitions;
  ar & d_relaxation_vacancies;
  ar & d_relaxation_particle_energies;
  ar & d_relaxation_cdf;
  ar & d_compton_profile_momentum_grids;
  ar & d_compton_profiles;
  ar & d_occupancy_number_momentum_grids;
  ar & d_occupancy_numbers;
  ar & d_waller_hartree_scattering_function_momentum_grid;
  ar & d_waller_hartree_scattering_function;
  ar & d_waller_hartree_atomic_form_factor_momentum_grid;
  ar & d_waller_hartree_atomic_form_factor;
  ar & d_photon_energy_grid;
  ar & d_average_photon_heating_numbers;
  ar & d_waller_hartree_incoherent_cross_section;
  ar & d_waller_hartree_incoherent_cross_section_threshold_index;
  ar & d_impulse_approx_incoherent_cross_section;
  ar & d_impulse_approx_incoherent_cross_section_threshold_index;
  ar & d_impulse_approx_subshell_incoherent_cross_sections;
  ar & d_impulse_approx_subshell_incoherent_cross_section_threshold_indices;
  ar & d_waller_hartree_coherent_cross_section;
  ar & d_waller_hartree_coherent_cross_section_threshold_index;
  ar & d_pair_production_cross_section;
  ar & d_pair_production_cross_section_threshold_index;
  ar & d_photoelectric_cross_section;
  ar & d_photoelectric_cross_section_threshold_index;
  ar & d_subshell_photoelectric_cross_sections;
  ar & d_subshell_photoelectric_cross_section_threshold_indices;
  ar & d_waller_hartree_total_cross_section;
  ar & d_impulse_approx_total_cross_section;
}

} // end Data namespace

#endif // end DATA_ELECTRON_PHOTON_RELAXATION_CONTAINER_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_ElectronPhotonRelaxationContainer_def.hpp
//---------------------------------------------------------------------------//
