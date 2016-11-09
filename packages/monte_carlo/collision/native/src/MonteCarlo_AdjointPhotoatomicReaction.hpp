//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The adjoint photoatomic reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTOATOMIC_REACTION
#define MONTE_CARLO_ADJOINT_PHOTOATOMIC_REACTION

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_AtomicReaction.hpp"
#include "MonteCarlo_AdjointPhotoatomicReactionType.hpp"
#include "Data_SubshellType.hpp"

namespace MonteCarlo{

//! The adjoint photoatomic reaction base class
class AdjointPhotoatomicReaction : public AtomicReaction
{

public:

  //! Constructor
  AdjointPhotoatomicReaction();

  //! Destructor
  virtual ~AdjointPhotoatomicReaction()
  { /* ... */ }

  //! Return the reaction type
  virtual AdjointPhotoatomicReactionType getReactionType() const = 0;

  //! Return the max energy
  virtual double getMaxEnergy() const = 0;

  //! Simulation the reaction
  virtual void react( AdjointPhotonState& adjoint_photon,
                      ParticleBank& bank,
                      Data::SubshellType& shell_of_interaction ) const = 0;

  //! Simulate the reaction and track the number of sampling trials
  virtual void react( AdjointPhotonState& adjoint_photon,
                      ParticleBank& bank,
                      Data::SubshellType& shell_of_interaction,
                      unsigned& trials ) const;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTOATOMIC_REACTION

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
