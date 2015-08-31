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

// Return the elastic cutoff angle
double EvaluatedElectronDataContainer::getCutoffAngle() const
{
  return d_cutoff_angle;
}

// Return the elastic angular energy grid
const std::vector<double>& 
EvaluatedElectronDataContainer::getElasticAngularEnergyGrid() const
{
  return d_angular_energy_grid;
}
/*
// Return the number of discrete angles for an incoming energy
unsigned EvaluatedElectronDataContainer::getNumberOfDiscreteAngles( 
                            const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );

  return d_number_of_discrete_angles.find( incoming_energy )->second;
}
*/
// Return the elastic angles for an incoming energy
const std::vector<double>& 
EvaluatedElectronDataContainer::getAnalogElasticAngles(
					        const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );

  return d_analog_elastic_angles.find( incoming_energy )->second;
}

// Return the elastic pdf for an incoming energy
const std::vector<double>& 
EvaluatedElectronDataContainer::getAnalogElasticPDF(
					        const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );

  return d_analog_elastic_pdf.find( incoming_energy )->second;
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

// Return the moment preserving elastic discrete angles for an incoming energy
const std::vector<double>& 
EvaluatedElectronDataContainer::getMomentPreservingElasticDiscreteAngles(
					        const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );

  return d_moment_preserving_elastic_discrete_angles.find( incoming_energy )->second;
}

// Return the moment preserving elastic weights for an incoming energy
const std::vector<double>& 
EvaluatedElectronDataContainer::getMomentPreservingElasticWeights(
					        const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );

  return d_moment_preserving_elastic_weights.find( incoming_energy )->second;
}

// Return the electroionization energy grid for a subshell
const std::vector<double>& 
EvaluatedElectronDataContainer::getElectroionizationEnergyGrid( 
                            const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_electroionization_energy_grid.find( subshell )->second;
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
            d_electroionization_energy_grid.find( subshell )->second.front() );
  testPrecondition( 
            incoming_energy <= 
            d_electroionization_energy_grid.find( subshell )->second.back() );

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
            d_electroionization_energy_grid.find( subshell )->second.front() );
  testPrecondition( 
            incoming_energy <= 
            d_electroionization_energy_grid.find( subshell )->second.back() );

  return d_electroionization_recoil_pdf.find( subshell )->second.find( incoming_energy )->second;
}

// Return the bremsstrahlung energy grid
const std::vector<double>& 
EvaluatedElectronDataContainer::getBremsstrahlungEnergyGrid() const
{
  return d_bremsstrahlung_energy_grid;
}

// Return the bremsstrahlung for an incoming energy
const std::vector<double>& 
EvaluatedElectronDataContainer::getBremsstrahlungPhotonEnergy(
					        const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_bremsstrahlung_energy_grid.front() );
  testPrecondition( incoming_energy <= d_bremsstrahlung_energy_grid.back() );

  return d_bremsstrahlung_photon_energy.find( incoming_energy )->second;
}

// Return the bremsstrahlung photon pdf for an incoming energy
const std::vector<double>& 
EvaluatedElectronDataContainer::getBremsstrahlungPhotonPDF(
					        const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_bremsstrahlung_energy_grid.front() );
  testPrecondition( incoming_energy <= d_bremsstrahlung_energy_grid.back() );

  return d_bremsstrahlung_photon_pdf.find( incoming_energy )->second;
}

// Return the atomic excitation energy grid
const std::vector<double>& 
EvaluatedElectronDataContainer::getAtomicExcitationEnergyGrid() const
{
  return d_atomic_excitation_energy_grid;
}

// Return the atomic excitation energy loss
const std::vector<double>& 
EvaluatedElectronDataContainer::getAtomicExcitationEnergyLoss() const
{
  return d_atomic_excitation_energy_loss;
}

// Return the electron energy grid
const std::vector<double>& 
EvaluatedElectronDataContainer::getElectronEnergyGrid() const
{
  return d_electron_energy_grid;
}
// Return the cutoff elastic electron cross section
const std::vector<double>& 
EvaluatedElectronDataContainer::getCutoffElasticCrossSection() const
{
  return d_cutoff_elastic_cross_section;
}

// Return the cutoff elastic cross section threshold energy bin index
unsigned
EvaluatedElectronDataContainer::getCutoffElasticCrossSectionThresholdEnergyIndex() const
{
  return d_cutoff_elastic_cross_section_threshold_index;
}
// Return the screened Rutherford elastic electron cross section
const std::vector<double>& 
EvaluatedElectronDataContainer::getScreenedRutherfordElasticCrossSection() const
{
  return d_screened_rutherford_elastic_cross_section;
}

// Return the screened Rutherford elastic cross section threshold energy bin index
unsigned
EvaluatedElectronDataContainer::getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex() const
{
  return d_screened_rutherford_elastic_cross_section_threshold_index;
}
// Return the total elastic electron cross section
const std::vector<double>& 
EvaluatedElectronDataContainer::getTotalElasticCrossSection() const
{
  return d_total_elastic_cross_section;
}

// Return the total elastic cross section threshold energy bin index
unsigned
EvaluatedElectronDataContainer::getTotalElasticCrossSectionThresholdEnergyIndex() const
{
  return d_total_elastic_cross_section_threshold_index;
}
/*
// Return the hard elastic electron cross section
const std::vector<double>& 
EvaluatedElectronDataContainer::getHardElasticCrossSection() const
{
  return d_hard_elastic_cross_section;
}

// Return the hard elastic cross section threshold energy bin index
unsigned
EvaluatedElectronDataContainer::getHardElasticCrossSectionThresholdEnergyIndex() const
{
  return d_hard_elastic_cross_section_threshold_index;
}
*/
// Return the Moment Preserving (MP) elastic electron cross section
const std::vector<double>& 
EvaluatedElectronDataContainer::getMomentPreservingCrossSection() const
{
  return d_moment_preserving_elastic_cross_section;
}

// Return the MP elastic cross section threshold energy bin index
unsigned
EvaluatedElectronDataContainer::getMomentPreservingCrossSectionThresholdEnergyIndex() const
{
  return d_moment_preserving_elastic_cross_section_threshold_index;
}

// Return the electroionization electron cross section for a subshell
const std::vector<double>& 
EvaluatedElectronDataContainer::getElectroionizationCrossSection( 
    const unsigned subshell ) const
{
  return d_electroionization_subshell_cross_section.find( subshell )->second;
}

// Return the electroionization cross section threshold energy bin index for a subshell
unsigned
EvaluatedElectronDataContainer::getElectroionizationCrossSectionThresholdEnergyIndex( 
    const unsigned subshell ) const
{
  return d_electroionization_subshell_cross_section_threshold_index.find( subshell )->second;
}

// Return the bremsstrahlung electron cross section
const std::vector<double>& 
EvaluatedElectronDataContainer::getBremsstrahlungCrossSection() const
{
  return d_bremsstrahlung_cross_section;
}

// Return the bremsstrahlung cross section threshold energy bin index
unsigned
EvaluatedElectronDataContainer::getBremsstrahlungCrossSectionThresholdEnergyIndex() const
{
  return d_bremsstrahlung_cross_section_threshold_index;
}

// Return the atomic excitation electron cross section
const std::vector<double>& 
EvaluatedElectronDataContainer::getAtomicExcitationCrossSection() const
{
  return d_atomic_excitation_cross_section;
}

// Return the atomic excitation cross section threshold energy bin index
unsigned
EvaluatedElectronDataContainer::getAtomicExcitationCrossSectionThresholdEnergyIndex() const
{
  return d_atomic_excitation_cross_section_threshold_index;
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
  testPrecondition( std::find_if( subshells.begin(),
                    subshells.end(),
                    isValueLessThanOrEqualToZero ) == subshells.end() );

  d_subshells = subshells;
}

// Set the elastic cutoff angle
void EvaluatedElectronDataContainer::setCutoffAngle( 
                         const double cutoff_angle )
{
  // Make sure the elastic cutoff angle is valid
  testPrecondition( cutoff_angle >= 0.0 );
  testPrecondition( cutoff_angle < 2.0 );

  d_cutoff_angle = cutoff_angle;
}

// Set the elastic angular energy grid
void EvaluatedElectronDataContainer::setElasticAngularEnergyGrid( 
				       const std::vector<double>& angular_energy_grid )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition( 
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
			                              angular_energy_grid.end() ) );

  testPrecondition( std::find_if( angular_energy_grid.begin(),
                                  angular_energy_grid.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    angular_energy_grid.end() );

  d_angular_energy_grid = angular_energy_grid;
}
/*
// Set the number of discrete angles for an incoming energy
void EvaluatedElectronDataContainer::setNumberOfDiscreteAngles( 
             const double incoming_energy,
             const unsigned number_of_discrete_angles )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );
  // Make sure the number of discrete angles is valid
  testPrecondition( number_of_discrete_angles > 0 );
  
  d_number_of_discrete_angles[incoming_energy] = number_of_discrete_angles;
}
*/
// Set the total elastic angles for an incoming energy
void EvaluatedElectronDataContainer::setAnalogElasticAnglesAtEnergy(
    const double incoming_energy,
    const std::vector<double>& analog_elastic_angles )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );
  // Make sure the elastic angles are valid
  testPrecondition( std::find_if( analog_elastic_angles.begin(),
                                  analog_elastic_angles.end(),
                                  isValueLessThanMinusOne ) ==
                    analog_elastic_angles.end() );
  testPrecondition( std::find_if( analog_elastic_angles.begin(),
                                  analog_elastic_angles.end(),
                                  isValueGreaterThanOne ) ==
                    analog_elastic_angles.end() );

  d_analog_elastic_angles[incoming_energy] = analog_elastic_angles;
}

// Set the total elastic pdf for an incoming energy
void EvaluatedElectronDataContainer::setAnalogElasticPDFAtEnergy( 
    const double incoming_energy,
    const std::vector<double>& analog_elastic_pdf )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );
  // Make sure the weight is valid
  testPrecondition( std::find_if( analog_elastic_pdf.begin(),
                                  analog_elastic_pdf.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    analog_elastic_pdf.end() );
  
  d_analog_elastic_pdf[incoming_energy] = analog_elastic_pdf;
}
// Set the total elastic angles
void EvaluatedElectronDataContainer::setAnalogElasticAngles(
    const std::map<double,std::vector<double> >& analog_elastic_angles )
{
  d_analog_elastic_angles = analog_elastic_angles;
}

// Set the total elastic pdf 
void EvaluatedElectronDataContainer::setAnalogElasticPDF( 
    const std::map<double,std::vector<double> >& analog_elastic_pdf )
{
  d_analog_elastic_pdf = analog_elastic_pdf;
}

// Set the screened Rutherford elastic normalization constant 
void EvaluatedElectronDataContainer::setScreenedRutherfordNormalizationConstant(
		     const std::vector<double>& screened_rutherford_normalization_constant )
{
  // Make sure the screened_rutherford_normalization_constants are valid
  testPrecondition( std::find_if( screened_rutherford_normalization_constant.begin(),
                                  screened_rutherford_normalization_constant.end(),
                                  isValueLessThanZero ) ==
                    screened_rutherford_normalization_constant.end() );

  d_screened_rutherford_normalization_constant = 
    screened_rutherford_normalization_constant;
}

// Set Moliere's screening constant 
void EvaluatedElectronDataContainer::setMoliereScreeningConstant( 
			 const std::vector<double>& moliere_screening_constant )
{
  d_moliere_screening_constant = moliere_screening_constant;
}

// Set the moment preserving elastic discrete angles for an incoming energy
void EvaluatedElectronDataContainer::setMomentPreservingElasticDiscreteAngles(
		     const double incoming_energy,
		     const std::vector<double>& moment_preserving_elastic_discrete_angles )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );
  // Make sure the moment preserving elastic discrete angles are valid
 /* testPrecondition( moment_preserving_elastic_discrete_angles.size() ==
               d_number_of_discrete_angles.find( incoming_energy )->second );*/
  testPrecondition( std::find_if( moment_preserving_elastic_discrete_angles.begin(),
                                  moment_preserving_elastic_discrete_angles.end(),
                                  isValueLessThanMinusOne ) ==
                    moment_preserving_elastic_discrete_angles.end() );
  testPrecondition( std::find_if( moment_preserving_elastic_discrete_angles.begin(),
                                  moment_preserving_elastic_discrete_angles.end(),
                                  isValueGreaterThanOne ) ==
                    moment_preserving_elastic_discrete_angles.end() );

  d_moment_preserving_elastic_discrete_angles[incoming_energy] = 
        moment_preserving_elastic_discrete_angles;
}

// Set the moment preserving elastic weights for an incoming energy
void EvaluatedElectronDataContainer::setMomentPreservingElasticWeights( 
			 const double incoming_energy,
			 const std::vector<double>& moment_preserving_elastic_weights )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );
  // Make sure the weight is valid
  /*testPrecondition( moment_preserving_elastic_weights.size() ==
               d_number_of_discrete_angles.find( incoming_energy )->second );*/
  testPrecondition( std::find_if( moment_preserving_elastic_weights.begin(),
                                  moment_preserving_elastic_weights.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    moment_preserving_elastic_weights.end() );
  testPrecondition( std::find_if( moment_preserving_elastic_weights.begin(),
                                  moment_preserving_elastic_weights.end(),
                                  isValueGreaterThanOne ) ==
                    moment_preserving_elastic_weights.end() );
  
  d_moment_preserving_elastic_weights[incoming_energy] = moment_preserving_elastic_weights;
}

// Set the electroionization energy grid for a subshell
void EvaluatedElectronDataContainer::setElectroionizationEnergyGrid(
            const unsigned subshell, 
            const std::vector<double>& electroionization_energy_grid )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  testPrecondition( Utility::Sort::isSortedAscending( 
                        electroionization_energy_grid.begin(),
                        electroionization_energy_grid.end() ) );

  d_electroionization_energy_grid[subshell]=electroionization_energy_grid;
}

// Set the electroionization recoil energy for a subshell and energy bin
void EvaluatedElectronDataContainer::setElectroionizationRecoilEnergyAtIncomingEnergy( 
            const unsigned subshell, 
            const double incoming_energy,
            const std::vector<double>& electroionization_recoil_energy )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_electroionization_energy_grid[subshell].front() );
  testPrecondition( incoming_energy <= d_electroionization_energy_grid[subshell].back() );
  // Make sure the electroionization recoil energy is valid
  testPrecondition( std::find_if( electroionization_recoil_energy.begin(),
                                  electroionization_recoil_energy.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    electroionization_recoil_energy.end() );

  d_electroionization_recoil_energy[subshell][ incoming_energy] =
    electroionization_recoil_energy;
}

// Set the electroionization recoil energy pdf for a subshell and energy bin
void EvaluatedElectronDataContainer::setElectroionizationRecoilPDFAtIncomingEnergy(
            const unsigned subshell,
            const double incoming_energy,
            const std::vector<double>& electroionization_recoil_pdf )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_electroionization_energy_grid[subshell].front() );
  testPrecondition( incoming_energy <= d_electroionization_energy_grid[subshell].back() );
  // Make sure the electroionization recoil pdf is valid
  testPrecondition( std::find_if( electroionization_recoil_pdf.begin(),
                                  electroionization_recoil_pdf.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    electroionization_recoil_pdf.end() );

  d_electroionization_recoil_pdf[subshell][ incoming_energy] =
    electroionization_recoil_pdf;
}

// Set electroionization recoil energy for all incoming energies in a subshell
void EvaluatedElectronDataContainer::setElectroionizationRecoilEnergy( 
    const unsigned subshell, 
    const std::map<double,std::vector<double> >& electroionization_recoil_energy )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  d_electroionization_recoil_energy[subshell] =
    electroionization_recoil_energy;
}

// Set electroionization recoil energy pdf for all incoming energies in a subshell
void EvaluatedElectronDataContainer::setElectroionizationRecoilPDF(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& electroionization_recoil_pdf )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  d_electroionization_recoil_pdf[subshell] =
    electroionization_recoil_pdf;
}

// Set the bremsstrahlung energy grid
void EvaluatedElectronDataContainer::setBremsstrahlungEnergyGrid( 
				       const std::vector<double>& bremsstrahlung_energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( 
        Utility::Sort::isSortedAscending( bremsstrahlung_energy_grid.begin(),
			                              bremsstrahlung_energy_grid.end() ) );

  testPrecondition( bremsstrahlung_energy_grid.front() > 0.0 );

  d_bremsstrahlung_energy_grid = bremsstrahlung_energy_grid;
}

// Set the bremsstrahlung photon energy for an incoming energy
void EvaluatedElectronDataContainer::setBremsstrahlungPhotonEnergyAtIncomingEnergy(
		     const double incoming_energy,
		     const std::vector<double>&  bremsstrahlung_photon_energy )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >= d_bremsstrahlung_energy_grid.front() );
  testPrecondition( incoming_energy <= d_bremsstrahlung_energy_grid.back() );
  // Make sure the bremsstrahlung photon energies are valid
  testPrecondition( std::find_if( bremsstrahlung_photon_energy.begin(),
                                  bremsstrahlung_photon_energy.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    bremsstrahlung_photon_energy.end() );

  d_bremsstrahlung_photon_energy[incoming_energy] = 
    bremsstrahlung_photon_energy;
}

// Set the bremsstrahlung photon pdf for an incoming energy
void EvaluatedElectronDataContainer::setBremsstrahlungPhotonPDFAtIncomingEnergy( 
			 const double incoming_energy,
			 const std::vector<double>& bremsstrahlung_photon_pdf )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >= d_bremsstrahlung_energy_grid.front() );
  testPrecondition( incoming_energy <= d_bremsstrahlung_energy_grid.back() );
  // Make sure the pdf is valid
  testPrecondition( std::find_if( bremsstrahlung_photon_pdf.begin(),
                                  bremsstrahlung_photon_pdf.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    bremsstrahlung_photon_pdf.end() );
  
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

// Set the atomic excitation energy grid
void EvaluatedElectronDataContainer::setAtomicExcitationEnergyGrid( 
				       const std::vector<double>& atomic_excitation_energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( Utility::Sort::isSortedAscending( 
                        atomic_excitation_energy_grid.begin(),
                        atomic_excitation_energy_grid.end() ) );

  testPrecondition( atomic_excitation_energy_grid.front() > 0.0 );

  d_atomic_excitation_energy_grid = atomic_excitation_energy_grid;
}

// Set the atomic excitation energy loss for an incoming energy
void EvaluatedElectronDataContainer::setAtomicExcitationEnergyLoss(
		     const std::vector<double>&  atomic_excitation_energy_loss )
{
  // Make sure the atomic excitation energy loss are valid
  testPrecondition( std::find_if( atomic_excitation_energy_loss.begin(),
                                  atomic_excitation_energy_loss.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    atomic_excitation_energy_loss.end() );

  d_atomic_excitation_energy_loss = 
    atomic_excitation_energy_loss;
}

// Set the electron energy grid
void EvaluatedElectronDataContainer::setElectronEnergyGrid( 
				       const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.back() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						                              energy_grid.end() ) );
  testPrecondition( energy_grid.front() > 0.0 );

  d_electron_energy_grid = energy_grid;
}

// Set the cutoff elastic electron cross section 
void EvaluatedElectronDataContainer::setCutoffElasticCrossSection(
			 const std::vector<double>& cutoff_elastic_cross_section )
{
  // Make sure the cutoff elastic cross section is valid
  testPrecondition( cutoff_elastic_cross_section.size() <= 
                    d_electron_energy_grid.size() );
  testPrecondition( std::find_if( cutoff_elastic_cross_section.begin(),
                                  cutoff_elastic_cross_section.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    cutoff_elastic_cross_section.end() );
  
  d_cutoff_elastic_cross_section = cutoff_elastic_cross_section;
}

// Set the cutoff elastic cross section threshold energy bin index
void EvaluatedElectronDataContainer::setCutoffElasticCrossSectionThresholdEnergyIndex(
						        const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( 
        d_cutoff_elastic_cross_section.size() + index ==
        d_electron_energy_grid.size() );
  
 d_cutoff_elastic_cross_section_threshold_index = index;
}

// Set the screened rutherford elastic electron cross section 
void EvaluatedElectronDataContainer::setScreenedRutherfordElasticCrossSection(
			 const std::vector<double>& screened_rutherford_elastic_cross_section )
{
  // Make sure the screened rutherford elastic cross section is valid
  testPrecondition( screened_rutherford_elastic_cross_section.size() <= 
                    d_electron_energy_grid.size() );
  testPrecondition( std::find_if( screened_rutherford_elastic_cross_section.begin(),
                                  screened_rutherford_elastic_cross_section.end(),
                                  isValueLessThanZero ) ==
                    screened_rutherford_elastic_cross_section.end() );
  
  d_screened_rutherford_elastic_cross_section = screened_rutherford_elastic_cross_section;
}

// Set the screened rutherford elastic cross section threshold energy bin index
void EvaluatedElectronDataContainer::setScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(
						        const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( 
        d_screened_rutherford_elastic_cross_section.size() + index ==
        d_electron_energy_grid.size() );
  
 d_screened_rutherford_elastic_cross_section_threshold_index = index;
}

// Set the total elastic electron cross section 
void EvaluatedElectronDataContainer::setTotalElasticCrossSection(
			 const std::vector<double>& total_elastic_cross_section )
{
  // Make sure the total elastic cross section is valid
  testPrecondition( total_elastic_cross_section.size() <= 
                    d_electron_energy_grid.size() );
  testPrecondition( std::find_if( total_elastic_cross_section.begin(),
                                  total_elastic_cross_section.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    total_elastic_cross_section.end() );
  
  d_total_elastic_cross_section = total_elastic_cross_section;
}

// Set the total elastic cross section threshold energy bin index
void EvaluatedElectronDataContainer::setTotalElasticCrossSectionThresholdEnergyIndex(
						        const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( 
        d_total_elastic_cross_section.size() + index ==
        d_electron_energy_grid.size() );
  
 d_total_elastic_cross_section_threshold_index = index;
}
/*
// Set the hard elastic electron cross section 
void EvaluatedElectronDataContainer::setHardElasticCrossSection(
			 const std::vector<double>& hard_elastic_cross_section )
{
  // Make sure the hard elastic cross section is valid
  testPrecondition( hard_elastic_cross_section.size() <= 
                    d_electron_energy_grid.size() );
  testPrecondition( std::find_if( hard_elastic_cross_section.begin(),
                                  hard_elastic_cross_section.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    hard_elastic_cross_section.end() );
  
  d_hard_elastic_cross_section = hard_elastic_cross_section;
}

// Set the hard elastic cross section threshold energy bin index
void EvaluatedElectronDataContainer::setHardElasticCrossSectionThresholdEnergyIndex(
						        const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( 
        d_hard_elastic_cross_section.size() + index ==
        d_electron_energy_grid.size() );
  
 d_hard_elastic_cross_section_threshold_index = index;
}
*/
// Set the elastic electron cross section using Moment Preserving (MP) theory
void EvaluatedElectronDataContainer::setMomentPreservingCrossSection(
			 const std::vector<double>& moment_preserving_elastic_cross_section )
{
  // Make sure the moment preserving elastic cross section is valid
  testPrecondition( moment_preserving_elastic_cross_section.size() <= 
                    d_electron_energy_grid.size() );
  testPrecondition( std::find_if( moment_preserving_elastic_cross_section.begin(),
                                  moment_preserving_elastic_cross_section.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    moment_preserving_elastic_cross_section.end() );
  
  d_moment_preserving_elastic_cross_section = 
        moment_preserving_elastic_cross_section;
}

// Set the MP elastic cross section threshold energy bin index
void EvaluatedElectronDataContainer::setMomentPreservingCrossSectionThresholdEnergyIndex(
						        const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( 
        d_moment_preserving_elastic_cross_section.size() + index ==
        d_electron_energy_grid.size() );
  
 d_moment_preserving_elastic_cross_section_threshold_index= index;
}

// Set the electroionization electron cross section 
void EvaluatedElectronDataContainer::setElectroionizationCrossSection(
            const unsigned subshell,
            const std::vector<double>& electroionization_cross_section )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the electroionization cross section is valid
  testPrecondition( electroionization_cross_section.size() <= 
                    d_electron_energy_grid.size() );
  testPrecondition( std::find_if( electroionization_cross_section.begin(),
                                  electroionization_cross_section.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    electroionization_cross_section.end() );
  
  d_electroionization_subshell_cross_section[subshell] = 
    electroionization_cross_section;
}

// Set the electroionization cross section threshold energy bin index
void EvaluatedElectronDataContainer::setElectroionizationCrossSectionThresholdEnergyIndex(
            const unsigned subshell,
	        const unsigned index )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the threshold index is valid
  testPrecondition( 
        d_electroionization_subshell_cross_section[subshell].size() + index ==
        d_electron_energy_grid.size() );
  
 d_electroionization_subshell_cross_section_threshold_index[subshell] = index;
}

// Set the bremsstrahlung electron cross section 
void EvaluatedElectronDataContainer::setBremsstrahlungCrossSection(
			 const std::vector<double>& bremsstrahlung_cross_section )
{
  // Make sure the bremsstrahlung cross section is valid
  testPrecondition( bremsstrahlung_cross_section.size() <= 
                    d_electron_energy_grid.size() );
  testPrecondition( std::find_if( bremsstrahlung_cross_section.begin(),
                                  bremsstrahlung_cross_section.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    bremsstrahlung_cross_section.end() );
  
  d_bremsstrahlung_cross_section = bremsstrahlung_cross_section;
}

// Set the bremsstrahlung cross section threshold energy bin index
void EvaluatedElectronDataContainer::setBremsstrahlungCrossSectionThresholdEnergyIndex(
						        const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( 
        d_bremsstrahlung_cross_section.size() + index ==
        d_electron_energy_grid.size() );
  
 d_bremsstrahlung_cross_section_threshold_index = index;
}

// Set the atomic excitation electron cross section 
void EvaluatedElectronDataContainer::setAtomicExcitationCrossSection(
			 const std::vector<double>& atomic_excitation_cross_section )
{
  // Make sure the atomic excitation cross section is valid
  testPrecondition( atomic_excitation_cross_section.size() <= 
                    d_electron_energy_grid.size() );
  testPrecondition( std::find_if( atomic_excitation_cross_section.begin(),
                                  atomic_excitation_cross_section.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    atomic_excitation_cross_section.end() );
  
  d_atomic_excitation_cross_section = atomic_excitation_cross_section;
}

// Set the atomic excitation cross section threshold energy bin index
void EvaluatedElectronDataContainer::setAtomicExcitationCrossSectionThresholdEnergyIndex(
						        const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( 
        d_atomic_excitation_cross_section.size() + index ==
        d_electron_energy_grid.size() );
  
 d_atomic_excitation_cross_section_threshold_index = index;
}

// Test if a value is less than or equal to zero
bool EvaluatedElectronDataContainer::isValueLessThanOrEqualToZero( 
							   const double value )
{
  return value <= 0.0;
}

// Test if a value is less than zero
bool EvaluatedElectronDataContainer::isValueLessThanZero( 
							   const double value )
{
  return value < 0.0;
}

// Test if a value is greater than one
bool EvaluatedElectronDataContainer::isValueGreaterThanOne( 
							   const double value )
{
  return value > 1.0;
}

// Test if a value is less than -1.0
bool EvaluatedElectronDataContainer::isValueLessThanMinusOne( 
							   const double value )
{
  return value < -1.0;
}


} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_EvaluatedElectronDataContainer.cpp
//---------------------------------------------------------------------------//
