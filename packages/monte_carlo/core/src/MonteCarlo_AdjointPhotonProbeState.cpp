//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonProbeState.cpp
//! \author Alex Robinson
//! \brief  Adjoint photon probe state class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AdjointPhotonProbeState::AdjointPhotonProbeState( 
		       const ParticleState::historyNumberType history_number )
{

}

// Copy constructor
AdjointPhotonProbeState::AdjointPhotonProbeState( 
			              const ParticleState& existing_base_state,
				      const bool increment_generation_number,
				      const bool reset_collision_number )
{

}

// Core constructor
AdjointPhotonProbeState( const ParticleStateCore& core )
{

}

// Set the energy of the particle (MeV)
/*! \details The probe particle gets killed when its energy changes.
 */
void setEnergy( const energyType energy )
{
  ParticleState::setEnergy( energy );

  this->setAsGone();
}

// Print the adjoint photon state
void print( std::ostream& os ) const
{
  os << "Particle Type: Adjoint Photon Probe" << std::endl;
  
  this->printImplementation( os );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonProbeState.cpp
//---------------------------------------------------------------------------//
