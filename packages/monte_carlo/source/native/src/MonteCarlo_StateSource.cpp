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
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
StateSource::StateSource( 
	         const Teuchos::Array<ParticleStateCore>& raw_particle_states )
{ 
  // Make sure that there is at least one state in the array
  testPrecondition( raw_particle_states.size() > 0 );

  // Create a map of the history numbers and 
  Teuchos::Array<ParticleStateCore> raw_particle_states_copy = 
    raw_particle_states;
  
  // Sort the particle state cores
  std::sort( raw_particle_states_copy.begin(),
  	     raw_particle_states_copy.end(),
  	     StateSource::compareCores );

  // Reset the history numbers
  unsigned long long history_number = 0ull;
  unsigned long long current_history_number = 
    raw_particle_states_copy[0].history_number;
  
  for( unsigned i = 0; i < raw_particle_states_copy.size(); ++i )
  {
    if( raw_particle_states_copy[i].history_number == current_history_number )
    {
      raw_particle_states_copy[i].history_number = history_number;
      
      d_raw_particle_states[history_number].push_back(
						 raw_particle_states_copy[i] );
    }
    else
    {
      ++history_number;
      
      current_history_number = raw_particle_states_copy[i].history_number;
      
      raw_particle_states_copy[i].history_number = history_number;
      
      d_raw_particle_states[history_number].push_back(
						 raw_particle_states_copy[i] );
    }
  }
}

// Sample a particle state from the source
  void StateSource::sampleParticleState( ParticleBank& bank,
					 const unsigned long long history )
{
  TEST_FOR_EXCEPTION( d_raw_particle_states.find( history ) ==
		      d_raw_particle_states.end(),
		      std::runtime_error,
		      "Error: No particle states in the state source were "
		      "found for history number " << history << "!" );

  for( unsigned i = 0; i < d_raw_particle_states[history].size(); ++i )
  {
    const ParticleStateCore& core = d_raw_particle_states[history][i];

    bank.push( ParticleStateFactory::createState( core ) );
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
