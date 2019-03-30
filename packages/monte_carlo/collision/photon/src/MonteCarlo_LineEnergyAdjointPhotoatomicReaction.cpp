//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_LineEnergyAdjontPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The line energy adjoint photoatomic reaction class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_LineEnergyAdjointPhotoatomicReaction.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
LineEnergyAdjointPhotoatomicReaction::LineEnergyAdjointPhotoatomicReaction(
    const AdjointPhotoatomicReactionType reaction,
    const double cross_section_value,
    const std::shared_ptr<LineEnergyAdjointPhotonScatteringDistribution>&
    energy_dist )
  : d_reaction_type( reaction ),
    d_cross_section( cross_section_value ),
    d_scattering_distribution( energy_dist )
{
  // Make sure the cross section is valid
  testPrecondition( cross_section_value > 0.0 );
  // Make sure the energy distribution is valid
  testPrecondition( energy_dist.get() != NULL );
}

// Set the critical line energies
void LineEnergyAdjointPhotoatomicReaction::setCriticalLineEnergies(
    const std::shared_ptr<const std::vector<double> >& critical_line_energies )
{
  d_scattering_distribution->setCriticalLineEnergies( critical_line_energies );
}

// Get the critical line energies
const std::vector<double>& LineEnergyAdjointPhotoatomicReaction::getCriticalLineEnergies() const
{
  return d_scattering_distribution->getCriticalLineEnergies();
}

// Return the minimum outgoing energy
double LineEnergyAdjointPhotoatomicReaction::getMinOutgoingEnergy() const
{
  return d_scattering_distribution->getMinOutgoingEnergy();
}

// Return the maximum outgoing energy
double LineEnergyAdjointPhotoatomicReaction::getMaxOutgoingEnergy() const
{
  return d_scattering_distribution->getMaxOutgoingEnergy();
}

// Test if the energy falls within the energy grid
bool LineEnergyAdjointPhotoatomicReaction::isEnergyWithinEnergyGrid(
                                                    const double energy ) const
{
  return energy == d_scattering_distribution->getLineEnergy();
}

// Return the cross section at the given energy
double LineEnergyAdjointPhotoatomicReaction::getCrossSection(
                                                    const double energy ) const
{
  if( energy == d_scattering_distribution->getLineEnergy() )
    return d_cross_section;
  else
    return 0.0;
}

// Return the cross section at the given energy (efficient)
double LineEnergyAdjointPhotoatomicReaction::getCrossSection(
                                               const double energy,
                                               const size_t bin_index ) const
{
  return this->getCrossSection( energy );    
}

// Return the line energy
double LineEnergyAdjointPhotoatomicReaction::getLineEnergy() const
{
  return d_scattering_distribution->getLineEnergy();
}

// Return the max energy
double LineEnergyAdjointPhotoatomicReaction::getMaxEnergy() const
{
  return d_scattering_distribution->getLineEnergy();
}

// Return the threshold energy
double LineEnergyAdjointPhotoatomicReaction::getThresholdEnergy() const
{
  return d_scattering_distribution->getLineEnergy();
}

// Return the number of adjoint photons emitted from the rxn at the given energy
unsigned LineEnergyAdjointPhotoatomicReaction::getNumberOfEmittedAdjointPhotons(
                                                    const double energy ) const
{
  if( energy == d_scattering_distribution->getLineEnergy() )
    return 1u;
  else
    return 0u;
}

// Return the number of adjoint electrons emitted from the rxn at the given energy
unsigned LineEnergyAdjointPhotoatomicReaction::getNumberOfEmittedAdjointElectrons(
                                                    const double energy ) const
{
  return 0u;
}

// Return the number of adjoint positrons emitted from the rxn at the given energy
unsigned LineEnergyAdjointPhotoatomicReaction::getNumberOfEmittedAdjointPositrons(
                                                    const double energy ) const
{
  return 0u;
}

// Return the reaction type
AdjointPhotoatomicReactionType LineEnergyAdjointPhotoatomicReaction::getReactionType() const
{
  return d_reaction_type;
}

// Simulate the reaction
/*! \details Only probe particles should ever enter this react method as they
 * are the only particle types that will ever have exactly the line energy
 * where this reaction is defined. Note that the probe particle will be killed
 * by this reaction. It is not clear yet how the particle generation number and
 * collision number should be treated with these types of reactions 
 * (currently both are incremented in the generated adjoint photon).
 */
void LineEnergyAdjointPhotoatomicReaction::react(
                               AdjointPhotonState& adjoint_photon,
                               ParticleBank& bank,
                               Data::SubshellType& shell_of_interaction ) const
{
  // Make sure only probe states enter this react method
  testPrecondition( adjoint_photon.isProbe() );
  // Make sure the energy is valid
  testPrecondition( adjoint_photon.getEnergy() ==
                    d_scattering_distribution->getLineEnergy() );

  if( adjoint_photon.getEnergy() ==
      d_scattering_distribution->getLineEnergy() )
  {
    // Create a clone of the probe particle (a clone is required that is not
    // a probe because if the probe's energy is changed - it will be killed)
    std::shared_ptr<AdjointPhotonState> adjoint_photon_clone(
                      new AdjointPhotonState( adjoint_photon, false, false ) );

    // Increment the collision number of the clone first so that any
    // generated probe particles have the correct collision number
    adjoint_photon_clone->incrementCollisionNumber();

    ParticleBank local_interaction_bank;

    // Scatter the clone
    d_scattering_distribution->scatterAdjointPhoton( *adjoint_photon_clone,
                                                     local_interaction_bank,
                                                     shell_of_interaction );

    // Add the clone to the bank
    bank.push( adjoint_photon_clone );

    // Splice the local bank with the global bank (do this operation second
    // so that all of the particle's children are added after the clone)
    bank.splice( local_interaction_bank );

    // Kill the probe
    adjoint_photon.setAsGone();
  }
}

// Return the head of the energy grid
/*! \details There is no energy grid with line energy reactions.
 */
const double* LineEnergyAdjointPhotoatomicReaction::getEnergyGridHead() const
{
  return NULL;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_LineEnergyAdjointPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
