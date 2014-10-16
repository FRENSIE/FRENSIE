//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PairProductionPhotonScatteringDistribution.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The pair production photon scattering distribution
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PAIR_PRODUCTION_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define FACEMC_PAIR_PRODUCTION_PHOTON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotonScatteringDistribution.hpp"

namespace MonteCarlo{

/*! The pair production scattering distribution
 * \details This classes uses a simplified model of pair production. It is
 * assumed that the positron annihilates at the photon collision point. One
 * annihilation photon is emitted isotropically and the second is emitted
 * in the opposite direction of the first.
 */
class PairProductionPhotonScatteringDistribution : public PhotonScatteringDistribution
{

public:
  
  //! Constructor
  PairProductionPhotonScatteringDistribution()
  { /* ... */ }

  //! Destructor
  ~PairProductionPhotonScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the photon
  void scatterPhoton( PhotonState& photon, 
                      ParticleBank& bank,
                      unsigned& shell_of_interaction ) const;
};

} // end MonteCarlo namespace

#endif // end FACEMC_PAIR_PRODUCTION_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PairProductionPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
