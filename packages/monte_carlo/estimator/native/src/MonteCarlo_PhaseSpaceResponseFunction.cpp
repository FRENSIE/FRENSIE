//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Phase space dependent reponse function definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceResponseFunction.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
PhaseSpaceResponseFunction::PhaseSpaceResponseFunction(
     const unsigned id,
     const std::string& name,			      
     const std::shared_ptr<Utility::SpatialDistribution>& spatial_distribution,
     const std::shared_ptr<Utility::DirectionalDistribution>& 
     directional_distribution,
     const std::shared_ptr<Utility::OneDDistribution>& energy_distribution,
     const std::shared_ptr<Utility::OneDDistribution>& time_distribution )
  : ResponseFunction( id, name ),
    d_spatial_distribution( spatial_distribution ),
    d_directional_distribution( directional_distribution ),
    d_energy_distribution( energy_distribution ),
    d_time_distribution( time_distribution ),
    d_spatially_uniform( false )
{
  // Make sure that the distributions have been set
  testPrecondition( spatial_distribution.get() );
  testPrecondition( directional_distribution.get() );
  testPrecondition( energy_distribution.get() );
  testPrecondition( time_distribution.get() );

  // Determine if the response function is spatially uniform
  if( spatial_distribution->isUniform() )
    d_spatially_uniform = true;
}

// Evaluate the response function at the desired phase space point
double PhaseSpaceResponseFunction::evaluate( 
				          const ParticleState& particle ) const
{
  double spatial_response = 
    d_spatial_distribution->evaluate( particle.getPosition() );
  
  double directional_response = 
    d_directional_distribution->evaluate( particle.getDirection() );

  double energy_response = 
    d_energy_distribution->evaluate( particle.getEnergy() );

  double time_response = 
    d_time_distribution->evaluate( particle.getTime() );

  return spatial_response*directional_response*energy_response*time_response;
}

// Check if the response function is spatially uniform
bool PhaseSpaceResponseFunction::isSpatiallyUniform() const
{
  return d_spatially_uniform;
}


} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceResponseFunction.cpp
//---------------------------------------------------------------------------//
