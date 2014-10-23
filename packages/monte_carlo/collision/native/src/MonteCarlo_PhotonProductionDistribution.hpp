//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonProductionDistribution.hpp
//! \author Alex Robinson
//! \brief  The photon production distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_PRODUCTION_DISTRIBUTION_HPP
#define MONTE_CARLO_PHOTON_PRODUCTION_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"

namespace MonteCarlo{

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

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTON_PRODUCTION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonProductionDistribution.hpp
//---------------------------------------------------------------------------//
