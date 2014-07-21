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

// FRENSIE Includes
#include "Facemc_NeutronScatteringDistribution.hpp"
#include "Facemc_NeutronScatteringEnergyDistribution.hpp"
#include "Facemc_NeutronScatteringAngularDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_Tuple.hpp"

namespace Facemc{

//! The law 44 scattering eneryg distribution class (ENDF Law 44)
template<typename Law44InterpolationPolicy>
class Law44NeutronScatteringDistribution : public NeutronScatteringDistribution
{

public:

  //! Typedef for the distribution
  typedef Teuchos::Array<Utility::Quad<double,
                                       Teuchos::Array<double>,
                                       Teuchos::Array<double>,
                                       Teuchos::Array<double> > > ScatteringDistribution;
 
  //! Constructor
  Law44NeutronScatteringDistribution( 
		      const double atomic_weight_ratio,
		      const Teuchos::RCP<NeutronScatteringEnergyDistribution>& energy_scattering_distribution,
                      ScatteringDistribution& scattering_distribution ); 
                                              
  //! Destructor
  ~Law44NeutronScatteringDistribution()
  { /* ... */ }
  
  //! Randomly scatter the neutron
  void scatterNeutron( NeutronState& neutron,
		       const double temperature ) const;

private:

  // Law 4 distribution should always be stored
  Teuchos::RCP<NeutronScatteringEnergyDistribution> d_energy_scattering_distribution;

  ScatteringDistribution d_scattering_distribution;
};

} // end Facemc namespace


//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Facemc_Law44NeutronScatteringDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_LAW_44_NEUTRON_SCATTERING_DISTRIBUTION

//---------------------------------------------------------------------------//
// end Facemc_Law44NeutronScatteringDistribution.hpp
//---------------------------------------------------------------------------//

