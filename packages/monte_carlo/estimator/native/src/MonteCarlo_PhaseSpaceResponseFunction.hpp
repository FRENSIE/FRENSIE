//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Phase space dependent response function declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PHASE_SPACE_RESPONSE_FUNCTION_HPP
#define FACEMC_PHASE_SPACE_RESPONSE_FUNCTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ResponseFunction.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_SpatialDistribution.hpp"
#include "Utility_DirectionalDistribution.hpp"

namespace MonteCarlo{

//! The phase space response function
class PhaseSpaceResponseFunction : public ResponseFunction
{
  
public:

  //! Constructor
  PhaseSpaceResponseFunction( 
	const unsigned id,
	const std::string& name,			      
	const Teuchos::RCP<Utility::SpatialDistribution>& spatial_distribution,
        const Teuchos::RCP<Utility::DirectionalDistribution>& 
	directional_distribution,
	const Teuchos::RCP<Utility::OneDDistribution>& energy_distribution,
	const Teuchos::RCP<Utility::OneDDistribution>& time_distribution );

  //! Destructor
  ~PhaseSpaceResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const;

private:

  // The spatial distribution
  Teuchos::RCP<Utility::SpatialDistribution> d_spatial_distribution;

  // The directional distribution
  Teuchos::RCP<Utility::DirectionalDistribution> d_directional_distribution;

  // The energy distribution
  Teuchos::RCP<Utility::OneDDistribution> d_energy_distribution;

  // The time distribution
  Teuchos::RCP<Utility::OneDDistribution> d_time_distribution;

  // Records if the response function is spatially uniform
  bool d_spatially_uniform;
};

} // end MonteCarlo namespace

#endif // end MonteCarlo_PHASE_SPACE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceResponseFunction.hpp
//---------------------------------------------------------------------------//
