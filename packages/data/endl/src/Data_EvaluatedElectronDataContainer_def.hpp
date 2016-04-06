//---------------------------------------------------------------------------//
//!
//! \file   Data_EvaluatedElectronDataContainer_def.hpp
//! \author Luke Kersting
//! \brief  The native eedl container template defs.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_EVALUATED_ELECTRON_DATA_CONTAINER_DEF_HPP
#define DATA_EVALUATED_ELECTRON_DATA_CONTAINER_DEF_HPP

// Boost Includes
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>

namespace Data{

// Save the data to an archive
template<typename Archive>
void EvaluatedElectronDataContainer::save( Archive& ar, 
						  const unsigned version) const
{
  ar & boost::serialization::make_nvp( "atomic_number", d_atomic_number );
  ar & boost::serialization::make_nvp( "subshells", d_subshells );

//---------------------------------------------------------------------------//
// ELASTIC DATA 
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp( "elastic_energy_grid",
				                        d_elastic_energy_grid );
  ar & boost::serialization::make_nvp( "elastic_transport_cross_section",
				                        d_elastic_transport_cross_section );
  ar & boost::serialization::make_nvp( "cutoff_elastic_cross_section", 
                                        d_cutoff_elastic_cross_section );

  ar & boost::serialization::make_nvp(
    "cutoff_elastic_residual_incoming_energy", 
    d_cutoff_elastic_residual_incoming_energy );
  ar & boost::serialization::make_nvp( "cutoff_elastic_residual_energy", 
                                        d_cutoff_elastic_residual_energy );
  ar & boost::serialization::make_nvp(
    "cutoff_elastic_scattered_electron_incoming_energy", 
    d_cutoff_elastic_scattered_electron_incoming_energy );
  ar & boost::serialization::make_nvp(
    "cutoff_elastic_scattered_electron_energy", 
    d_cutoff_elastic_scattered_electron_energy );
  ar & boost::serialization::make_nvp( "cutoff_elastic_angular_energy_grid",
				                        d_cutoff_elastic_angular_energy_grid );

  ar & boost::serialization::make_nvp( "cutoff_elastic_angles", 
                                        d_cutoff_elastic_angles );
  ar & boost::serialization::make_nvp( "cutoff_elastic_pdf", 
                                        d_cutoff_elastic_pdf );
  ar & boost::serialization::make_nvp( "total_elastic_cross_section", 
                                        d_total_elastic_cross_section );
/*
  ar & boost::serialization::make_nvp( 
            "screened_rutherford_elastic_cross_section", 
            d_screened_rutherford_elastic_cross_section );
  ar & boost::serialization::make_nvp( 
            "screened_rutherford_normalization_constant", 
            d_screened_rutherford_normalization_constant );
  ar & boost::serialization::make_nvp( "moliere_screening_constant", 
                                        d_moliere_screening_constant );
*/

//---------------------------------------------------------------------------//
// ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp( 
    "electroionization_subshell_cross_section_energy_grid", 
    d_electroionization_subshell_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( 
    "electroionization_subshell_cross_section", 
    d_electroionization_subshell_cross_section );

  ar & boost::serialization::make_nvp( 
    "electroionization_average_scattered_electron_incoming_energy", 
    d_electroionization_average_scattered_electron_incoming_energy );
  ar & boost::serialization::make_nvp( 
    "electroionization_average_scattered_electron_energy", 
    d_electroionization_average_scattered_electron_energy );
  ar & boost::serialization::make_nvp( 
    "electroionization_average_recoil_electron_incoming_energy", 
    d_electroionization_average_recoil_electron_incoming_energy );
  ar & boost::serialization::make_nvp( 
    "electroionization_average_recoil_electron_energy", 
    d_electroionization_average_recoil_electron_energy );
  ar & boost::serialization::make_nvp( "electroionization_recoil_energy_grid",
				                        d_electroionization_recoil_energy_grid );
  ar & boost::serialization::make_nvp( "electroionization_recoil_energy",
				                        d_electroionization_recoil_energy );
  ar & boost::serialization::make_nvp( "electroionization_recoil_pdf",
				                        d_electroionization_recoil_pdf );

//---------------------------------------------------------------------------//
// BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_cross_section_energy_grid", 
    d_bremsstrahlung_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "bremsstrahlung_cross_section", 
                                        d_bremsstrahlung_cross_section );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_photon_incoming_energy", 
    d_bremsstrahlung_average_photon_incoming_energy );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_photon_energy", 
    d_bremsstrahlung_average_photon_energy );
  ar & boost::serialization::make_nvp( "bremsstrahlung_photon_energy_grid",
				                        d_bremsstrahlung_photon_energy_grid );
  ar & boost::serialization::make_nvp( "bremsstrahlung_photon_energy",
				                        d_bremsstrahlung_photon_energy );
  ar & boost::serialization::make_nvp( "bremsstrahlung_photon_pdf",
				                        d_bremsstrahlung_photon_pdf );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_electron_incoming_energy", 
    d_bremsstrahlung_average_electron_incoming_energy );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_electron_energy", 
    d_bremsstrahlung_average_electron_energy );

//---------------------------------------------------------------------------//
// ATOMIC EXCITAION DATA 
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp(
    "atomic_excitation_energy_grid", 
    d_atomic_excitation_energy_grid );
  ar & boost::serialization::make_nvp( "atomic_excitation_cross_section", 
                                        d_atomic_excitation_cross_section );
  ar & boost::serialization::make_nvp( "atomic_excitation_energy_loss",
				                        d_atomic_excitation_energy_loss );
}
  
// Load the data from an archive
template<typename Archive>
void EvaluatedElectronDataContainer::load( Archive& ar, 
						  const unsigned version )
{
  ar & boost::serialization::make_nvp( "atomic_number", d_atomic_number );
  ar & boost::serialization::make_nvp( "subshells", d_subshells );

//---------------------------------------------------------------------------//
// ELASTIC DATA 
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp( "elastic_energy_grid",
				                        d_elastic_energy_grid );
  ar & boost::serialization::make_nvp( "elastic_transport_cross_section",
				                        d_elastic_transport_cross_section );
  ar & boost::serialization::make_nvp( "cutoff_elastic_cross_section", 
                                        d_cutoff_elastic_cross_section );

  ar & boost::serialization::make_nvp(
    "cutoff_elastic_residual_incoming_energy", 
    d_cutoff_elastic_residual_incoming_energy );
  ar & boost::serialization::make_nvp( "cutoff_elastic_residual_energy", 
                                        d_cutoff_elastic_residual_energy );
  ar & boost::serialization::make_nvp(
    "cutoff_elastic_scattered_electron_incoming_energy", 
    d_cutoff_elastic_scattered_electron_incoming_energy );
  ar & boost::serialization::make_nvp(
    "cutoff_elastic_scattered_electron_energy", 
    d_cutoff_elastic_scattered_electron_energy );
  ar & boost::serialization::make_nvp( "cutoff_elastic_angular_energy_grid",
				                        d_cutoff_elastic_angular_energy_grid );

  ar & boost::serialization::make_nvp( "cutoff_elastic_angles", 
                                        d_cutoff_elastic_angles );
  ar & boost::serialization::make_nvp( "cutoff_elastic_pdf", 
                                        d_cutoff_elastic_pdf );
  ar & boost::serialization::make_nvp( "total_elastic_cross_section", 
                                        d_total_elastic_cross_section );
/*
  ar & boost::serialization::make_nvp( 
            "screened_rutherford_elastic_cross_section", 
            d_screened_rutherford_elastic_cross_section );
  ar & boost::serialization::make_nvp( 
            "screened_rutherford_normalization_constant", 
            d_screened_rutherford_normalization_constant );
  ar & boost::serialization::make_nvp( "moliere_screening_constant", 
                                        d_moliere_screening_constant );
*/

//---------------------------------------------------------------------------//
// ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp( 
    "electroionization_subshell_cross_section_energy_grid", 
    d_electroionization_subshell_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( 
    "electroionization_subshell_cross_section", 
    d_electroionization_subshell_cross_section );

  ar & boost::serialization::make_nvp( 
    "electroionization_average_scattered_electron_incoming_energy", 
    d_electroionization_average_scattered_electron_incoming_energy );
  ar & boost::serialization::make_nvp( 
    "electroionization_average_scattered_electron_energy", 
    d_electroionization_average_scattered_electron_energy );
  ar & boost::serialization::make_nvp( 
    "electroionization_average_recoil_electron_incoming_energy", 
    d_electroionization_average_recoil_electron_incoming_energy );
  ar & boost::serialization::make_nvp( 
    "electroionization_average_recoil_electron_energy", 
    d_electroionization_average_recoil_electron_energy );
  ar & boost::serialization::make_nvp( "electroionization_recoil_energy_grid",
				                        d_electroionization_recoil_energy_grid );
  ar & boost::serialization::make_nvp( "electroionization_recoil_energy",
				                        d_electroionization_recoil_energy );
  ar & boost::serialization::make_nvp( "electroionization_recoil_pdf",
				                        d_electroionization_recoil_pdf );

//---------------------------------------------------------------------------//
// BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_cross_section_energy_grid", 
    d_bremsstrahlung_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "bremsstrahlung_cross_section", 
                                        d_bremsstrahlung_cross_section );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_photon_incoming_energy", 
    d_bremsstrahlung_average_photon_incoming_energy );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_photon_energy", 
    d_bremsstrahlung_average_photon_energy );
  ar & boost::serialization::make_nvp( "bremsstrahlung_photon_energy_grid",
				                        d_bremsstrahlung_photon_energy_grid );
  ar & boost::serialization::make_nvp( "bremsstrahlung_photon_energy",
				                        d_bremsstrahlung_photon_energy );
  ar & boost::serialization::make_nvp( "bremsstrahlung_photon_pdf",
				                        d_bremsstrahlung_photon_pdf );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_electron_incoming_energy", 
    d_bremsstrahlung_average_electron_incoming_energy );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_electron_energy", 
    d_bremsstrahlung_average_electron_energy );

//---------------------------------------------------------------------------//
// ATOMIC EXCITAION DATA 
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp(
    "atomic_excitation_energy_grid", 
    d_atomic_excitation_energy_grid );
  ar & boost::serialization::make_nvp( "atomic_excitation_cross_section", 
                                        d_atomic_excitation_cross_section );
  ar & boost::serialization::make_nvp( "atomic_excitation_energy_loss",
				                        d_atomic_excitation_energy_loss );
}

} // end Data namespace

#endif // end DATA_EVALUATED_ELECTRON_DATA_CONTAINER_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_EvaluatedElectronDataContainer_def.hpp
//---------------------------------------------------------------------------//

