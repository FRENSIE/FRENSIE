//---------------------------------------------------------------------------//
//!
//! \file   DistributedSource_def.hpp
//! \author Alex Robinson
//! \brief  Distributed source class definition.
//!
//---------------------------------------------------------------------------//

#ifndef DISTRIBUTED_SOURCE_DEF_HPP
#define DISTRIBUTED_SOURCE_DEF_HPP

// Std Lib Includes
#include <limits>

// FACEMC
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
/*! \details The distributions set in the constructor will be used for
 * sampling the initial state of a particle unless an importance (or bias) 
 * distribution is set for the particular portion of phase space. If an 
 * importance distribution is set the distribution in the constructor will be 
 * used to calculate the necessary starting particle weight to keep the 
 * estimators unbiased.
 */
template<typename GeometryHandler>
DistributedSource<GeometryHandler>::DistributedSource( 
	 const Teuchos::RCP<SpatialDistribution>& spatial_distribution,
	 const Teuchos::RCP<DirectionalDistribution>& directional_distribution,
	 const Teuchos::RCP<OneDDistribution>& energy_distribution,
	 const Teuchos::RCP<OneDDistribution>& time_distribution,
	 const ParticleType particle_type )
  : d_spatial_distribution( spatial_distribution ),
    d_spatial_importance_distribution( NULL ),
    d_directional_distribution( directional_distribution ),
    d_directional_importance_distribution( NULL ),
    d_energy_distribution( energy_distribution ),
    d_energy_importance_distribution( NULL ),
    d_time_distribution( time_distribution ),
    d_time_importance_distribution( NULL ),
    d_particle_type( particle_type ),
    d_rejection_cell( GHT::invalidCellHandle() ),
    d_number_of_trials( 0u ),
    d_number_of_samples( 0u )
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
template<typename GeometryHandler>
void DistributedSource<GeometryHandler>::setSpatialImportanceDistribution(
		const Teuchos::RCP<SpatialDistribution>& spatial_distribution )
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
template<typename GeometryHandler>
void DistributedSource<GeometryHandler>::setDirectionalImportanceDistribution(
	const Teuchos::RCP<DirectionalDistribution>& directional_distribution )
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
template<typename GeometryHandler>
void DistributedSource<GeometryHandler>::setEnergyImportanceDistribution(
		    const Teuchos::RCP<OneDDistribution>& energy_distribution )
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
template<typename GeometryHandler>
void DistributedSource<GeometryHandler>::setTimeImportanceDistribution(
		      const Teuchos::RCP<OneDDistribution>& time_distribution )
{
  // Make sure that the distribution has been set
  testPrecondition( !time_distribution.is_null() );

  d_time_importance_distribution = time_distribution;
}

template<typename GeometryHandler>
template<typename CellHandle>
void DistributedSource<GeometryHandler>::setRejectionCell( 
						       const CellHandle& cell )
{
  // Make sure that the CellHandle is compatible with the geometry handler
  testStaticPrecondition((boost::is_same<CellHandle,typename GHT::CellHandle>::value));

  d_rejection_cell = cell;
}


// Sample the particle state from the source
template<typename GeometryHandler>
void DistributedSource<GeometryHandler>::sampleParticleState( 
						 BasicParticleState& particle )
{  
  // Set the particle type
  particle.setParticleType( d_particle_type );
  
  // Initialize the particle weight
  particle.setWeight( 1.0 );

  // Sample the particle direction
  sampleParticleDirection( particle );

  // Sample the particle position
  // NOTE: The particle direction must be sampled first in case cell rejection
  // sampling is done (which requires the particle direction)
  sampleParticlePosition( particle );

  // Sample the particle energy
  sampleParticleEnergy( particle );

  // Sample the particle start time
  sampleParticleTime( particle );
}

// Get the sampling efficiency from the source distribution
template<typename GeometryHandler>
double DistributedSource<GeometryHandler>::getSamplingEfficiency() const
{
  return static_cast<double>( d_number_of_samples )/d_number_of_trials;
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
template<typename GeometryHandler>
void DistributedSource<GeometryHandler>::sampleParticlePosition(
						 BasicParticleState& particle )
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

    // Test if the point is in the rejection cell
    if( d_rejection_cell != GHT::invalidCellHandle() )
    {
      PointLocation location = GHT::getParticleLocation( 
						     d_rejection_cell,
						     position,
						     particle.getDirection() );
      if( location == POINT_INSIDE_CELL )
	break;
      else
      {
	position_weight = 1.0;
	
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
  ++d_number_of_trials;
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
template<typename GeometryHandler>
void DistributedSource<GeometryHandler>::sampleParticleDirection(
						 BasicParticleState& particle )
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
template<typename GeometryHandler>
void DistributedSource<GeometryHandler>::sampleParticleEnergy(
						 BasicParticleState& particle )
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
template<typename GeometryHandler>
void DistributedSource<GeometryHandler>::sampleParticleTime(
						 BasicParticleState& particle )
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

} // end FACEMC namespace

#endif // end DISTRIBUTED_SOURCE_DEF_HPP

//---------------------------------------------------------------------------//
// end DistributedSource_def.hpp
//---------------------------------------------------------------------------//
