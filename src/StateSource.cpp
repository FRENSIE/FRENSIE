//---------------------------------------------------------------------------//
//!
//! \file   StateSource.cpp
//! \author Alex Robinson
//! \brief  State source class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FACEMC Includes
#include "StateSource.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
StateSource::StateSource( 
		    const Teuchos::Array<BasicParticleState>& particle_states )
  : d_particle_states( particle_states ),
    d_next_state_index( 0u )
{ 
  // Make sure that there is at least one state in the array
  testPrecondition( particle_states.size() > 0 );
}

// Sample a particle state from the source
void StateSource::sampleParticleState( BasicParticleState& particle )
{
  if( d_next_state_index >= d_particle_states.size() )
  {
    std::string error_message = "Error: All particle states in the state ";
    error_message += "source have been used.\n";
    
    throw std::runtime_error( error_message );
  }
  
  particle = d_particle_states[d_next_state_index];
    
  ++d_next_state_index;
}

// Return the sampling efficiency from the source
double StateSource::getSamplingEfficiency() const
{
  return 1.0;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end StateSource.cpp
//---------------------------------------------------------------------------//
