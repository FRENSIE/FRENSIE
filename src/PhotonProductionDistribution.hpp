//---------------------------------------------------------------------------//
//!
//! \file   PhotonProductionDistribution.hpp
//! \author Alex Robinson
//! \brief  The photon production distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PHOTON_PRODUCTION_DISTRIBUTION_HPP
#define PHOTON_PRODUCTION_DISTRIBUTION_HPP

// Trilinos Includes
#include "Teuchos_RCP.hpp"

// FACEMC Includes
#include "NeutronState.hpp"
#include "PhotonState.hpp"

namespace FACEMC{

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

} // end FACEMC namespace

#endif // end PHOTON_PRODUCTION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end PhotonProductionDistribution.hpp
//---------------------------------------------------------------------------//
