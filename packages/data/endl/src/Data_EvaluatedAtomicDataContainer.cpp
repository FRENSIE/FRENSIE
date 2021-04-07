//---------------------------------------------------------------------------//
//!
//! \file   Data_EvaluatedAtomicDataContainer.cpp
//! \author Luke Kersting
//! \brief  The native evaluated atomic data container class def.
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
// GET RELAXATION DATA
//---------------------------------------------------------------------------//

// Return the atomic subshells
const std::set<unsigned>&
ENDLDataContainer::getSubshells() const
{
  return d_subshells;
}

// Return the number of electrons for a subshell
const double ENDLDataContainer::getSubshellOccupancy(
    const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_subshell_occupancies.find( subshell )->second;
}

// Return the binding energy for a subshell
const double ENDLDataContainer::getSubshellBindingEnergy(
    const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_subshell_binding_energies.find( subshell )->second;
}

// Return the kinetic energy for a subshell
const double ENDLDataContainer::getSubshellKineticEnergy(
    const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_subshell_kinetic_energies.find( subshell )->second;
}

// Return the average radius for a subshell
const double ENDLDataContainer::getSubshellAverageRadius(
    const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_subshell_average_radii.find( subshell )->second;
}

// Return the radiative level width for a subshell
const double ENDLDataContainer::getSubshellRadiativeLevel(
    const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_subshell_radiative_levels.find( subshell )->second;
}

// Return the non radiative level for a subshell
const double ENDLDataContainer::getSubshellNonRadiativeLevel(
    const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_subshell_non_radiative_levels.find( subshell )->second;
}

// Return the average energy to the residual atom per initial vacancy
const double ENDLDataContainer::getLocalDepositionPerInitialVacancy(
    const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_subshell_local_depositions.find( subshell )->second;
}

// Return the average number of photons per initial vacancy
const double ENDLDataContainer::getAveragePhotonsPerInitialVacancy(
    const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_subshell_average_photon_numbers.find( subshell )->second;
}

// Return the average energy of photons per initial vacancy
const double
ENDLDataContainer::getAveragePhotonEnergyPerInitialVacancy(
    const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_subshell_average_photon_energies.find( subshell )->second;
}

// Return the average number of electrons per initial vacancy
const double ENDLDataContainer::getAverageElectronsPerInitialVacancy(
    const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_subshell_average_electron_numbers.find( subshell )->second;
}

// Return the average energy of electrons per initial vacancy
const double
ENDLDataContainer::getAverageElectronEnergyPerInitialVacancy(
    const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_subshell_average_electron_energies.find( subshell )->second;
}

// Check if a subshell has radiative transitions
bool ENDLDataContainer::hasRadiativeTransitions( const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_radiative_transition_probabilities.find( subshell ) !=
    d_radiative_transition_probabilities.end();
}

// Return the radiative transition probability
const std::map<unsigned,double>&
ENDLDataContainer::getRadiativeTransitionProbability(
    const unsigned subshell ) const
{
  // Make sure the subshells are valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );
  testPrecondition( this->hasRadiativeTransitions( subshell ) );

  return d_radiative_transition_probabilities.find( subshell )->second;
}

// Return the radiative transition energy
const std::map<unsigned,double>&
ENDLDataContainer::getRadiativeTransitionEnergy(
    const unsigned subshell ) const
{
  // Make sure the subshells are valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );
  testPrecondition( this->hasRadiativeTransitions( subshell ) );

  return d_radiative_transition_energies.find( subshell )->second;
}

// Check if a subshell has non radiative transitions
bool ENDLDataContainer::hasNonRadiativeTransitions( const unsigned subshell ) const
{
  // Make sure the subshells are valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_non_radiative_transition_probabilities.find( subshell ) !=
    d_non_radiative_transition_probabilities.end();
}

// Return the non radiative transition probability
const std::map<unsigned,std::map<unsigned,double> >&
ENDLDataContainer::getNonRadiativeTransitionProbability(
    const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );
  testPrecondition( this->hasNonRadiativeTransitions( subshell ) );

  return d_non_radiative_transition_probabilities.find( subshell )->second;
}

// Return the non radiative transition energy
const std::map<unsigned,std::map<unsigned,double> >&
ENDLDataContainer::getNonRadiativeTransitionEnergy(
    const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_non_radiative_transition_energies.find( subshell )->second;
}

//---------------------------------------------------------------------------//
// SET RELAXATION DATA
//---------------------------------------------------------------------------//

// Set the atomic subshells
void ENDLDataContainer::setSubshells(
    const std::set<unsigned>& subshells )
{
  // Make sure the subshells are valid
  testPrecondition( subshells.size() > 0 );
  testPrecondition( std::find_if( subshells.begin(),
				  subshells.end(),
				  isValueLessThanOrEqualToZero ) ==
		    subshells.end() );

  d_subshells = subshells;
}

// Set the number of electrons in subshells
void ENDLDataContainer::setSubshellOccupancy(
    const std::map<unsigned,double>& number_of_electrons )
{
  d_subshell_occupancies = number_of_electrons;
}

// Set the binding energy in subshells
void ENDLDataContainer::setSubshellBindingEnergy(
    const std::map<unsigned,double>& binding_energies )
{
  d_subshell_binding_energies = binding_energies;
}

// Set the kinetic energy in subshells
void ENDLDataContainer::setSubshellKineticEnergy(
    const std::map<unsigned,double>& kinetic_energies )
{
  d_subshell_kinetic_energies = kinetic_energies;
}

// Set the average radius in subshells
void ENDLDataContainer::setSubshellAverageRadius(
    const std::map<unsigned,double>& average_radii )
{
  d_subshell_average_radii = average_radii;
}

// Set the radiative level width in subshells
void ENDLDataContainer::setSubshellRadiativeLevel(
    const std::map<unsigned,double>& radiative_levels )
{
  d_subshell_radiative_levels = radiative_levels;
}

// Set the non radiative level in subshells
void ENDLDataContainer::setSubshellNonRadiativeLevel(
    const std::map<unsigned,double>& non_radiative_levels )
{
  d_subshell_non_radiative_levels = non_radiative_levels;
}

// Set the average energy to the residual atom per initial vacancy
void ENDLDataContainer::setLocalDepositionPerInitialVacancy(
    const std::map<unsigned,double>& local_depositions )
{
  d_subshell_local_depositions = local_depositions;
}

// Set the average number of photons per initial vacancy
void ENDLDataContainer::setAveragePhotonsPerInitialVacancy(
    const std::map<unsigned,double>& average_particle_numbers )
{
  d_subshell_average_photon_numbers = average_particle_numbers;
}

// Set the average energy of photons per initial vacancy
void ENDLDataContainer::setAveragePhotonEnergyPerInitialVacancy(
    const std::map<unsigned,double>& average_particle_energies )
{
  d_subshell_average_photon_energies = average_particle_energies;
}

// Set the average number of electrons per initial vacancy
void ENDLDataContainer::setAverageElectronsPerInitialVacancy(
    const std::map<unsigned,double>& average_particle_numbers )
{
  d_subshell_average_electron_numbers = average_particle_numbers;
}

// Set the average energy of electrons per initial vacancy
void ENDLDataContainer::setAverageElectronEnergyPerInitialVacancy(
    const std::map<unsigned,double>& average_particle_energies )
{
  d_subshell_average_electron_energies = average_particle_energies;
}

// Set the radiative transition probability
void ENDLDataContainer::setRadiativeTransitionProbability(
    const unsigned subshell,
    const std::map<unsigned,double>&
        radiative_transition_probability )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  d_radiative_transition_probabilities[subshell] =
    radiative_transition_probability;
}

// Set the radiative transition energy
void ENDLDataContainer::setRadiativeTransitionEnergy(
    const unsigned subshell,
    const std::map<unsigned,double>&
        radiative_transition_energy )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  d_radiative_transition_energies[subshell] =
    radiative_transition_energy;
}

// Set the non radiative transition probability
void ENDLDataContainer::setNonRadiativeTransitionProbability(
    const unsigned subshell,
    std::map<unsigned,std::map<unsigned,double> >&
        non_radiative_transition_probability )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  d_non_radiative_transition_probabilities[subshell] =
    non_radiative_transition_probability;
}

// Set the non radiative transition energy
void ENDLDataContainer::setNonRadiativeTransitionEnergy(
    const unsigned subshell,
    std::map<unsigned,std::map<unsigned,double> >&
        non_radiative_transition_energy )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  d_non_radiative_transition_energies[subshell] =
    non_radiative_transition_energy;
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ENDLDataContainer.cpp
//---------------------------------------------------------------------------//

