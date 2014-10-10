//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The photon scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define FACEMC_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class PhotonScatteringDistribution
{

public:

  //! Constructor
  PhotonScatteringDistribution();

  //! Destructor
  virtual ~PhotonScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the photon
  virtual void scatterPhoton( PhotonState& photon ) const = 0;

  //! Randomly scatter the photon and return the shell that was interacted with
  virtual void scatterPhoton( PhotonState& photon,
			      unsigned& shell_of_interaction );

protected:

  //! Sample an azimuthal angle from a uniform distribution
  double sampleAzimuthalAngle() const;
};

// Randomly scatter the photon and return the shell that was interacted with
inline void PhotonScatteringDistribution::scatterPhoton( 
					       PhotonState& photon,
					       unsigned& shell_of_interaction )
{
  shell_of_interaction = std::numeric_limits<unsigned>::max();

  this->scatterPhoton( photon );
}

// Sample an azimuthal angle from a uniform distribution
inline double 
PhotonScatteringDistribution::sampleAzimuthalAngle() const
{
  return 2*Utility::PhysicalConstants::pi*
    Utility::RandomNumberGenerator::getRandomNumber<double>();
}

} // end MonteCarlo namespace

#endif // end FACEMC_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
