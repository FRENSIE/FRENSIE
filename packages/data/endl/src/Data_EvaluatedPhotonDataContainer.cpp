//---------------------------------------------------------------------------//
//!
//! \file   Data_EvaluatedPhotonDataContainer.cpp
//! \author Luke Kersting
//! \brief  The native evaluated photon data container class def.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>
#include <fstream>
#include <sstream>
#include <typeinfo>

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

// FRENSIE Includes
#include "Data_ENDLDataContainer.hpp"
#include "Data_DataContainerHelpers.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

//---------------------------------------------------------------------------//
// GET COHERENT PHOTON DATA
//---------------------------------------------------------------------------//

// Return the coherent cross section energy grid
const std::vector<double>&
ENDLDataContainer::getCoherentCrossSectionEnergyGrid() const
{
  return d_coherent_cross_section_energy_grid;
}

// Return the coherent photon cross section
const std::vector<double>& ENDLDataContainer::getCoherentCrossSection() const
{
  return d_coherent_cross_section;
}

// Return the coherent photon cross section interpolation type
const std::string& ENDLDataContainer::getCoherentCrossSectionInterpType() const
{
  return d_coherent_cross_section_interp_type;
}

// Return the argument for the coherent form factor
const std::vector<double>& ENDLDataContainer::getCoherentFormFactorArgument() const
{
  return d_coherent_form_factor_argument;
}

// Return the coherent form factor
const std::vector<double>& ENDLDataContainer::getCoherentFormFactor() const
{
  return d_coherent_form_factor;
}

// Return the coherent form factor interpolation type
const std::string& ENDLDataContainer::getCoherentFormFactorInterpType() const
{
  return d_coherent_form_factor_interp_type;
}

// Return the incident energy grid for the coherent imaginary anomalous scattering factor
const std::vector<double>&
  ENDLDataContainer::getCoherentImaginaryAnomalousFactorIncidentEnergy() const
{
  return d_coherent_imaginary_anomalous_scattering_factor_incident_energy;
}

// Return the coherent imaginary anomalous scattering factor
const std::vector<double>& ENDLDataContainer::getCoherentImaginaryAnomalousFactor() const
{
  return d_coherent_imaginary_anomalous_scattering_factor;
}

// Return the coherent imaginary anomalous scattering factor interpolation type
const std::string& ENDLDataContainer::getCoherentImaginaryAnomalousFactorInterpType() const
{
  return d_coherent_imaginary_anomalous_scattering_factor_interp_type;
}

// Return the incident energy grid for the coherent real anomalous scattering factor
const std::vector<double>&
  ENDLDataContainer::getCoherentRealAnomalousFactorIncidentEnergy() const
{
  return d_coherent_real_anomalous_scattering_factor_incident_energy;
}

// Return the coherent real anomalous scattering factor
const std::vector<double>& ENDLDataContainer::getCoherentRealAnomalousFactor() const
{
  return d_coherent_real_anomalous_scattering_factor;
}

// Return the coherent real anomalous scattering factor interpolation type
const std::string& ENDLDataContainer::getCoherentRealAnomalousFactorInterpType() const
{
  return d_coherent_real_anomalous_scattering_factor_interp_type;
}

// Return the incident energy grid for the coherent average energy of the scattered photon
/*! \details By definition for photon scattering, the average energy for the
 * coherently scattered photon is equal to the energy of the incident photon.
 * These values are carried in the data files so as not to make any special
 * unique cases.
 */
const std::vector<double>& ENDLDataContainer::getCoherentAveragePhotonIncidentEnergy() const
{
  return d_coherent_average_photon_incident_energy;
}

// Return the coherent average energy of the scattered photon
const std::vector<double>& ENDLDataContainer::getCoherentAveragePhotonEnergy() const
{
  return d_coherent_average_photon_energy;
}

// Return the coherent average energy of the scattered photon
const std::string& ENDLDataContainer::getCoherentAveragePhotonEnergyInterpType() const
{
  return d_coherent_average_photon_energy_interp_type;
}

//---------------------------------------------------------------------------//
// GET INCOHERENT PHOTON DATA
//---------------------------------------------------------------------------//

// Return the incoherent cross section energy grid
const std::vector<double>& ENDLDataContainer::getIncoherentCrossSectionEnergyGrid() const
{
  return d_incoherent_cross_section_energy_grid;
}

// Return the incoherent photon cross section
const std::vector<double>& ENDLDataContainer::getIncoherentCrossSection() const
{
  return d_incoherent_cross_section;
}

// Return the incoherent photon cross section interpolation type
const std::string& ENDLDataContainer::getIncoherentCrossSectionInterpType() const
{
  return d_incoherent_cross_section_interp_type;
}

// Return the argument for the incoherent scattering function
const std::vector<double>& ENDLDataContainer::getIncoherentScatteringFunctionArgument() const
{
  return d_incoherent_scattering_function_argument;
}

// Return the incoherent scattering function
const std::vector<double>& ENDLDataContainer::getIncoherentScatteringFunction() const
{
  return d_incoherent_scattering_function;
}

// Return the incoherent scattering function
const std::string& ENDLDataContainer::getIncoherentScatteringFunctionInterpType() const
{
  return d_incoherent_scattering_function_interp_type;
}

// Return the incident energy grid for the incoherent average energy of the scattered photon
const std::vector<double>& ENDLDataContainer::getIncoherentAveragePhotonIncidentEnergy() const
{
  return d_incoherent_average_photon_incident_energy;
}

// Return the incoherent average energy of the scattered photon
const std::vector<double>& ENDLDataContainer::getIncoherentAveragePhotonEnergy() const
{
  return d_incoherent_average_photon_energy;
}

// Return the incoherent average energy of the scattered photon interpolation type
const std::string& ENDLDataContainer::getIncoherentAveragePhotonEnergyInterpType() const
{
  return d_incoherent_average_photon_energy_interp_type;
}

// Return the incident energy grid for the incoherent average energy of the recoil electron
const std::vector<double>& ENDLDataContainer::getIncoherentAverageElectronIncidentEnergy() const
{
  return d_incoherent_average_electron_incident_energy;
}

// Return the incoherent average energy of the recoil electron
const std::vector<double>& ENDLDataContainer::getIncoherentAverageElectronEnergy() const
{
  return d_incoherent_average_electron_energy;
}

// Return the incoherent average energy of the recoil electron interpolation type
const std::string& ENDLDataContainer::getIncoherentAverageElectronEnergyInterpType() const
{
  return d_incoherent_average_electron_energy_interp_type;
}

//---------------------------------------------------------------------------//
// GET PHOTOELECTRIC PHOTON DATA
//---------------------------------------------------------------------------//

// Return the photoelectric cross section energy grid
const std::vector<double>& ENDLDataContainer::getPhotoelectricCrossSectionEnergyGrid() const
{
  return d_photoelectric_cross_section_energy_grid;
}

// Return the photoelectric photon cross section
const std::vector<double>& ENDLDataContainer::getPhotoelectricCrossSection() const
{
  return d_photoelectric_cross_section;
}

// Return the photoelectric photon cross section interpolation type
const std::string& ENDLDataContainer::getPhotoelectricCrossSectionInterpType() const
{
  return d_photoelectric_cross_section_interp_type;
}

// Return the incident energy grid for the photoelectric average energy of the residual atom
const std::vector<double>& ENDLDataContainer::getPhotoelectricAverageResidualIncidentEnergy() const
{
  return d_photoelectric_average_residual_incident_energy;
}

// Return the photoelectric average energy of the residual atom
/*! \details The average energy to the residual atom insures energy
 * conservation and is deposited locally.
 */
const std::vector<double>& ENDLDataContainer::getPhotoelectricAverageResidualEnergy() const
{
  return d_photoelectric_average_residual_energy;
}

// Return the photoelectric average energy of the residual atom interpolation type
const std::string& ENDLDataContainer::getPhotoelectricAverageResidualEnergyInterpType() const
{
  return d_photoelectric_average_residual_energy_interp_type;
}

// Return the incident energy grid for the photoelectric average energy of the secondary photons
const std::vector<double>& ENDLDataContainer::getPhotoelectricAveragePhotonsIncidentEnergy() const
{
  return d_photoelectric_secondary_photons_incident_energy;
}

// Return the photoelectric average energy of the secondary photons
/*! \details For the photoelectric effect, photons and electrons are
 * released from the atom. These are accounted for in energy deposition through
 * the atom relaxation data.
 */
const std::vector<double>& ENDLDataContainer::getPhotoelectricAveragePhotonsEnergy() const
{
  return d_photoelectric_secondary_photons_energy;
}

// Return the photoelectric average energy of the secondary photons interpolation type
const std::string& ENDLDataContainer::getPhotoelectricAveragePhotonsEnergyInterpType() const
{
  return d_photoelectric_secondary_photons_energy_interp_type;
}

// Return the incident energy grid for the photoelectric average energy of the secondary electrons
const std::vector<double>& ENDLDataContainer::getPhotoelectricAverageElectronsIncidentEnergy() const
{
  return d_photoelectric_secondary_electrons_incident_energy;
}

// Return the photoelectric average energy of the secondary electrons
/*! \details For the photoelectric effect, photons and electrons are
 * released from the atom. These are accounted for in energy deposition through
 * the atom relaxation data.
 */
const std::vector<double>& ENDLDataContainer::getPhotoelectricAverageElectronsEnergy() const
{
  return d_photoelectric_secondary_electrons_energy;
}

// Return the photoelectric average energy of the secondary electrons
const std::string& ENDLDataContainer::getPhotoelectricAverageElectronsEnergyInterpType() const
{
  return d_photoelectric_secondary_electrons_energy_interp_type;
}

//---------------------------------------------------------------------------//
// GET PHOTOELECTRIC PHOTON DATA BY SUBSHELL
//---------------------------------------------------------------------------//

// Return the photoelectric cross section energy grid for a subshell
const std::vector<double>&
  ENDLDataContainer::getPhotoelectricCrossSectionEnergyGrid( const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_photoelectric_subshell_cross_section_energy_grid.find( subshell )->second;
}

// Return the photoelectric photon cross section for a subshell
const std::vector<double>&
  ENDLDataContainer::getPhotoelectricCrossSection( const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_photoelectric_subshell_cross_section.find( subshell )->second;
}

// Return the photoelectric photon cross section interpolation type for a subshell
const std::string&
  ENDLDataContainer::getPhotoelectricCrossSectionInterpType( const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_photoelectric_subshell_cross_section_interp_type.find( subshell )->second;
}

// Return the incident energy grid for the photoelectric average energy of the residual atom for a subshell
const std::vector<double>&
  ENDLDataContainer::getPhotoelectricAverageResidualIncidentEnergy( const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_photoelectric_subshell_average_residual_incident_energy.find( subshell )->second;
}

// Return the photoelectric average energy of the residual atom for a subshell
/*! \details The average energy to the residual atom insures energy
 * conservation and is deposited locally.
 */
const std::vector<double>&
  ENDLDataContainer::getPhotoelectricAverageResidualEnergy( const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_photoelectric_subshell_average_residual_energy.find( subshell )->second;
}

// Return the photoelectric average energy of the residual atom interpolation type for a subshell
/*! \details The average energy to the residual atom insures energy
 * conservation and is deposited locally.
 */
const std::string&
  ENDLDataContainer::getPhotoelectricAverageResidualEnergyInterpType( const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_photoelectric_subshell_average_residual_energy_interp_type.find( subshell )->second;
}

// Return the incident energy grid for the photoelectric average energy of the secondary photons for a subshell
const std::vector<double>&
  ENDLDataContainer::getPhotoelectricAveragePhotonsIncidentEnergy( const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_photoelectric_subshell_secondary_photons_incident_energy.find( subshell )->second;
}

// Return the photoelectric average energy of the secondary photons for a subshell
/*! \details For the photoelectric effect, photons and electrons are
 * released from the atom. These are accounted for in energy deposition through
 * the atom relaxation data.
 */
const std::vector<double>&
  ENDLDataContainer::getPhotoelectricAveragePhotonsEnergy( const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_photoelectric_subshell_secondary_photons_energy.find( subshell )->second;
}

// Return the photoelectric average energy of the secondary photons interpolation type for a subshell
const std::string&
  ENDLDataContainer::getPhotoelectricAveragePhotonsEnergyInterpType( const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_photoelectric_subshell_secondary_photons_energy_interp_type.find( subshell )->second;
}

// Return the incident energy grid for the photoelectric average energy of the secondary electrons for a subshell
const std::vector<double>&
  ENDLDataContainer::getPhotoelectricAverageElectronsIncidentEnergy( const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_photoelectric_subshell_secondary_electrons_incident_energy.find( subshell )->second;
}

// Return the photoelectric average energy of the secondary electrons for a subshell
/*! \details For the photoelectric effect, photons and electrons are
 * released from the atom. These are accounted for in energy deposition through
 * the atom relaxation data.
 */
const std::vector<double>&
  ENDLDataContainer::getPhotoelectricAverageElectronsEnergy( const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_photoelectric_subshell_secondary_electrons_energy.find( subshell )->second;
}

// Return the photoelectric average energy of the secondary electrons for a subshell
const std::string&
  ENDLDataContainer::getPhotoelectricAverageElectronsEnergyInterpType( const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_photoelectric_subshell_secondary_electrons_energy_interp_type.find( subshell )->second;
}

//---------------------------------------------------------------------------//
// GET PAIR PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

// Return the pair production cross section energy grid
const std::vector<double>& ENDLDataContainer::getPairProductionCrossSectionEnergyGrid() const
{
  return d_pair_production_cross_section_energy_grid;
}

// Return the pair production photon cross section
const std::vector<double>& ENDLDataContainer::getPairProductionCrossSection() const
{
  return d_pair_production_cross_section;
}

// Return the pair production photon cross section interpolation type
const std::string& ENDLDataContainer::getPairProductionCrossSectionInterpType() const
{
  return d_pair_production_cross_section_interp_type;
}

// Return the incident energy grid for the pair production average energy of the secondary positron
const std::vector<double>& ENDLDataContainer::getPairProductionAveragePositronIncidentEnergy() const
{
  return d_pair_production_average_positron_incident_energy;
}

// Return the pair production average energy of the secondary positron
const std::vector<double>& ENDLDataContainer::getPairProductionAveragePositronEnergy() const
{
  return d_pair_production_average_positron_energy;
}

// Return the pair production average energy of the secondary positron interpolation type
const std::string& ENDLDataContainer::getPairProductionAveragePositronEnergyInterpType() const
{
  return d_pair_production_average_positron_energy_interp_type;
}

// Return the incident energy grid for the pair production average energy of the secondary electron
const std::vector<double>& ENDLDataContainer::getPairProductionAverageElectronIncidentEnergy() const
{
  return d_pair_production_average_electron_incident_energy;
}

// Return the pair production average energy of the secondary electron
const std::vector<double>& ENDLDataContainer::getPairProductionAverageElectronEnergy() const
{
  return d_pair_production_average_electron_energy;
}

// Return the pair production average energy of the secondary electron interpolation type
const std::string& ENDLDataContainer::getPairProductionAverageElectronEnergyInterpType() const
{
  return d_pair_production_average_electron_energy_interp_type;
}

//---------------------------------------------------------------------------//
// GET TRIPLET PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

// Return the triplet production cross section energy grid
const std::vector<double>& ENDLDataContainer::getTripletProductionCrossSectionEnergyGrid() const
{
  return d_triplet_production_cross_section_energy_grid;
}

// Return the triplet production photon cross section
const std::vector<double>& ENDLDataContainer::getTripletProductionCrossSection() const
{
  return d_triplet_production_cross_section;
}

// Return the triplet production photon cross section interpolation type
const std::string& ENDLDataContainer::getTripletProductionCrossSectionInterpType() const
{
  return d_triplet_production_cross_section_interp_type;
}

// Return the incident energy grid for the triplet production average energy of the secondary positron
const std::vector<double>& ENDLDataContainer::getTripletProductionAveragePositronIncidentEnergy() const
{
  return d_triplet_production_average_positron_incident_energy;
}

// Return the triplet production average energy of the secondary positron
const std::vector<double>& ENDLDataContainer::getTripletProductionAveragePositronEnergy() const
{
  return d_triplet_production_average_positron_energy;
}

// Return the triplet production average energy of the secondary positron interpolation type
const std::string& ENDLDataContainer::getTripletProductionAveragePositronEnergyInterpType() const
{
  return d_triplet_production_average_positron_energy_interp_type;
}

// Return the incident energy grid for the triplet production average energy of the secondary electron
const std::vector<double>& ENDLDataContainer::getTripletProductionAverageElectronIncidentEnergy() const
{
  return d_triplet_production_average_electron_incident_energy;
}

// Return the triplet production average energy of the secondary electron
const std::vector<double>& ENDLDataContainer::getTripletProductionAverageElectronEnergy() const
{
  return d_triplet_production_average_electron_energy;
}

// Return the triplet production average energy of the secondary electron interpolation type
const std::string& ENDLDataContainer::getTripletProductionAverageElectronEnergyInterpType() const
{
  return d_triplet_production_average_electron_energy_interp_type;
}

//---------------------------------------------------------------------------//
// SET COHERENT PHOTON DATA
//---------------------------------------------------------------------------//

// Set the coherent cross section energy grid
void ENDLDataContainer::setCoherentCrossSectionEnergyGrid(
  const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( Data::energyGridValid( energy_grid ) );

  d_coherent_cross_section_energy_grid = energy_grid;
}

// Set the coherent photon cross section
void ENDLDataContainer::setCoherentCrossSection( const std::vector<double>& cross_section )
{
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() <=
    d_coherent_cross_section_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanZero( cross_section ) );

  d_coherent_cross_section = cross_section;
}

// Set the argument for the coherent form factor
void ENDLDataContainer::setCoherentFormFactorArgument(
  const std::vector<double>& form_factor_argument )
{
  // Make sure the argument for the coherent form factor is valid
  testPrecondition( form_factor_argument.back() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( form_factor_argument.begin(),
						                              form_factor_argument.end() ) );
  testPrecondition( form_factor_argument.front() == 0.0 );

  d_coherent_form_factor_argument = form_factor_argument;
}

// Set the coherent form factor
void ENDLDataContainer::setCoherentFormFactor( const std::vector<double>& form_factor )
{
  // Make sure the coherent form factor is valid
  testPrecondition( form_factor.size() ==
    d_coherent_form_factor_argument.size() );
  testPrecondition( Utility::Sort::isSortedAscending( form_factor.rbegin(),
						                              form_factor.rend() ) );
  testPrecondition( form_factor.front() == 1.0*d_atomic_number );

  d_coherent_form_factor = form_factor;
}

// Set the incident energy grid for the coherent imaginary anomalous scattering factor
void ENDLDataContainer::setCoherentImaginaryAnomalousFactorIncidentEnergy(
  const std::vector<double>& anomalous_incident_energy )
{
  // Make sure incident energy grid is valid
  testPrecondition( Data::energyGridValid( anomalous_incident_energy ) );

  d_coherent_imaginary_anomalous_scattering_factor_incident_energy =
    anomalous_incident_energy;
}

// Set the coherent imaginary anomalous scattering factor
void ENDLDataContainer::setCoherentImaginaryAnomalousFactor(
  const std::vector<double>& anomalous_factor )
{
  // Make sure the coherent imaginary anomalous scattering factor is valid
  testPrecondition( anomalous_factor.size() ==
    d_coherent_imaginary_anomalous_scattering_factor_incident_energy.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( anomalous_factor ) );

  d_coherent_imaginary_anomalous_scattering_factor = anomalous_factor;
}

// Set the incident energy grid for the coherent real anomalous scattering factor
void ENDLDataContainer::setCoherentRealAnomalousFactorIncidentEnergy(
  const std::vector<double>& anomalous_incident_energy )
{
  // Make sure incident energy grid is valid
  testPrecondition( Data::energyGridValid( anomalous_incident_energy ) );

  d_coherent_real_anomalous_scattering_factor_incident_energy =
    anomalous_incident_energy;
}

// Set the coherent real anomalous scattering factor
void ENDLDataContainer::setCoherentRealAnomalousFactor(
  const std::vector<double>& anomalous_factor )
{
  // Make sure the coherent real anomalous scattering factor is valid
  testPrecondition( anomalous_factor.size() ==
    d_coherent_real_anomalous_scattering_factor_incident_energy.size() );

  d_coherent_real_anomalous_scattering_factor = anomalous_factor;
}

// Set the incident energy grid for the coherent average energy of the scattered photon
void ENDLDataContainer::setCoherentAveragePhotonIncidentEnergy(
  const std::vector<double>& incident_energy )
{
  // Make sure incident energy grid is valid
  testPrecondition( Data::energyGridValid( incident_energy ) );

  d_coherent_average_photon_incident_energy =
    incident_energy;
}

// Set the coherent average energy of the scattered photon
void ENDLDataContainer::setCoherentAveragePhotonEnergy(
  const std::vector<double>& average_energy )
{
  // Make sure the average energy is valid
  testPrecondition( average_energy.size() ==
                    d_coherent_average_photon_incident_energy.size() );
  testPrecondition( Data::valuesGreaterThanZero( average_energy ) );

  d_coherent_average_photon_energy = average_energy;
}

//---------------------------------------------------------------------------//
// SET INCOHERENT PHOTON DATA
//---------------------------------------------------------------------------//

// Set the incoherent cross section energy grid
void ENDLDataContainer::setIncoherentCrossSectionEnergyGrid(
  const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( Data::energyGridValid( energy_grid ) );

  d_incoherent_cross_section_energy_grid = energy_grid;
}

// Set the incoherent photon cross section
void ENDLDataContainer::setIncoherentCrossSection( const std::vector<double>& cross_section )
{
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() <=
    d_incoherent_cross_section_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanZero( cross_section ) );

  d_incoherent_cross_section = cross_section;
}

// Set the argument for the incoherent scattering function
void ENDLDataContainer::setIncoherentScatteringFunctionArgument(
  const std::vector<double>& scattering_function_argument )
{
  // Make sure the argument for the coherent form factor is valid
  testPrecondition( scattering_function_argument.back() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( scattering_function_argument.begin(),
						                              scattering_function_argument.end() ) );
  testPrecondition( scattering_function_argument.front() == 0.0 );

  d_incoherent_scattering_function_argument = scattering_function_argument;
}

// Set the incoherent scattering function
void ENDLDataContainer::setIncoherentScatteringFunction(
  const std::vector<double>& scattering_function )
{
  // Make sure the incoherent scattering function is valid
  testPrecondition( scattering_function.size() ==
    d_incoherent_scattering_function_argument.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( scattering_function ) );
  testPrecondition( scattering_function.front() == 0.0 );
  testPrecondition( scattering_function.back() == 1.0*d_atomic_number );

  d_incoherent_scattering_function = scattering_function;
}

// Set the incident energy grid for the incoherent average energy of the scattered photon
void ENDLDataContainer::setIncoherentAveragePhotonIncidentEnergy(
  const std::vector<double>& incident_energy )
{
  // Make sure incident energy grid is valid
  testPrecondition( Data::energyGridValid( incident_energy ) );

  d_incoherent_average_photon_incident_energy =
    incident_energy;
}

// Set the incoherent average energy of the scattered photon
void ENDLDataContainer::setIncoherentAveragePhotonEnergy(
  const std::vector<double>& average_energy )
{
  // Make sure the average energy is valid
  testPrecondition( average_energy.size() ==
                    d_incoherent_average_photon_incident_energy.size() );
  testPrecondition( Data::valuesGreaterThanZero( average_energy ) );

  d_incoherent_average_photon_energy = average_energy;
}

// Set the incident energy grid for the incoherent average energy of the recoil electron
void ENDLDataContainer::setIncoherentAverageElectronIncidentEnergy(
  const std::vector<double>& incident_energy )
{
  // Make sure incident energy grid is valid
  testPrecondition( Data::energyGridValid( incident_energy ) );

  d_incoherent_average_electron_incident_energy =
    incident_energy;
}

// Set the incoherent average energy of the recoil electron
void ENDLDataContainer::setIncoherentAverageElectronEnergy(
  const std::vector<double>& average_energy )
{
  // Make sure the average energy is valid
  testPrecondition( average_energy.size() ==
                    d_incoherent_average_electron_incident_energy.size() );
  testPrecondition( Data::valuesGreaterThanZero( average_energy ) );

  d_incoherent_average_electron_energy = average_energy;
}

//---------------------------------------------------------------------------//
// SET PHOTOELECTRIC PHOTON DATA
//---------------------------------------------------------------------------//

// Set the photoelectric cross section energy grid
void ENDLDataContainer::setPhotoelectricCrossSectionEnergyGrid(
  const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( Data::energyGridValid( energy_grid ) );

  d_photoelectric_cross_section_energy_grid = energy_grid;
}

// Set the photoelectric photon cross section
void ENDLDataContainer::setPhotoelectricCrossSection( const std::vector<double>& cross_section )
{
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() <=
    d_photoelectric_cross_section_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanZero( cross_section ) );

  d_photoelectric_cross_section = cross_section;
}

// Set the incident energy grid for the photoelectric average energy of the residual atom
void ENDLDataContainer::setPhotoelectricAverageResidualIncidentEnergy(
  const std::vector<double>& incident_energy )
{
  // Make sure incident energy grid is valid
  testPrecondition( Data::energyGridValid( incident_energy ) );

  d_photoelectric_average_residual_incident_energy =
    incident_energy;
}

// Set the photoelectric average energy of the residual atom
void ENDLDataContainer::setPhotoelectricAverageResidualEnergy(
  const std::vector<double>& average_energy )
{
  // Make sure the average energy is valid
  testPrecondition( average_energy.size() ==
                    d_photoelectric_average_residual_incident_energy.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( average_energy ) );

  d_photoelectric_average_residual_energy = average_energy;
}

// Set the incident energy grid for the photoelectric average energy of the secondary photons
void ENDLDataContainer::setPhotoelectricAveragePhotonsIncidentEnergy(
  const std::vector<double>& incident_energy )
{
  // Make sure incident energy grid is valid
  testPrecondition( Data::energyGridValid( incident_energy ) );

  d_photoelectric_secondary_photons_incident_energy =
    incident_energy;
}

// Set the photoelectric average energy of the secondary photons
void ENDLDataContainer::setPhotoelectricAveragePhotonsEnergy(
  const std::vector<double>& average_energy )
{
  // Make sure the average energy is valid
  testPrecondition( average_energy.size() ==
                    d_photoelectric_secondary_photons_incident_energy.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( average_energy ) );

  d_photoelectric_secondary_photons_energy = average_energy;
}

// Set the incident energy grid for the photoelectric average energy of the secondary electrons
void ENDLDataContainer::setPhotoelectricAverageElectronsIncidentEnergy(
  const std::vector<double>& incident_energy )
{
  // Make sure incident energy grid is valid
  testPrecondition( Data::energyGridValid( incident_energy ) );

  d_photoelectric_secondary_electrons_incident_energy =
    incident_energy;
}

// Set the photoelectric average energy of the secondary electrons
void ENDLDataContainer::setPhotoelectricAverageElectronsEnergy(
  const std::vector<double>& average_energy )
{
  // Make sure the average energy is valid
  testPrecondition( average_energy.size() ==
                    d_photoelectric_secondary_electrons_incident_energy.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( average_energy ) );

  d_photoelectric_secondary_electrons_energy = average_energy;
}

//---------------------------------------------------------------------------//
// SET PHOTOELECTRIC PHOTON DATA BY SUBSHELL
//---------------------------------------------------------------------------//

// Set the photoelectric cross section energy grid for a subshell
void ENDLDataContainer::setPhotoelectricCrossSectionEnergyGrid(
  const unsigned subshell,
  const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( Data::energyGridValid( energy_grid ) );

  d_photoelectric_subshell_cross_section_energy_grid[subshell] = energy_grid;
}

// Set the photoelectric photon cross section a subshell
void ENDLDataContainer::setPhotoelectricCrossSection(
  const unsigned subshell,
  const std::vector<double>& cross_section )
{
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() <=
    d_photoelectric_subshell_cross_section_energy_grid[subshell].size() );
  testPrecondition( Data::valuesGreaterThanZero( cross_section ) );

  d_photoelectric_subshell_cross_section[subshell] = cross_section;
}

// Set the incident energy grid for the photoelectric average energy of the residual atom a subshell
void ENDLDataContainer::setPhotoelectricAverageResidualIncidentEnergy(
  const unsigned subshell,
  const std::vector<double>& incident_energy )
{
  // Make sure incident energy grid is valid
  testPrecondition( Data::energyGridValid( incident_energy ) );

  d_photoelectric_subshell_average_residual_incident_energy[subshell] =
    incident_energy;
}

// Set the photoelectric average energy of the residual atom a subshell
void ENDLDataContainer::setPhotoelectricAverageResidualEnergy(
  const unsigned subshell,
  const std::vector<double>& average_energy  )
{
  // Make sure the average energy is valid
  testPrecondition( average_energy.size() ==
    d_photoelectric_subshell_average_residual_incident_energy[subshell].size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( average_energy ) );

  d_photoelectric_subshell_average_residual_energy[subshell] = average_energy;
}

// Set the incident energy grid for the photoelectric average energy of the secondary photons a subshell
void ENDLDataContainer::setPhotoelectricAveragePhotonsIncidentEnergy(
  const unsigned subshell,
  const std::vector<double>& incident_energy )
{
  // Make sure incident energy grid is valid
  testPrecondition( Data::energyGridValid( incident_energy ) );

  d_photoelectric_subshell_secondary_photons_incident_energy[subshell] =
    incident_energy;
}

// Set the photoelectric average energy of the secondary photons a subshell
void ENDLDataContainer::setPhotoelectricAveragePhotonsEnergy(
  const unsigned subshell,
  const std::vector<double>& average_energy  )
{
  // Make sure the average energy is valid
  testPrecondition( average_energy.size() ==
    d_photoelectric_subshell_secondary_photons_incident_energy[subshell].size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( average_energy ) );

  d_photoelectric_subshell_secondary_photons_energy[subshell] = average_energy;
}

// Set the incident energy grid for the photoelectric average energy of the secondary electrons a subshell
void ENDLDataContainer::setPhotoelectricAverageElectronsIncidentEnergy(
  const unsigned subshell,
  const std::vector<double>& incident_energy )
{
  // Make sure incident energy grid is valid
  testPrecondition( Data::energyGridValid( incident_energy ) );

  d_photoelectric_subshell_secondary_electrons_incident_energy[subshell] =
    incident_energy;
}

// Set the photoelectric average energy of the secondary electrons a subshell
void ENDLDataContainer::setPhotoelectricAverageElectronsEnergy(
  const unsigned subshell,
  const std::vector<double>& average_energy )
{
  // Make sure the average energy is valid
  testPrecondition( average_energy.size() ==
    d_photoelectric_subshell_secondary_electrons_incident_energy[subshell].size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( average_energy ) );

  d_photoelectric_subshell_secondary_electrons_energy[subshell] = average_energy;
}

//---------------------------------------------------------------------------//
// SET PAIR PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

// Set the pair production cross section energy grid
void ENDLDataContainer::setPairProductionCrossSectionEnergyGrid(
  const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( Data::energyGridValid( energy_grid ) );

  d_pair_production_cross_section_energy_grid = energy_grid;
}

// Set the pair production photon cross section
void ENDLDataContainer::setPairProductionCrossSection( const std::vector<double>& cross_section )
{
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() <=
    d_pair_production_cross_section_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( cross_section ) );

  d_pair_production_cross_section = cross_section;
}

// Set the incident energy grid for the pair production average energy of the secondary positron
void ENDLDataContainer::setPairProductionAveragePositronIncidentEnergy(
  const std::vector<double>& incident_energy )
{
  // Make sure incident energy grid is valid
  testPrecondition( Data::energyGridValid( incident_energy ) );

  d_pair_production_average_positron_incident_energy =
    incident_energy;
}

// Set the pair production average energy of the secondary positron
void ENDLDataContainer::setPairProductionAveragePositronEnergy(
  const std::vector<double>& average_energy )
{
  // Make sure the average energy is valid
  testPrecondition( average_energy.size() ==
                    d_pair_production_average_positron_incident_energy.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( average_energy ) );

  d_pair_production_average_positron_energy = average_energy;
}

// Set the incident energy grid for the pair production average energy of the secondary electron
void ENDLDataContainer::setPairProductionAverageElectronIncidentEnergy(
  const std::vector<double>& incident_energy )
{
  // Make sure incident energy grid is valid
  testPrecondition( Data::energyGridValid( incident_energy ) );

  d_pair_production_average_electron_incident_energy =
    incident_energy;
}

// Set the pair production average energy of the secondary electron
void ENDLDataContainer::setPairProductionAverageElectronEnergy(
  const std::vector<double>& average_energy )
{
  // Make sure the average energy is valid
  testPrecondition( average_energy.size() ==
                    d_pair_production_average_electron_incident_energy.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( average_energy ) );

  d_pair_production_average_electron_energy = average_energy;
}

//---------------------------------------------------------------------------//
// SET TRIPLET PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

// Set the triplet production cross section energy grid
void ENDLDataContainer::setTripletProductionCrossSectionEnergyGrid(
  const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( Data::energyGridValid( energy_grid ) );

  d_triplet_production_cross_section_energy_grid = energy_grid;
}

// Set the triplet production photon cross section
void ENDLDataContainer::setTripletProductionCrossSection(
  const std::vector<double>& cross_section )
{
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() <=
    d_triplet_production_cross_section_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( cross_section ) );

  d_triplet_production_cross_section = cross_section;
}

// Set the incident energy grid for the triplet production average energy of the secondary positron
void ENDLDataContainer::setTripletProductionAveragePositronIncidentEnergy(
  const std::vector<double>& incident_energy )
{
  // Make sure incident energy grid is valid
  testPrecondition( Data::energyGridValid( incident_energy ) );

  d_triplet_production_average_positron_incident_energy =
    incident_energy;
}

// Set the triplet production average energy of the secondary positron
void ENDLDataContainer::setTripletProductionAveragePositronEnergy(
  const std::vector<double>& average_energy )
{
  // Make sure the average energy is valid
  testPrecondition( average_energy.size() ==
                    d_triplet_production_average_positron_incident_energy.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( average_energy ) );

  d_triplet_production_average_positron_energy = average_energy;
}

// Set the incident energy grid for the triplet production average energy of the secondary electron
void ENDLDataContainer::setTripletProductionAverageElectronIncidentEnergy(
  const std::vector<double>& incident_energy )
{
  // Make sure incident energy grid is valid
  testPrecondition( Data::energyGridValid( incident_energy ) );

  d_triplet_production_average_electron_incident_energy =
    incident_energy;
}

// Set the triplet production average energy of the secondary electron
void ENDLDataContainer::setTripletProductionAverageElectronEnergy(
  const std::vector<double>& average_energy )
{
  // Make sure the average energy is valid
  testPrecondition( average_energy.size() ==
                    d_triplet_production_average_electron_incident_energy.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( average_energy ) );

  d_triplet_production_average_electron_energy = average_energy;
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ENDLDataContainer.cpp
//---------------------------------------------------------------------------//

