//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FullPhaseSpaceParticleResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Full phase-space particle response function class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_FULL_PHASE_SPACE_PARTICLE_RESPONSE_FUNCTION_HPP
#define MONTE_CARLO_FULL_PHASE_SPACE_PARTICLE_RESPONSE_FUNCTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleResponseFunction.hpp"
#include "MonteCarlo_ParticleDistribution.hpp"

namespace MonteCarlo{

//! The detailed response function class
class FullPhaseSpaceParticleResponseFunction : public ParticleResponseFunction
{

public:

  //! Constructor
  FullPhaseSpaceParticleResponseFunction(
            const std::shared_ptr<const ParticleDistribution>& particle_dist );

  //! Destructor
  ~FullPhaseSpaceParticleResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const final override;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const final override;

  //! Get a description of the response function
  std::string description() const final override;

private:

  // The particle distribution
  std::shared_ptr<const ParticleDistribution> d_particle_dist;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_FULL_PHASE_SPACE_PARTICLE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FullPhaseSpaceParticleResponseFunction.hpp
//---------------------------------------------------------------------------//
