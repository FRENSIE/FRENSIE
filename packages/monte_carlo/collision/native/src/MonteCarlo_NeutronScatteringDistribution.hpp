//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The neutron scattering distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_NEUTRON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class NeutronScatteringDistribution
{

public:

  //! Constructor 
  NeutronScatteringDistribution( const double atomic_weight_ratio );

  //! Destructor
  virtual ~NeutronScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the neutron
  virtual void scatterNeutron( NeutronState& neutron,
			       const double temperature ) const = 0;

protected:
  
  //! Return the atomic weight ratio
  double getAtomicWeightRatio() const;

  //! Sample an azimuthal angle from a uniform distribution
  double sampleAzimuthalAngle() const;

private:

  // The atomic weight of the nuclide in units of neutron mass
  double d_atomic_weight_ratio;
};

// Return the atomic weight ratio
inline double 
NeutronScatteringDistribution::getAtomicWeightRatio() const
{
  return d_atomic_weight_ratio;
}

// Sample an azimuthal angle from a uniform distribution
inline double 
NeutronScatteringDistribution::sampleAzimuthalAngle() const
{
  return 2*Utility::PhysicalConstants::pi*
    Utility::RandomNumberGenerator::getRandomNumber<double>();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
