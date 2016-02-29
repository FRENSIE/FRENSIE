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
#include <iostream>

// Boost Includes
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/nvp.hpp>

// FRENSIE Includes
#include "MonteCarlo_StateSource.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
StateSource::StateSource( 
		    const std::string& state_source_bank_archive_name,
		    const std::string& bank_name_in_archive,
		    const Utility::ArchivableObject::ArchiveType archive_type )
{ 
  // Make sure that the source bank archive name is valid
  testPrecondition( state_source_bank_archive_name.size() > 0 );

  // Load the the archived bank
  ParticleBank state_bank;
  
  std::ifstream ifs( state_source_bank_archive_name.c_str() );

  switch( archive_type )
  {
    case Utility::ArchivableObject::ASCII_ARCHIVE:
    {
      boost::archive::text_iarchive ar(ifs);
      ar >> boost::serialization::make_nvp( bank_name_in_archive.c_str(), 
					    state_bank );
      
      break;
    }

    case Utility::ArchivableObject::BINARY_ARCHIVE:
    {
      boost::archive::binary_iarchive ar(ifs);
      ar >> boost::serialization::make_nvp( bank_name_in_archive.c_str(), 
					    state_bank );
      
      break;
    }

    case Utility::ArchivableObject::XML_ARCHIVE:
    {
      boost::archive::xml_iarchive ar(ifs);
      ar >> boost::serialization::make_nvp( bank_name_in_archive.c_str(), 
					    state_bank );
      
      break;
    }
  }

  // Sort the bank by history number
  state_bank.sort( StateSource::compareHistoryNumbers );

  // Reset the history numbers
  unsigned long long history_number = 0ull;
  unsigned long long current_history_number = 
    state_bank.top().getHistoryNumber();
  
  while( !state_bank.isEmpty() )
  {
    if( state_bank.top().getHistoryNumber() != current_history_number )
    {
      ++history_number;
      
      current_history_number = state_bank.top().getHistoryNumber();
    }
    
    boost::shared_ptr<ParticleState> modified_state( 
				    state_bank.top().clone( history_number ) );

    d_particle_states[history_number].push_back( modified_state );

    state_bank.pop();
  }
}

// Sample a particle state from the source
void StateSource::sampleParticleState( ParticleBank& bank,
				       const unsigned long long history )
{
  TEST_FOR_EXCEPTION( d_particle_states.find( history ) ==
		      d_particle_states.end(),
		      std::runtime_error,
		      "Error: No particle states in the state source were "
		      "found for history number " << history << "!" );

  for( unsigned i = 0; i < d_particle_states[history].size(); ++i )
    bank.push( *d_particle_states[history][i] );
}

// Return the sampling efficiency from the source
double StateSource::getSamplingEfficiency() const
{
  return 1.0;
}

// Compare two particle state cores
bool StateSource::compareHistoryNumbers( const ParticleState& state_a,
					 const ParticleState& state_b )
{
  return state_a.getHistoryNumber() < state_b.getHistoryNumber();
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StateSource.cpp
//---------------------------------------------------------------------------//
