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
#include "MonteCarlo_ParticleState.hpp"

namespace MonteCarlo{

//! The electron state class
class ElectronState : public ParticleState
{
  
private:
  
  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  // The electron tag
  struct ElectronTag{};

  // Typedef for the electron tag
  typedef ElectronTag ParticleTag;

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

  //! Set the energy of the electron (MeV)
  void setEnergy( const ParticleState::energyType energy );

  //! Return the speed of the electron (cm/s)
  double getSpeed() const;

  //! Set the speed of the electron (cm/s)
  void setSpeed( const double speed );

  //! Print the electron state
  void print( std::ostream& os ) const;

private:

  //! Calculate the time to traverse a distance
  ParticleState::timeType calculateTraversalTime( const double distance) const;

  // The speed of the particle
  double d_speed;
};

} // end MonteCarlo namespace

#endif // end MonteCarlo_ELECTRON_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronState.hpp
//---------------------------------------------------------------------------//
