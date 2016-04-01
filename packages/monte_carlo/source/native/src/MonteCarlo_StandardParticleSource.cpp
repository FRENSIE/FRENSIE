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
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "MonteCarlo_ParticleStateFactory.hpp"
#include "Utility_CommHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
/*! \details The distributions set in the constructor will be used for
 * sampling the initial state of a particle unless an importance (or bias) 
 * distribution is set for the particular portion of phase space. If an 
 * importance distribution is set the distribution in the constructor will be 
 * used to calculate the necessary starting particle weight to keep the 
 * estimators unbiased.
 */
StandardParticleSource::StandardParticleSource( 
     const unsigned id,
     const std::shared_ptr<Utility::SpatialDistribution>& spatial_distribution,
     const std::shared_ptr<Utility::DirectionalDistribution>& 
     directional_distribution,
     const std::shared_ptr<Utility::OneDDistribution>& 
     energy_distribution,
     const std::shared_ptr<Utility::OneDDistribution>& 
     time_distribution,
     const ParticleType particle_type )
  : d_id( id ),
    d_spatial_distribution( spatial_distribution ),
    d_spatial_importance_distribution( NULL ),
    d_directional_distribution( directional_distribution ),
    d_directional_importance_distribution( NULL ),
    d_energy_distribution( energy_distribution ),
    d_energy_importance_distribution( NULL ),
    d_time_distribution( time_distribution ),
    d_time_importance_distribution( NULL ),
    d_particle_type( particle_type ),
    d_cell_rejection_functions(),
    d_number_of_trials( 1, 0ull ),
    d_number_of_samples( 1, 0ull )
{
  // Make sure that the distributions have been set
  testPrecondition( spatial_distribution.get() );
  testPrecondition( directional_distribution.get() );
  testPrecondition( energy_distribution.get() );
  testPrecondition( time_distribution.get() );
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

// Set the spatial importance distribution
/*! \details The spatial importance distribution will be used to sample 
 * particle positions. The spatial distribution will only be used to determine
 * the necessary weight of the particle to prevent biasing the estimators.
 * Only the master thread should call this method.
 */ 
void StandardParticleSource::setSpatialImportanceDistribution(
    const std::shared_ptr<Utility::SpatialDistribution>& spatial_distribution )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure that the distribution has been set
  testPrecondition( spatial_distribution.get() );
  
  d_spatial_importance_distribution = spatial_distribution;
}

// Set the directional importance distribution
/*! \details The directional importance distribution will be used to sample
 * particle positions. The directional distribution will only be used to 
 * determine the necessary weight of the particle to prevent biasing the 
 * estimators. Only the master thread should call this method.
 */ 
void StandardParticleSource::setDirectionalImportanceDistribution( 
                       const std::shared_ptr<Utility::DirectionalDistribution>&
		       directional_distribution )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure that the distribution has been set
  testPrecondition( directional_distribution.get() );

  d_directional_importance_distribution = directional_distribution;
}					 

// Set the energy importance distribution
/*! \details The energy importance distribution will be used to sample
 * particle positions. The energy distribution will only be used to determine
 * the necessary weight of the particle to prevent biasing the estimators.
 * Only the master thread should call this method.
 */
void StandardParticleSource::setEnergyImportanceDistribution(
	const std::shared_ptr<Utility::OneDDistribution>& energy_distribution )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure that the distribution has been set
  testPrecondition( energy_distribution.get() );

  d_energy_importance_distribution = energy_distribution;
}

// Set the time importance distribution
/*! \details The time importance distribution will be used to sample
 * particle start times. The time distribution will only be used to determine
 * the necessary weight of the particle to prevent biasing the estimators.
 * Only the master thread should call this method.
 */ 
void StandardParticleSource::setTimeImportanceDistribution(
	  const std::shared_ptr<Utility::OneDDistribution>& time_distribution )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure that the distribution has been set
  testPrecondition( time_distribution.get() );

  d_time_importance_distribution = time_distribution;
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
    
  // Initialize the particle weight
  particle->setWeight( 1.0 );

  // Sample the particle direction
  sampleParticleDirection( *particle );

  // Sample the particle position
  // NOTE: The particle direction must be sampled first in case cell rejection
  // sampling is done (which requires the particle direction)
  sampleParticlePosition( *particle );

  // Sample the particle energy
  sampleParticleEnergy( *particle );

  // Sample the particle start time
  sampleParticleTime( *particle );

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

// Sample the particle position
/*! \details The particle position will be sampled from the spatial
 * spatial distribution that was specified. If a spatial importance function
 * has been set, the particle position will instead be sampled from the 
 * importance function with the weight of the particle multiplied by the
 * PDF value of the original function divided by the importance PDF value
 * corresponding to the sampled point. If a rejection cell has been set, the
 * sampled position will only be kept if it lies within the rejection cell.
 * The efficiency of the rejection sampling is also recorded.
 * \note The particle direction must be sampled first in case cell rejection
 * sampling is done (which requires a particle direction to work effectively).
 */
void StandardParticleSource::sampleParticlePosition( ParticleState& particle )
{
  // Make sure thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() < 
                    d_number_of_trials.size() );
  
  double position[3];
  double position_weight = 1.0;
  
  while( true )  
  {
    if( !d_spatial_importance_distribution.get() )
      d_spatial_distribution->sample( position );
    else
    {
      d_spatial_importance_distribution->sample( position );
      
      double spatial_weight_numerator = 
	d_spatial_distribution->evaluatePDF( position );

      double spatial_weight_denominator = 
	d_spatial_importance_distribution->evaluatePDF( position );
      
      // If both evaluate to 0, a weight of 1 is desired but nan will result
      if( spatial_weight_numerator > 0.0 || spatial_weight_denominator > 0.0 )
	position_weight = spatial_weight_numerator/spatial_weight_denominator;
    }

    // Assign the position to the particle
    particle.setPosition( position );

    // Check if the position is acceptable
    if( d_cell_rejection_functions.size() > 0 )
    {
      bool valid_position = false;
      
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

      if( valid_position )
        break;
      else // Position rejected - sample a new one
      {
	position_weight = 1.0;
	
        ++d_number_of_trials[Utility::GlobalOpenMPSession::getThreadId()];
      }
    }
    // No rejection cells to test
    else
      break;
  }
  
  // Increment the number of trials and samples
  ++d_number_of_trials[Utility::GlobalOpenMPSession::getThreadId()];

  ++d_number_of_samples[Utility::GlobalOpenMPSession::getThreadId()];

  // Make sure the weight is valid
  testPostcondition( !ST::isnaninf( position_weight ) );
  testPostcondition( position_weight > 0.0 );
  
  particle.multiplyWeight( position_weight );
}

// Sample the particle direction
/*! \details The particle direction will be sampled from the directional
 * distribution that was specified. If a directional importance function
 * has been set, the particle direction will instead be sampled from the 
 * importance function with the weight of the particle multiplied by the
 * PDF value of the original function divided by the importance PDF value
 * corresponding to the sampled point.
 */
void StandardParticleSource::sampleParticleDirection( ParticleState& particle )
{
  double direction[3];
  double direction_weight = 1.0;

  if( !d_directional_importance_distribution.get() )
    d_directional_distribution->sample( direction );
  else
  {
    d_directional_importance_distribution->sample( direction );

    double directional_weight_numerator = 
      d_directional_distribution->evaluatePDF( direction );

    double directional_weight_denominator = 
      d_directional_importance_distribution->evaluatePDF( direction );

    // If both evaluate to 0, a weight of 1 is desired but nan will result
    if( directional_weight_numerator > 0.0 ||
	directional_weight_denominator > 0.0 )
    {
      direction_weight = directional_weight_numerator/
	directional_weight_denominator;
    }
  }

  // Make sure the weight is valid
  testPostcondition( !ST::isnaninf( direction_weight ) );
  testPostcondition( direction_weight > 0.0 );

  particle.setDirection( direction );
  particle.multiplyWeight( direction_weight );
}

// Sample the particle energy
/*! \details The particle energy will be sampled from the energy
 * distribution that was specified. If an energy importance function
 * has been set, the particle energy will instead be sampled from the 
 * importance function with the weight of the particle multiplied by the
 * PDF value of the original function divided by the importance PDF value
 * corresponding to the sampled point.
 */
void StandardParticleSource::sampleParticleEnergy( ParticleState& particle )
{
  double energy;
  double energy_weight = 1.0;

  if( !d_energy_importance_distribution.get() )
    energy = d_energy_distribution->sample();
  else
  {
    energy = d_energy_importance_distribution->sample();
    
    double energy_weight_numerator = 
      d_energy_distribution->evaluatePDF( energy );
    
    double energy_weight_denominator = 
      d_energy_importance_distribution->evaluatePDF( energy );
    
    // If both evaluate to 0, a weight of 1 is desired but nan will result
    if( energy_weight_numerator > 0.0 || energy_weight_denominator > 0.0 )
      energy_weight = energy_weight_numerator/energy_weight_denominator;
  }
  
  // Make sure the weight is valid
  testPostcondition( !ST::isnaninf( energy_weight ) );
  testPostcondition( energy_weight > 0.0 );

  particle.setEnergy( energy );
  particle.multiplyWeight( energy_weight );
}

// Sample the particle time
/*! \details The particle time will be sampled from the time
 * distribution that was specified. If a time importance function
 * has been set, the particle time will instead be sampled from the 
 * importance function with the weight of the particle multiplied by the
 * PDF value of the original function divided by the importance PDF value
 * corresponding to the sampled point.
 */
void StandardParticleSource::sampleParticleTime( ParticleState& particle )
{
  
  double time;
  double time_weight = 1.0;
  
  if( !d_time_importance_distribution.get() )
    time = d_time_distribution->sample();
  else
  {
    time = d_time_importance_distribution->sample();

    double time_weight_numerator = 
      d_time_distribution->evaluatePDF( time );

    double time_weight_denominator = 
      d_time_importance_distribution->evaluatePDF( time );

    // If both evaluate to 0, a weight of 1 is desired but nan will result
    if( time_weight_numerator > 0.0 || time_weight_denominator > 0.0 )
      time_weight = time_weight_numerator/time_weight_denominator;
  }

  // Make sure the weight is valid
  testPostcondition( !ST::isnaninf( time_weight ) );
  testPostcondition( time_weight > 0.0 );

  particle.setTime( time );
  particle.multiplyWeight( time_weight );
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
