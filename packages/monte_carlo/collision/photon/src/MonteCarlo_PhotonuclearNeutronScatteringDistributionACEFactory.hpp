//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonuclearNeutronScatteringDistributionACEFactory.hpp
//! \author Alex Robinson, Ryan Pease
//! \brief  Photon neutron (photonuclear) scattering distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTONUCLEAR_NEUTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_PHOTONUCLEAR_NEUTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Data_XSSPhotonuclearDataExtractor.hpp"

namespace MonteCarlo{

//! The scattering distribution factory class
class PhotonuclearNeutronScatteringDistributionACEFactory : public NuclearScatteringDistributionACEFactory<PhotonState,NeutronState>
{

public:

  //! Constructor
  PhotonuclearNeutronScatteringDistributionACEFactory(
		       const std::string& table_name,
		       const double atomic_weight_ratio,
		       const Data::XSSPhotonuclearDataExtractor& raw_nuclide_data );

  //! Destructor
  ~PhotonuclearNeutronScatteringDistributionACEFactory()
  { /* ... */ }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTONUCLEAR_NEUTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonuclearNeutronScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
