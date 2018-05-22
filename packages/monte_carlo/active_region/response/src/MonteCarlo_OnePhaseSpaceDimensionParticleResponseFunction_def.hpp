//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_OnePhaseSpaceDimensionParticleResponseFunction.hpp
//! \author Alex Robinson
//! \brief  One phase-space dimension particle response function class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ONE_PHASE_SPACE_DIMENSION_PARTICLE_RESPONSE_FUNCTION_DEF_HPP
#define MONTE_CARLO_ONE_PHASE_SPACE_DIMENSION_PARTICLE_RESPONSE_FUNCTION_DEF_HPP

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Distribution constructor
template<PhaseSpaceDimension dimension>
OnePhaseSpaceDimensionParticleResponseFunction<dimension>::OnePhaseSpaceDimensionParticleResponseFunction(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  dimension_distribution )
  : d_dimension_response_distribution( dimension_distribution )
{
  // Make sure that the response distribution is valid
  testPrecondition( dimension_distribution.get() );
}

// Raw distribution constructor
template<PhaseSpaceDimension dimension>
OnePhaseSpaceDimensionParticleResponseFunction<dimension>::OnePhaseSpaceDimensionParticleResponseFunction(
                                   const std::vector<double> dimension_grid,
                                   const std::vector<double> response_values )
  : d_dimension_response_distribution( std::make_shared<Utility::TabularDistribution>( dimension_grid, response_values ) )
{ /* ... */ }

// Evaluate the response function at the desired phase space point
template<PhaseSpaceDimension dimension>
double OnePhaseSpaceDimensionParticleResponseFunction<dimension>::evaluate( const ParticleState& particle ) const
{
  return d_dimension_response_distribution->evaluate(
                            MonteCarlo::getCoordinate<dimension>( particle ) );
}

// Check if the response function is spatially uniform
template<PhaseSpaceDimension dimension>
bool OnePhaseSpaceDimensionParticleResponseFunction<dimension>::isSpatiallyUniform() const
{
  if( MonteCarlo::PhaseSpaceDimensionTraits<dimension>::getClass() !=
      SPATIAL_DIMENSION_CLASS )
    return true;
  else
  {
    if( d_dimension_response_distribution->getDistributionType() ==
        Utility::UNIFORM_DISTRIBUTION )
      return true;
    else
      return false;
  }
}

// Get a description of the response function
template<PhaseSpaceDimension dimension>
std::string OnePhaseSpaceDimensionParticleResponseFunction<dimension>::description() const
{
  return std::string("f(") + Utility::toString( dimension ) + ")";
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ONE_PHASE_SPACE_DIMENSION_PARTICLE_RESPONSE_FUNCTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_OnePhaseSpaceDimensionParticleResponseFunction.hpp
//---------------------------------------------------------------------------//
