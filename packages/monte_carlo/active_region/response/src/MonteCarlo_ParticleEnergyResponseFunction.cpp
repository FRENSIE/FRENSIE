//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnergyResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Particle energy response function base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleEnergyResponseFunction.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Distribution constructor
ParticleEnergyResponseFunction::ParticleEnergyResponseFunction(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  energy_distribution )
  : d_energy_response_distribution( energy_distribution )
{
  // Make sure that the distribution is valid
  testPrecondition( energy_distribution.get() );
}

// Raw distribution constructor
ParticleEnergyResponseFunction::ParticleEnergyResponseFunction(
                                    const std::vector<double> energy_grid,
                                    const std::vector<double> response_values )
  : d_energy_response_distribution()
{
  try{
    d_energy_response_distribution.reset(
            new Utility::TabularDistribution( energy_grid, response_values ) );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Could not construct the particle energy response "
                           "function!" );
}

// Evaluate the response function at the desired phase space point
double ParticleEnergyResponseFunction::evaluate(
                                          const ParticleState& particle ) const
{
  return d_energy_response_distribution->evaluate( particle.getEnergy() );
}

// Check if the response function is spatially uniform
bool ParticleEnergyResponseFunction::isSpatiallyUniform() const
{
  return true;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnergyResponseFunction.cpp
//---------------------------------------------------------------------------//
