//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SourceHandler.cpp
//! \author Alex Robinson
//! \brief  The source handler class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SourceHandler.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
SourceHandler::SourceHandler()
  : d_sources(),
    d_source_cdf(),
    d_total_source_weight( 0.0 )
{ /* ... */ }

// Add a source to the source handler
void SourceHandler::addSource( const std::shared_ptr<ParticleSource>& source,
                               const double weight )
{
  // Make sure that the source is valid
  testPrecondition( source.get() );
  testPrecondition( d_sources.find( source->getId() ) == d_sources.end() );
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );
  
  d_sources[source->getId()] = source;

  // Cache the current total weight
  double old_total_weight = d_total_source_weight;

  // Update the total weight
  d_total_source_weight += weight;

  // Update the source cdf
  for( size_t i = 0; i < d_source_cdf.size(); ++i )
    d_source_cdf[i].second *= old_total_weight/d_total_source_weight;

  d_source_cdf.push_back( std::make_pair( source->getId(), 1.0 ) );
}

// Get the number of sources
size_t SourceHandler::getNumberOfSources() const
{
  return d_sources.size();
}

// Check if a source exists
bool SourceHandler::doesSourceExist(
                        const ModuleTraits::InternalROIHandle source_id ) const
{
  return d_sources.find( source_id ) != d_sources.end();
}

// Enable thread support
void SourceHandler::enableThreadSupport( const size_t threads )
{
  SourceIdMap::iterator source_it, source_end;
  source_it = d_sources.begin();
  source_end = d_sources.end();

  while( source_it != source_end )
  {
    source_it->second->enableThreadSupport( threads );

    ++source_it;
  }
}

// Reset the source data
void SourceHandler::resetSourceData()
{
  SourceIdMap::iterator source_it, source_end;
  source_it = d_sources.begin();
  source_end = d_sources.end();

  while( source_it != source_end )
  {
    source_it->second->resetData();

    ++source_it;
  }
}

// Reduce the source data
void SourceHandler::reduceSourceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process )
{
  SourceIdMap::iterator source_it, source_end;
  source_it = d_sources.begin();
  source_end = d_sources.end();

  while( source_it != source_end )
  {
    source_it->second->reduceData( comm, root_process );

    comm->barrier();

    ++source_it;
  }
}

// Export the source data
void SourceHandler::exportSourceData(
                               const std::shared_ptr<Utility::HDF5FileHandler>&
                               hdf5_file ) const
{
  SourceIdMap::const_iterator source_it, source_end;
  source_it = d_sources.begin();
  source_end = d_sources.end();

  while( source_it != source_end )
  {
    source_it->second->exportData( hdf5_file );

    ++source_it;
  }
}

// Print the source summaries
void SourceHandler::printSourceSummaries( std::ostream& os ) const
{
  SourceIdMap::const_iterator source_it, source_end;
  source_it = d_sources.begin();
  source_end = d_sources.end();

  while( source_it != source_end )
  {
    source_it->second->printSummary( os );

    ++source_it;
  }
}

// Sample a particle state from the source
void SourceHandler::sampleParticleState( ParticleBank& bank,
                                         const unsigned long long history )
{
  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Sample the source that will be sampled from
  SourceIdCDFPairArray::iterator selected_source =
    Utility::Search::binaryUpperBound<Utility::SECOND>( d_source_cdf.begin(),
							d_source_cdf.end(),
							random_number );
  // Sample from the source
  d_sources.find( selected_source->first )->second->sampleParticleState( bank, history );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SourceHandler.cpp
//---------------------------------------------------------------------------//
