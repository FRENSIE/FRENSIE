//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourceDimension.hpp
//! \author Alex Robinson
//! \brief  Particle source dimension class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SOURCE_DIMENSION_HPP
#define MONTE_CARLO_PARTICLE_SOURCE_DIMENSION_HPP

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

  //! Sample from the dimension distribution (and all dependent dim. dists.)
  virtual void sample(
                 ParticleSourcePhaseSpacePoint& phase_space_sample ) const = 0;
};
  
} // end MonteCarlo namespace


#endif // end MONTE_CARLO_STANDARD_PARTICLE_SOURCE_DIMENSION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourceDimension.hpp
//---------------------------------------------------------------------------//
