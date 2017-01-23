//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourceDimension.hpp
//! \author Alex Robinson
//! \brief  Particle source dimension class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SOURCE_DIMENSION_HPP
#define MONTE_CARLO_PARTICLE_SOURCE_DIMENSION_HPP

// Std Lib Includes
#include <memory>
#include <vector>

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceDimensionType.hpp"
#include "MonteCarlo_ParticleSourceDimensionClassType.hpp"
#include "MonteCarlo_ParticleSourcePhaseSpacePoint.hpp"

namespace MonteCarlo{

//! The particle source dimension class
class ParticleSourceDimension
{

public:

  //! Constructor
  ParticleSourceDimension();

  //! Destructor
  virtual ~ParticleSourceDimension()
  { /* ... */ }

  //! Return the dimension type
  virtual ParticleSourceDimensionType getDimensionType() const = 0;

  //! Return the dimension class type
  virtual ParticleSourceDimensionClassType getDimensionClassType() const = 0;

  //! Check if the dimension is independent
  virtual bool isIndependent() const = 0;

  //! Check if the dimension is dependent on the dimension of interest
  virtual bool isDependentOnDimension( const ParticleSourceDimensionType dimension ) const = 0;

  //! Check if the dimension distribution is uniform
  virtual bool isDistributionUniform() const = 0;

  //! Evaluate the dimension distribution at the desired phase space point
  double evaluateDistribution(
                const ParticleSourcePhaseSpacePoint& phase_space_point ) const;

  //! Sample from the dimension distribution 
  void sampleFromDistribution(
                     ParticleSourcePhaseSpacePoint& phase_space_sample ) const;

  //! Set the dimension value and weight appropriately
  void setDimensionValueAndCalculateWeight(
                             ParticleSourcePhaseSpacePoint& phase_space_sample,
                             const double dimension_value ) const;

  //! Add a dependent dimension
  void addDependentDimension(
                          const std::shared_ptr<const ParticleSourceDimension>&
                          dependent_dimension );

protected:

  //! Evaluate the dimension distribution at the desired phase space point
  virtual double evaluateDistributionWithoutCascade(
            const ParticleSourcePhaseSpacePoint& phase_space_point ) const = 0;

  //! Sample a value for this dimension distribution only
  virtual void sampleFromDistributionWithoutCascade(
                 ParticleSourcePhaseSpacePoint& phase_space_sample ) const = 0;

  //! Set the value for this dimension only and weight appropriately
  virtual void setDimensionValueAndCalculateWeightWithoutCascade(
                             ParticleSourcePhaseSpacePoint& phase_space_sample,
                             const double dimension_value ) const = 0;

private:

  // Evaluate the dependent dimension dists. at the desired phase space point
  double evaluateDependentDistributions(
                const ParticleSourcePhaseSpacePoint& phase_space_point ) const;

  // Sample from all of the dependent dimensions with the value from this dim.
  void sampleFromDependentDimensionDistributions(
                     ParticleSourcePhaseSpacePoint& phase_space_sample ) const;

  // The dependent dimensions
  std::vector<std::shared_ptr<const ParticleSourceDimension> >
  d_dependent_dimensions; 
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SOURCE_DIMENSION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourceDimension.hpp
//---------------------------------------------------------------------------//
