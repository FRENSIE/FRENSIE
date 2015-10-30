//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_ElectronState.hpp
//! \author Luke Kersting
//! \brief  Electron state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRON_STATE_HPP
#define MONTE_CARLO_ELECTRON_STATE_HPP

// FRENSIE Includes
#include "MonteCarlo_MassiveParticleState.hpp"

namespace MonteCarlo{

//! The electron state class
class ElectronState : public MassiveParticleState
{
  
private:
  
  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  // The electron tag
  struct ElectronTag{};

  // Typedef for the electron tag
  typedef ElectronTag ParticleTag;

  //! The particle state type (for compile time usage)
  static const ParticleType type = ELECTRON;

  //! Constructor
  ElectronState( const ParticleState::historyNumberType history_number );

  //! Copy constructor (with possible creation of new generation)
  ElectronState( const ElectronState& existing_electron_state,
		const bool increment_generation_number = false,
		const bool reset_collision_number = false );

  //! Copy constructor (with possible creation of new generation)
  ElectronState( const ParticleState& existing_base_state,
		const bool increment_generation_number = false,
		const bool reset_collision_number = false );

  //! Core constructor
  ElectronState( const ParticleStateCore& core );

  //! Assignment operator
  ElectronState& operator=( const ElectronState& existing_electron_state );

  //! Destructor
  ~ElectronState()
  { /* ... */ }

  // Return the rest mass energy of the electron (MeV)
  double getRestMassEnergy() const;

  //! Print the electron state
  void print( std::ostream& os ) const;
};

} // end MonteCarlo namespace

#endif // end MonteCarlo_ELECTRON_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronState.hpp
//---------------------------------------------------------------------------//
