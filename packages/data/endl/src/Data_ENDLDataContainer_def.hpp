//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDLDataContainer_def.hpp
//! \author Luke Kersting
//! \brief  The native eadl container template defs.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ENDL_DATA_CONTAINER_DEF_HPP
#define DATA_ENDL_DATA_CONTAINER_DEF_HPP

// Boost Includes
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>

namespace Data{

// Set the coherent photon cross section interpolation type
template<typename InterpType>
void ENDLDataContainer::setCoherentCrossSectionInterpType()
{
  d_coherent_cross_section_interp_type = InterpType::name();
}

// Set the coherent form factor interpolation type
template<typename InterpType>
void ENDLDataContainer::setCoherentFormFactorInterpType()
{
  d_coherent_form_factor_interp_type = InterpType::name();
}

// Set the coherent imaginary anomalous scattering factor interpolation type
template<typename InterpType>
void ENDLDataContainer::setCoherentImaginaryAnomalousFactorInterpType()
{
  d_coherent_imaginary_anomalous_scattering_factor_interp_type =
    InterpType::name();
}

// Set the coherent real anomalous scattering factor interpolation type
template<typename InterpType>
void ENDLDataContainer::setCoherentRealAnomalousFactorInterpType()
{
  d_coherent_real_anomalous_scattering_factor_interp_type = InterpType::name();
}

// Set the coherent average energy of the scattered photon interpolation type
template<typename InterpType>
void ENDLDataContainer::setCoherentAveragePhotonEnergyInterpType()
{
  d_coherent_average_photon_energy_interp_type = InterpType::name();
}

// Set the incoherent photon cross section interpolation type
template<typename InterpType>
void ENDLDataContainer::setIncoherentCrossSectionInterpType()
{
  d_incoherent_cross_section_interp_type = InterpType::name();
}

// Set the incoherent scattering function interpolation type
template<typename InterpType>
void ENDLDataContainer::setIncoherentScatteringFunctionInterpType()
{
  d_incoherent_scattering_function_interp_type = InterpType::name();
}

// Set the incoherent average energy of the scattered photon
template<typename InterpType>
void ENDLDataContainer::setIncoherentAveragePhotonEnergyInterpType()
{
  d_incoherent_average_photon_energy_interp_type = InterpType::name();
}

// Set the incoherent average energy of the recoil electron interpolation type
template<typename InterpType>
void ENDLDataContainer::setIncoherentAverageElectronEnergyInterpType()
{
  d_incoherent_average_electron_energy_interp_type = InterpType::name();
}

// Set the photoelectric photon cross section interpolation type
template<typename InterpType>
void ENDLDataContainer::setPhotoelectricCrossSectionInterpType()
{
  d_photoelectric_cross_section_interp_type = InterpType::name();
}

// Set the photoelectric average energy of the residual atom interpolation type
template<typename InterpType>
void ENDLDataContainer::setPhotoelectricAverageResidualEnergyInterpType()
{
  d_photoelectric_average_residual_energy_interp_type = InterpType::name();
}

// Set the photoelectric average energy of the secondary photons interpolation type
template<typename InterpType>
void ENDLDataContainer::setPhotoelectricAveragePhotonsEnergyInterpType()
{
  d_photoelectric_secondary_photons_energy_interp_type = InterpType::name();
}

// Set the photoelectric average energy of the secondary electrons interpolation type
template<typename InterpType>
void ENDLDataContainer::setPhotoelectricAverageElectronsEnergyInterpType()
{
  d_photoelectric_secondary_electrons_energy_interp_type = InterpType::name();
}

// Set the photoelectric photon cross section interpolation type for a subshell
template<typename InterpType>
void ENDLDataContainer::setPhotoelectricCrossSectionInterpType( const unsigned subshell )
{
  d_photoelectric_subshell_cross_section_interp_type[subshell] =
    InterpType::name();
}

// Set the photoelectric average energy of the residual atom interpolation type for a subshell
template<typename InterpType>
void ENDLDataContainer::setPhotoelectricAverageResidualEnergyInterpType( const unsigned subshell )
{
  d_photoelectric_subshell_average_residual_energy_interp_type[subshell] =
    InterpType::name();
}

// Set the photoelectric average energy of the secondary photons interpolation type for a subshell
template<typename InterpType>
void ENDLDataContainer::setPhotoelectricAveragePhotonsEnergyInterpType( const unsigned subshell )
{
  d_photoelectric_subshell_secondary_photons_energy_interp_type[subshell] =
    InterpType::name();
}

// Set the photoelectric average energy of the secondary electrons interpolation type for a subshell
template<typename InterpType>
void ENDLDataContainer::setPhotoelectricAverageElectronsEnergyInterpType( const unsigned subshell )
{
  d_photoelectric_subshell_secondary_electrons_energy_interp_type[subshell] =
    InterpType::name();
}

// Set the pair production photon cross section interpolation type
template<typename InterpType>
void ENDLDataContainer::setPairProductionCrossSectionInterpType()
{
  d_pair_production_cross_section_interp_type = InterpType::name();
}

// Set the pair production average energy of the secondary positron interpolation type
template<typename InterpType>
void ENDLDataContainer::setPairProductionAveragePositronEnergyInterpType()
{
  d_pair_production_average_positron_energy_interp_type = InterpType::name();
}

// Set the pair production average energy of the secondary electron interpolation type
template<typename InterpType>
void ENDLDataContainer::setPairProductionAverageElectronEnergyInterpType()
{
  d_pair_production_average_electron_energy_interp_type = InterpType::name();
}

// Set the triplet production photon cross section interpolation type
template<typename InterpType>
void ENDLDataContainer::setTripletProductionCrossSectionInterpType()
{
  d_triplet_production_cross_section_interp_type = InterpType::name();
}

// Set the triplet production average energy of the secondary positron interpolation type
template<typename InterpType>
void ENDLDataContainer::setTripletProductionAveragePositronEnergyInterpType()
{
  d_triplet_production_average_positron_energy_interp_type =
    InterpType::name();
}

// Set the triplet production average energy of the secondary electron interpolation type
template<typename InterpType>
void ENDLDataContainer::setTripletProductionAverageElectronEnergyInterpType()
{
  d_triplet_production_average_electron_energy_interp_type =
    InterpType::name();
}

// Set the electron elastic transport cross section interpolation type
template<typename InterpType>
void ENDLDataContainer::setElasticTransportCrossSectionInterpType()
{
  d_elastic_transport_cross_section_interp_type = InterpType::name();
}

// Set the electron elastic cross section below mu = 0.999999 interpolation type
template<typename InterpType>
void ENDLDataContainer::setCutoffElasticCrossSectionInterpType()
{
  d_cutoff_elastic_cross_section_interp_type = InterpType::name();
}

// Set the cutoff elastic average energy to the residual atom interpolation type
template<typename InterpType>
void ENDLDataContainer::setCutoffElasticResidualEnergyInterpType()
{
  d_cutoff_elastic_residual_energy_interp_type = InterpType::name();
}

// Set the cutoff elastic average energy of the scattered electron
template<typename InterpType>
void ENDLDataContainer::setCutoffElasticScatteredElectronEnergyInterpType()
{
  d_cutoff_elastic_scattered_electron_energy_interp_type = InterpType::name();
}

// Set the elastic scattering pdf interpolation type
template<typename InterpType>
void ENDLDataContainer::setCutoffElasticPDFInterpType()
{
  d_cutoff_elastic_pdf_interp_type = InterpType::name();
}

// Set the total elastic electron cross section interpolation type
template<typename InterpType>
void ENDLDataContainer::setTotalElasticCrossSectionInterpType()
{
  d_total_elastic_cross_section_interp_type = InterpType::name();
}

// Set the electroionization electron cross section interpolation type for a subshell
template<typename InterpType>
void ENDLDataContainer::setElectroionizationCrossSectionInterpType( const unsigned subshell )
{
  d_electroionization_subshell_cross_section_interp_type[subshell] =
    InterpType::name();
}

// Set the electroionization average scattered electron energy interpolation type for a subshell
template<typename InterpType>
void ENDLDataContainer::setElectroionizationAverageScatteredElectronEnergyInterpType( const unsigned subshell )
{
  d_electroionization_average_scattered_electron_energy_interp_type[subshell] =
    InterpType::name();
}

// Set the electroionization average recoil electron energy interp type for a subshell
template<typename InterpType>
void ENDLDataContainer::setElectroionizationAverageRecoilElectronEnergyInterpType( const unsigned subshell )
{
  d_electroionization_average_recoil_electron_energy_interp_type[subshell] =
    InterpType::name();
}

// Set electroionization recoil energy pdf interpolation type for all incident energies in a subshell
template<typename InterpType>
void ENDLDataContainer::setElectroionizationRecoilPDFInterpType( const unsigned subshell )
{
  d_electroionization_recoil_pdf_interp_type[subshell] = InterpType::name();
}

// Set the bremsstrahlung electron cross section interpolation type
template<typename InterpType>
void ENDLDataContainer::setBremsstrahlungCrossSectionInterpType()
{
  d_bremsstrahlung_cross_section_interp_type = InterpType::name();
}

// Set the bremsstrahlung average energy of the secondary photon interpolation type
template<typename InterpType>
void ENDLDataContainer::setBremsstrahlungAveragePhotonEnergyInterpType()
{
  d_bremsstrahlung_average_photon_energy_interp_type = InterpType::name();
}

// Set all the bremsstrahlung photon energy pdf data interpolation type
template<typename InterpType>
void ENDLDataContainer::setBremsstrahlungPhotonPDFInterpType()
{
  d_bremsstrahlung_photon_pdf_interp_type = InterpType::name();
}

// Set the bremsstrahlung average energy of the secondary electron interpolation type
template<typename InterpType>
void ENDLDataContainer::setBremsstrahlungAverageElectronEnergyInterpType()
{
  d_bremsstrahlung_average_electron_energy_interp_type = InterpType::name();
}

// Set the atomic excitation electron cross section interpolation type
template<typename InterpType>
void ENDLDataContainer::setAtomicExcitationCrossSectionInterpType()
{
  d_atomic_excitation_cross_section_interp_type = InterpType::name();
}

// Set the atomic excitation average energy loss interpolation type
template<typename InterpType>
void ENDLDataContainer::setAtomicExcitationEnergyLossInterpType()
{
  d_atomic_excitation_energy_loss_interp_type = InterpType::name();
}

// Save the data to an archive
template<typename Archive>
void ENDLDataContainer::save( Archive& ar,
                              const unsigned version) const
{
  ar & boost::serialization::make_nvp( "atomic_number", d_atomic_number );
  ar & boost::serialization::make_nvp( "atomic_weight", d_atomic_weight );

//---------------------------------------------------------------------------//
// RELAXATION DATA
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp( "subshells", d_subshells );
  ar & boost::serialization::make_nvp( "subshell_occupancies",
        d_subshell_occupancies );
  ar & boost::serialization::make_nvp( "subshell_binding_energies",
        d_subshell_binding_energies );
  ar & boost::serialization::make_nvp( "subshell_kinetic_energies",
        d_subshell_kinetic_energies );
  ar & boost::serialization::make_nvp( "subshell_average_radii",
        d_subshell_average_radii );
  ar & boost::serialization::make_nvp( "subshell_radiative_levels",
        d_subshell_radiative_levels );
  ar & boost::serialization::make_nvp( "subshell_non_radiative_levels",
        d_subshell_non_radiative_levels );
  ar & boost::serialization::make_nvp( "subshell_local_depositions",
        d_subshell_local_depositions );
  ar & boost::serialization::make_nvp( "subshell_average_photon_numbers",
        d_subshell_average_photon_numbers );
  ar & boost::serialization::make_nvp( "subshell_average_photon_energies",
        d_subshell_average_photon_energies );
  ar & boost::serialization::make_nvp( "subshell_average_electron_numbers",
        d_subshell_average_electron_numbers );
  ar & boost::serialization::make_nvp( "subshell_average_electron_energies",
        d_subshell_average_electron_energies );
  ar & boost::serialization::make_nvp( "radiative_transition_probabilities",
        d_radiative_transition_probabilities );
  ar & boost::serialization::make_nvp( "radiative_transition_energies",
        d_radiative_transition_energies );
  ar & boost::serialization::make_nvp( "non_radiative_transition_probabilities",
        d_non_radiative_transition_probabilities );
  ar & boost::serialization::make_nvp( "non_radiative_transition_energies",
        d_non_radiative_transition_energies );

//---------------------------------------------------------------------------//
// THE COHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  ar & boost::serialization::make_nvp( "coherent_cross_section_energy_grid",
        d_coherent_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "coherent_cross_section",
        d_coherent_cross_section );
  ar & boost::serialization::make_nvp( "coherent_cross_section_interp_type",
        d_coherent_cross_section_interp_type );
  ar & boost::serialization::make_nvp( "coherent_form_factor_argument",
        d_coherent_form_factor_argument );
  ar & boost::serialization::make_nvp( "coherent_form_factor",
        d_coherent_form_factor );
  ar & boost::serialization::make_nvp( "coherent_form_factor_interp_type",
        d_coherent_form_factor_interp_type );
  ar & boost::serialization::make_nvp(
        "coherent_imaginary_anomalous_scattering_factor_incident_energy",
        d_coherent_imaginary_anomalous_scattering_factor_incident_energy );
  ar & boost::serialization::make_nvp(
        "coherent_imaginary_anomalous_scattering_factor",
        d_coherent_imaginary_anomalous_scattering_factor );
  ar & boost::serialization::make_nvp(
        "coherent_imaginary_anomalous_scattering_factor_interp_type",
        d_coherent_imaginary_anomalous_scattering_factor_interp_type );
  ar & boost::serialization::make_nvp(
        "coherent_real_anomalous_scattering_factor_incident_energy",
        d_coherent_real_anomalous_scattering_factor_incident_energy );
  ar & boost::serialization::make_nvp(
        "coherent_real_anomalous_scattering_factor",
        d_coherent_real_anomalous_scattering_factor );
  ar & boost::serialization::make_nvp(
        "coherent_real_anomalous_scattering_factor_interp_type",
        d_coherent_real_anomalous_scattering_factor_interp_type ); 
  ar & boost::serialization::make_nvp(
        "coherent_average_photon_incident_energy",
        d_coherent_average_photon_incident_energy );
  ar & boost::serialization::make_nvp( "coherent_average_photon_energy",
        d_coherent_average_photon_energy );
  ar & boost::serialization::make_nvp(
        "coherent_average_photon_energy_interp_type",
        d_coherent_average_photon_energy_interp_type );

//---------------------------------------------------------------------------//
// THE INCOHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  ar & boost::serialization::make_nvp( "incoherent_cross_section_energy_grid",
        d_incoherent_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "incoherent_cross_section",
        d_incoherent_cross_section );
  ar & boost::serialization::make_nvp( "incoherent_cross_section_interp_type",
        d_incoherent_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
        "incoherent_scattering_function_argument",
        d_incoherent_scattering_function_argument );
  ar & boost::serialization::make_nvp( "incoherent_scattering_function",
        d_incoherent_scattering_function );
  ar & boost::serialization::make_nvp(
        "incoherent_scattering_function_interp_type",
        d_incoherent_scattering_function_interp_type );
  ar & boost::serialization::make_nvp(
        "incoherent_average_photon_incident_energy",
        d_incoherent_average_photon_incident_energy );
  ar & boost::serialization::make_nvp( "incoherent_average_photon_energy",
        d_incoherent_average_photon_energy );
  ar & boost::serialization::make_nvp(
        "incoherent_average_photon_energy_interp_type",
        d_incoherent_average_photon_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "incoherent_average_electron_incident_energy",
        d_incoherent_average_electron_incident_energy );
  ar & boost::serialization::make_nvp( "incoherent_average_electron_energy",
        d_incoherent_average_electron_energy );
  ar & boost::serialization::make_nvp(
        "incoherent_average_electron_energy_interp_type",
        d_incoherent_average_electron_energy_interp_type );

//---------------------------------------------------------------------------//
// THE PHOTOELECTRIC PHOTON DATA
//---------------------------------------------------------------------------//

  ar & boost::serialization::make_nvp(
        "photoelectric_cross_section_energy_grid",
        d_photoelectric_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "photoelectric_cross_section",
        d_photoelectric_cross_section );
  ar & boost::serialization::make_nvp(
        "photoelectric_cross_section_interp_type",
        d_photoelectric_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
        "photoelectric_average_residual_incident_energy",
        d_photoelectric_average_residual_incident_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_average_residual_energy",
        d_photoelectric_average_residual_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_average_residual_energy_interp_type",
        d_photoelectric_average_residual_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "photoelectric_secondary_photons_incident_energy",
        d_photoelectric_secondary_photons_incident_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_secondary_photons_energy",
        d_photoelectric_secondary_photons_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_secondary_photons_energy_interp_type",
        d_photoelectric_secondary_photons_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "photoelectric_secondary_electrons_incident_energy",
        d_photoelectric_secondary_electrons_incident_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_secondary_electrons_energy",
        d_photoelectric_secondary_electrons_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_secondary_electrons_energy_interp_type",
        d_photoelectric_secondary_electrons_energy_interp_type );

//---------------------------------------------------------------------------//
// THE PHOTOELECTRIC PHOTON DATA BY SUBSHELL
//---------------------------------------------------------------------------//

  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_cross_section_energy_grid",
        d_photoelectric_subshell_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "photoelectric_subshell_cross_section",
        d_photoelectric_subshell_cross_section );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_cross_section_interp_type",
        d_photoelectric_subshell_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_average_residual_incident_energy",
        d_photoelectric_subshell_average_residual_incident_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_average_residual_energy",
        d_photoelectric_subshell_average_residual_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_average_residual_energy_interp_type",
        d_photoelectric_subshell_average_residual_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_secondary_photons_incident_energy",
        d_photoelectric_subshell_secondary_photons_incident_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_secondary_photons_energy",
        d_photoelectric_subshell_secondary_photons_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_secondary_photons_energy_interp_type",
        d_photoelectric_subshell_secondary_photons_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_secondary_electrons_incident_energy",
        d_photoelectric_subshell_secondary_electrons_incident_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_secondary_electrons_energy",
        d_photoelectric_subshell_secondary_electrons_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_secondary_electrons_energy_interp_type",
        d_photoelectric_subshell_secondary_electrons_energy_interp_type );

//---------------------------------------------------------------------------//
// THE PAIR PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  ar & boost::serialization::make_nvp(
        "pair_production_cross_section_energy_grid",
        d_pair_production_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "pair_production_cross_section",
        d_pair_production_cross_section );
  ar & boost::serialization::make_nvp(
        "pair_production_cross_section_interp_type",
        d_pair_production_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
        "pair_production_average_positron_incident_energy",
        d_pair_production_average_positron_incident_energy );
  ar & boost::serialization::make_nvp(
        "pair_production_average_positron_energy",
        d_pair_production_average_positron_energy );
  ar & boost::serialization::make_nvp(
        "pair_production_average_positron_energy_interp_type",
        d_pair_production_average_positron_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "pair_production_average_electron_incident_energy",
        d_pair_production_average_electron_incident_energy );
  ar & boost::serialization::make_nvp(
        "pair_production_average_electron_energy",
        d_pair_production_average_electron_energy );
  ar & boost::serialization::make_nvp(
        "pair_production_average_electron_energy_interp_type",
        d_pair_production_average_electron_energy_interp_type );

//---------------------------------------------------------------------------//
// THE TRIPLET PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  ar & boost::serialization::make_nvp(
        "triplet_production_cross_section_energy_grid",
        d_triplet_production_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "triplet_production_cross_section",
        d_triplet_production_cross_section );
  ar & boost::serialization::make_nvp(
        "triplet_production_cross_section_interp_type",
        d_triplet_production_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
        "triplet_production_average_positron_incident_energy",
        d_triplet_production_average_positron_incident_energy );
  ar & boost::serialization::make_nvp(
        "triplet_production_average_positron_energy",
        d_triplet_production_average_positron_energy );
  ar & boost::serialization::make_nvp(
        "triplet_production_average_positron_energy_interp_type",
        d_triplet_production_average_positron_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "triplet_production_average_electron_incident_energy",
        d_triplet_production_average_electron_incident_energy );
  ar & boost::serialization::make_nvp(
        "triplet_production_average_electron_energy",
        d_triplet_production_average_electron_energy );
  ar & boost::serialization::make_nvp(
        "triplet_production_average_electron_energy_interp_type",
        d_triplet_production_average_electron_energy_interp_type );

//---------------------------------------------------------------------------//
// ELASTIC DATA
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp( "elastic_energy_grid",
	d_elastic_energy_grid );
  ar & boost::serialization::make_nvp( "elastic_transport_cross_section",
        d_elastic_transport_cross_section );
  ar & boost::serialization::make_nvp(
        "elastic_transport_cross_section_interp_type",
        d_elastic_transport_cross_section_interp_type );
  ar & boost::serialization::make_nvp( "cutoff_elastic_cross_section",
        d_cutoff_elastic_cross_section );
  ar & boost::serialization::make_nvp(
        "cutoff_elastic_cross_section_interp_type",
        d_cutoff_elastic_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
        "cutoff_elastic_residual_incident_energy",
        d_cutoff_elastic_residual_incident_energy );
  ar & boost::serialization::make_nvp( "cutoff_elastic_residual_energy",
        d_cutoff_elastic_residual_energy );
  ar & boost::serialization::make_nvp(
        "cutoff_elastic_residual_energy_interp_type",
        d_cutoff_elastic_residual_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "cutoff_elastic_scattered_electron_incident_energy",
        d_cutoff_elastic_scattered_electron_incident_energy );
  ar & boost::serialization::make_nvp(
        "cutoff_elastic_scattered_electron_energy",
        d_cutoff_elastic_scattered_electron_energy );
  ar & boost::serialization::make_nvp(
        "cutoff_elastic_scattered_electron_energy_interp_type",
        d_cutoff_elastic_scattered_electron_energy_interp_type );
  ar & boost::serialization::make_nvp( "cutoff_elastic_angular_energy_grid",
	d_cutoff_elastic_angular_energy_grid );
  ar & boost::serialization::make_nvp( "cutoff_elastic_angles",
        d_cutoff_elastic_angles );
  ar & boost::serialization::make_nvp( "cutoff_elastic_pdf",
        d_cutoff_elastic_pdf );
  ar & boost::serialization::make_nvp( "cutoff_elastic_pdf_interp_type",
        d_cutoff_elastic_pdf_interp_type );
  ar & boost::serialization::make_nvp( "total_elastic_cross_section",
        d_total_elastic_cross_section );
  ar & boost::serialization::make_nvp(
        "total_elastic_cross_section_interp_type",
        d_total_elastic_cross_section_interp_type );
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
    "electroionization_subshell_cross_section_interp_type",
    d_electroionization_subshell_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
    "electroionization_average_scattered_electron_incident_energy",
    d_electroionization_average_scattered_electron_incident_energy );
  ar & boost::serialization::make_nvp(
    "electroionization_average_scattered_electron_energy",
    d_electroionization_average_scattered_electron_energy );
  ar & boost::serialization::make_nvp(
    "electroionization_average_scattered_electron_energy_interp_type",
    d_electroionization_average_scattered_electron_energy_interp_type );
  ar & boost::serialization::make_nvp(
    "electroionization_average_recoil_electron_incident_energy",
    d_electroionization_average_recoil_electron_incident_energy );
  ar & boost::serialization::make_nvp(
    "electroionization_average_recoil_electron_energy",
    d_electroionization_average_recoil_electron_energy );
  ar & boost::serialization::make_nvp(
    "electroionization_average_recoil_electron_energy_interp_type",
    d_electroionization_average_recoil_electron_energy_interp_type );
  ar & boost::serialization::make_nvp( "electroionization_recoil_energy_grid",
    d_electroionization_recoil_energy_grid );
  ar & boost::serialization::make_nvp( "electroionization_recoil_energy",
    d_electroionization_recoil_energy );
  ar & boost::serialization::make_nvp( "electroionization_recoil_pdf",
    d_electroionization_recoil_pdf );
  ar & boost::serialization::make_nvp(
    "electroionization_recoil_pdf_interp_type",
    d_electroionization_recoil_pdf_interp_type );

//---------------------------------------------------------------------------//
// BREMSSTRAHLUNG DATA
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_cross_section_energy_grid",
    d_bremsstrahlung_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "bremsstrahlung_cross_section",
                                        d_bremsstrahlung_cross_section );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_cross_section_interp_type",
    d_bremsstrahlung_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_photon_incident_energy",
    d_bremsstrahlung_average_photon_incident_energy );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_photon_energy",
    d_bremsstrahlung_average_photon_energy );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_photon_energy_interp_type",
    d_bremsstrahlung_average_photon_energy_interp_type );
  ar & boost::serialization::make_nvp( "bremsstrahlung_photon_energy_grid",
                                       d_bremsstrahlung_photon_energy_grid );
  ar & boost::serialization::make_nvp( "bremsstrahlung_photon_energy",
                                       d_bremsstrahlung_photon_energy );
  ar & boost::serialization::make_nvp( "bremsstrahlung_photon_pdf",
                                       d_bremsstrahlung_photon_pdf );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_photon_pdf_interp_type",
    d_bremsstrahlung_photon_pdf_interp_type );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_electron_incident_energy",
    d_bremsstrahlung_average_electron_incident_energy );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_electron_energy",
    d_bremsstrahlung_average_electron_energy );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_electron_energy_interp_type",
    d_bremsstrahlung_average_electron_energy_interp_type );

//---------------------------------------------------------------------------//
// ATOMIC EXCITATION DATA
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp(
    "atomic_excitation_energy_grid",
    d_atomic_excitation_energy_grid );
  ar & boost::serialization::make_nvp( "atomic_excitation_cross_section",
                                        d_atomic_excitation_cross_section );
  ar & boost::serialization::make_nvp(
    "atomic_excitation_cross_section_interp_type",
    d_atomic_excitation_cross_section_interp_type );
  ar & boost::serialization::make_nvp( "atomic_excitation_energy_loss",
                                       d_atomic_excitation_energy_loss );
  ar & boost::serialization::make_nvp(
    "atomic_excitation_energy_loss_interp_type",
    d_atomic_excitation_energy_loss_interp_type );
}

// Load the data from an archive
template<typename Archive>
void ENDLDataContainer::load( Archive& ar,
                              const unsigned version )
{
  ar & boost::serialization::make_nvp( "atomic_number", d_atomic_number );
  ar & boost::serialization::make_nvp( "atomic_weight", d_atomic_weight );

//---------------------------------------------------------------------------//
// RELAXATION DATA
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp( "subshells", d_subshells );
  ar & boost::serialization::make_nvp( "subshell_occupancies",
        d_subshell_occupancies );
  ar & boost::serialization::make_nvp( "subshell_binding_energies",
        d_subshell_binding_energies );
  ar & boost::serialization::make_nvp( "subshell_kinetic_energies",
        d_subshell_kinetic_energies );
  ar & boost::serialization::make_nvp( "subshell_average_radii",
        d_subshell_average_radii );
  ar & boost::serialization::make_nvp( "subshell_radiative_levels",
        d_subshell_radiative_levels );
  ar & boost::serialization::make_nvp( "subshell_non_radiative_levels",
        d_subshell_non_radiative_levels );
  ar & boost::serialization::make_nvp( "subshell_local_depositions",
        d_subshell_local_depositions );
  ar & boost::serialization::make_nvp( "subshell_average_photon_numbers",
        d_subshell_average_photon_numbers );
  ar & boost::serialization::make_nvp( "subshell_average_photon_energies",
        d_subshell_average_photon_energies );
  ar & boost::serialization::make_nvp( "subshell_average_electron_numbers",
        d_subshell_average_electron_numbers );
  ar & boost::serialization::make_nvp( "subshell_average_electron_energies",
        d_subshell_average_electron_energies );
  ar & boost::serialization::make_nvp( "radiative_transition_probabilities",
        d_radiative_transition_probabilities );
  ar & boost::serialization::make_nvp( "radiative_transition_energies",
        d_radiative_transition_energies );
  ar & boost::serialization::make_nvp( "non_radiative_transition_probabilities",
        d_non_radiative_transition_probabilities );
  ar & boost::serialization::make_nvp( "non_radiative_transition_energies",
        d_non_radiative_transition_energies );

//---------------------------------------------------------------------------//
// THE COHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  ar & boost::serialization::make_nvp( "coherent_cross_section_energy_grid",
        d_coherent_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "coherent_cross_section",
        d_coherent_cross_section );
  ar & boost::serialization::make_nvp( "coherent_cross_section_interp_type",
        d_coherent_cross_section_interp_type );
  ar & boost::serialization::make_nvp( "coherent_form_factor_argument",
        d_coherent_form_factor_argument );
  ar & boost::serialization::make_nvp( "coherent_form_factor",
        d_coherent_form_factor );
  ar & boost::serialization::make_nvp( "coherent_form_factor_interp_type",
        d_coherent_form_factor_interp_type );
  ar & boost::serialization::make_nvp(
        "coherent_imaginary_anomalous_scattering_factor_incident_energy",
        d_coherent_imaginary_anomalous_scattering_factor_incident_energy );
  ar & boost::serialization::make_nvp(
        "coherent_imaginary_anomalous_scattering_factor",
        d_coherent_imaginary_anomalous_scattering_factor );
  ar & boost::serialization::make_nvp(
        "coherent_imaginary_anomalous_scattering_factor_interp_type",
        d_coherent_imaginary_anomalous_scattering_factor_interp_type );
  ar & boost::serialization::make_nvp(
        "coherent_real_anomalous_scattering_factor_incident_energy",
        d_coherent_real_anomalous_scattering_factor_incident_energy );
  ar & boost::serialization::make_nvp(
        "coherent_real_anomalous_scattering_factor",
        d_coherent_real_anomalous_scattering_factor );
  ar & boost::serialization::make_nvp(
        "coherent_real_anomalous_scattering_factor_interp_type",
        d_coherent_real_anomalous_scattering_factor_interp_type ); 
  ar & boost::serialization::make_nvp(
        "coherent_average_photon_incident_energy",
        d_coherent_average_photon_incident_energy );
  ar & boost::serialization::make_nvp( "coherent_average_photon_energy",
        d_coherent_average_photon_energy );
  ar & boost::serialization::make_nvp(
        "coherent_average_photon_energy_interp_type",
        d_coherent_average_photon_energy_interp_type );

//---------------------------------------------------------------------------//
// THE INCOHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  ar & boost::serialization::make_nvp( "incoherent_cross_section_energy_grid",
        d_incoherent_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "incoherent_cross_section",
        d_incoherent_cross_section );
  ar & boost::serialization::make_nvp( "incoherent_cross_section_interp_type",
        d_incoherent_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
        "incoherent_scattering_function_argument",
        d_incoherent_scattering_function_argument );
  ar & boost::serialization::make_nvp( "incoherent_scattering_function",
        d_incoherent_scattering_function );
  ar & boost::serialization::make_nvp(
        "incoherent_scattering_function_interp_type",
        d_incoherent_scattering_function_interp_type );
  ar & boost::serialization::make_nvp(
        "incoherent_average_photon_incident_energy",
        d_incoherent_average_photon_incident_energy );
  ar & boost::serialization::make_nvp( "incoherent_average_photon_energy",
        d_incoherent_average_photon_energy );
  ar & boost::serialization::make_nvp(
        "incoherent_average_photon_energy_interp_type",
        d_incoherent_average_photon_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "incoherent_average_electron_incident_energy",
        d_incoherent_average_electron_incident_energy );
  ar & boost::serialization::make_nvp( "incoherent_average_electron_energy",
        d_incoherent_average_electron_energy );
  ar & boost::serialization::make_nvp(
        "incoherent_average_electron_energy_interp_type",
        d_incoherent_average_electron_energy_interp_type );

//---------------------------------------------------------------------------//
// THE PHOTOELECTRIC PHOTON DATA
//---------------------------------------------------------------------------//

  ar & boost::serialization::make_nvp(
        "photoelectric_cross_section_energy_grid",
        d_photoelectric_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "photoelectric_cross_section",
        d_photoelectric_cross_section );
  ar & boost::serialization::make_nvp(
        "photoelectric_cross_section_interp_type",
        d_photoelectric_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
        "photoelectric_average_residual_incident_energy",
        d_photoelectric_average_residual_incident_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_average_residual_energy",
        d_photoelectric_average_residual_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_average_residual_energy_interp_type",
        d_photoelectric_average_residual_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "photoelectric_secondary_photons_incident_energy",
        d_photoelectric_secondary_photons_incident_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_secondary_photons_energy",
        d_photoelectric_secondary_photons_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_secondary_photons_energy_interp_type",
        d_photoelectric_secondary_photons_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "photoelectric_secondary_electrons_incident_energy",
        d_photoelectric_secondary_electrons_incident_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_secondary_electrons_energy",
        d_photoelectric_secondary_electrons_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_secondary_electrons_energy_interp_type",
        d_photoelectric_secondary_electrons_energy_interp_type );

//---------------------------------------------------------------------------//
// THE PHOTOELECTRIC PHOTON DATA BY SUBSHELL
//---------------------------------------------------------------------------//

  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_cross_section_energy_grid",
        d_photoelectric_subshell_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "photoelectric_subshell_cross_section",
        d_photoelectric_subshell_cross_section );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_cross_section_interp_type",
        d_photoelectric_subshell_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_average_residual_incident_energy",
        d_photoelectric_subshell_average_residual_incident_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_average_residual_energy",
        d_photoelectric_subshell_average_residual_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_average_residual_energy_interp_type",
        d_photoelectric_subshell_average_residual_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_secondary_photons_incident_energy",
        d_photoelectric_subshell_secondary_photons_incident_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_secondary_photons_energy",
        d_photoelectric_subshell_secondary_photons_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_secondary_photons_energy_interp_type",
        d_photoelectric_subshell_secondary_photons_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_secondary_electrons_incident_energy",
        d_photoelectric_subshell_secondary_electrons_incident_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_secondary_electrons_energy",
        d_photoelectric_subshell_secondary_electrons_energy );
  ar & boost::serialization::make_nvp(
        "photoelectric_subshell_secondary_electrons_energy_interp_type",
        d_photoelectric_subshell_secondary_electrons_energy_interp_type );

//---------------------------------------------------------------------------//
// THE PAIR PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  ar & boost::serialization::make_nvp(
        "pair_production_cross_section_energy_grid",
        d_pair_production_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "pair_production_cross_section",
        d_pair_production_cross_section );
  ar & boost::serialization::make_nvp(
        "pair_production_cross_section_interp_type",
        d_pair_production_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
        "pair_production_average_positron_incident_energy",
        d_pair_production_average_positron_incident_energy );
  ar & boost::serialization::make_nvp(
        "pair_production_average_positron_energy",
        d_pair_production_average_positron_energy );
  ar & boost::serialization::make_nvp(
        "pair_production_average_positron_energy_interp_type",
        d_pair_production_average_positron_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "pair_production_average_electron_incident_energy",
        d_pair_production_average_electron_incident_energy );
  ar & boost::serialization::make_nvp(
        "pair_production_average_electron_energy",
        d_pair_production_average_electron_energy );
  ar & boost::serialization::make_nvp(
        "pair_production_average_electron_energy_interp_type",
        d_pair_production_average_electron_energy_interp_type );

//---------------------------------------------------------------------------//
// THE TRIPLET PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  ar & boost::serialization::make_nvp(
        "triplet_production_cross_section_energy_grid",
        d_triplet_production_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "triplet_production_cross_section",
        d_triplet_production_cross_section );
  ar & boost::serialization::make_nvp(
        "triplet_production_cross_section_interp_type",
        d_triplet_production_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
        "triplet_production_average_positron_incident_energy",
        d_triplet_production_average_positron_incident_energy );
  ar & boost::serialization::make_nvp(
        "triplet_production_average_positron_energy",
        d_triplet_production_average_positron_energy );
  ar & boost::serialization::make_nvp(
        "triplet_production_average_positron_energy_interp_type",
        d_triplet_production_average_positron_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "triplet_production_average_electron_incident_energy",
        d_triplet_production_average_electron_incident_energy );
  ar & boost::serialization::make_nvp(
        "triplet_production_average_electron_energy",
        d_triplet_production_average_electron_energy );
  ar & boost::serialization::make_nvp(
        "triplet_production_average_electron_energy_interp_type",
        d_triplet_production_average_electron_energy_interp_type );

//---------------------------------------------------------------------------//
// ELASTIC DATA
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp( "elastic_energy_grid",
	d_elastic_energy_grid );
  ar & boost::serialization::make_nvp( "elastic_transport_cross_section",
        d_elastic_transport_cross_section );
  ar & boost::serialization::make_nvp(
        "elastic_transport_cross_section_interp_type",
        d_elastic_transport_cross_section_interp_type );
  ar & boost::serialization::make_nvp( "cutoff_elastic_cross_section",
        d_cutoff_elastic_cross_section );
  ar & boost::serialization::make_nvp(
        "cutoff_elastic_cross_section_interp_type",
        d_cutoff_elastic_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
        "cutoff_elastic_residual_incident_energy",
        d_cutoff_elastic_residual_incident_energy );
  ar & boost::serialization::make_nvp( "cutoff_elastic_residual_energy",
        d_cutoff_elastic_residual_energy );
  ar & boost::serialization::make_nvp(
        "cutoff_elastic_residual_energy_interp_type",
        d_cutoff_elastic_residual_energy_interp_type );
  ar & boost::serialization::make_nvp(
        "cutoff_elastic_scattered_electron_incident_energy",
        d_cutoff_elastic_scattered_electron_incident_energy );
  ar & boost::serialization::make_nvp(
        "cutoff_elastic_scattered_electron_energy",
        d_cutoff_elastic_scattered_electron_energy );
  ar & boost::serialization::make_nvp(
        "cutoff_elastic_scattered_electron_energy_interp_type",
        d_cutoff_elastic_scattered_electron_energy_interp_type );
  ar & boost::serialization::make_nvp( "cutoff_elastic_angular_energy_grid",
	d_cutoff_elastic_angular_energy_grid );
  ar & boost::serialization::make_nvp( "cutoff_elastic_angles",
        d_cutoff_elastic_angles );
  ar & boost::serialization::make_nvp( "cutoff_elastic_pdf",
        d_cutoff_elastic_pdf );
  ar & boost::serialization::make_nvp( "cutoff_elastic_pdf_interp_type",
        d_cutoff_elastic_pdf_interp_type );
  ar & boost::serialization::make_nvp( "total_elastic_cross_section",
        d_total_elastic_cross_section );
  ar & boost::serialization::make_nvp(
        "total_elastic_cross_section_interp_type",
        d_total_elastic_cross_section_interp_type );
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
    "electroionization_subshell_cross_section_interp_type",
    d_electroionization_subshell_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
    "electroionization_average_scattered_electron_incident_energy",
    d_electroionization_average_scattered_electron_incident_energy );
  ar & boost::serialization::make_nvp(
    "electroionization_average_scattered_electron_energy",
    d_electroionization_average_scattered_electron_energy );
  ar & boost::serialization::make_nvp(
    "electroionization_average_scattered_electron_energy_interp_type",
    d_electroionization_average_scattered_electron_energy_interp_type );
  ar & boost::serialization::make_nvp(
    "electroionization_average_recoil_electron_incident_energy",
    d_electroionization_average_recoil_electron_incident_energy );
  ar & boost::serialization::make_nvp(
    "electroionization_average_recoil_electron_energy",
    d_electroionization_average_recoil_electron_energy );
  ar & boost::serialization::make_nvp(
    "electroionization_average_recoil_electron_energy_interp_type",
    d_electroionization_average_recoil_electron_energy_interp_type );
  ar & boost::serialization::make_nvp( "electroionization_recoil_energy_grid",
    d_electroionization_recoil_energy_grid );
  ar & boost::serialization::make_nvp( "electroionization_recoil_energy",
    d_electroionization_recoil_energy );
  ar & boost::serialization::make_nvp( "electroionization_recoil_pdf",
    d_electroionization_recoil_pdf );
  ar & boost::serialization::make_nvp(
    "electroionization_recoil_pdf_interp_type",
    d_electroionization_recoil_pdf_interp_type );

//---------------------------------------------------------------------------//
// BREMSSTRAHLUNG DATA
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_cross_section_energy_grid",
    d_bremsstrahlung_cross_section_energy_grid );
  ar & boost::serialization::make_nvp( "bremsstrahlung_cross_section",
                                        d_bremsstrahlung_cross_section );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_cross_section_interp_type",
    d_bremsstrahlung_cross_section_interp_type );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_photon_incident_energy",
    d_bremsstrahlung_average_photon_incident_energy );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_photon_energy",
    d_bremsstrahlung_average_photon_energy );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_photon_energy_interp_type",
    d_bremsstrahlung_average_photon_energy_interp_type );
  ar & boost::serialization::make_nvp( "bremsstrahlung_photon_energy_grid",
                                       d_bremsstrahlung_photon_energy_grid );
  ar & boost::serialization::make_nvp( "bremsstrahlung_photon_energy",
                                       d_bremsstrahlung_photon_energy );
  ar & boost::serialization::make_nvp( "bremsstrahlung_photon_pdf",
                                       d_bremsstrahlung_photon_pdf );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_photon_pdf_interp_type",
    d_bremsstrahlung_photon_pdf_interp_type );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_electron_incident_energy",
    d_bremsstrahlung_average_electron_incident_energy );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_electron_energy",
    d_bremsstrahlung_average_electron_energy );
  ar & boost::serialization::make_nvp(
    "bremsstrahlung_average_electron_energy_interp_type",
    d_bremsstrahlung_average_electron_energy_interp_type );

//---------------------------------------------------------------------------//
// ATOMIC EXCITATION DATA
//---------------------------------------------------------------------------//
  ar & boost::serialization::make_nvp(
    "atomic_excitation_energy_grid",
    d_atomic_excitation_energy_grid );
  ar & boost::serialization::make_nvp( "atomic_excitation_cross_section",
                                        d_atomic_excitation_cross_section );
  ar & boost::serialization::make_nvp(
    "atomic_excitation_cross_section_interp_type",
    d_atomic_excitation_cross_section_interp_type );
  ar & boost::serialization::make_nvp( "atomic_excitation_energy_loss",
                                       d_atomic_excitation_energy_loss );
  ar & boost::serialization::make_nvp(
    "atomic_excitation_energy_loss_interp_type",
    d_atomic_excitation_energy_loss_interp_type );
}

} // end Data namespace

#endif // end DATA_ENDL_DATA_CONTAINER_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_ENDLDataContainer_def.hpp
//---------------------------------------------------------------------------//

