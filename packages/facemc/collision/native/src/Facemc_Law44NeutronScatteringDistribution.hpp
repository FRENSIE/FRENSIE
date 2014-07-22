//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_Law44NeutronScatteringDistribution.hpp
//! \author Alex Bennett
//! \brief  The law 44 scattering distribution class
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_LAW_44_NEUTRON_SCATTERING_DISTRIBUTION
#define FACEMC_LAW_44_NEUTRON_SCATTERING_DISTRIBUTION

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringDistribution.hpp"
#include "Facemc_NeutronScatteringEnergyDistribution.hpp"
#include "Facemc_Law44ARDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_Tuple.hpp"

namespace Facemc{

//! The law 44 scattering energy distribution class (ENDF Law 44)
class Law44NeutronScatteringDistribution : public NeutronScatteringDistribution
{

public:

  //! Typedef for the distribution
  typedef Teuchos::Array<Teuchos::RCP<Law44ARDistribution> > ARDistributions;
 
  //! Constructor
  Law44NeutronScatteringDistribution( 
		      const double atomic_weight_ratio,
		      const Teuchos::RCP<NeutronScatteringEnergyDistribution>&
		      energy_scattering_distribution,
                      const Teuchos::Array<Teuchos::RCP<Law44ARDistribution> >&
		      ar_distributions );
                                              
  //! Destructor
  ~Law44NeutronScatteringDistribution()
  { /* ... */ }
  
  //! Randomly scatter the neutron
  void scatterNeutron( NeutronState& neutron,
		       const double temperature ) const;

private:

  // The energy distribution (only a law 4 distribution should be stored)
  Teuchos::RCP<NeutronScatteringEnergyDistribution> d_energy_scattering_distribution;

  // The AR distributions
  ARDistributions d_ar_distributions;
};

} // end Facemc namespace


#endif // end FACEMC_LAW_44_NEUTRON_SCATTERING_DISTRIBUTION

//---------------------------------------------------------------------------//
// end Facemc_Law44NeutronScatteringDistribution.hpp
//---------------------------------------------------------------------------//

