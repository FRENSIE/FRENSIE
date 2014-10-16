//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PairProductionPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The pair production photon scattering distribution
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PAIR_PRODUCTION_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define FACEMC_PAIR_PRODUCTION_PHOTON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The pair production scattering distribution
class PairProductionPhotonScatteringDistribution : public PhotonScatteringDistribution
{

public:
  
  //! Constructor
  PairProductionPhotonScatteringDistribution(
const Teuchos::RCP<Utility::OneDDistribution>& pair_production_cross_sections );

  //! Destructor
  ~PairProductionPhotonScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the photon
  void scatterPhoton( PhotonState& photon,
		      ParticleBank& bank,
		      unsigned& shell_of_interaction ) const;

private:

  // The combined pair and triplet production cross sections
  Teuchos::RCP<Utility::OneDDistribution> d_pair_production_cross_sections;

};

} // end MonteCarlo namespace

#endif // end FACEMC_PAIR_PRODUCTION_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PairProductionPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
