//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class ElectronScatteringDistribution
{

public:

  //! Constructor
  ElectronScatteringDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~ElectronScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the electron
  virtual void scatterElectron( ElectronState& electron,
			                    ParticleBank& bank,
                                SubshellType& shell_of_interaction ) const = 0;

protected:

  //! Sample an azimuthal angle from a uniform distribution
  double sampleAzimuthalAngle() const;
};

// Sample an azimuthal angle from a uniform distribution
inline double 
ElectronScatteringDistribution::sampleAzimuthalAngle() const
{
  return 2*Utility::PhysicalConstants::pi*
    Utility::RandomNumberGenerator::getRandomNumber<double>();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
