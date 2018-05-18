//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnergyResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Particle energy response function base class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_ENERGY_RESPONSE_FUNCTION_HPP
#define MONTE_CARLO_PARTICLE_ENERGY_RESPONSE_FUNCTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleResponseFunction.hpp"
#include "Utility_UnivariateDistribution.hpp"

namespace MonteCarlo{

//! The particle energy response function
class ParticleEnergyResponseFunction : public ParticleResponseFunction
{

public:

  //! Distribution constructor
  ParticleEnergyResponseFunction(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  energy_distribution );

  //! Raw distribution constructor
  ParticleEnergyResponseFunction( const std::vector<double> energy_grid,
                                  const std::vector<double> response_values );

  //! Destructor
  ~ParticleEnergyResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const final override;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const final override;

private:

  //! Default constructor
  ParticleEnergyResponseFunction()
  { /* ... */ }

  // The energy distribution
  std::shared_ptr<const Utility::UnivariateDistribution>
  d_energy_response_distribution;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_ENERGY_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnergyResponseFunction.hpp
//---------------------------------------------------------------------------//
