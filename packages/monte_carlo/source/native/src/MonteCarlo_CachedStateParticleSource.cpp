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
#include <limits>

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
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
CachedStateParticleSource::CachedStateParticleSource(
		    const std::string& state_source_bank_archive_name,
		    const std::string& bank_name_in_archive,
		    const Utility::ArchivableObject::ArchiveType archive_type )
  : ParticleSource(),
    d_particle_states()
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

    std::shared_ptr<ParticleState> modified_state(
				    state_bank.top().clone( history_number ) );

    d_particle_states[history_number].push_back( modified_state );

    state_bank.pop();
  }
}

// Get the source id
ModuleTraits::InternalROIHandle CachedStateParticleSource::getId() const
{
  return ModuleTraits::reserved_internal_roi_handle;
}

// Enable thread support
/*! \details There is no data that needs to be made thread safe.
 */
void CachedStateParticleSource::enableThreadSupportImpl( const size_t )
{ /* ... */ }

// Reset the source data
/*! \details There is no data that needs to be reset
 */
void CachedStateParticleSource::resetDataImpl()
{ /* ... */ }

// Reduce the source data
/*! \details There is no data that needs to be reduced.
 */
void CachedStateParticleSource::reduceDataImpl(
                 const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >&,
                 const int )
{ /* ... */ }

// Export the source data
/*! \details There is no data that needs to be exported.
 */
void CachedStateParticleSource::exportDataImpl(
                                SourceHDF5FileHandler& source_hdf5_file ) const
{ /* ... */ }

// Print a summary of the source data
/*! \details Only the master thread should call this method.
 */
void CachedStateParticleSource::printSummary( std::ostream& os ) const
{ 
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  // Print the source sampling statistics
  this->printStandardSummary( "Cached State Source",
                              this->getNumberOfTrials(),
                              this->getNumberOfSamples(),
                              this->getSamplingEfficiency(),
                              os );

  // Print the starting cell summary
  std::set<Geometry::ModuleTraits::InternalCellHandle> starting_cells;
  this->getStartingCells( starting_cells );
  
  this->printStandardStartingCellSummary( starting_cells, os );
}

/*! \brief Return the number of particle states that will be sampled for the 
 * given history number
 */
unsigned long long CachedStateParticleSource::getNumberOfParticleStateSamples(
                                       const unsigned long long history ) const
{
  HistoryStateMap::const_iterator history_it =
    d_particle_states.find( history );

  if( history_it != d_particle_states.end() )
    return history_it->second.size();
  else
  {
    FRENSIE_LOG_WARNING( "The cached state particle source has no cached "
                         "particle states for history " << history << "!" );
    
    return 0;
  }
}

// Initialize a particle state
std::shared_ptr<ParticleState>
CachedStateParticleSource::initializeParticleState(
                                    const unsigned long long history,
                                    const unsigned long long history_state_id )
{
  HistoryStateMap::iterator history_it = d_particle_states.find( history );
    
  if( history_it != d_particle_states.end() )
    return d_particle_states.find( history )->second[history_state_id];
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "The cached state particle source has no particles for "
                     "history " << history << "!" );
    
    return std::shared_ptr<ParticleState>();
  }
}

// Sample a particle state from the source
/*! \details Particle states are not sampled by this source. They are simply
 * extracted from the particle state cache. All of the particle's info
 * is set in the 
 * MonteCarlo::CachedStateParticleSource::initializeParticleStateImpl method.
 */
bool CachedStateParticleSource::sampleParticleStateImpl(
                                         const std::shared_ptr<ParticleState>&,
                                         const unsigned long long )
{ 
  return false;
}

// Return the number of sampling trials in the phase space dimension
ModuleTraits::InternalCounter
CachedStateParticleSource::getNumberOfDimensionTrials(
                                              const PhaseSpaceDimension ) const
{
  return 0.0;
}

// Return the number of samples in the phase space dimension
ModuleTraits::InternalCounter
CachedStateParticleSource::getNumberOfDimensionSamples(
                                              const PhaseSpaceDimension ) const
{
  return 0.0;
}

// Return the sampling efficiency in the phase space dimension
double CachedStateParticleSource::getDimensionSamplingEfficiency(
                                              const PhaseSpaceDimension ) const
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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CachedStateParticleSource.cpp
//---------------------------------------------------------------------------//
