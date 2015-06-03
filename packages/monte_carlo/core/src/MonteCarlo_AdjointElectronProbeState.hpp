//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronProbeState.hpp
//! \author Luke Kersting
//! \brief  Adjoint electron probe state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTRON_PROBE_STATE_HPP
#define MONTE_CARLO_ADJOINT_ELECTRON_PROBE_STATE_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronState.hpp"

namespace MonteCarlo{

/*! The adjoint electron probe state class
 * \details The probe state get killed when its energy changes.
 */
class AdjointElectronProbeState : public AdjointElectronState
{

public:

  // The adjoint electron probe tag
  struct AdjointElectronProbeTag{};

  // Typedef for the adjoint electron probe tag
  struct AdjointElectronProbeTag ParticleTag;

  //! Constructor
  AdjointElectronProbeState( 
		       const ParticleState::historyNumberType history_number );

  //! Copy constructor (with possible creation of new generation)
  AdjointElectronProbeState( const ParticleState& existing_base_state,
			   const bool increment_generation_number = false,
			   const bool reset_collision_number = false );

  //! Copy constructor (with possible creation of new generation)
  AdjointElectronProbeState( const AdjointElectronProbeState& existing_base_state,
			   const bool increment_generation_number = false,
			   const bool reset_collision_number = false );

  //! Core constructor
  AdjointElectronProbeState( const ParticleStateCore& core );

  //! Destructor
  ~AdjointElectronProbeState()
  { /* ... */ }

  //! Set the energy of the particle (MeV)
  void setEnergy( const energyType energy );

  //! Print the adjoint electron state
  void print( std::ostream& os ) const;

private:

  // Flag that indicates if the initial energy has been set
  bool d_initial_energy_set;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTRON_PROBE_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronProbeState.hpp
//---------------------------------------------------------------------------//
