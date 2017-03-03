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
  : ParticleSource(),
    d_sources( sources.size() )
{
  // Make sure that every source has a sampling weight
  testPrecondition( sources.size() == source_sampling_weights.size() );

  // Create the array of sources
  double total_weight = 0.0;

  for( size_t i = 0; i < sources.size(); ++i )
  {
    total_weight += source_sampling_weights[i];

    Utility::get<0>(d_sources[i]) = sources[i];
    Utility::get<1>(d_sources[i]) = total_weight;
  }

  // Normalize the CDF
  for( size_t i = 0; i < sources.size(); ++i )
    Utility::get<1>(d_sources[i]) /= total_weight;

  // Make sure that the CDF has been normalized correctly
  testPostcondition( Utility::get<1>(d_sources.back()) == 1.0 );
}

// Get the source id
ModuleTraits::InternalROIHandle CompoundStandardParticleSource::getId() const
{
  return ModuleTraits::reserved_internal_roi_handle;
}

// Enable thread support
/*! \details Only the master thread should call this method
 */
void CompoundStandardParticleSource::enableThreadSupport(
                                                         const size_t threads )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure a valid number of threads has been requested
  testPrecondition( threads > 0 );

  for( size_t i = 0; i < d_sources.size(); ++i )
    Utility::get<0>(d_sources[i])->enableThreadSupport( threads );
}

// Reset the source data
/*! \details Only the master thread should call this method
 */
void CompoundStandardParticleSource::resetData()
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  for( size_t i = 0; i < d_sources.size(); ++i )
    Utility::get<0>(d_sources[i])->resetData();
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

  for( size_t i = 0; i < d_sources.size(); ++i )
    Utility::get<0>(d_sources[i])->reduceData( comm, root_process );
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

  for( size_t i = 0; i < d_sources.size(); ++i )
    Utility::get<0>(d_sources[i])->exportData( hdf5_file );
}

// Print a summary of the source data
/*! \details Only the master thread should call this method.
 */
void CompoundStandardParticleSource::printSummary( std::ostream& os ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  // Print the individual source summaries
  for( size_t i = 0; i < d_sources.size(); ++i )
    Utility::get<0>(d_sources[i])->printSummary( os );
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
  StandardSourceWeightPairArray::iterator selected_source =
    Utility::Search::binaryUpperBound<Utility::SECOND>( d_sources.begin(),
							d_sources.end(),
							random_number );
  // Sample from the source
  Utility::get<0>(*selected_source)->sampleParticleState( bank, history );
}

// Return the number of sampling trials
/*! \details Only the master thread should call this method.
 */
ModuleTraits::InternalCounter
CompoundStandardParticleSource::getNumberOfTrials() const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  ModuleTraits::InternalCounter trials = 0;

  for( size_t i = 0; i < d_sources.size(); ++i )
    trials += Utility::get<0>(d_sources[i])->getNumberOfTrials();

  return trials;
}

// Return the number of sampling trials in the phase space dimension
/*! \details Only the master thread should call this method.
 */
ModuleTraits::InternalCounter
CompoundStandardParticleSource::getNumberOfDimensionTrials(
                                    const PhaseSpaceDimension dimension ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  ModuleTraits::InternalCounter trials = 0;

  for( size_t i = 0; i < d_sources.size(); ++i )
  {
    trials +=
      Utility::get<0>(d_sources[i])->getNumberOfDimensionTrials( dimension );
  }

  return trials;
}

// Return the number of samples
/*! \details Only the master thread should call this method.
 */
ModuleTraits::InternalCounter
CompoundStandardParticleSource::getNumberOfSamples() const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  ModuleTraits::InternalCounter samples = 0;

  for( size_t i = 0; i < d_sources.size(); ++i )
    samples += Utility::get<0>(d_sources[i])->getNumberOfSamples();

  return samples;
}

// Return the number of samples in the phase space dimension
/*! \details Only the master thread should call this method.
 */
ModuleTraits::InternalCounter
CompoundStandardParticleSource::getNumberOfDimensionSamples(
                                    const PhaseSpaceDimension dimension ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  ModuleTraits::InternalCounter samples = 0;

  for( size_t i = 0; i < d_sources.size(); ++i )
  {
    samples +=
      Utility::get<0>(d_sources[i])->getNumberOfDimensionSamples( dimension );
  }

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
  ModuleTraits::InternalCounter trials = this->getNumberOfTrials();
  ModuleTraits::InternalCounter samples = this->getNumberOfSamples();

  if( trials > 0 )
    return static_cast<double>( samples )/trials;
  else
    return 1.0;
}

//! Return the sampling efficiency in the phase space dimension
double CompoundStandardParticleSource::getDimensionSamplingEfficiency(
                                    const PhaseSpaceDimension dimension ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  // Get the number of trials performed by each source
  ModuleTraits::InternalCounter trials =
    this->getNumberOfDimensionTrials( dimension );
  ModuleTraits::InternalCounter samples =
    this->getNumberOfDimensionSamples( dimension );

  if( trials > 0 )
    return static_cast<double>( samples )/trials;
  else
    return 1.0;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CompoundStandardParticleSource.cpp
//---------------------------------------------------------------------------//
