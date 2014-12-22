//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DistributedSource.cpp
//! \author Alex Robinson
//! \brief  Distributed source class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_DistributedSource.hpp"
#include "MonteCarlo_ParticleStateFactory.hpp"
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
DistributedSource::DistributedSource( 
	const unsigned id,
	const Teuchos::RCP<Utility::SpatialDistribution>& spatial_distribution,
        const Teuchos::RCP<Utility::DirectionalDistribution>& 
	directional_distribution,
	const Teuchos::RCP<Utility::OneDDistribution>& 
	energy_distribution,
	const Teuchos::RCP<Utility::OneDDistribution>& 
	time_distribution,
	const ParticleType particle_type,
	getLocationFunction get_particle_location_func )
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
    d_rejection_cell( Geometry::ModuleTraits::invalid_internal_cell_handle ),
    d_number_of_trials( 0u ),
    d_number_of_samples( 0u ),
    d_get_particle_location_func( get_particle_location_func )
    
{
  // Make sure that the distributions have been set
  testPrecondition( !spatial_distribution.is_null() );
  testPrecondition( !directional_distribution.is_null() );
  testPrecondition( !energy_distribution.is_null() );
  testPrecondition( !time_distribution.is_null() );
}

// Set the spatial importance distribution
/*! \details The spatial importance distribution will be used to sample 
 * particle positions. The spatial distribution will only be used to determine
 * the necessary weight of the particle to prevent biasing the estimators.
 */ 
void DistributedSource::setSpatialImportanceDistribution(
       const Teuchos::RCP<Utility::SpatialDistribution>& spatial_distribution )
{
  // Make sure that the distribution has been set
  testPrecondition( !spatial_distribution.is_null() );
  
  d_spatial_importance_distribution = spatial_distribution;
}

// Set the directional importance distribution
/*! \details The directional importance distribution will be used to sample
 * particle positions. The directional distribution will only be used to 
 * determine the necessary weight of the particle to prevent biasing the 
 * estimators.
 */ 
void DistributedSource::setDirectionalImportanceDistribution( 
                          const Teuchos::RCP<Utility::DirectionalDistribution>&
			  directional_distribution )
{
  // Make sure that the distribution has been set
  testPrecondition( !directional_distribution.is_null() );

  d_directional_importance_distribution = directional_distribution;
}					 

// Set the energy importance distribution
/*! \details The energy importance distribution will be used to sample
 * particle positions. The energy distribution will only be used to determine
 * the necessary weight of the particle to prevent biasing the estimators.
 */
void DistributedSource::setEnergyImportanceDistribution(
	   const Teuchos::RCP<Utility::OneDDistribution>& energy_distribution )
{
  // Make sure that the distribution has been set
  testPrecondition( !energy_distribution.is_null() );

  d_energy_importance_distribution = energy_distribution;
}

// Set the time importance distribution
/*! \details The time importance distribution will be used to sample
 * particle start times. The time distribution will only be used to determine
 * the necessary weight of the particle to prevent biasing the estimators.
 */ 
void DistributedSource::setTimeImportanceDistribution(
	     const Teuchos::RCP<Utility::OneDDistribution>& time_distribution )
{
  // Make sure that the distribution has been set
  testPrecondition( !time_distribution.is_null() );

  d_time_importance_distribution = time_distribution;
}

void DistributedSource::setRejectionCell( 
		       const Geometry::ModuleTraits::InternalCellHandle& cell )
{
  d_rejection_cell = cell;
}

// Sample the particle state from the source
void DistributedSource::sampleParticleState( ParticleBank& bank,
					     const unsigned long long history )
{  
  // Initialize the particle
  ParticleState::pointerType particle = 
    ParticleStateFactory::createState( d_particle_type, history );
    
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
  bank.push( particle );
}

// Get the sampling efficiency from the source distribution
double DistributedSource::getSamplingEfficiency() const
{
  return static_cast<double>( d_number_of_samples )/d_number_of_trials;
}

// Get the source id
unsigned DistributedSource::getId() const
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
void DistributedSource::sampleParticlePosition( ParticleState& particle )
{
  double position[3];
  double position_weight = 1.0;
  
  while( true )  
  {
    if( d_spatial_importance_distribution.is_null() )
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

    if( d_rejection_cell != 
	Geometry::ModuleTraits::invalid_internal_cell_handle )
    {
      Geometry::Ray ray( position, particle.getDirection() );
            
      Geometry::PointLocation location = (*d_get_particle_location_func)( 
							    ray,
							    d_rejection_cell );
      
      if( location == Geometry::POINT_INSIDE_CELL )
	break;
      else
      {
	position_weight = 1.0;
	
	#pragma omp atomic update
	++d_number_of_trials;
      }
    }
    // No rejection cell to test
    else
      break;
  }

  // Make sure the weight is valid
  testPostcondition( !ST::isnaninf( position_weight ) );
  testPostcondition( position_weight > 0.0 );
  
  particle.setPosition( position );
  particle.multiplyWeight( position_weight );

  // Increment the number of trials and samples
  #pragma omp atomic update
  ++d_number_of_trials;

  #pragma omp atomic update
  ++d_number_of_samples;
}

// Sample the particle direction
/*! \details The particle direction will be sampled from the directional
 * distribution that was specified. If a directional importance function
 * has been set, the particle direction will instead be sampled from the 
 * importance function with the weight of the particle multiplied by the
 * PDF value of the original function divided by the importance PDF value
 * corresponding to the sampled point.
 */
void DistributedSource::sampleParticleDirection( ParticleState& particle )
{
  double direction[3];
  double direction_weight = 1.0;

  if( d_directional_importance_distribution.is_null() )
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
void DistributedSource::sampleParticleEnergy( ParticleState& particle )
{
  double energy;
  double energy_weight = 1.0;

  if( d_energy_importance_distribution.is_null() )
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
void DistributedSource::sampleParticleTime( ParticleState& particle )
{
  
  double time;
  double time_weight = 1.0;
  
  if( d_time_importance_distribution.is_null() )
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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DistributedSource.cpp
//---------------------------------------------------------------------------//
