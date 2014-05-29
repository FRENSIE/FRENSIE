//---------------------------------------------------------------------------//
//!
//! \file   Facemc_PhotonProductionDistribution.hpp
//! \author Alex Robinson
//! \brief  The photon production distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PHOTON_PRODUCTION_DISTRIBUTION_HPP
#define FACEMC_PHOTON_PRODUCTION_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_NeutronState.hpp"
#include "Facemc_PhotonState.hpp"

namespace Facemc{

//! The photon production distribution base class
class PhotonProductionDistribution
{

public:
  
  //! Constructor
  PhotonProductionDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~PhotonProductionDistribution()
  { /* ... */ }
  
  //! Randomly create a photon
  virtual void createPhoton( const NeutronState& neutron,
			     Teuchos::RCP<PhotonState>& new_photon ) = 0;
};

} // end Facemc namespace

#endif // end FACEMC_PHOTON_PRODUCTION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_PhotonProductionDistribution.hpp
//---------------------------------------------------------------------------//
