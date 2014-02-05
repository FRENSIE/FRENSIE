//---------------------------------------------------------------------------//
//!
//! \file   ParticleState.hpp
//! \author Alex Robinson
//! \brief  Particle state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PARTICLE_STATE_HPP
#define PARTICLE_STATE_HPP

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "ParticleType.hpp"
#include "BasicParticleState.hpp"

namespace FACEMC{

//! The particle state class
template<typename CellHandle>
class ParticleState : public BasicParticleState
{
  
public:
  
  //! Typedef for the cell handle
  typedef CellHandle cellHandle;
  //! Typedef for particle state pointer
  typedef Teuchos::RCP<ParticleState<CellHandle> > ParticleStatePtr;

  //! Default constructor
  ParticleState();

  //! Constructor for a particular history
  ParticleState( const unsigned long long history_number );

  //! Copy constructor
  ParticleState( const ParticleState<CellHandle>& existing_particle_state );

  //! Assignment operator
  ParticleState<CellHandle>& operator=( 
		    const ParticleState<CellHandle>& existing_particle_state );

  //! Destructor
  ~ParticleState()
  { /* ... */ }

  //! Return the history number
  unsigned long long getHistoryNumber() const;

  //! Return the cell handle for the cell containing the particle
  CellHandle getCell() const;

  //! Set the cell handle for the cell containing the particle
  void setCell( const CellHandle& cell );

  //! Return if the history is the root
  bool isRootHistory() const;

  //! Return if the particle is lost
  bool isLost() const;

  //! Set the particle as lost
  void setAsLost();

  //! Return if the particle is gone
  bool isGone() const;

  //! Set the particle as gone
  void setAsGone();

  //! Spawn a child state (the history number will not change)
  ParticleStatePtr spawnChildState( 
			        const ParticleType child_particle_type ) const;

  //! Spawn a child state that is the same type as the parent
  ParticleStatePtr spawnChildState() const;

  //! Print method that defines the behavior of the std::stream << operator
  void print( std::ostream& os ) const;

private:

  //! Set the history as a child
  void setAsChildHistory();

  // History number
  unsigned long long d_history_number;

  // Current cell handle
  CellHandle d_cell;

  // Root history boolean
  bool d_root_history;  

  // Lost particle boolean
  bool d_lost;

  // Finished history boolean
  bool d_gone;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//

#include "ParticleState_def.hpp"

//---------------------------------------------------------------------------//

#endif // end PARTICLE_STATE_HPP

//---------------------------------------------------------------------------//
// end ParticleState.hpp
//---------------------------------------------------------------------------//
