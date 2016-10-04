//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The adjoint photoatomic reaction base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomicReaction.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default constructor
AdjointPhotoatomicReaction::AdjointPhotoatomicReaction()
  : d_max_energy( 0.0 )
{ /* ... */ }

// Constructor
AdjointPhotoatomicReaction::AdjointPhotoatomicReaction(
                                                      const double max_energy )
  : d_max_energy( max_energy )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > 0.0 );
}

// Set the max energy
void AdjointPhotoatomicReaction::setMaxEnergy( const double max_energy )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > 0.0 );
  
  d_max_energy = max_energy;
}

// Return the max energy
double AdjointPhotoatomicReaction::getMaxEnergy() const
{
  return d_max_energy;
}

// Simulate the reaction and track the number of sampling trials
void AdjointPhotoatomicReaction::react(
                                      AdjointPhotonState& adjoint_photon,
                                      ParticleBank& bank,
                                      Data::SubshellType& shell_of_interaction,
                                      unsigned& trials ) const
{
  ++trials;

  this->react( adjoint_photon, bank, shell_of_interaction );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
