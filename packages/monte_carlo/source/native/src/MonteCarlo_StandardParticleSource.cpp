//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleSource.cpp
//! \author Alex Robinson
//! \brief  Distributed source class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>
#include <numeric>

// FRENSIE Includes
#include "MonteCarlo_StandardParticleSource.hpp"
#include "MonteCarlo_ParticleSourcePhaseSpacePoint.hpp"
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "MonteCarlo_ParticleStateFactory.hpp"
#include "Utility_CommHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
StandardParticleSource::StandardParticleSource(
   const unsigned id,
   const ParticleType particle_type,
   const std::vector<std::shared_ptr<const ParticleSourceDimension> >&
   independent_dimensions,
   const std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>&
   spatial_coord_conversion_policy,
   const std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>&
   directional_coord_conversion_policy)
  : d_id( id ),
    d_particle_type( particle_type ),
    d_independent_dimensions( independent_dimensions ),
    d_spatial_coord_conversion_policy( spatial_coord_conversion_policy ),
    d_directional_coord_conversion_policy( directional_coord_conversion_policy ),
    d_cell_rejection_functions(),
    d_number_of_trials( 1, 0ull ),
    d_number_of_samples( 1, 0ull )
{ 
  // Make sure the conversion policies are valid
  testPrecondition( spatial_coord_conversion_policy.get() );
  testPrecondition( directional_coord_conversion_policyt.get() );
}

// Enable thread support
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::enableThreadSupport( const unsigned threads )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure a valid number of threads has been requested
  testPrecondition( threads > 0 );

  d_number_of_trials.resize( threads, 0ull );
  d_number_of_samples.resize( threads, 0ull );
}

// Reset the source data
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::resetData()
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  for( unsigned i = 0; i < d_number_of_trials.size(); ++i )
  {
    d_number_of_trials[i] = 0ull;
    d_number_of_samples[i] = 0ull;
  }
}

// Reduce the source data
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::reduceData(
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
                                              d_number_of_trials.size(),
                                              d_number_of_trials.getRawPtr(),
                                              d_number_of_trials.getRawPtr() );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Error: unable to reduce the source trials!" );

    try{
      Teuchos::reduceAll<unsigned long long>( *comm,
                                              Teuchos::REDUCE_SUM,
                                              d_number_of_samples.size(),
                                              d_number_of_samples.getRawPtr(),
                                              d_number_of_samples.getRawPtr());
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
void StandardParticleSource::exportData(
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

  source_hdf5_file.setNumberOfSourceSamplingTrials( this->getId(), trials );

  source_hdf5_file.setNumberOfDefaultSourceSamplingTrials( trials );


  // Set the number of samples
  unsigned long long samples = this->getNumberOfSamples();

  source_hdf5_file.setNumberOfSourceSamples( this->getId(), samples );

  source_hdf5_file.setNumberOfDefaultSourceSamples( samples );
}

// Print a summary of the source data
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::printSummary( std::ostream& os ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  this->printStandardSummary( "Standard Source",
                              this->getNumberOfTrials(),
                              this->getNumberOfSamples(),
                              this->getSamplingEfficiency(),
                              os );
}

// Sample the particle state from the source
/*! \details If enableThreadSupport has been called, this method is
 * thread-safe. The cell that contains the sampled particle state will
 * not be set and must be determined by the geometry module.
 */
void StandardParticleSource::sampleParticleState(
                                             ParticleBank& bank,
					     const unsigned long long history )
{
  // Make sure thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
                    d_number_of_samples.size() );

  // Initialize the particle
  std::shared_ptr<ParticleState> particle;
    
  ParticleStateFactory::createState( particle, d_particle_type, history );

  // Initialize a source phase space point
  ParticleSourcePhaseSpacePoint phase_space_sample;
  
  // Sample the particle state
  while( true )
  {
    // Increment the trials counter
    ++d_number_of_trials[Utility::GlobalOpenMPSession::getThreadId()];

    for( unsigned i = 0; i < d_independent_dimension.size(); ++i )
      d_independent_dimensions[i]->sample( phase_space_sample );
    
    phase_space_sample.setParticleState(*d_spatial_coord_conversion_policy,
                                        *d_directional_coord_conversion_policy,
                                        *particle );

    if( this->isSampledParticlePositionValid( *particle ) )
      break;
  }

  // Increment the samples counter
  ++d_number_of_samples[Utility::GlobalOpenMPSession::getThreadId()];

  // Add the particle to the bank
  bank.push( *particle );
}

// Return the number of sampling trials
/*! \details Only the master thread should call this method.
 */
unsigned long long StandardParticleSource::getNumberOfTrials() const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  return this->reduceLocalTrialsCounters();
}

// Return the number of samples
/*! \details Only the master thread should call this method.
 */
unsigned long long StandardParticleSource::getNumberOfSamples() const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  return this->reduceLocalSamplesCounters();
}

// Get the sampling efficiency from the source distribution
/*! \details Only the master thread should call this method.
 */
double StandardParticleSource::getSamplingEfficiency() const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  // Reduce the number of samples
  unsigned long long total_samples = this->reduceLocalSamplesCounters();

  // Reduce the number of trials
  unsigned long long total_trials = this->reduceLocalTrialsCounters();

  if( total_trials > 0ull )
    return static_cast<double>( total_samples )/total_trials;
  else
    return 1.0;
}

// Get the source id
unsigned StandardParticleSource::getId() const
{
  return d_id;
}

// Check if the sampled particle position is valid
bool StandardParticleSource::isSampledParticlePositionValid(
                                          const ParticleState& particle ) const
{
  bool valid_position = false;
  
  // Check if the position is acceptable
  if( d_cell_rejection_functions.size() > 0 )
  {
    for( unsigned i = 0; i < d_cell_rejection_functions.size(); ++i )
    {
      Geometry::PointLocation location =
        d_cell_rejection_functions[i]( particle.ray() );

      if( location == Geometry::POINT_INSIDE_CELL )
      {
        valid_position = true;
        
        break;
      }
    }
  }
  else
    valid_position = true;

  return valid_position;
}

// Reduce the local samples counters
unsigned long long
StandardParticleSource::reduceLocalSamplesCounters() const
{
  return std::accumulate( d_number_of_samples.begin(),
                          d_number_of_samples.end(),
                          0ull );
}

// Reduce the local trials counters
unsigned long long StandardParticleSource::reduceLocalTrialsCounters() const
{
  return std::accumulate( d_number_of_trials.begin(),
                          d_number_of_trials.end(),
                          0ull );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSource.cpp
//---------------------------------------------------------------------------//
