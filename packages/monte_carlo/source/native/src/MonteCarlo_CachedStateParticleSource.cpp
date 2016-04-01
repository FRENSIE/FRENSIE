//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CachedStateParticleSource.cpp
//! \author Alex Robinson
//! \brief  Cached state particle source class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <numeric>

// Boost Includes
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/nvp.hpp>

// FRENSIE Includes
#include "MonteCarlo_CachedStateParticleSource.hpp"
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "Utility_CommHelpers.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
CachedStateParticleSource::CachedStateParticleSource( 
		    const std::string& state_source_bank_archive_name,
		    const std::string& bank_name_in_archive,
		    const Utility::ArchivableObject::ArchiveType archive_type )
  : d_particle_states(),
    d_number_of_samples( 1, 0ull )
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
  state_bank.sort( CachedStateParticleSource::compareHistoryNumbers );

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

// Enable thread support
/*! \details Only the master thread should call this method.
 */
void CachedStateParticleSource::enableThreadSupport( const unsigned threads )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure a valid number of threads has been requested
  testPrecondition( threads > 0 );

  d_number_of_samples.resize( threads, 0ull );
}

// Reset the source data
/*! \details Only the master thread should call this method.
 */
void CachedStateParticleSource::resetData()
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  for( unsigned i = 0; i < d_number_of_samples.size(); ++i )
    d_number_of_samples[i] = 0ull;
}

// Reduce the source data
/*! \details Only the master thread should call this method.
 */
void CachedStateParticleSource::reduceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure the communicator is valid
  testPrecondition( !comm.is_null() );
  // Make sure the root process is valid
  testPrecondition( root_process < comm->getSize() );

  // Only do the reduction if there is more than one process
  if( comm->getSize() > 1 )
  {
    try{
      Teuchos::reduceAll<unsigned long long>( *comm,
                                              Teuchos::REDUCE_SUM,
                                              d_number_of_samples.size(),
                                              d_number_of_samples.getRawPtr(),
                                              d_number_of_samples.getRawPtr() );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Error: unable to reduce the source samples!" );

    // Reset the sampling data if not the root process
    if( comm->getRank() != root_process )
      this->resetData();
  }
}

// Export the source data
/*! \details Only the master thread should call this method.
 */
void CachedStateParticleSource::exportData(
             const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure the hdf5 file is valid
  testPrecondition( hdf5_file.get() != NULL );
  
  // Open the source hdf5 file
  SourceHDF5FileHandler source_hdf5_file( hdf5_file );

  // Set the number of trials
  unsigned long long trials = this->getNumberOfTrials();

  source_hdf5_file.setNumberOfDefaultSourceSamplingTrials( trials );

  // Set the number of samples
  unsigned long long samples = this->getNumberOfSamples();

  source_hdf5_file.setNumberOfDefaultSourceSamples( samples );  
}

// Print a summary of the source data
/*! \details Only the master thread should call this method.
 */
// Print a summary of the source data
void CachedStateParticleSource::printSummary( std::ostream& os ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  this->printStandardSummary( "Cached State Source",
                              this->getNumberOfTrials(),
                              this->getNumberOfSamples(),
                              this->getSamplingEfficiency(),
                              os );
}

// Sample a particle state from the source
/*! \details All cached particle states with the requested history number will
 * be added to the bank. If enableThreadSupport has been called, this method is
 * thread-safe. The cell that contains the sampled particle state will
 * not be set and must be determined by the geometry module.
 */
void CachedStateParticleSource::sampleParticleState( 
                                             ParticleBank& bank,
                                             const unsigned long long history )
{
  TEST_FOR_EXCEPTION( d_particle_states.find( history ) ==
		      d_particle_states.end(),
		      std::runtime_error,
		      "Error: No particle states in the state source were "
		      "found for history number " << history << "!" );

  for( unsigned i = 0; i < d_particle_states[history].size(); ++i )
  {
    bank.push( *d_particle_states[history][i] );
    
    ++d_number_of_samples[Utility::GlobalOpenMPSession::getThreadId()];
  }
}

// Return the number of sampling trials
/*! \details Only the master thread should call this method.
 */
unsigned long long CachedStateParticleSource::getNumberOfTrials() const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  return this->reduceLocalSamplesCounters();
}

// Return the number of samples
/*! \details Only the master thread should call this method.
 */
unsigned long long CachedStateParticleSource::getNumberOfSamples() const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  return this->reduceLocalSamplesCounters();
}

// Return the sampling efficiency from the source
/*! \details Only the master thread should call this method.
 */
double CachedStateParticleSource::getSamplingEfficiency() const
{
  return 1.0;
}

// Compare two particle state cores
bool CachedStateParticleSource::compareHistoryNumbers( 
                                                 const ParticleState& state_a,
                                                 const ParticleState& state_b )
{
  return state_a.getHistoryNumber() < state_b.getHistoryNumber();
}

// Reduce the local samples counters
unsigned long long 
CachedStateParticleSource::reduceLocalSamplesCounters() const
{
  return std::accumulate( d_number_of_samples.begin(),
                          d_number_of_samples.end(),
                          0ull );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CachedStateParticleSource.cpp
//---------------------------------------------------------------------------//
