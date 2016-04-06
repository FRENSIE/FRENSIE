//---------------------------------------------------------------------------//
//!
//! \file   Data_EvaluatedElectronDataContainer.cpp
//! \author Luke Kersting
//! \brief  The native evaluated electron data container class def.
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
#include "Data_EvaluatedElectronDataContainer.hpp"
#include "Data_ENDLDataContainerHelpers.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Constructor (from saved archive)
EvaluatedElectronDataContainer::EvaluatedElectronDataContainer( 
		    const std::string& archive_name,
		    const Utility::ArchivableObject::ArchiveType archive_type )
{
  // Import the data in the archive - no way to use initializer list :(
  this->importData( archive_name, archive_type );
}

// Return the atomic number
unsigned EvaluatedElectronDataContainer::getAtomicNumber() const
{
  return d_atomic_number;
}

// Return the atomic subshells 
const std::set<unsigned>& 
EvaluatedElectronDataContainer::getSubshells() const
{
  return d_subshells;
}

/*
//---------------------------------------------------------------------------//
// GET RELAXATION DATA
//---------------------------------------------------------------------------//

// Return the atomic subshells 
const std::set<unsigned>& 
EvaluatedElectronDataContainer::getSubshells() const
{
  return d_subshells;
}

// Return the subshell occupancies
double EvaluatedElectronDataContainer::getSubshellOccupancy(
					        const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != 
		    d_subshells.end() );
  
  return d_subshell_occupancies.find( subshell )->second;
}

// Return the subshell binding energies
double EvaluatedElectronDataContainer::getSubshellBindingEnergy(
						const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != 
		    d_subshells.end() );
  
  return d_subshell_binding_energies.find( subshell )->second;
}

// Return if there is relaxation data
bool EvaluatedElectronDataContainer::hasRelaxationData() const
{
  return d_relaxation_transitions.size() > 0;
}

// Return if the subshell has relaxation data
bool EvaluatedElectronDataContainer::hasSubshellRelaxationData( 
						const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );
  
  return d_relaxation_transitions.find( subshell ) != 
    d_relaxation_transitions.end();
}

// Return the number of transitions that can fill a subshell vacancy
unsigned EvaluatedElectronDataContainer::getSubshellRelaxationTransitions( 
						const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_relaxation_transitions.find( subshell )->second;
}

// Return the relaxation vacancies for a subshell
const std::vector<std::pair<unsigned,unsigned> >&
EvaluatedElectronDataContainer::getSubshellRelaxationVacancies( 
						const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_relaxation_vacancies.find( subshell )->second;
}

// Return the relaxation particle energies for a subshell
const std::vector<double>& 
EvaluatedElectronDataContainer::getSubshellRelaxationParticleEnergies(
					        const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_relaxation_particle_energies.find( subshell )->second;
}

// Return the relaxation probabilities for a subshell
const std::vector<double>& 
EvaluatedElectronDataContainer::getSubshellRelaxationProbabilities(
					        const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_relaxation_probabilities.find( subshell )->second;
}
*/

//---------------------------------------------------------------------------//
// GET ELASTIC DATA 
//---------------------------------------------------------------------------//

// Return the elastic energy grid
const std::vector<double>& 
EvaluatedElectronDataContainer::getElasticEnergyGrid() const
{
  return d_elastic_energy_grid;
}

// Return the elastic transport electron cross section
const std::vector<double>&
EvaluatedElectronDataContainer::getElasticTransportCrossSection() const
{
  return d_elastic_transport_cross_section;
}

// Return the cutoff elastic electron cross section
const std::vector<double>& 
EvaluatedElectronDataContainer::getCutoffElasticCrossSection() const
{
  return d_cutoff_elastic_cross_section;
}

// Return the cutoff elastic average energy to the residual atom incoming energy grid
const std::vector<double>& 
EvaluatedElectronDataContainer::getCutoffElasticResidualIncomingEnergy() const
{
  return d_cutoff_elastic_residual_incoming_energy;;
}

// Return the cutoff elastic average energy to the residual atom
const std::vector<double>& 
EvaluatedElectronDataContainer::getCutoffElasticResidualEnergy() const
{
  return d_cutoff_elastic_residual_energy;
}

// Return the cutoff elastic average energy to the scattered electron incoming energy grid
const std::vector<double>& 
EvaluatedElectronDataContainer::getCutoffElasticScatteredElectronIncomingEnergy() const
{
  return d_cutoff_elastic_scattered_electron_incoming_energy;
}

// Return the cutoff elastic average energy to the scattered electron
const std::vector<double>& 
EvaluatedElectronDataContainer::getCutoffElasticScatteredElectronEnergy() const
{
  return d_cutoff_elastic_scattered_electron_energy;
}

// Return the cutoff elastic angular energy grid
const std::vector<double>& 
EvaluatedElectronDataContainer::getCutoffElasticAngularEnergyGrid() const
{
  return d_cutoff_elastic_angular_energy_grid;
}

// Return the elastic angles for an incoming energy
const std::vector<double>& 
EvaluatedElectronDataContainer::getCutoffElasticAngles(
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
EvaluatedElectronDataContainer::getCutoffElasticPDF(
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
EvaluatedElectronDataContainer::getTotalElasticCrossSection() const
{
  return d_total_elastic_cross_section;
}

/*
// Return the screened Rutherford elastic electron cross section
const std::vector<double>& 
EvaluatedElectronDataContainer::getScreenedRutherfordElasticCrossSection() const
{
  return d_screened_rutherford_elastic_cross_section;
}

// Return the screened Rutherford elastic normalization constant 
const std::vector<double>& 
EvaluatedElectronDataContainer::getScreenedRutherfordNormalizationConstant() const
{
  return d_screened_rutherford_normalization_constant;
}

// Return Moliere's screening constant 
const std::vector<double>& 
EvaluatedElectronDataContainer::getMoliereScreeningConstant() const
{
  return d_moliere_screening_constant;
}
*/

//---------------------------------------------------------------------------//
// GET ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//

// Return the electroionization cross section energy grid for a subshell
const std::vector<double>& 
EvaluatedElectronDataContainer::getElectroionizationCrossSectionEnergyGrid( 
                            const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_electroionization_subshell_cross_section_energy_grid.find( subshell )->second;
}

// Return the electroionization electron cross section for a subshell
const std::vector<double>& 
EvaluatedElectronDataContainer::getElectroionizationCrossSection( 
    const unsigned subshell ) const
{
  return d_electroionization_subshell_cross_section.find( subshell )->second;
}


// Return the electroionization incoming energy grid for the average scattered electron energy for a subshell
const std::vector<double>& 
EvaluatedElectronDataContainer::getElectroionizationAverageScatteredElectronIncomingEnergy( 
                           const unsigned subshell ) const
{
  return d_electroionization_average_scattered_electron_incoming_energy.find( subshell )->second;
}

// Return the electroionization average scattered electron energy for a subshell
const std::vector<double>& 
EvaluatedElectronDataContainer::getElectroionizationAverageScatteredElectronEnergy( 
                           const unsigned subshell ) const
{
  return d_electroionization_average_scattered_electron_energy.find( subshell )->second;
}

// Return the electroionization incoming energy grid for the average recoil electron energy for a subshell
const std::vector<double>& 
EvaluatedElectronDataContainer::getElectroionizationAverageRecoilElectronIncomingEnergy( 
                           const unsigned subshell ) const
{
  return d_electroionization_average_recoil_electron_incoming_energy.find( subshell )->second;
}

// Return the electroionization average recoil electron energy for a subshell
const std::vector<double>& 
EvaluatedElectronDataContainer::getElectroionizationAverageRecoilElectronEnergy( 
                           const unsigned subshell ) const
{
  return d_electroionization_average_recoil_electron_energy.find( subshell )->second;
}

// Return the electroionization recoil energy grid for a subshell
const std::vector<double>& 
EvaluatedElectronDataContainer::getElectroionizationRecoilEnergyGrid( 
                            const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_electroionization_recoil_energy_grid.find( subshell )->second;
}

// Return the electroionization recoil energy for a subshell and energy bin
const std::vector<double>& 
EvaluatedElectronDataContainer::getElectroionizationRecoilEnergy( 
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
EvaluatedElectronDataContainer::getElectroionizationRecoilPDF( 
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
EvaluatedElectronDataContainer::getBremsstrahlungCrossSectionEnergyGrid() const
{
  return d_bremsstrahlung_cross_section_energy_grid;
}

// Return the bremsstrahlung electron cross section
const std::vector<double>& 
EvaluatedElectronDataContainer::getBremsstrahlungCrossSection() const
{
  return d_bremsstrahlung_cross_section;
}

// Return the bremsstrahlung incoming electron energy grid for the average energy of the secondary photon
const std::vector<double>& 
EvaluatedElectronDataContainer::getBremsstrahlungAveragePhotonIncomingEnergy() const
{
  return d_bremsstrahlung_average_photon_incoming_energy;
}

// Return the bremsstrahlung average energy of the secondary photon
const std::vector<double>& 
EvaluatedElectronDataContainer::getBremsstrahlungAveragePhotonEnergy() const
{
  return d_bremsstrahlung_average_photon_energy;
}

// Return the bremsstrahlung photon energy grid
const std::vector<double>& 
EvaluatedElectronDataContainer::getBremsstrahlungPhotonEnergyGrid() const
{
  return d_bremsstrahlung_photon_energy_grid;
}

// Return the bremsstrahlung for an incoming energy
const std::vector<double>& 
EvaluatedElectronDataContainer::getBremsstrahlungPhotonEnergy(
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
EvaluatedElectronDataContainer::getBremsstrahlungPhotonPDF(
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
EvaluatedElectronDataContainer::getBremsstrahlungAverageElectronIncomingEnergy() const
{
  return d_bremsstrahlung_average_electron_incoming_energy;
}

// Return the bremsstrahlung average energy of the secondary electron
const std::vector<double>& 
EvaluatedElectronDataContainer::getBremsstrahlungAverageElectronEnergy() const
{
  return d_bremsstrahlung_average_electron_energy;
}

//---------------------------------------------------------------------------//
// GET ATOMIC EXCITAION DATA 
//---------------------------------------------------------------------------//

// Return the atomic excitation electron energy grid
const std::vector<double>& 
EvaluatedElectronDataContainer::getAtomicExcitationEnergyGrid() const
{
  return d_atomic_excitation_energy_grid;
}

// Return the atomic excitation electron cross section
const std::vector<double>& 
EvaluatedElectronDataContainer::getAtomicExcitationCrossSection() const
{
  return d_atomic_excitation_cross_section;
}

// Return the atomic excitation energy loss
const std::vector<double>& 
EvaluatedElectronDataContainer::getAtomicExcitationEnergyLoss() const
{
  return d_atomic_excitation_energy_loss;
}

// Set the atomic number
void EvaluatedElectronDataContainer::setAtomicNumber( 
						 const unsigned atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0 );
  testPrecondition( atomic_number <= 100 );

  d_atomic_number = atomic_number;
}

// Set the atomic subshells
void EvaluatedElectronDataContainer::setSubshells( 
				       const std::set<unsigned>& subshells )
{
  // Make sure the subshells are valid
  testPrecondition( subshells.size() > 0 );
  testPreconditionValuesGreaterThanZero( subshells );

  d_subshells = subshells;
}

/*
//---------------------------------------------------------------------------//
// SET RELAXATION DATA
//---------------------------------------------------------------------------//

// Set the atomic subshells
void EvaluatedElectronDataContainer::setSubshells( 
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
void EvaluatedElectronDataContainer::setSubshellOccupancy( 
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
void EvaluatedElectronDataContainer::setSubshellBindingEnergy(
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
void EvaluatedElectronDataContainer::setSubshellRelaxationTransitions( 
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
void EvaluatedElectronDataContainer::setSubshellRelaxationVacancies( 
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
void EvaluatedElectronDataContainer::setSubshellRelaxationParticleEnergies(
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
void EvaluatedElectronDataContainer::setSubshellRelaxationProbabilities( 
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
*/
//---------------------------------------------------------------------------//
// SET ELASTIC DATA 
//---------------------------------------------------------------------------//

// Set the elastic energy grid
void EvaluatedElectronDataContainer::setElasticEnergyGrid( 
				       const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPreconditionEnergyGrid( energy_grid );

  d_elastic_energy_grid = energy_grid;
}

// Set the elastic transport cross section 
void EvaluatedElectronDataContainer::setElasticTransportCrossSection(
			 const std::vector<double>& elastic_transport_cross_section )
{
  // Make sure the elastic transport cross section is valid
  testPrecondition( elastic_transport_cross_section.size() <= 
    d_elastic_energy_grid.size() );
  testPreconditionValuesGreaterThanZero( elastic_transport_cross_section );
  
  d_elastic_transport_cross_section = elastic_transport_cross_section;
}

// Set the cutoff elastic electron cross section 
void EvaluatedElectronDataContainer::setCutoffElasticCrossSection(
			 const std::vector<double>& cutoff_elastic_cross_section )
{
  // Make sure the cutoff elastic cross section is valid
  testPrecondition( cutoff_elastic_cross_section.size() <= 
    d_elastic_energy_grid.size() );
  testPreconditionValuesGreaterThanZero( cutoff_elastic_cross_section );
  
  d_cutoff_elastic_cross_section = cutoff_elastic_cross_section;
}

// Set the cutoff elastic average energy to the residual atom incoming energy grid
void EvaluatedElectronDataContainer::setCutoffElasticResidualIncomingEnergy( 
    const std::vector<double>& residual_incoming_energy )
{
  // Make sure residual incoming energy grid is valid
  testPreconditionEnergyGrid( residual_incoming_energy );

  d_cutoff_elastic_residual_incoming_energy = residual_incoming_energy;
}

// Set the cutoff elastic average energy to the residual atom
void EvaluatedElectronDataContainer::setCutoffElasticResidualEnergy( 
    const std::vector<double>& residual_energy )
{
  // Make sure the cutoff elastic average energy to the residual atom is valid
  testPrecondition( residual_energy.size() == 
                    d_cutoff_elastic_residual_incoming_energy.size() );
  testPreconditionValuesGreaterThanOrEqualToZero( residual_energy );

  d_cutoff_elastic_residual_energy = residual_energy;
}

// Set the cutoff elastic average energy of the scattered electron incoming energy grid
void EvaluatedElectronDataContainer::setCutoffElasticScatteredElectronIncomingEnergy( 
    const std::vector<double>& scattered_electron_incoming_energy )
{
  // Make sure scattered electron energy grid is valid
  testPreconditionEnergyGrid( scattered_electron_incoming_energy );

  d_cutoff_elastic_scattered_electron_incoming_energy = 
    scattered_electron_incoming_energy;
}

// Set the cutoff elastic average energy of the scattered electron
void EvaluatedElectronDataContainer::setCutoffElasticScatteredElectronEnergy(
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
void EvaluatedElectronDataContainer::setCutoffElasticAngularEnergyGrid( 
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
void EvaluatedElectronDataContainer::setCutoffElasticAnglesAtEnergy(
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
void EvaluatedElectronDataContainer::setCutoffElasticPDFAtEnergy( 
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
void EvaluatedElectronDataContainer::setCutoffElasticAngles(
    const std::map<double,std::vector<double> >& cutoff_elastic_angles )
{
  d_cutoff_elastic_angles = cutoff_elastic_angles;
}

// Set the total elastic pdf 
void EvaluatedElectronDataContainer::setCutoffElasticPDF( 
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf )
{
  d_cutoff_elastic_pdf = cutoff_elastic_pdf;
}

// Set the total elastic electron cross section 
void EvaluatedElectronDataContainer::setTotalElasticCrossSection(
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
void EvaluatedElectronDataContainer::setScreenedRutherfordElasticCrossSection(
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
void EvaluatedElectronDataContainer::setScreenedRutherfordNormalizationConstant(
		     const std::vector<double>& screened_rutherford_normalization_constant )
{
  // Make sure the screened_rutherford_normalization_constants are valid
  testPreconditionValuesGreaterThanOrEqualToZero(
    screened_rutherford_normalization_constant );

  d_screened_rutherford_normalization_constant = 
    screened_rutherford_normalization_constant;
}

// Set Moliere's screening constant 
void EvaluatedElectronDataContainer::setMoliereScreeningConstant( 
			 const std::vector<double>& moliere_screening_constant )
{
  d_moliere_screening_constant = moliere_screening_constant;
}
*/

//---------------------------------------------------------------------------//
// SET ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//

// Set the electroionization energy grid
void EvaluatedElectronDataContainer::setElectroionizationCrossSectionEnergyGrid(
    const unsigned subshell,
    const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPreconditionEnergyGrid( energy_grid );

  d_electroionization_subshell_cross_section_energy_grid[subshell] = 
    energy_grid;
}

// Set the electroionization electron cross section 
void EvaluatedElectronDataContainer::setElectroionizationCrossSection(
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
void EvaluatedElectronDataContainer::setElectroionizationAverageScatteredElectronIncomingEnergy(
    const unsigned subshell,
    const std::vector<double>& average_scattered_electron_incoming_energy )
{
  // Make sure the incoming energy grid is valid
  testPreconditionEnergyGrid( average_scattered_electron_incoming_energy );

  d_electroionization_average_scattered_electron_incoming_energy[subshell] = 
    average_scattered_electron_incoming_energy;
}

// Set the electroionization average scattered electron energy for a subshell
void EvaluatedElectronDataContainer::setElectroionizationAverageScatteredElectronEnergy(
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
void EvaluatedElectronDataContainer::setElectroionizationAverageRecoilElectronIncomingEnergy(
    const unsigned subshell,
    const std::vector<double>& average_recoil_electron_incoming_energy )
{
  // Make sure the incoming energy grid is valid
  testPreconditionEnergyGrid( average_recoil_electron_incoming_energy );

  d_electroionization_average_recoil_electron_incoming_energy[subshell] = 
    average_recoil_electron_incoming_energy;
}

// Set the electroionization average recoil electron energy for a subshell
void EvaluatedElectronDataContainer::setElectroionizationAverageRecoilElectronEnergy(
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
void EvaluatedElectronDataContainer::setElectroionizationRecoilEnergyGrid(
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
void EvaluatedElectronDataContainer::setElectroionizationRecoilEnergyAtIncomingEnergy( 
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
void EvaluatedElectronDataContainer::setElectroionizationRecoilPDFAtIncomingEnergy(
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
void EvaluatedElectronDataContainer::setElectroionizationRecoilEnergy( 
    const unsigned subshell, 
    const std::map<double,std::vector<double> >& electroionization_recoil_energy )
{
  d_electroionization_recoil_energy[subshell] =
    electroionization_recoil_energy;
}

// Set electroionization recoil energy pdf for all incoming energies in a subshell
void EvaluatedElectronDataContainer::setElectroionizationRecoilPDF(
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
void EvaluatedElectronDataContainer::setBremsstrahlungCrossSectionEnergyGrid( 
				       const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPreconditionEnergyGrid( energy_grid );

  d_bremsstrahlung_cross_section_energy_grid = energy_grid;
}

// Set the bremsstrahlung electron cross section 
void EvaluatedElectronDataContainer::setBremsstrahlungCrossSection(
			 const std::vector<double>& bremsstrahlung_cross_section )
{
  // Make sure the bremsstrahlung cross section is valid
  testPrecondition( bremsstrahlung_cross_section.size() <= 
                    d_bremsstrahlung_cross_section_energy_grid.size() );
  testPreconditionValuesGreaterThanZero( bremsstrahlung_cross_section );
  
  d_bremsstrahlung_cross_section = bremsstrahlung_cross_section;
}

// Set the bremsstrahlung incoming electron energy grid for the average energy of the secondary photon
void EvaluatedElectronDataContainer::setBremsstrahlungAveragePhotonIncomingEnergy(
    const std::vector<double>& bremsstrahlung_average_photon_incoming_energy )
{
  // Make sure the incoming energy grid is valid
  testPreconditionEnergyGrid( bremsstrahlung_average_photon_incoming_energy );

  d_bremsstrahlung_average_photon_incoming_energy = 
    bremsstrahlung_average_photon_incoming_energy;
}

// Set the bremsstrahlung average energy of the secondary photon
void EvaluatedElectronDataContainer::setBremsstrahlungAveragePhotonEnergy(
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
void EvaluatedElectronDataContainer::setBremsstrahlungPhotonEnergyGrid( 
				       const std::vector<double>& photon_energy_grid )
{
  // Make sure the energy grid is valid
  testPreconditionEnergyGrid( photon_energy_grid );

  d_bremsstrahlung_photon_energy_grid = photon_energy_grid;
}

// Set the bremsstrahlung photon energy for an incoming energy
void EvaluatedElectronDataContainer::setBremsstrahlungPhotonEnergyAtIncomingEnergy(
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
void EvaluatedElectronDataContainer::setBremsstrahlungPhotonPDFAtIncomingEnergy( 
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
void EvaluatedElectronDataContainer::setBremsstrahlungPhotonEnergy(
    const std::map<double,std::vector<double> >&  bremsstrahlung_photon_energy )
{
  d_bremsstrahlung_photon_energy = bremsstrahlung_photon_energy;
}

// Set all the bremsstrahlung photon pdf
void EvaluatedElectronDataContainer::setBremsstrahlungPhotonPDF( 
    const std::map<double,std::vector<double> >& bremsstrahlung_photon_pdf )
{
  d_bremsstrahlung_photon_pdf = bremsstrahlung_photon_pdf;
}

// Set the bremsstrahlung incoming electron energy grid for the average energy of the secondary electron
void EvaluatedElectronDataContainer::setBremsstrahlungAverageElectronIncomingEnergy(
    const std::vector<double>& bremsstrahlung_average_electron_incoming_energy )
{
  // Make sure the incoming energy grid is valid
  testPreconditionEnergyGrid( bremsstrahlung_average_electron_incoming_energy );

  d_bremsstrahlung_average_electron_incoming_energy = 
    bremsstrahlung_average_electron_incoming_energy;
}

// Set the bremsstrahlung average energy of the secondary electron
void EvaluatedElectronDataContainer::setBremsstrahlungAverageElectronEnergy(
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
void EvaluatedElectronDataContainer::setAtomicExcitationEnergyGrid( 
				       const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPreconditionEnergyGrid( energy_grid );

  d_atomic_excitation_energy_grid = energy_grid;
}


// Set the atomic excitation electron cross section 
void EvaluatedElectronDataContainer::setAtomicExcitationCrossSection(
			 const std::vector<double>& atomic_excitation_cross_section )
{
  // Make sure the atomic excitation cross section is valid
  testPrecondition( atomic_excitation_cross_section.size() <= 
                    d_atomic_excitation_energy_grid.size() );
  testPreconditionValuesGreaterThanOrEqualToZero( atomic_excitation_cross_section );
  
  d_atomic_excitation_cross_section = atomic_excitation_cross_section;
}

// Set the atomic excitation energy loss for an incoming energy
void EvaluatedElectronDataContainer::setAtomicExcitationEnergyLoss(
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

