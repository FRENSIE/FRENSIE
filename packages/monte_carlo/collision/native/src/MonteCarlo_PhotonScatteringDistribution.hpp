//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The photon scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class PhotonScatteringDistribution
{

public:

  //! Constructor
  PhotonScatteringDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~PhotonScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the photon and return the shell that was interacted with
  virtual void scatterPhoton( PhotonState& photon,
			      ParticleBank& bank,
			      unsigned& shell_of_interaction ) const = 0;

protected:

  //! Sample an azimuthal angle from a uniform distribution
  double sampleAzimuthalAngle() const;
};

// Sample an azimuthal angle from a uniform distribution
inline double 
PhotonScatteringDistribution::sampleAzimuthalAngle() const
{
  return 2*Utility::PhysicalConstants::pi*
    Utility::RandomNumberGenerator::getRandomNumber<double>();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
