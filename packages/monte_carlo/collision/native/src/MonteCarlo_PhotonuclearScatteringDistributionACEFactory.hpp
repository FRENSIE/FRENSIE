//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonuclearScatteringDistributionACEFactory.hpp
//! \author Alex Robinson, Ryan Pease
//! \brief  Photon photon (photonuclear) scattering distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTONUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_PHOTONUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Data_XSSPhotonuclearDataExtractor.hpp"

namespace MonteCarlo{

//! The scattering distribution factory class
class PhotonuclearScatteringDistributionACEFactory : public NuclearScatteringDistributionACEFactory<MonteCarlo::PhotonState,MonteCarlo::PhotonState>
{

public:

  //! Constructor
  PhotonuclearScatteringDistributionACEFactory(
		       const std::string& table_name,
		       const double atomic_weight_ratio,
		       const Data::XSSPhotonuclearDataExtractor& raw_nuclide_data );

  //! Destructor
  ~PhotonuclearScatteringDistributionACEFactory()
  { /* ... */ }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTONUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonuclearScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
