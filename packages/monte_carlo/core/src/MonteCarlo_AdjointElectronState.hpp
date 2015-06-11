//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronState.hpp
//! \author Luke Kersting
//! \brief  Adjoint electron state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTRON_STATE_HPP
#define MONTE_CARLO_ADJOINT_ELECTRON_STATE_HPP

// FRENSIE Includes
#include "MonteCarlo_MassiveParticleState.hpp"

namespace MonteCarlo{

//! The adjoint electron state class
class AdjointElectronState : public MassiveParticleState
{

public:

  // The adjoint electron tag
  struct AdjointElectronTag{};

  // Typedef for the adjoint electron tag
  struct AdjointElectronTag ParticleTag;

  //! Constructor
  AdjointElectronState( const ParticleState::historyNumberType history_number );

  //! Copy constructor (with possible creation of new generation)
  AdjointElectronState( const ParticleState& existing_base_state,
                        const bool increment_generation_number = false,
                        const bool reset_collision_number = false );

  //! Copy constructor (with possible creation of new generation)
  AdjointElectronState( const AdjointElectronState& existing_base_state,
                        const bool increment_generation_number = false,
                        const bool reset_collision_number = false );

  //! Core constructor
  AdjointElectronState( const ParticleStateCore& core );

  //! Destructor
  virtual ~AdjointElectronState()
  { /* ... */ }

  //! Check if this is a probe
  virtual bool isProbe() const;

  //! Return the rest mass energy of the electron (MeV)
  double getRestMassEnergy() const;

  //! Print the adjoint electron state
  virtual void print( std::ostream& os ) const;

protected:

  //! Probe constructor
  AdjointElectronState( const ParticleState::historyNumberType history_number,
                        const ParticleType probe_type );

  //! Probe copy constructor
  AdjointElectronState( const ParticleState& existing_base_state,
                        const ParticleType probe_type,
                        const bool increment_generation_number,
                        const bool reset_collision_number );

  //! Probe core constructor
  AdjointElectronState( const ParticleStateCore& core,
                        const ParticleType probe_type );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTRON_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronState.hpp
//---------------------------------------------------------------------------//
