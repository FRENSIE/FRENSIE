//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StateSource.cpp
//! \author Alex Robinson
//! \brief  State source class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_StateSource.hpp"
#include "MonteCarlo_ParticleStateFactory.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
StateSource::StateSource( 
	      const Teuchos::ArrayRCP<ParticleStateCore>& raw_particle_states )
  : d_raw_particle_states( raw_particle_states ),
    d_next_index( 0u )
{ 
  // Make sure that there is at least one state in the array
  testPrecondition( raw_particle_states.size() > 0 );

  // Sort the particle state cores
  std::sort( d_raw_particle_states.begin(),
	     d_raw_particle_states.end(),
	     StateSource::compareCores );

  // Reset the history numbers
  ParticleState::historyNumberType reset_history_number = 0ull;
  ParticleState::historyNumberType current_history_number = 
    d_raw_particle_states[0].history_number;
  
  for( unsigned i = 0; i < d_raw_particle_states.size(); ++i )
  {
    if( d_raw_particle_states[i].history_number == current_history_number )
      d_raw_particle_states[i].history_number = reset_history_number;
    else
    {
      ++reset_history_number;
      
      current_history_number = d_raw_particle_states[i].history_number;
      
      d_raw_particle_states[i].history_number = reset_history_number;
    }
  }
}

// Sample a particle state from the source
void StateSource::sampleParticleState( ParticleBank& bank )
{
  if( d_next_index >= d_raw_particle_states.size() )
  {
    std::string error_message = "Error: All particle states in the state ";
    error_message += "source have been used.\n";
    
    throw std::runtime_error( error_message );
  }

  ParticleState::historyNumberType history_number = 
    d_raw_particle_states[d_next_index].history_number;

  while( d_raw_particle_states[d_next_index].history_number == history_number )
  {
    const ParticleStateCore& core = d_raw_particle_states[d_next_index];

    bank.push( ParticleStateFactory::createState( core ) );
    
    ++d_next_index;

    if( d_next_index >= d_raw_particle_states.size() )
      break;
  }
}

// Return the sampling efficiency from the source
double StateSource::getSamplingEfficiency() const
{
  return 1.0;
}

// Compare two particle state cores
bool StateSource::compareCores( const ParticleStateCore& core_a,
				const ParticleStateCore& core_b )
{
  return core_a.history_number < core_b.history_number;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StateSource.cpp
//---------------------------------------------------------------------------//
