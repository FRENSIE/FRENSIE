//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_OnePhaseSpaceDimensionParticleResponseFunction.hpp
//! \author Alex Robinson
//! \brief  One phase-space dimension particle response function class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ONE_PHASE_SPACE_DIMENSION_PARTICLE_RESPONSE_FUNCTION_HPP
#define MONTE_CARLO_ONE_PHASE_SPACE_DIMENSION_PARTICLE_RESPONSE_FUNCTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_UnivariateDistribution.hpp"

namespace MonteCarlo{

//! The one-dimensional particle response function
template<PhaseSpaceDimension dimension>
class OnePhaseSpaceDimensionParticleResponseFunction : public ParticleResponseFunction
{

public:

  //! Distribution constructor
  OnePhaseSpaceDimensionParticleResponseFunction(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  dimension_distribution );

  //! Raw distribution constructor
  OnePhaseSpaceDimensionParticleResponseFunction(
                                   const std::vector<double> dimension_grid,
                                   const std::vector<double> response_values );

  //! Destructor
  ~OnePhaseSpaceDimensionParticleResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const final override;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const final override;

  //! Get a description of the response function
  std::string description() const final override;

private:

  //! Default constructor
  OnePhaseSpaceDimensionParticleResponseFunction()
  { /* ... */ }

  // The dimension distribution
  std::shared_ptr<const Utility::UnivariateDistribution>
  d_dimension_response_distribution;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_OnePhaseSpaceDimensionParticleResponseFunction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ONE_PHASE_SPACE_DIMENSION_PARTICLE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MontCarlo_OnePhaseSpaceDimensionParticleResponseFunction.hpp
//---------------------------------------------------------------------------//
