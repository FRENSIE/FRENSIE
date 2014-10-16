//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The standard photoatomic reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_STANDARD_PHOTOATOMIC_REACTION_HPP
#define FACEMC_STANDARD_PHOTOATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardPhotoatomicReaction.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"

namespace MonteCarlo{

//! The standard photoatomic reaction base class
template<typename InterpPolicy>
class StandardPhotoatomicReaction : PhotoatomicReaction
{

public:

  //! Constructor
  StandardPhotoatomicReaction( 
		  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		  const Teuchos::ArrayRCP<const double>& cross_section,
		  const double threshold_energy = 0.0 );

  //! Destructor
  virtual ~StandardPhotoatomicReaction()
  { /* ... */ }

  //! Return the cross section at the given energy
  double getCrossSection( const double energy ) const;

private:

  // The incoming energy grid (logarithms)
  Teuchos::ArrayRCP<const double> d_incoming_energy_grid;

  // The cross section values evaluated on the incoming erg grid (logarithms)
  Teuchos::ArrayRCP<const double> d_cross_section;

  // The threshold energy
  const double d_threshold_energy;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_STANDARD_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
