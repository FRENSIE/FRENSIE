//---------------------------------------------------------------------------//
//!
//! \file   Data_ElectronPhotonRelaxationDataContainer.cpp
//! \author Alex Robinson
//! \brief  The native electron-photon-relaxation data container class decl.
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
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Constructor (from saved archive)
ElectronPhotonRelaxationDataContainer::ElectronPhotonRelaxationDataContainer( 
		    const std::string& archive_name,
		    const Utility::ArchivableObject::ArchiveType archive_type )
{
  // Import the data in the archive - no way to use initializer list :(
  this->importData( archive_name, archive_type );
}

// Return the atomic number
unsigned ElectronPhotonRelaxationDataContainer::getAtomicNumber() const
{
  return d_atomic_number;
}

// Return the atomic subshells 
const std::set<unsigned>& 
ElectronPhotonRelaxationDataContainer::getSubshells() const
{
  return d_subshells;
}

// Return the subshell occupancies
double ElectronPhotonRelaxationDataContainer::getSubshellOccupancy(
					        const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != 
		    d_subshells.end() );
  
  return d_subshell_occupancies.find( subshell )->second;
}

// Return the subshell binding energies
double ElectronPhotonRelaxationDataContainer::getSubshellBindingEnergy(
						const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != 
		    d_subshells.end() );
  
  return d_subshell_binding_energies.find( subshell )->second;
}

// Return if there is relaxation data
bool ElectronPhotonRelaxationDataContainer::hasRelaxationData() const
{
  return d_relaxation_transitions.size() > 0;
}

// Return if the subshell has relaxation data
bool ElectronPhotonRelaxationDataContainer::hasSubshellRelaxationData( 
						const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );
  
  return d_relaxation_transitions.find( subshell ) != 
    d_relaxation_transitions.end();
}

// Return the number of transitions that can fill a subshell vacancy
unsigned ElectronPhotonRelaxationDataContainer::getSubshellRelaxationTransitions( 
						const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_relaxation_transitions.find( subshell )->second;
}

// Return the relaxation vacancies for a subshell
const std::vector<std::pair<unsigned,unsigned> >&
ElectronPhotonRelaxationDataContainer::getSubshellRelaxationVacancies( 
						const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_relaxation_vacancies.find( subshell )->second;
}

// Return the relaxation particle energies for a subshell
const std::vector<double>& 
ElectronPhotonRelaxationDataContainer::getSubshellRelaxationParticleEnergies(
					        const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_relaxation_particle_energies.find( subshell )->second;
}

// Return the relaxation probabilities for a subshell
const std::vector<double>& 
ElectronPhotonRelaxationDataContainer::getSubshellRelaxationProbabilities(
					        const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_relaxation_probabilities.find( subshell )->second;
}

// Return the Compton profile momentum grid for a subshell
const std::vector<double>& 
ElectronPhotonRelaxationDataContainer::getComptonProfileMomentumGrid() const
{
  return d_compton_profile_momentum_grid;
}

// Return the Compton profile for a subshell
const std::vector<double>& 
ElectronPhotonRelaxationDataContainer::getComptonProfile(
						const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != 
		    d_subshells.end() );

  return d_compton_profiles.find( subshell )->second;
}

// Return the occupancy number momentum grid for a subshell
const std::vector<double>& 
ElectronPhotonRelaxationDataContainer::getOccupancyNumberMomentumGrid() const
{
  return d_occupancy_number_momentum_grid;
}
  
// Return the occupancy number for a subshell
const std::vector<double>& 
ElectronPhotonRelaxationDataContainer::getOccupancyNumber(
					        const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );
  
  return d_occupancy_numbers.find( subshell )->second;
}

// Return the Waller-Hartree scattering function momentum grid
const std::vector<double>& 
ElectronPhotonRelaxationDataContainer::getWallerHartreeScatteringFunctionMomentumGrid() const
{
  return d_waller_hartree_scattering_function_momentum_grid;
}

// Return the Waller-Hartree scattering function
const std::vector<double>& 
ElectronPhotonRelaxationDataContainer::getWallerHartreeScatteringFunction() const
{
  return d_waller_hartree_scattering_function;
}
  
// Return the Waller-Hartree atomic form factor momentum grid
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getWallerHartreeAtomicFormFactorMomentumGrid() const
{
  return d_waller_hartree_atomic_form_factor_momentum_grid;
}

// Return the Waller-Hartree atomic form factor
const std::vector<double>& ElectronPhotonRelaxationDataContainer::getWallerHartreeAtomicFormFactor() const
{
  return d_waller_hartree_atomic_form_factor;
}

// Return the photon energy grid
const std::vector<double>& 
ElectronPhotonRelaxationDataContainer::getPhotonEnergyGrid() const
{
  return d_photon_energy_grid;
}

// Return the average heating numbers
const std::vector<double>& 
ElectronPhotonRelaxationDataContainer::getAveragePhotonHeatingNumbers() const
{
  return d_average_photon_heating_numbers;
}

// Return the Waller-Hartree (WH) incoherent photoncross section 
const std::vector<double>& 
ElectronPhotonRelaxationDataContainer::getWallerHartreeIncoherentCrossSection() const
{
  return d_waller_hartree_incoherent_cross_section;
}

// Return the WH incoherent photon cross section threshold energy bin index
unsigned
ElectronPhotonRelaxationDataContainer::getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex() const
{
  return d_waller_hartree_incoherent_cross_section_threshold_index;
}

// Return the impluse approx. (IA) incoherent photon cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getImpulseApproxIncoherentCrossSection() const
{
  return d_impulse_approx_incoherent_cross_section;
}

// Return the IA incoherent photon cross section threshold energy bin index
unsigned
ElectronPhotonRelaxationDataContainer::getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex() const
{
  return d_impulse_approx_incoherent_cross_section_threshold_index;
}

// Return the subshell Impulse approx. incoherent photon cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getImpulseApproxSubshellIncoherentCrossSection( 
					        const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_impulse_approx_subshell_incoherent_cross_sections.find( subshell )->second;
}

// Return the subshell IA incoherent photon cs threshold energy bin index
unsigned
ElectronPhotonRelaxationDataContainer::getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 
					        const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_impulse_approx_subshell_incoherent_cross_section_theshold_indices.find( subshell )->second;
}

// Return the Waller-Hartree coherent cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getWallerHartreeCoherentCrossSection() const
{
  return d_waller_hartree_coherent_cross_section;
}

// Return the Waller-Hartree coherent cs threshold energy bin index
unsigned
ElectronPhotonRelaxationDataContainer::getWallerHartreeCoherentCrossSectionThresholdEnergyIndex() const
{
  return d_waller_hartree_coherent_cross_section_threshold_index;
}

// Return the pair production cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getPairProductionCrossSection() const
{
  return d_pair_production_cross_section;
}

// Return the pair production cross section threshold energy bin index
unsigned ElectronPhotonRelaxationDataContainer::getPairProductionCrossSectionThresholdEnergyIndex() const
{
  return d_pair_production_cross_section_threshold_index;
}

// Return the Photoelectric effect cross section
const std::vector<double>& ElectronPhotonRelaxationDataContainer::getPhotoelectricCrossSection() const
{
  return d_photoelectric_cross_section;
}

// Return the Photoelectric effect cross section theshold energy bin index
unsigned ElectronPhotonRelaxationDataContainer::getPhotoelectricCrossSectionThresholdEnergyIndex() const
{
  return d_photoelectric_cross_section_threshold_index;
}

// Return the Photoelectric effect cross section for a subshell
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getSubshellPhotoelectricCrossSection( 
						const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_subshell_photoelectric_cross_sections.find( subshell )->second;
}

// Return the subshell Photoelectric effect cross section threshold index
unsigned
ElectronPhotonRelaxationDataContainer::getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 
					        const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_subshell_photoelectric_cross_section_threshold_indices.find( subshell )->second;
}

// Return the Waller-Hartree total cross section
const std::vector<double>& ElectronPhotonRelaxationDataContainer::getWallerHartreeTotalCrossSection() const
{
  return d_waller_hartree_total_cross_section;
}

// Return the impulse approx. total cross section
const std::vector<double>& ElectronPhotonRelaxationDataContainer::getImpulseApproxTotalCrossSection() const
{
  return d_impulse_approx_total_cross_section;
}

// Set the atomic number
void ElectronPhotonRelaxationDataContainer::setAtomicNumber( 
						 const unsigned atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0 );
  testPrecondition( atomic_number <= 100 );

  d_atomic_number = atomic_number;
}
  
// Set the atomic subshells
void ElectronPhotonRelaxationDataContainer::setSubshells( 
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

// Set the subshell occupancy
void ElectronPhotonRelaxationDataContainer::setSubshellOccupancy( 
						       const unsigned subshell,
						       const double occupancy )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the subshell occupancy is valid
  testPrecondition( occupancy > 0.0 );

  d_subshell_occupancies[subshell] = occupancy;
}

// Set the subshell binding energy
void ElectronPhotonRelaxationDataContainer::setSubshellBindingEnergy(
						  const unsigned subshell,
						  const double binding_energy )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the subshell binding energy is valid
  testPrecondition( binding_energy > 0.0 );

  d_subshell_binding_energies[subshell] = binding_energy;
}

// Set the number of transitions that can fill a subshell vacancy
void ElectronPhotonRelaxationDataContainer::setSubshellRelaxationTransitions( 
						   const unsigned subshell,
						   const unsigned transitions )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the number of transitions is valid
  testPrecondition( transitions > 0 );
  
  d_relaxation_transitions[subshell] = transitions;
}

// Set the relaxation vacancies for a subshell
void ElectronPhotonRelaxationDataContainer::setSubshellRelaxationVacancies( 
       const unsigned subshell,
       const std::vector<std::pair<unsigned,unsigned> >& relaxation_vacancies )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the relaxation vacancies are valid
  testPrecondition( relaxation_vacancies.size() ==
		    d_relaxation_transitions.find( subshell )->second );

  d_relaxation_vacancies[subshell] = relaxation_vacancies;
}

// Set the relaxation particle energies for a subshell
void ElectronPhotonRelaxationDataContainer::setSubshellRelaxationParticleEnergies(
		      const unsigned subshell,
		      const std::vector<double>& relaxation_particle_energies )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the relaxation particle energies are valid
  testPrecondition( relaxation_particle_energies.size() ==
		    d_relaxation_transitions.find( subshell )->second );

  d_relaxation_particle_energies[subshell] = relaxation_particle_energies;
}

// Set the relaxation probabilities for a subshell
void ElectronPhotonRelaxationDataContainer::setSubshellRelaxationProbabilities( 
			  const unsigned subshell,
			  const std::vector<double>& relaxation_probabilities )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the relaxation cdf is valid
  testPrecondition( relaxation_probabilities.size() ==
		    d_relaxation_transitions.find( subshell )->second );
  testPrecondition( std::find_if( relaxation_probabilities.begin(),
				  relaxation_probabilities.end(),
				  isValueLessThanOrEqualToZero ) ==
		    relaxation_probabilities.end() );
  
  d_relaxation_probabilities[subshell] = relaxation_probabilities;
}
  
// Set the Compton profile momentum grid for a subshell
void ElectronPhotonRelaxationDataContainer::setComptonProfileMomentumGrid( 
		     const std::vector<double>& compton_profile_momentum_grid )
{
  // Make sure the momentum grid is valid
  testPrecondition( compton_profile_momentum_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( 
				       compton_profile_momentum_grid.begin(),
				       compton_profile_momentum_grid.end() ) );
  testPrecondition( compton_profile_momentum_grid.front() == -1.0 );

  d_compton_profile_momentum_grid = compton_profile_momentum_grid;
}
  
// Set the Compton profile for a subshell
void ElectronPhotonRelaxationDataContainer::setComptonProfile( 
				   const unsigned subshell,
				   const std::vector<double>& compton_profile )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the compton_profile is valid
  testPrecondition( compton_profile.size() ==
		    d_compton_profile_momentum_grid.size() );
  testPrecondition( std::find_if( compton_profile.begin(),
				  compton_profile.end(),
				  isValueLessThanOrEqualToZero ) ==
		    compton_profile.end() );

  d_compton_profiles[subshell] = compton_profile;
}
  
// Set the occupancy number momentum grid for a subshell
void ElectronPhotonRelaxationDataContainer::setOccupancyNumberMomentumGrid( 
		    const std::vector<double>& occupancy_number_momentum_grid )
{
  // Make sure the occupancy number momentum grid is valid
  testPrecondition( occupancy_number_momentum_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( 
					occupancy_number_momentum_grid.begin(),
					occupancy_number_momentum_grid.end()));
  testPrecondition( occupancy_number_momentum_grid.front() == -1.0 );

  d_occupancy_number_momentum_grid = occupancy_number_momentum_grid;
}
  
// Set the occupancy number for a subshell
void ElectronPhotonRelaxationDataContainer::setOccupancyNumber( 
				  const unsigned subshell,
				  const std::vector<double>& occupancy_number )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the occupancy number is valid
  testPrecondition( occupancy_number.size() ==
		    d_occupancy_number_momentum_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( occupancy_number.begin(),
						      occupancy_number.end()));
  testPrecondition( occupancy_number.front() == 0.0 );
  testPrecondition( occupancy_number.back() <= 1.0 );

  d_occupancy_numbers[subshell] = occupancy_number;
}

// Set the Waller-Hartree scattering function momentum grid
void ElectronPhotonRelaxationDataContainer::setWallerHartreeScatteringFunctionMomentumGrid(
				     const std::vector<double>& momentum_grid )
{
  // Make sure the momentum grid is valid
  testPrecondition( momentum_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( momentum_grid.begin(),
						      momentum_grid.end() ) );
  testPrecondition( std::find_if( momentum_grid.begin(),
				  momentum_grid.end(),
				  isValueLessThanOrEqualToZero ) ==
		    momentum_grid.end() );
  
  d_waller_hartree_scattering_function_momentum_grid = momentum_grid;
}
  
// Set the Waller-Hartree scattering function 
void ElectronPhotonRelaxationDataContainer::setWallerHartreeScatteringFunction(
			       const std::vector<double>& scattering_function )
{
  // Make sure the scattering function is valid
  testPrecondition( scattering_function.size() == 
		    d_waller_hartree_scattering_function_momentum_grid.size());
  testPrecondition( Utility::Sort::isSortedAscending( 
						 scattering_function.begin(),
						 scattering_function.end() ) );
  testPrecondition( scattering_function.front() >= 0.0 );
  testPrecondition( scattering_function.back() == d_atomic_number );

  d_waller_hartree_scattering_function = scattering_function;
}

// Set the Waller-Hartree atomic form factor momentum grid
void ElectronPhotonRelaxationDataContainer::setWallerHartreeAtomicFormFactorMomentumGrid(
				     const std::vector<double>& momentum_grid )
{
  // Make sure the momentum grid is valid
  testPrecondition( momentum_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( momentum_grid.begin(),
						      momentum_grid.end() ) );
  testPrecondition( std::find_if( momentum_grid.begin(),
				  momentum_grid.end(),
				  isValueLessThanOrEqualToZero ) ==
		    momentum_grid.end() );
  
  d_waller_hartree_atomic_form_factor_momentum_grid = momentum_grid;
}
  
// Set the Waller-Hartree atomic form factor 
void ElectronPhotonRelaxationDataContainer::setWallerHartreeAtomicFormFactor(
			        const std::vector<double>& atomic_form_factor )
{
  // Make sure the atomic form factor is valid
  testPrecondition( atomic_form_factor.size() ==
		    d_waller_hartree_atomic_form_factor_momentum_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending( 
						 atomic_form_factor.rbegin(),
						 atomic_form_factor.rend() ) );
  testPrecondition( atomic_form_factor.front() == d_atomic_number );
  testPrecondition( atomic_form_factor.back() >= 0.0 );

  d_waller_hartree_atomic_form_factor = atomic_form_factor;
}
  
// Set the photon energy grid
void ElectronPhotonRelaxationDataContainer::setPhotonEnergyGrid( 
				       const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );
  testPrecondition( energy_grid.front() > 0.0 );

  d_photon_energy_grid = energy_grid;
}

// Set the average photon heating numbers
void ElectronPhotonRelaxationDataContainer::setAveragePhotonHeatingNumbers( 
				   const std::vector<double>& heating_numbers )
{
  // Make sure the heating numbers are valid
  testPrecondition( heating_numbers.size() == d_photon_energy_grid.size() );
  testPrecondition( std::find_if( heating_numbers.begin(),
				  heating_numbers.end(),
				  isValueLessThanOrEqualToZero ) ==
		    heating_numbers.end() );

  d_average_photon_heating_numbers = heating_numbers;
}
  
// Set the incoherent photon cross section using Waller-Hartree (WH) theory
void ElectronPhotonRelaxationDataContainer::setWallerHartreeIncoherentCrossSection(
			  const std::vector<double>& incoherent_cross_section )
{
  // Make sure the incoherent cross section is valid
  testPrecondition( incoherent_cross_section.size() <= 
		    d_photon_energy_grid.size() );
  testPrecondition( std::find_if( incoherent_cross_section.begin(),
				  incoherent_cross_section.end(),
				  isValueLessThanOrEqualToZero ) ==
		    incoherent_cross_section.end() );
  
  d_waller_hartree_incoherent_cross_section = incoherent_cross_section;
}

// Set the WH incoherent cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(
						         const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( d_waller_hartree_incoherent_cross_section.size() + index ==
		    d_photon_energy_grid.size() );
  
  d_waller_hartree_incoherent_cross_section_threshold_index = index;
}
  
// Set the incoherent photon cross section using the impulse approx. (IA)
void ElectronPhotonRelaxationDataContainer::setImpulseApproxIncoherentCrossSection(
			  const std::vector<double>& incoherent_cross_section )
{
  // Make sure the incoherent cross section is valid
  testPrecondition( incoherent_cross_section.size() <= 
		    d_photon_energy_grid.size() );
  testPrecondition( std::find_if( incoherent_cross_section.begin(),
				  incoherent_cross_section.end(),
				  isValueLessThanOrEqualToZero ) ==
		    incoherent_cross_section.end() );
  
  d_impulse_approx_incoherent_cross_section = incoherent_cross_section;
}

// Set the IA incoherent photon cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(
							 const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( d_impulse_approx_incoherent_cross_section.size() + index ==
		    d_photon_energy_grid.size() );
  
  d_impulse_approx_incoherent_cross_section_threshold_index = index;
}

// Set the IA subshell incoherent photon cross section
void ElectronPhotonRelaxationDataContainer::setImpulseApproxSubshellIncoherentCrossSection(
			  const unsigned subshell,
			  const std::vector<double>& incoherent_cross_section )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoherent cross section is valid
  testPrecondition( incoherent_cross_section.size() <= 
		    d_photon_energy_grid.size() );
  testPrecondition( std::find_if( incoherent_cross_section.begin(),
				  incoherent_cross_section.end(),
				  isValueLessThanOrEqualToZero ) ==
		    incoherent_cross_section.end() );
  
  d_impulse_approx_subshell_incoherent_cross_sections[subshell] = 
    incoherent_cross_section;
}

// Set the IA subshell incoherent photon cs threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(
						       const unsigned subshell,
						       const unsigned index )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the threshold index is valid
  testPrecondition( d_impulse_approx_subshell_incoherent_cross_sections.find( subshell ) !=
		    d_impulse_approx_subshell_incoherent_cross_sections.end());
  remember( const std::vector<double>& incoherent_cross_section = 
	    d_impulse_approx_subshell_incoherent_cross_sections.find( subshell )->second );
  testPrecondition( incoherent_cross_section.size() + index ==
		    d_photon_energy_grid.size() );
  
  d_impulse_approx_subshell_incoherent_cross_section_theshold_indices[subshell] =
    index;
}
  
// Set the WH coherent cross section 
void ElectronPhotonRelaxationDataContainer::setWallerHartreeCoherentCrossSection(
			    const std::vector<double>& coherent_cross_section )
{
  // Make sure the coherent cross section is valid
  testPrecondition( coherent_cross_section.size() <= 
		    d_photon_energy_grid.size() );
  testPrecondition( std::find_if( coherent_cross_section.begin(),
				  coherent_cross_section.end(),
				  isValueLessThanOrEqualToZero ) ==
		    coherent_cross_section.end() );
  
  d_waller_hartree_coherent_cross_section = coherent_cross_section;
}

// Set the WH coherent cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setWallerHartreeCoherentCrossSectionThresholdEnergyIndex(
							 const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( d_waller_hartree_coherent_cross_section.size() + index ==
		    d_photon_energy_grid.size() );
  
  d_waller_hartree_coherent_cross_section_threshold_index = index;
}
  
// Set the pair production cross section
void ElectronPhotonRelaxationDataContainer::setPairProductionCrossSection(
		     const std::vector<double>& pair_production_cross_section )
{
  // Make sure the pair production cross section is valid
  testPrecondition( pair_production_cross_section.size() <=
		    d_photon_energy_grid.size() );
  testPrecondition( std::find_if( pair_production_cross_section.begin(),
				  pair_production_cross_section.end(),
				  isValueLessThanOrEqualToZero ) ==
		    pair_production_cross_section.end() );

  d_pair_production_cross_section = pair_production_cross_section;
}

// Set the pair production cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setPairProductionCrossSectionThresholdEnergyIndex( 
							 const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( d_pair_production_cross_section.size() + index ==
		    d_photon_energy_grid.size() );
  
  d_pair_production_cross_section_threshold_index = index;
}

// Set the Photoelectric effect cross section
void ElectronPhotonRelaxationDataContainer::setPhotoelectricCrossSection(
		       const std::vector<double>& photoelectric_cross_section )
{
  // Make sure the photoelectric cross section is valid
  testPrecondition( photoelectric_cross_section.size() <=
		    d_photon_energy_grid.size() );
  
  d_photoelectric_cross_section = photoelectric_cross_section;
}

// Set the Photoelectric effect cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setPhotoelectricCrossSectionThresholdEnergyIndex(
							 const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( d_photoelectric_cross_section.size() + index ==
		    d_photon_energy_grid.size() );
  
  d_photoelectric_cross_section_threshold_index = index;
}
  
// Set the Photoelectric effect cross section for a subshell
void ElectronPhotonRelaxationDataContainer::setSubshellPhotoelectricCrossSection( 
		       const unsigned subshell,
		       const std::vector<double>& photoelectric_cross_section )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the photoelectric cross section is valid
  testPrecondition( photoelectric_cross_section.size() <= 
		    d_photon_energy_grid.size() );
  testPrecondition( std::find_if( photoelectric_cross_section.begin(),
				  photoelectric_cross_section.end(),
				  isValueLessThanOrEqualToZero ) ==
		    photoelectric_cross_section.end() );
  
  d_subshell_photoelectric_cross_sections[subshell] = 
    photoelectric_cross_section;
}
  
// Set the subshell Photoelectric effect cross section threshold index
void ElectronPhotonRelaxationDataContainer::setSubshellPhotoelectricCrossSectionThresholdEnergyIndex(
						       const unsigned subshell,
						       const unsigned index )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the index is valid
  testPrecondition( d_subshell_photoelectric_cross_sections.find( subshell ) !=
		    d_subshell_photoelectric_cross_sections.end() );
  remember( const std::vector<double> photoelectric_cross_section = 
	    d_subshell_photoelectric_cross_sections.find( subshell )->second );
  testPrecondition( photoelectric_cross_section.size() + index ==
		    d_photon_energy_grid.size() );
  
  d_subshell_photoelectric_cross_section_threshold_indices[subshell] = index;
}

// Set the Waller-Hartree total cross section
void ElectronPhotonRelaxationDataContainer::setWallerHartreeTotalCrossSection( 
			       const std::vector<double>& total_cross_section )
{
  // Make sure the total cross section is valid
  testPrecondition( total_cross_section.size() == d_photon_energy_grid.size());
  testPrecondition( std::find_if( total_cross_section.begin(),
				  total_cross_section.end(),
				  isValueLessThanOrEqualToZero ) ==
		    total_cross_section.end() );
  
  d_waller_hartree_total_cross_section = total_cross_section;
}

// Set the impulse approx. total cross section
void ElectronPhotonRelaxationDataContainer::setImpulseApproxTotalCrossSection(
			       const std::vector<double>& total_cross_section )
{
  // Make sure the total cross section is valid
  testPrecondition( total_cross_section.size() == d_photon_energy_grid.size());
  testPrecondition( std::find_if( total_cross_section.begin(),
				  total_cross_section.end(),
				  isValueLessThanOrEqualToZero ) ==
		    total_cross_section.end() );
  
  d_impulse_approx_total_cross_section = total_cross_section;
}

// Test if a value is less than or equal to zero
bool ElectronPhotonRelaxationDataContainer::isValueLessThanOrEqualToZero( 
							   const double value )
{
  return value <= 0.0;
}

// Test if a value is less than zero
bool ElectronPhotonRelaxationDataContainer::isValueLessThanZero( 
							   const double value )
{
  return value < 0.0;
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ElectronPhotonRelaxationDataContainer.cpp
//---------------------------------------------------------------------------//
