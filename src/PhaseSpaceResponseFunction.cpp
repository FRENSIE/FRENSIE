//---------------------------------------------------------------------------//
//!
//! \file   PhaseSpaceResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Phase space dependent reponse function definition
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "PhaseSpaceResponseFunction.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
PhaseSpaceResponseFunction::PhaseSpaceResponseFunction(
         const std::string& name,			      
	 const Teuchos::RCP<SpatialDistribution>& spatial_distribution,
	 const Teuchos::RCP<DirectionalDistribution>& directional_distribution,
	 const Teuchos::RCP<OneDDistribution>& energy_distribution,
	 const Teuchos::RCP<OneDDistribution>& time_distribution )
  : ResponseFunction( name ),
    d_spatial_distribution( spatial_distribution ),
    d_directional_distribution( directional_distribution ),
    d_energy_distribution( energy_distribution ),
    d_time_distribution( time_distribution ),
    d_spatially_uniform( false )
{
  // Make sure that the distributions have been set
  testPrecondition( !spatial_distribution.is_null() );
  testPrecondition( !directional_distribution.is_null() );
  testPrecondition( !energy_distribution.is_null() );
  testPrecondition( !time_distribution.is_null() );

  // Determine if the response function is spatially uniform
  if( spatial_distribution->isUniform() )
    d_spatially_uniform = true;
}

// Evaluate the response function at the desired phase space point
double PhaseSpaceResponseFunction::evaluate( 
				     const BasicParticleState& particle ) const
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


} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end PhaseSpaceResponseFunction.cpp
//---------------------------------------------------------------------------//
