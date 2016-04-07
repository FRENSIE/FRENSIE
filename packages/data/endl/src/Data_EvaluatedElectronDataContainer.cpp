//---------------------------------------------------------------------------//
//!
//! \file   Data_EvaluatedElectronDataContainer.cpp
//! \author Luke Kersting
//! \brief  The native endl container class eedl def.
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
#include "Data_ENDLDataContainerHelpers.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

//---------------------------------------------------------------------------//
// GET ELASTIC DATA 
//---------------------------------------------------------------------------//

// Return the elastic energy grid
const std::vector<double>& 
ENDLDataContainer::getElasticEnergyGrid() const
{
  return d_elastic_energy_grid;
}

// Return the elastic transport electron cross section
const std::vector<double>&
ENDLDataContainer::getElasticTransportCrossSection() const
{
  return d_elastic_transport_cross_section;
}

// Return the cutoff elastic electron cross section
const std::vector<double>& 
ENDLDataContainer::getCutoffElasticCrossSection() const
{
  return d_cutoff_elastic_cross_section;
}

// Return the cutoff elastic average energy to the residual atom incoming energy grid
const std::vector<double>& 
ENDLDataContainer::getCutoffElasticResidualIncomingEnergy() const
{
  return d_cutoff_elastic_residual_incoming_energy;;
}

// Return the cutoff elastic average energy to the residual atom
const std::vector<double>& 
ENDLDataContainer::getCutoffElasticResidualEnergy() const
{
  return d_cutoff_elastic_residual_energy;
}

// Return the cutoff elastic average energy to the scattered electron incoming energy grid
const std::vector<double>& 
ENDLDataContainer::getCutoffElasticScatteredElectronIncomingEnergy() const
{
  return d_cutoff_elastic_scattered_electron_incoming_energy;
}

// Return the cutoff elastic average energy to the scattered electron
const std::vector<double>& 
ENDLDataContainer::getCutoffElasticScatteredElectronEnergy() const
{
  return d_cutoff_elastic_scattered_electron_energy;
}

// Return the cutoff elastic angular energy grid
const std::vector<double>& 
ENDLDataContainer::getCutoffElasticAngularEnergyGrid() const
{
  return d_cutoff_elastic_angular_energy_grid;
}

// Return the elastic angles for an incoming energy
const std::vector<double>& 
ENDLDataContainer::getCutoffElasticAngles(
    const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= 
                    d_cutoff_elastic_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= 
                    d_cutoff_elastic_angular_energy_grid.back() );

  return d_cutoff_elastic_angles.find( incoming_energy )->second;
}

// Return the elastic pdf for an incoming energy
const std::vector<double>& 
ENDLDataContainer::getCutoffElasticPDF(
    const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= 
                    d_cutoff_elastic_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= 
                    d_cutoff_elastic_angular_energy_grid.back() );

  return d_cutoff_elastic_pdf.find( incoming_energy )->second;
}

// Return the total elastic electron cross section
const std::vector<double>& 
ENDLDataContainer::getTotalElasticCrossSection() const
{
  return d_total_elastic_cross_section;
}

/*
// Return the screened Rutherford elastic electron cross section
const std::vector<double>& 
ENDLDataContainer::getScreenedRutherfordElasticCrossSection() const
{
  return d_screened_rutherford_elastic_cross_section;
}

// Return the screened Rutherford elastic normalization constant 
const std::vector<double>& 
ENDLDataContainer::getScreenedRutherfordNormalizationConstant() const
{
  return d_screened_rutherford_normalization_constant;
}

// Return Moliere's screening constant 
const std::vector<double>& 
ENDLDataContainer::getMoliereScreeningConstant() const
{
  return d_moliere_screening_constant;
}
*/

//---------------------------------------------------------------------------//
// GET ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//

// Return the electroionization cross section energy grid for a subshell
const std::vector<double>& 
ENDLDataContainer::getElectroionizationCrossSectionEnergyGrid( 
                            const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_electroionization_subshell_cross_section_energy_grid.find( subshell )->second;
}

// Return the electroionization electron cross section for a subshell
const std::vector<double>& 
ENDLDataContainer::getElectroionizationCrossSection( 
    const unsigned subshell ) const
{
  return d_electroionization_subshell_cross_section.find( subshell )->second;
}


// Return the electroionization incoming energy grid for the average scattered electron energy for a subshell
const std::vector<double>& 
ENDLDataContainer::getElectroionizationAverageScatteredElectronIncomingEnergy( 
                           const unsigned subshell ) const
{
  return d_electroionization_average_scattered_electron_incoming_energy.find( subshell )->second;
}

// Return the electroionization average scattered electron energy for a subshell
const std::vector<double>& 
ENDLDataContainer::getElectroionizationAverageScatteredElectronEnergy( 
                           const unsigned subshell ) const
{
  return d_electroionization_average_scattered_electron_energy.find( subshell )->second;
}

// Return the electroionization incoming energy grid for the average recoil electron energy for a subshell
const std::vector<double>& 
ENDLDataContainer::getElectroionizationAverageRecoilElectronIncomingEnergy( 
                           const unsigned subshell ) const
{
  return d_electroionization_average_recoil_electron_incoming_energy.find( subshell )->second;
}

// Return the electroionization average recoil electron energy for a subshell
const std::vector<double>& 
ENDLDataContainer::getElectroionizationAverageRecoilElectronEnergy( 
                           const unsigned subshell ) const
{
  return d_electroionization_average_recoil_electron_energy.find( subshell )->second;
}

// Return the electroionization recoil energy grid for a subshell
const std::vector<double>& 
ENDLDataContainer::getElectroionizationRecoilEnergyGrid( 
                            const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_electroionization_recoil_energy_grid.find( subshell )->second;
}

// Return the electroionization recoil energy for a subshell and energy bin
const std::vector<double>& 
ENDLDataContainer::getElectroionizationRecoilEnergy( 
                           const unsigned subshell,
					       const double incoming_energy ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition( 
            incoming_energy >= 
            d_electroionization_recoil_energy_grid.find( subshell )->second.front() );
  testPrecondition( 
            incoming_energy <= 
            d_electroionization_recoil_energy_grid.find( subshell )->second.back() );

  return d_electroionization_recoil_energy.find( subshell )->second.find( incoming_energy )->second;
}

// Return the electroionization recoil energy pdf for a subshell and energy bin
const std::vector<double>&  
ENDLDataContainer::getElectroionizationRecoilPDF( 
                           const unsigned subshell,
					       const double incoming_energy ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition( 
            incoming_energy >= 
            d_electroionization_recoil_energy_grid.find( subshell )->second.front() );
  testPrecondition( 
            incoming_energy <= 
            d_electroionization_recoil_energy_grid.find( subshell )->second.back() );

  return d_electroionization_recoil_pdf.find( subshell )->second.find( incoming_energy )->second;
}

//---------------------------------------------------------------------------//
// GET BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//

// Return the bremsstrahlung electron cross section energy grid
const std::vector<double>& 
ENDLDataContainer::getBremsstrahlungCrossSectionEnergyGrid() const
{
  return d_bremsstrahlung_cross_section_energy_grid;
}

// Return the bremsstrahlung electron cross section
const std::vector<double>& 
ENDLDataContainer::getBremsstrahlungCrossSection() const
{
  return d_bremsstrahlung_cross_section;
}

// Return the bremsstrahlung incoming electron energy grid for the average energy of the secondary photon
const std::vector<double>& 
ENDLDataContainer::getBremsstrahlungAveragePhotonIncomingEnergy() const
{
  return d_bremsstrahlung_average_photon_incoming_energy;
}

// Return the bremsstrahlung average energy of the secondary photon
const std::vector<double>& 
ENDLDataContainer::getBremsstrahlungAveragePhotonEnergy() const
{
  return d_bremsstrahlung_average_photon_energy;
}

// Return the bremsstrahlung photon energy grid
const std::vector<double>& 
ENDLDataContainer::getBremsstrahlungPhotonEnergyGrid() const
{
  return d_bremsstrahlung_photon_energy_grid;
}

// Return the bremsstrahlung for an incoming energy
const std::vector<double>& 
ENDLDataContainer::getBremsstrahlungPhotonEnergy(
					        const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >=
                    d_bremsstrahlung_photon_energy_grid.front() );
  testPrecondition( incoming_energy <=
                    d_bremsstrahlung_photon_energy_grid.back() );

  return d_bremsstrahlung_photon_energy.find( incoming_energy )->second;
}

// Return the bremsstrahlung photon pdf for an incoming energy
const std::vector<double>& 
ENDLDataContainer::getBremsstrahlungPhotonPDF(
					        const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >=
                    d_bremsstrahlung_photon_energy_grid.front() );
  testPrecondition( incoming_energy <=
                    d_bremsstrahlung_photon_energy_grid.back() );

  return d_bremsstrahlung_photon_pdf.find( incoming_energy )->second;
}

// Return the bremsstrahlung incoming electron energy grid for the average energy of the secondary electron
const std::vector<double>& 
ENDLDataContainer::getBremsstrahlungAverageElectronIncomingEnergy() const
{
  return d_bremsstrahlung_average_electron_incoming_energy;
}

// Return the bremsstrahlung average energy of the secondary electron
const std::vector<double>& 
ENDLDataContainer::getBremsstrahlungAverageElectronEnergy() const
{
  return d_bremsstrahlung_average_electron_energy;
}

//---------------------------------------------------------------------------//
// GET ATOMIC EXCITAION DATA 
//---------------------------------------------------------------------------//

// Return the atomic excitation electron energy grid
const std::vector<double>& 
ENDLDataContainer::getAtomicExcitationEnergyGrid() const
{
  return d_atomic_excitation_energy_grid;
}

// Return the atomic excitation electron cross section
const std::vector<double>& 
ENDLDataContainer::getAtomicExcitationCrossSection() const
{
  return d_atomic_excitation_cross_section;
}

// Return the atomic excitation energy loss
const std::vector<double>& 
ENDLDataContainer::getAtomicExcitationEnergyLoss() const
{
  return d_atomic_excitation_energy_loss;
}

//---------------------------------------------------------------------------//
// SET ELASTIC DATA 
//---------------------------------------------------------------------------//

// Set the elastic energy grid
void ENDLDataContainer::setElasticEnergyGrid( 
				       const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPreconditionEnergyGrid( energy_grid );

  d_elastic_energy_grid = energy_grid;
}

// Set the elastic transport cross section 
void ENDLDataContainer::setElasticTransportCrossSection(
			 const std::vector<double>& elastic_transport_cross_section )
{
  // Make sure the elastic transport cross section is valid
  testPrecondition( elastic_transport_cross_section.size() <= 
    d_elastic_energy_grid.size() );
  testPreconditionValuesGreaterThanZero( elastic_transport_cross_section );
  
  d_elastic_transport_cross_section = elastic_transport_cross_section;
}

// Set the cutoff elastic electron cross section 
void ENDLDataContainer::setCutoffElasticCrossSection(
			 const std::vector<double>& cutoff_elastic_cross_section )
{
  // Make sure the cutoff elastic cross section is valid
  testPrecondition( cutoff_elastic_cross_section.size() <= 
    d_elastic_energy_grid.size() );
  testPreconditionValuesGreaterThanZero( cutoff_elastic_cross_section );
  
  d_cutoff_elastic_cross_section = cutoff_elastic_cross_section;
}

// Set the cutoff elastic average energy to the residual atom incoming energy grid
void ENDLDataContainer::setCutoffElasticResidualIncomingEnergy( 
    const std::vector<double>& residual_incoming_energy )
{
  // Make sure residual incoming energy grid is valid
  testPreconditionEnergyGrid( residual_incoming_energy );

  d_cutoff_elastic_residual_incoming_energy = residual_incoming_energy;
}

// Set the cutoff elastic average energy to the residual atom
void ENDLDataContainer::setCutoffElasticResidualEnergy( 
    const std::vector<double>& residual_energy )
{
  // Make sure the cutoff elastic average energy to the residual atom is valid
  testPrecondition( residual_energy.size() == 
                    d_cutoff_elastic_residual_incoming_energy.size() );
  testPreconditionValuesGreaterThanOrEqualToZero( residual_energy );

  d_cutoff_elastic_residual_energy = residual_energy;
}

// Set the cutoff elastic average energy of the scattered electron incoming energy grid
void ENDLDataContainer::setCutoffElasticScatteredElectronIncomingEnergy( 
    const std::vector<double>& scattered_electron_incoming_energy )
{
  // Make sure scattered electron energy grid is valid
  testPreconditionEnergyGrid( scattered_electron_incoming_energy );

  d_cutoff_elastic_scattered_electron_incoming_energy = 
    scattered_electron_incoming_energy;
}

// Set the cutoff elastic average energy of the scattered electron
void ENDLDataContainer::setCutoffElasticScatteredElectronEnergy(
    const std::vector<double>& scattered_electron_average_energy )
{
  // Make sure the cutoff elastic average energy of the residual atom is valid
  testPrecondition( scattered_electron_average_energy.size() == 
                    d_cutoff_elastic_scattered_electron_incoming_energy.size() );
  testPreconditionValuesGreaterThanOrEqualToZero(
    scattered_electron_average_energy );

  d_cutoff_elastic_scattered_electron_energy = 
    scattered_electron_average_energy;
}

// Set the elastic angular energy grid
void ENDLDataContainer::setCutoffElasticAngularEnergyGrid( 
				       const std::vector<double>& angular_energy_grid )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition( 
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
			                              angular_energy_grid.end() ) );

  testPreconditionValuesGreaterThanZero( angular_energy_grid );

  d_cutoff_elastic_angular_energy_grid = angular_energy_grid;
}

// Set the total elastic angles for an incoming energy
void ENDLDataContainer::setCutoffElasticAnglesAtEnergy(
    const double incoming_energy,
    const std::vector<double>& cutoff_elastic_angles )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >= 
                    d_cutoff_elastic_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= 
                    d_cutoff_elastic_angular_energy_grid.back() );
  // Make sure the elastic angles are valid
  testPrecondition( std::find_if( cutoff_elastic_angles.begin(),
                                  cutoff_elastic_angles.end(),
                                  isValueLessThanMinusOne ) ==
                    cutoff_elastic_angles.end() );
  testPrecondition( std::find_if( cutoff_elastic_angles.begin(),
                                  cutoff_elastic_angles.end(),
                                  isValueGreaterThanOne ) ==
                    cutoff_elastic_angles.end() );

  d_cutoff_elastic_angles[incoming_energy] = cutoff_elastic_angles;
}

// Set the total elastic pdf for an incoming energy
void ENDLDataContainer::setCutoffElasticPDFAtEnergy( 
    const double incoming_energy,
    const std::vector<double>& cutoff_elastic_pdf )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >= 
                    d_cutoff_elastic_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= 
                    d_cutoff_elastic_angular_energy_grid.back() );

  // Make sure the weight is valid
  testPreconditionValuesGreaterThanZero( cutoff_elastic_pdf );
  
  d_cutoff_elastic_pdf[incoming_energy] = cutoff_elastic_pdf;
}
// Set the total elastic angles
void ENDLDataContainer::setCutoffElasticAngles(
    const std::map<double,std::vector<double> >& cutoff_elastic_angles )
{
  d_cutoff_elastic_angles = cutoff_elastic_angles;
}

// Set the total elastic pdf 
void ENDLDataContainer::setCutoffElasticPDF( 
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf )
{
  d_cutoff_elastic_pdf = cutoff_elastic_pdf;
}

// Set the total elastic electron cross section 
void ENDLDataContainer::setTotalElasticCrossSection(
			 const std::vector<double>& total_elastic_cross_section )
{
  // Make sure the total elastic cross section is valid
  testPrecondition( total_elastic_cross_section.size() <= 
    d_elastic_energy_grid.size() );
  testPreconditionValuesGreaterThanZero( total_elastic_cross_section );
  
  d_total_elastic_cross_section = total_elastic_cross_section;
}

/*
// Set the screened rutherford elastic electron cross section 
void ENDLDataContainer::setScreenedRutherfordElasticCrossSection(
			 const std::vector<double>& screened_rutherford_elastic_cross_section )
{
  // Make sure the screened rutherford elastic cross section is valid
  testPrecondition( screened_rutherford_elastic_cross_section.size() <= 
                    d_elastic_energy_grid.size() );
  testPreconditionValuesGreaterThanOrEqualToZero(
    screened_rutherford_elastic_cross_section );
  
  d_screened_rutherford_elastic_cross_section = screened_rutherford_elastic_cross_section;
}

// Set the screened Rutherford elastic normalization constant 
void ENDLDataContainer::setScreenedRutherfordNormalizationConstant(
		     const std::vector<double>& screened_rutherford_normalization_constant )
{
  // Make sure the screened_rutherford_normalization_constants are valid
  testPreconditionValuesGreaterThanOrEqualToZero(
    screened_rutherford_normalization_constant );

  d_screened_rutherford_normalization_constant = 
    screened_rutherford_normalization_constant;
}

// Set Moliere's screening constant 
void ENDLDataContainer::setMoliereScreeningConstant( 
			 const std::vector<double>& moliere_screening_constant )
{
  d_moliere_screening_constant = moliere_screening_constant;
}
*/

//---------------------------------------------------------------------------//
// SET ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//

// Set the electroionization energy grid
void ENDLDataContainer::setElectroionizationCrossSectionEnergyGrid(
    const unsigned subshell,
    const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPreconditionEnergyGrid( energy_grid );

  d_electroionization_subshell_cross_section_energy_grid[subshell] = 
    energy_grid;
}

// Set the electroionization electron cross section 
void ENDLDataContainer::setElectroionizationCrossSection(
            const unsigned subshell,
            const std::vector<double>& electroionization_cross_section )
{
  // Make sure the electroionization cross section is valid
  testPrecondition( electroionization_cross_section.size() <= 
    d_electroionization_subshell_cross_section_energy_grid[subshell].size() );
  testPreconditionValuesGreaterThanOrEqualToZero( electroionization_cross_section );
  
  d_electroionization_subshell_cross_section[subshell] = 
    electroionization_cross_section;
}

// Set the electroionization incoming energy grid for the average scattered electron energy for a subshell
void ENDLDataContainer::setElectroionizationAverageScatteredElectronIncomingEnergy(
    const unsigned subshell,
    const std::vector<double>& average_scattered_electron_incoming_energy )
{
  // Make sure the incoming energy grid is valid
  testPreconditionEnergyGrid( average_scattered_electron_incoming_energy );

  d_electroionization_average_scattered_electron_incoming_energy[subshell] = 
    average_scattered_electron_incoming_energy;
}

// Set the electroionization average scattered electron energy for a subshell
void ENDLDataContainer::setElectroionizationAverageScatteredElectronEnergy(
    const unsigned subshell,
    const std::vector<double>& average_scattered_electron_energy )
{
  // Make sure the average scattered electron energy is valid
  testPrecondition( average_scattered_electron_energy.size() == 
        d_electroionization_average_scattered_electron_incoming_energy[subshell].size() );
  testPreconditionValuesGreaterThanOrEqualToZero(
    average_scattered_electron_energy );

  d_electroionization_average_scattered_electron_energy[subshell] = 
    average_scattered_electron_energy;
}

// Set the electroionization incoming energy grid for the average recoil electron energy for a subshell
void ENDLDataContainer::setElectroionizationAverageRecoilElectronIncomingEnergy(
    const unsigned subshell,
    const std::vector<double>& average_recoil_electron_incoming_energy )
{
  // Make sure the incoming energy grid is valid
  testPreconditionEnergyGrid( average_recoil_electron_incoming_energy );

  d_electroionization_average_recoil_electron_incoming_energy[subshell] = 
    average_recoil_electron_incoming_energy;
}

// Set the electroionization average recoil electron energy for a subshell
void ENDLDataContainer::setElectroionizationAverageRecoilElectronEnergy(
    const unsigned subshell,
    const std::vector<double>& average_recoil_electron_energy )
{
  // Make sure the average recoil electron energy is valid
  testPrecondition( average_recoil_electron_energy.size() == 
        d_electroionization_average_recoil_electron_incoming_energy[subshell].size() );
  testPreconditionValuesGreaterThanOrEqualToZero(
    average_recoil_electron_energy );

  d_electroionization_average_recoil_electron_energy[subshell] = 
    average_recoil_electron_energy;
}

// Set the electroionization recoil energy grid for a subshell
void ENDLDataContainer::setElectroionizationRecoilEnergyGrid(
            const unsigned subshell, 
            const std::vector<double>& recoil_energy_grid )
{
  // Make sure the recoil energy is valid
  testPrecondition( Utility::Sort::isSortedAscending( 
                        recoil_energy_grid.begin(),
                        recoil_energy_grid.end() ) );

  d_electroionization_recoil_energy_grid[subshell]=recoil_energy_grid;
}

// Set the electroionization recoil energy for a subshell and energy bin
void ENDLDataContainer::setElectroionizationRecoilEnergyAtIncomingEnergy( 
            const unsigned subshell, 
            const double incoming_energy,
            const std::vector<double>& electroionization_recoil_energy )
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >=
                    d_electroionization_recoil_energy_grid[subshell].front() );
  testPrecondition( incoming_energy <=
                    d_electroionization_recoil_energy_grid[subshell].back() );
  // Make sure the electroionization recoil energy is valid
  testPreconditionValuesGreaterThanZero( electroionization_recoil_energy );

  d_electroionization_recoil_energy[subshell][ incoming_energy] =
    electroionization_recoil_energy;
}

// Set the electroionization recoil energy pdf for a subshell and energy bin
void ENDLDataContainer::setElectroionizationRecoilPDFAtIncomingEnergy(
            const unsigned subshell,
            const double incoming_energy,
            const std::vector<double>& electroionization_recoil_pdf )
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >=
                    d_electroionization_recoil_energy_grid[subshell].front() );
  testPrecondition( incoming_energy <=
                    d_electroionization_recoil_energy_grid[subshell].back() );
  // Make sure the electroionization recoil pdf is valid
  testPreconditionValuesGreaterThanZero( electroionization_recoil_pdf );

  d_electroionization_recoil_pdf[subshell][ incoming_energy] =
    electroionization_recoil_pdf;
}

// Set electroionization recoil energy for all incoming energies in a subshell
void ENDLDataContainer::setElectroionizationRecoilEnergy( 
    const unsigned subshell, 
    const std::map<double,std::vector<double> >& electroionization_recoil_energy )
{
  d_electroionization_recoil_energy[subshell] =
    electroionization_recoil_energy;
}

// Set electroionization recoil energy pdf for all incoming energies in a subshell
void ENDLDataContainer::setElectroionizationRecoilPDF(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& electroionization_recoil_pdf )
{
  d_electroionization_recoil_pdf[subshell] =
    electroionization_recoil_pdf;
}

//---------------------------------------------------------------------------//
// SET BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//

// Set the bremsstrahlung electron cross section energy grid
void ENDLDataContainer::setBremsstrahlungCrossSectionEnergyGrid( 
				       const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPreconditionEnergyGrid( energy_grid );

  d_bremsstrahlung_cross_section_energy_grid = energy_grid;
}

// Set the bremsstrahlung electron cross section 
void ENDLDataContainer::setBremsstrahlungCrossSection(
			 const std::vector<double>& bremsstrahlung_cross_section )
{
  // Make sure the bremsstrahlung cross section is valid
  testPrecondition( bremsstrahlung_cross_section.size() <= 
                    d_bremsstrahlung_cross_section_energy_grid.size() );
  testPreconditionValuesGreaterThanZero( bremsstrahlung_cross_section );
  
  d_bremsstrahlung_cross_section = bremsstrahlung_cross_section;
}

// Set the bremsstrahlung incoming electron energy grid for the average energy of the secondary photon
void ENDLDataContainer::setBremsstrahlungAveragePhotonIncomingEnergy(
    const std::vector<double>& bremsstrahlung_average_photon_incoming_energy )
{
  // Make sure the incoming energy grid is valid
  testPreconditionEnergyGrid( bremsstrahlung_average_photon_incoming_energy );

  d_bremsstrahlung_average_photon_incoming_energy = 
    bremsstrahlung_average_photon_incoming_energy;
}

// Set the bremsstrahlung average energy of the secondary photon
void ENDLDataContainer::setBremsstrahlungAveragePhotonEnergy(
    const std::vector<double>& bremsstrahlung_average_photon_energy )
{
  // Make sure the average photon energy is valid
  testPrecondition( bremsstrahlung_average_photon_energy.size() == 
        d_bremsstrahlung_average_photon_incoming_energy.size() );
  testPreconditionValuesGreaterThanZero(
    bremsstrahlung_average_photon_energy );

  d_bremsstrahlung_average_photon_energy = bremsstrahlung_average_photon_energy;
}

// Set the bremsstrahlung energy grid
void ENDLDataContainer::setBremsstrahlungPhotonEnergyGrid( 
				       const std::vector<double>& photon_energy_grid )
{
  // Make sure the energy grid is valid
  testPreconditionEnergyGrid( photon_energy_grid );

  d_bremsstrahlung_photon_energy_grid = photon_energy_grid;
}

// Set the bremsstrahlung photon energy for an incoming energy
void ENDLDataContainer::setBremsstrahlungPhotonEnergyAtIncomingEnergy(
		     const double incoming_energy,
		     const std::vector<double>&  bremsstrahlung_photon_energy )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >=
                    d_bremsstrahlung_photon_energy_grid.front() );
  testPrecondition( incoming_energy <=
                    d_bremsstrahlung_photon_energy_grid.back() );
  // Make sure the bremsstrahlung photon energies are valid
  testPreconditionValuesGreaterThanZero( bremsstrahlung_photon_energy );

  d_bremsstrahlung_photon_energy[incoming_energy] = 
    bremsstrahlung_photon_energy;
}

// Set the bremsstrahlung photon pdf for an incoming energy
void ENDLDataContainer::setBremsstrahlungPhotonPDFAtIncomingEnergy( 
			 const double incoming_energy,
			 const std::vector<double>& bremsstrahlung_photon_pdf )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >=
                    d_bremsstrahlung_photon_energy_grid.front() );
  testPrecondition( incoming_energy <=
                    d_bremsstrahlung_photon_energy_grid.back() );
  // Make sure the pdf is valid
  testPreconditionValuesGreaterThanZero( bremsstrahlung_photon_pdf );
  
  d_bremsstrahlung_photon_pdf[incoming_energy] = bremsstrahlung_photon_pdf;
}

// Set all the bremsstrahlung photon energy
void ENDLDataContainer::setBremsstrahlungPhotonEnergy(
    const std::map<double,std::vector<double> >&  bremsstrahlung_photon_energy )
{
  d_bremsstrahlung_photon_energy = bremsstrahlung_photon_energy;
}

// Set all the bremsstrahlung photon pdf
void ENDLDataContainer::setBremsstrahlungPhotonPDF( 
    const std::map<double,std::vector<double> >& bremsstrahlung_photon_pdf )
{
  d_bremsstrahlung_photon_pdf = bremsstrahlung_photon_pdf;
}

// Set the bremsstrahlung incoming electron energy grid for the average energy of the secondary electron
void ENDLDataContainer::setBremsstrahlungAverageElectronIncomingEnergy(
    const std::vector<double>& bremsstrahlung_average_electron_incoming_energy )
{
  // Make sure the incoming energy grid is valid
  testPreconditionEnergyGrid( bremsstrahlung_average_electron_incoming_energy );

  d_bremsstrahlung_average_electron_incoming_energy = 
    bremsstrahlung_average_electron_incoming_energy;
}

// Set the bremsstrahlung average energy of the secondary electron
void ENDLDataContainer::setBremsstrahlungAverageElectronEnergy(
    const std::vector<double>& bremsstrahlung_average_electron_energy )
{
  // Make sure the average electron energy is valid
  testPrecondition( bremsstrahlung_average_electron_energy.size() == 
        d_bremsstrahlung_average_electron_incoming_energy.size() );
  testPreconditionValuesGreaterThanZero( 
    bremsstrahlung_average_electron_energy );

  d_bremsstrahlung_average_electron_energy = 
    bremsstrahlung_average_electron_energy;
}

//---------------------------------------------------------------------------//
// SET ATOMIC EXCITAION DATA 
//---------------------------------------------------------------------------//

// Set the atomic excitation electron energy grid
void ENDLDataContainer::setAtomicExcitationEnergyGrid( 
				       const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPreconditionEnergyGrid( energy_grid );

  d_atomic_excitation_energy_grid = energy_grid;
}


// Set the atomic excitation electron cross section 
void ENDLDataContainer::setAtomicExcitationCrossSection(
			 const std::vector<double>& atomic_excitation_cross_section )
{
  // Make sure the atomic excitation cross section is valid
  testPrecondition( atomic_excitation_cross_section.size() <= 
                    d_atomic_excitation_energy_grid.size() );
  testPreconditionValuesGreaterThanOrEqualToZero( atomic_excitation_cross_section );
  
  d_atomic_excitation_cross_section = atomic_excitation_cross_section;
}

// Set the atomic excitation energy loss for an incoming energy
void ENDLDataContainer::setAtomicExcitationEnergyLoss(
		     const std::vector<double>&  atomic_excitation_energy_loss )
{
  // Make sure the atomic excitation energy loss are valid
  testPrecondition( atomic_excitation_energy_loss.size() <= 
                    d_atomic_excitation_energy_grid.size() );
  testPreconditionValuesGreaterThanZero( atomic_excitation_energy_loss );

  d_atomic_excitation_energy_loss = 
    atomic_excitation_energy_loss;
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_EvaluatedElectronDataContainer.cpp
//---------------------------------------------------------------------------//

