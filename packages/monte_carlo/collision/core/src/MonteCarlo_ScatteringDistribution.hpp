//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The scattering distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

//! The scattering distribution
class ScatteringDistribution
{

public:

  //! Constructor
  ScatteringDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~ScatteringDistribution()
  { /* ... */ }

protected:

  //! Sample an azimuthal angle from a uniform distribution
  double sampleAzimuthalAngle() const;
};

// Sample an azimuthal angle from a uniform distribution
inline double
ScatteringDistribution::sampleAzimuthalAngle() const
{
  return 2*Utility::PhysicalConstants::pi*
    Utility::RandomNumberGenerator::getRandomNumber<double>();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ScatteringDistribution.hpp
//---------------------------------------------------------------------------//
