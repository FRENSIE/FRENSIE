//---------------------------------------------------------------------------//
//!
//! \file MonteCarlo_ElectronReaction.hpp
//! \author Luke Kersting
//! \brief The Electron reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRON_REACTION_HPP
#define MONTE_CARLO_ELECTRON_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"

namespace MonteCarlo{

//! The electron/positron reaction base class
class ElectronReaction
{

public:

  //!Constructor
  ElectronReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		onst Teuchos::ArrayRCP<const double>& cross_section        );

  //!Destructor
  virtual ~ElectronReaction()
  { /* ... */}
	
  //! Return the cross section at the given energy
  double getCrossSection( const double energy ) const;

  //! Return the number of electrons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedElectrons( const double energy ) const = 0;

  //! Simulate the reaction
  virtual void react( ElectronState& photon, ParticleBank& bank ) const = 0;

private:

  // The incoming energy grid (logarithms)
  Teuchos::ArrayRCP<const double> d_incoming_energy_grid;

  // The cross section values evaluated on the incoming erg grid (logarithms)
  Teuchos::ArrayRCP<const double> d_cross_section;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTRON_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronReaction.hpp
//---------------------------------------------------------------------------//
