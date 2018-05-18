//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Detailed response function class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DETAILED_RESPONSE_FUNCTION_HPP
#define MONTE_CARLO_DETAILED_RESPONSE_FUNCTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ResponseFunction.hpp"
#include "MonteCarlo_ParticleDistribution.hpp"

namespace MonteCarlo{

//! The detailed response function class
class DetailedResponseFunction : public ResponseFunction
{

public:

  //! Constructor
  DetailedResponseFunction(
            const std::shared_ptr<const ParticleDistribution>& particle_dist );

  //! Destructor
  ~DetailedResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const final override;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const final override;

private:

  // The particle distribution
  std::shared_ptr<const ParticleDistribution> d_particle_dist;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DETAILED_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedResponseFunction.hpp
//---------------------------------------------------------------------------//
