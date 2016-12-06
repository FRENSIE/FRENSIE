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
  ParticleSourceDimensionClassType getDimensionClassType() const;

  //! Check if the dimension is independent
  virtual bool isIndependent() const = 0;

  //! Check if the dimension is dependent on the dimension of interest
  virtual bool isDependentOnDimension( const ParticleSourceDimensionType dimension ) const = 0;

  //! Sample from the dimension distribution (and all dependent dim. dists.)
  void sample( ParticleSourcePhaseSpacePoint& phase_space_sample ) const;

  //! Add a dependent dimension
  void addDependentDimension(
                          const std::shared_ptr<const ParticleSourceDimension>&
                          dependent_dimension );

protected:

  //! Sample a value for this dimension only
  virtual void sampleDimension(
                 ParticleSourcePhaseSpacePoint& phase_space_sample ) const = 0;

  //! Sample from all of the dependent dimensions with the value from this dim.
  void sampleDependentDimensions(
                     ParticleSourcePhaseSpacePoint& phase_space_sample ) const;

private:

  // The dependent dimensions
  std::vector<std::shared_ptr<const ParticleSourceDimension> >
  d_dependent_dimensions; 
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SOURCE_DIMENSION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourceDimension.hpp
//---------------------------------------------------------------------------//
