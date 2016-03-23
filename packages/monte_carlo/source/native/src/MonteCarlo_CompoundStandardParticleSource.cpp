//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CompoundStandardParticleSource.cpp
//! \author Alex Robinson
//! \brief  Compound source class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <numeric>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_CompoundStandardParticleSource.hpp"
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
CompoundStandardParticleSource::CompoundStandardParticleSource( 
    const Teuchos::Array<std::shared_ptr<StandardParticleSource> >& sources,
    const Teuchos::Array<double>& source_sampling_weights )
  : d_sources( sources.size() )
{
  // Make sure that every source has a sampling weight
  testPrecondition( sources.size() == source_sampling_weights.size() );

  // Create the array of sources
  double total_weight = 0.0;
  
  for( unsigned i = 0; i < sources.size(); ++i )
  {
    total_weight += source_sampling_weights[i];
    
    d_sources[i].first = sources[i];
    d_sources[i].second = total_weight;
  }

  // Normalize the CDF
  for( unsigned i = 0; i < sources.size(); ++i )
    d_sources[i].second /= total_weight;
  
  // Make sure that the CDF has been normalized correctly
  testPostcondition( d_sources.back().second == 1.0 );
}

// Enable thread support
/*! \details Only the master thread should call this method
 */
void CompoundStandardParticleSource::enableThreadSupport( 
                                                       const unsigned threads )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure a valid number of threads has been requested
  testPrecondition( threads > 0 );

  for( unsigned i = 0; i < d_sources.size(); ++i )
    d_sources[i].first->enableThreadSupport( threads );
}

// Reset the source data
/*! \details Only the master thread should call this method
 */
void CompoundStandardParticleSource::resetData()
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  for( unsigned i = 0; i < d_sources.size(); ++i )
    d_sources[i].first->resetData();
}

// Reduce the source data
/*! \details Only the master thread should call this method.
 */
void CompoundStandardParticleSource::reduceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  for( unsigned i = 0; i < d_sources.size(); ++i )
    d_sources[i].first->reduceData( comm, root_process );
}

// Export the source data
/*! \details Only the master thread should call this method.
 */
void CompoundStandardParticleSource::exportData(
             const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure the hdf5 file is valid
  testPrecondition( hdf5_file.get() != NULL );
  
  for( unsigned i = 0; i < d_sources.size(); ++i )
    d_sources[i].first->exportData( hdf5_file );

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
void CompoundStandardParticleSource::printSummary( std::ostream& os ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  // Print the compound source summary
  this->printStandardSummary( "Compound Standard Source",
                              this->getNumberOfTrials(),
                              this->getNumberOfSamples(),
                              this->getSamplingEfficiency(),
                              os );

  // Print the individual source summaries
  for( unsigned i = 0; i < d_sources.size(); ++i )
  {
    std::ostringstream oss;
    oss << "Standard Source " << d_sources[i].first->getId();
    
    // Print the compound source summary
    this->printStandardSummary( oss.str(),
                                d_sources[i].first->getNumberOfTrials(),
                                d_sources[i].first->getNumberOfSamples(),
                                d_sources[i].first->getSamplingEfficiency(),
                                os );
  }
}

// Sample a particle state from the source
/*! \details If enableThreadSupport has been called, this method is 
 * thread-safe. The cell that contains the sampled particle state will
 * not be set and must be determined by the geometry module.
 */
void CompoundStandardParticleSource::sampleParticleState( 
                                          ParticleBank& bank,
                                          const unsigned long long history )
{
  double random_number = 
    Utility::RandomNumberGenerator::getRandomNumber<double>();
  
  // Sample the source that will be sampled from
  Teuchos::Array<Utility::Pair<std::shared_ptr<StandardParticleSource>,
			       double> >::iterator
    selected_source = Utility::Search::binaryUpperBound<Utility::SECOND>( 
							d_sources.begin(),
							d_sources.end(),
							random_number );
  // Sample from the source
  selected_source->first->sampleParticleState( bank, history );  
}

// Return the number of sampling trials
/*! \details Only the master thread should call this method.
 */
unsigned long long CompoundStandardParticleSource::getNumberOfTrials() const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  unsigned long long trials = 0ull;
  
  for( unsigned i = 0; i < d_sources.size(); ++i )
    trials += d_sources[i].first->getNumberOfTrials();

  return trials;
}

// Return the number of samples
/*! \details Only the master thread should call this method.
 */
unsigned long long 
CompoundStandardParticleSource::getNumberOfSamples() const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  unsigned long long samples = 0ull;
  
  for( unsigned i = 0; i < d_sources.size(); ++i )
    samples += d_sources[i].first->getNumberOfSamples();

  return samples;
}

// Return the sampling efficiency from the source
/*! \details Only the master thread should call this method.
 */
double CompoundStandardParticleSource::getSamplingEfficiency() const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  // Get the number of trials performed by each source
  unsigned long long trials = this->getNumberOfTrials();
  unsigned long long samples = this->getNumberOfSamples();

  if( trials > 0ull )
    return static_cast<double>( samples )/trials;
  else
    return 1.0;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CompoundStandardParticleSource.cpp
//---------------------------------------------------------------------------//
