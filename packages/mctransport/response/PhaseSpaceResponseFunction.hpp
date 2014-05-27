//---------------------------------------------------------------------------//
//!
//! \file   PhaseSpaceResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Phase space dependent response function declaration
//!
//---------------------------------------------------------------------------//

#ifndef PHASE_SPACE_RESPONSE_FUNCTION_HPP
#define PHASE_SPACE_RESPONSE_FUNCTION_HPP

// FACEMC Includes
#include "ResponseFunction.hpp"
#include "OneDDistribution.hpp"
#include "SpatialDistribution.hpp"
#include "DirectionalDistribution.hpp"

namespace FACEMC{

//! The phase space response function
class PhaseSpaceResponseFunction : public ResponseFunction
{
  
public:

  //! Constructor
  PhaseSpaceResponseFunction( 
	 const std::string& name,			      
	 const Teuchos::RCP<SpatialDistribution>& spatial_distribution,
	 const Teuchos::RCP<DirectionalDistribution>& directional_distribution,
	 const Teuchos::RCP<OneDDistribution>& energy_distribution,
	 const Teuchos::RCP<OneDDistribution>& time_distribution );

  //! Destructor
  ~PhaseSpaceResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const;

private:

  // The spatial distribution
  Teuchos::RCP<SpatialDistribution> d_spatial_distribution;

  // The directional distribution
  Teuchos::RCP<DirectionalDistribution> d_directional_distribution;

  // The energy distribution
  Teuchos::RCP<OneDDistribution> d_energy_distribution;

  // The time distribution
  Teuchos::RCP<OneDDistribution> d_time_distribution;

  // Records if the response function is spatially uniform
  bool d_spatially_uniform;
};

} // end FACEMC namespace

#endif // end PHASE_SPACE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end PhaseSpaceResponseFunction.hpp
//---------------------------------------------------------------------------//
