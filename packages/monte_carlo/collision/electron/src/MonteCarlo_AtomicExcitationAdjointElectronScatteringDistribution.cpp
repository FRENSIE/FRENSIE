//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The atomic excitation adjoint electron scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
AtomicExcitationAdjointElectronScatteringDistribution::AtomicExcitationAdjointElectronScatteringDistribution(
      const AtomicDistribution& energy_gain_distribution )
  : d_energy_gain_distribution( energy_gain_distribution ),
    d_critical_line_energies( new std::vector<double>( 1, 0.0 ) ),
    d_nudge_tol( 1e-8 )
{
  // Make sure the array is valid
  testPrecondition( d_energy_gain_distribution.use_count() > 0 );
}

// Set the critical line energies
/*! \details The critical line energies must be sorted. It is acceptable for
 * some or all of them to be above the max energy.
 */
void AtomicExcitationAdjointElectronScatteringDistribution::setCriticalLineEnergies(
    const std::shared_ptr<const std::vector<double> >& critical_line_energies )
{
  // Make sure the critical line energies are valid
  testPrecondition( critical_line_energies.get() );
  testPrecondition( critical_line_energies->size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
                                             critical_line_energies->begin(),
                                             critical_line_energies->end() ) );

  d_critical_line_energies = critical_line_energies;
}

// Get the critical line energies
const std::vector<double>&
AtomicExcitationAdjointElectronScatteringDistribution::getCriticalLineEnergies() const
{
  return *d_critical_line_energies;
}

// Sample an outgoing energy and direction from the distribution
void AtomicExcitationAdjointElectronScatteringDistribution::sample(
             const double incoming_energy,
             double& outgoing_energy,
             double& scattering_angle_cosine ) const
{
  // Theree is no angle scattering
  scattering_angle_cosine = 1.0;

  // Get energy gain
  double energy_gain = d_energy_gain_distribution->evaluate( incoming_energy );

  // Calculate outgoing energy
  outgoing_energy = incoming_energy + energy_gain;

  testPostcondition( energy_gain > 0.0 );
}

// Sample an outgoing energy and direction and record the number of trials
void AtomicExcitationAdjointElectronScatteringDistribution::sampleAndRecordTrials(
             const double incoming_energy,
             double& outgoing_energy,
             double& scattering_angle_cosine,
             Counter& trials ) const
{
  // Update trial number
  trials++;

  // Sample an outgoing direction
  this->sample( incoming_energy,
                outgoing_energy,
                scattering_angle_cosine );
}

// Randomly scatter the adjoint electron
void AtomicExcitationAdjointElectronScatteringDistribution::scatterAdjointElectron(
                      AdjointElectronState& adjoint_electron,
                      ParticleBank& bank,
                      Data::SubshellType& shell_of_interaction ) const
{
  double outgoing_energy;
  double scattering_angle_cosine;

  // Sample an outgoing energy
  this->sample( adjoint_electron.getEnergy(),
                outgoing_energy,
                scattering_angle_cosine );

  // If possible nudge the energy to a line energy
  this->nudgeEnergyToLineEnergy( outgoing_energy );

  // Set the new energy
  adjoint_electron.setEnergy( outgoing_energy );
}

// Check if an energy is in the scattering window
bool AtomicExcitationAdjointElectronScatteringDistribution::isEnergyInNudgeWindow(
                                            const double energy_of_interest,
                                            const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest >= 0.0 );

  if( std::abs(energy - energy_of_interest) <
      d_nudge_tol*energy_of_interest )
    return true;
  else
    return false;
}

// Nudge the energy to a critical line energy if possible
/*! \details The nudge factor is small enough that it should be impossible for
 *  the energy to be nudged into multiple critical line energies.
 */
void AtomicExcitationAdjointElectronScatteringDistribution::nudgeEnergyToLineEnergy(
                                  double& energy ) const
{
  for( auto&& line_energy : *d_critical_line_energies )
  {
    // Check if energy is within nudge window
    if( this->isEnergyInNudgeWindow( line_energy, energy ) )
    {
      // Set energy to line energy
      energy = line_energy;
      break;
    }
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
