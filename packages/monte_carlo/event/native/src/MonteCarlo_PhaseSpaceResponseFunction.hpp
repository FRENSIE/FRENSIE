//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Phase space dependent response function declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHASE_SPACE_RESPONSE_FUNCTION_HPP
#define MONTE_CARLO_PHASE_SPACE_RESPONSE_FUNCTION_HPP

// Std Lib Includes
#include <memory>

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
     const std::shared_ptr<Utility::SpatialDistribution>& spatial_distribution,
     const std::shared_ptr<Utility::DirectionalDistribution>& 
     directional_distribution,
     const std::shared_ptr<Utility::OneDDistribution>& energy_distribution,
     const std::shared_ptr<Utility::OneDDistribution>& time_distribution );

  //! Destructor
  ~PhaseSpaceResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const;

private:

  // The spatial distribution
  std::shared_ptr<Utility::SpatialDistribution> d_spatial_distribution;

  // The directional distribution
  std::shared_ptr<Utility::DirectionalDistribution> d_directional_distribution;

  // The energy distribution
  std::shared_ptr<Utility::OneDDistribution> d_energy_distribution;

  // The time distribution
  std::shared_ptr<Utility::OneDDistribution> d_time_distribution;

  // Records if the response function is spatially uniform
  bool d_spatially_uniform;
};

} // end MonteCarlo namespace

#endif // end MonteCarlo_PHASE_SPACE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceResponseFunction.hpp
//---------------------------------------------------------------------------//
