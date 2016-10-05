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

// Constructor
AdjointPhotoatomicReaction::AdjointPhotoatomicReaction()
{ /* ... */ }

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
