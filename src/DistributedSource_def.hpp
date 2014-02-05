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
	   const Teuchos::RCP<DirectionalDistribution>& direction_distribution,
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
DistributedSource<GeometryHandler>::setSpatialImportanceDistribution(
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
DistributedSource<GeometryHandler>::setDirectionalImportanceDistribution(
	const Teuchos::RCP<DirectionalDistribution>& directional_distribution )
{
  // Make sure that the distribution has been set
  testPrecondition( !spatial_distribution.is_null() );

  d_directional_importance_distribution = directional_distribution;
}					 

// Set the energy importance distribution
/*! \details The energy importance distribution will be used to sample
 * particle positions. The energy distribution will only be used to determine
 * the necessary weight of the particle to prevent biasing the estimators.
 */
template<typename GeometryHandler>
DistributedSource<GeometryHandler>::setEnergyImportanceDistribution(
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
DistributedSource<GeometryHandler>::setTimeImportanceDistribution(
		      const Teuchos::RCP<OneDDistribution>& time_distribution )
{
  // Make sure that the distribution has been set
  testPrecondition( !time_distribution.is_null() );

  d_time_importance_distribution = time_distribution;
}

// Sample the particle state from the source
template<typename GeometryHandler>
template<typename ParticleState>
DistributedSource<GeometryHandler>::sampleParticleState( 
						      ParticleState& particle )
{
  // Make sure that the particle state is compatible with the geometry handler
  testStaticPrecondition((boost::is_same<typename ParticleState::CellHandle,
			  typename GHT::CellHandle));
  
  // Keep track of the starting particle weight
  double weight = 1.0;
  
  // Sample the particle position
  double position[3];
  double position_weight = 1.0;
  
  while( true )  
  {
    if( d_spatial_importance_distribution.is_null() )
      d_spatial_distribution.sample( position );
    else
    {
      d_spatial_importance_distribution.sample( position );
      
      position_weight *= d_spatial_distribution.evaluatePDF( position )/
	d_spatial_importance_distribution.evaluatePDF( position );
    }

    // Test if the point is in the rejection cell
    if( d_rejection_cell != GHT::invalidCellHandle() )
    {
      PointLocation location = GHT::getParticleLocation( d_rejection_cell,
							 position );
      if( location == POINT_INSIDE_CELL )
	break;
      else
	++d_number_of_trials;
    }
    // No rejection cell to test
    else
      break;
  }
  
  weight *= position_weight;
  
  // Sample the particle direction
  double direction[3];

  if( d_directional_importance_distribution.is_null() )
    d_directional_distribution.sample( direction );
  else
  {
    d_directional_importance_distribution.sample( direction );

    weight *= d_directional_distribution.evaluatePDF( direction )/
      d_directional_importance_distribution.evaluatePDF( direction );
  }

  // Sample the particle energy
  double energy = 14.1;

  if( d_energy_importance_distribution.is_null() )
    energy = d_energy_distribution.sample();
  else
  {
    energy = d_energy_importance_distribution.sample();

    weight *= d_energy_distribution.evaluatePDF( energy )/
      d_energy_importance_distribution.evaluatePDF( energy );
  }

  // Sample the particle start time
  double time = 0.0;
  
  if( d_time_importance_distribution.is_null() )
    time = d_time_distribution.sample();
  else
  {
    time = d_time_importance_distribution.sample();

    weight *= d_time_distribution.evaluatePDF( time )/
      d_time_importance_distribution.evaluatePDF( time );
  }

  // Set the particle state
  particle.setType( d_particle_type );
  particle.setPosition( position );
  particle.setDirection( direction );
  particle.setEnergy( energy );
  particle.setTime( time );
  particle.setWeight( weight );  

  // Increment the number of trials and samples
  ++d_number_of_trials;
  ++d_number_of_samples;
}

// Get the sampling efficiency from the source distribution
template<typename GeometryHandler>
void DistributedSource<GeometryHandler>::getSamplingEfficiency() const
{
  return static_cast<double>( d_number_of_samples )/d_number_of_trials;
}

} // end FACEMC namespace

#endif // end DISTRIBUTED_SOURCE_DEF_HPP

//---------------------------------------------------------------------------//
// end DistributedSource_def.hpp
//---------------------------------------------------------------------------//
