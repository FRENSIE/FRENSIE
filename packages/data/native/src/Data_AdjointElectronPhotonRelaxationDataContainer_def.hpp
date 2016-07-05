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

namespace Data{

// Save the data to an archive
template<typename Archive>
void AdjointElectronPhotonRelaxationDataContainer::save( Archive& ar,
						  const unsigned version) const
{
  // Table Data
  ar & boost::serialization::make_nvp( "atomic_number", d_atomic_number );
  ar & boost::serialization::make_nvp( "min_photon_energy",
                                        d_min_photon_energy );
  ar & boost::serialization::make_nvp( "max_photon_energy",
                                        d_max_photon_energy );
  ar & boost::serialization::make_nvp( "min_electron_energy",
                                        d_min_electron_energy );
  ar & boost::serialization::make_nvp( "max_electron_energy",
                                        d_max_electron_energy );
  ar & boost::serialization::make_nvp( "cutoff_angle_cosine",
                                        d_cutoff_angle_cosine );
  ar & boost::serialization::make_nvp( "number_of_adjoint_moment_preserving_angles",
                                        d_number_of_adjoint_moment_preserving_angles );
  ar & boost::serialization::make_nvp( "grid_convergence_tol",
                                        d_grid_convergence_tol );
  ar & boost::serialization::make_nvp( "grid_absolute_diff_tol",
                                        d_grid_absolute_diff_tol );
  ar & boost::serialization::make_nvp( "grid_distance_tol",
                                        d_grid_distance_tol );

  // Relaxation Data
  ar & boost::serialization::make_nvp( "subshells", d_subshells );
  ar & boost::serialization::make_nvp( "subshell_occupancies",
				       d_subshell_occupancies );
  ar & boost::serialization::make_nvp( "subshell_binding_energies",
				       d_subshell_binding_energies );

  // Photon Data

  // Electron Data
  ar & boost::serialization::make_nvp( "adjoint_angular_energy_grid",
				                        d_adjoint_angular_energy_grid );
  ar & boost::serialization::make_nvp( "adjoint_cutoff_elastic_angles",
                                        d_adjoint_cutoff_elastic_angles );
  ar & boost::serialization::make_nvp( "adjoint_cutoff_elastic_pdf",
                                        d_adjoint_cutoff_elastic_pdf );
  ar & boost::serialization::make_nvp(
            "adjoint_moment_preserving_elastic_discrete_angles",
            d_adjoint_moment_preserving_elastic_discrete_angles );
  ar & boost::serialization::make_nvp(
            "adjoint_moment_preserving_elastic_weights",
            d_adjoint_moment_preserving_elastic_weights );
  ar & boost::serialization::make_nvp( "adjoint_electroionization_energy_grid",
				                        d_adjoint_electroionization_energy_grid );
  ar & boost::serialization::make_nvp( "adjoint_electroionization_recoil_energy",
				                        d_adjoint_electroionization_recoil_energy );
  ar & boost::serialization::make_nvp( "adjoint_electroionization_recoil_pdf",
				                        d_adjoint_electroionization_recoil_pdf );
  ar & boost::serialization::make_nvp( "adjoint_bremsstrahlung_energy_grid",
				                        d_adjoint_bremsstrahlung_energy_grid );
  ar & boost::serialization::make_nvp( "adjoint_bremsstrahlung_photon_energy",
				                        d_adjoint_bremsstrahlung_photon_energy );
  ar & boost::serialization::make_nvp( "adjoint_bremsstrahlung_photon_pdf",
				                        d_adjoint_bremsstrahlung_photon_pdf );
  ar & boost::serialization::make_nvp( "adjoint_atomic_excitation_energy_grid",
				                        d_adjoint_atomic_excitation_energy_grid );
  ar & boost::serialization::make_nvp( "adjoint_atomic_excitation_energy_gain",
				                        d_adjoint_atomic_excitation_energy_gain );
  ar & boost::serialization::make_nvp( "adjoint_electron_energy_grid",
				                        d_adjoint_electron_energy_grid );
  ar & boost::serialization::make_nvp( "adjoint_cutoff_elastic_cross_section",
                                        d_adjoint_cutoff_elastic_cross_section );
  ar & boost::serialization::make_nvp(
            "adjoint_cutoff_elastic_cross_section_threshold_index",
            d_adjoint_cutoff_elastic_cross_section_threshold_index );
  ar & boost::serialization::make_nvp(
            "adjoint_screened_rutherford_elastic_cross_section",
            d_adjoint_screened_rutherford_elastic_cross_section );
  ar & boost::serialization::make_nvp(
            "adjoint_screened_rutherford_elastic_cross_section_threshold_index",
            d_adjoint_screened_rutherford_elastic_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "adjoint_total_elastic_cross_section",
                                        d_adjoint_total_elastic_cross_section );
  ar & boost::serialization::make_nvp(
            "adjoint_total_elastic_cross_section_threshold_index",
            d_adjoint_total_elastic_cross_section_threshold_index );
  ar & boost::serialization::make_nvp(
            "adjoint_moment_preserving_elastic_cross_section",
            d_adjoint_moment_preserving_elastic_cross_section );
  ar & boost::serialization::make_nvp(
            "adjoint_moment_preserving_elastic_cross_section_threshold_index",
            d_adjoint_moment_preserving_elastic_cross_section_threshold_index );
  ar & boost::serialization::make_nvp(
            "adjoint_electroionization_subshell_cross_section",
            d_adjoint_electroionization_subshell_cross_section );
  ar & boost::serialization::make_nvp(
            "adjoint_electroionization_subshell_cross_section_threshold_index",
            d_adjoint_electroionization_subshell_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "adjoint_bremsstrahlung_cross_section",
                                        d_adjoint_bremsstrahlung_cross_section );
  ar & boost::serialization::make_nvp(
            "adjoint_bremsstrahlung_cross_section_threshold_index",
            d_adjoint_bremsstrahlung_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "adjoint_atomic_excitation_cross_section",
                                        d_adjoint_atomic_excitation_cross_section );
  ar & boost::serialization::make_nvp(
            "adjoint_atomic_excitation_cross_section_threshold_index",
            d_adjoint_atomic_excitation_cross_section_threshold_index );
}

// Load the data from an archive
template<typename Archive>
void AdjointElectronPhotonRelaxationDataContainer::load( Archive& ar,
						  const unsigned version )
{
  // Table Data
  ar & boost::serialization::make_nvp( "atomic_number", d_atomic_number );
  ar & boost::serialization::make_nvp( "min_photon_energy",
                                        d_min_photon_energy );
  ar & boost::serialization::make_nvp( "max_photon_energy",
                                        d_max_photon_energy );
  ar & boost::serialization::make_nvp( "min_electron_energy",
                                        d_min_electron_energy );
  ar & boost::serialization::make_nvp( "max_electron_energy",
                                        d_max_electron_energy );
  ar & boost::serialization::make_nvp( "cutoff_angle_cosine",
                                        d_cutoff_angle_cosine );
  ar & boost::serialization::make_nvp( "number_of_adjoint_moment_preserving_angles",
                                        d_number_of_adjoint_moment_preserving_angles );
  ar & boost::serialization::make_nvp( "grid_convergence_tol",
                                        d_grid_convergence_tol );
  ar & boost::serialization::make_nvp( "grid_absolute_diff_tol",
                                        d_grid_absolute_diff_tol );
  ar & boost::serialization::make_nvp( "grid_distance_tol",
                                        d_grid_distance_tol );

  // Relaxation Data
  ar & boost::serialization::make_nvp( "subshells", d_subshells );
  ar & boost::serialization::make_nvp( "subshell_occupancies",
				       d_subshell_occupancies );
  ar & boost::serialization::make_nvp( "subshell_binding_energies",
				       d_subshell_binding_energies );

  // Photon Data

  // Electron Data
  ar & boost::serialization::make_nvp( "adjoint_angular_energy_grid",
				                        d_adjoint_angular_energy_grid );
  ar & boost::serialization::make_nvp( "adjoint_cutoff_elastic_angles",
                                        d_adjoint_cutoff_elastic_angles );
  ar & boost::serialization::make_nvp( "adjoint_cutoff_elastic_pdf",
                                        d_adjoint_cutoff_elastic_pdf );
  ar & boost::serialization::make_nvp(
            "adjoint_moment_preserving_elastic_discrete_angles",
            d_adjoint_moment_preserving_elastic_discrete_angles );
  ar & boost::serialization::make_nvp(
            "adjoint_moment_preserving_elastic_weights",
            d_adjoint_moment_preserving_elastic_weights );
  ar & boost::serialization::make_nvp( "adjoint_electroionization_energy_grid",
				                        d_adjoint_electroionization_energy_grid );
  ar & boost::serialization::make_nvp( "adjoint_electroionization_recoil_energy",
				                        d_adjoint_electroionization_recoil_energy );
  ar & boost::serialization::make_nvp( "adjoint_electroionization_recoil_pdf",
				                        d_adjoint_electroionization_recoil_pdf );
  ar & boost::serialization::make_nvp( "adjoint_bremsstrahlung_energy_grid",
				                        d_adjoint_bremsstrahlung_energy_grid );
  ar & boost::serialization::make_nvp( "adjoint_bremsstrahlung_photon_energy",
				                        d_adjoint_bremsstrahlung_photon_energy );
  ar & boost::serialization::make_nvp( "adjoint_bremsstrahlung_photon_pdf",
				                        d_adjoint_bremsstrahlung_photon_pdf );
  ar & boost::serialization::make_nvp( "adjoint_atomic_excitation_energy_grid",
				                        d_adjoint_atomic_excitation_energy_grid );
  ar & boost::serialization::make_nvp( "adjoint_atomic_excitation_energy_gain",
				                        d_adjoint_atomic_excitation_energy_gain );
  ar & boost::serialization::make_nvp( "adjoint_electron_energy_grid",
				                        d_adjoint_electron_energy_grid );
  ar & boost::serialization::make_nvp( "adjoint_cutoff_elastic_cross_section",
                                        d_adjoint_cutoff_elastic_cross_section );
  ar & boost::serialization::make_nvp(
            "adjoint_cutoff_elastic_cross_section_threshold_index",
            d_adjoint_cutoff_elastic_cross_section_threshold_index );
  ar & boost::serialization::make_nvp(
            "adjoint_screened_rutherford_elastic_cross_section",
            d_adjoint_screened_rutherford_elastic_cross_section );
  ar & boost::serialization::make_nvp(
            "adjoint_screened_rutherford_elastic_cross_section_threshold_index",
            d_adjoint_screened_rutherford_elastic_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "adjoint_total_elastic_cross_section",
                                        d_adjoint_total_elastic_cross_section );
  ar & boost::serialization::make_nvp(
            "adjoint_total_elastic_cross_section_threshold_index",
            d_adjoint_total_elastic_cross_section_threshold_index );
  ar & boost::serialization::make_nvp(
            "adjoint_moment_preserving_elastic_cross_section",
            d_adjoint_moment_preserving_elastic_cross_section );
  ar & boost::serialization::make_nvp(
            "adjoint_moment_preserving_elastic_cross_section_threshold_index",
            d_adjoint_moment_preserving_elastic_cross_section_threshold_index );
  ar & boost::serialization::make_nvp(
            "adjoint_electroionization_subshell_cross_section",
            d_adjoint_electroionization_subshell_cross_section );
  ar & boost::serialization::make_nvp(
            "adjoint_electroionization_subshell_cross_section_threshold_index",
            d_adjoint_electroionization_subshell_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "adjoint_bremsstrahlung_cross_section",
                                        d_adjoint_bremsstrahlung_cross_section );
  ar & boost::serialization::make_nvp(
            "adjoint_bremsstrahlung_cross_section_threshold_index",
            d_adjoint_bremsstrahlung_cross_section_threshold_index );
  ar & boost::serialization::make_nvp( "adjoint_atomic_excitation_cross_section",
                                        d_adjoint_atomic_excitation_cross_section );
  ar & boost::serialization::make_nvp(
            "adjoint_atomic_excitation_cross_section_threshold_index",
            d_adjoint_atomic_excitation_cross_section_threshold_index );
}

} // end Data namespace

#endif // end DATA_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_AdjointElectronPhotonRelaxationDataContainer_def.hpp
//---------------------------------------------------------------------------//
