//---------------------------------------------------------------------------//
//!
//! \file   Facemc_PhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The photoatomic reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PHOTOATOMIC_REACTION_HPP
#define FACEMC_PHOTOATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "Facemc_PhotonState.hpp"
#include "Facemc_ParticleBank.hpp"

namespace Facemc{

//! The photoatomic reaction base class
class PhotoatomicReaction
{

public:

  //! Constructor
  PhotoatomicReaction( 
		  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		  const Teuchos::ArrayRCP<const double>& cross_section );

  //! Destructor
  virtual ~PhotoatomicReaction()
  { /* ... */ }

  //! Return the cross section at the given energy
  double getCrossSection( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Simulate the reaction
  virtual void react( PhotonState& photon, ParticleBank& bank ) const;

private:

  // The incoming energy grid (logarithms)
  Teuchos::ArrayRCP<const double> d_incoming_energy_grid;

  // The cross section values evaluated on the incoming erg grid (logarithms)
  Teuchos::ArrayRCP<const double> d_cross_section;
};

} // end Facemc namespace

#endif // end FACEMC_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_PhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
