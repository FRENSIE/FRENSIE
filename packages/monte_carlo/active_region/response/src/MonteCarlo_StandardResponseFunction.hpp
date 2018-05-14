//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Standard response function class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_RESPONSE_FUNCTION_HPP
#define MONTE_CARLO_STANDARD_RESPONSE_FUNCTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ResponseFunction.hpp"
#include "MonteCarlo_ParticleDistribution.hpp"

namespace MonteCarlo{

//! The standard response function class
class StandardResponseFunction : public ResponseFunction
{

public:

  //! The particle distribution pointer type
  typedef std::shared_ptr<const ParticleDistribution>
  ParticleDistributionPointer;

  //! Constructor
  StandardResponseFunction( const ParticleDistributionPointer& particle_dist );

  //! Destructor
  ~StandardResponseFunction()
  { /* ... */ }

  //! Return the id
  ModuleTraits::InternalROIHandle getId() const override;

  //! Return the name of the response function
  const std::string& getName() const override;

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const override;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const override;

private:

  // The particle distribution
  ParticleDistributionPointer d_particle_dist;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardResponseFunction.hpp
//---------------------------------------------------------------------------//
