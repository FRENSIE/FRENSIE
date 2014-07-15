//---------------------------------------------------------------------------//
//!
//! \file   Facemc_InelasticLevelNeutronScatteringDistribution.hpp
//! \author Alex Bennett
//! \brief  The inelastic level scattering distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_INELASTIC_LEVEL_NEUTRON_SCATTERING_DISTRIBUTION_HPP
#define FACEMC_INELASTIC_LEVEL_NEUTRON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringDistribution.hpp"
#include "Facemc_NeutronScatteringAngularDistribution.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace Facemc{

//! The inelastic level neutron scattering distribution class
class InelasticLevelNeutronScatteringDistribution : public NeutronScatteringDistribution
{

public:

  //! Constructor
  InelasticLevelNeutronScatteringDistribution( 
		      const double atomic_weight_ratio,
		      const double param_a,
		      const double param_b,
		      const Teuchos::RCP<NeutronScatteringAngularDistribution>&
		      angular_scattering_distribution );
                                              
  //! Destructor
  ~InelasticLevelNeutronScatteringDistribution()
  { /* ... */ }
  
  //! Randomly scatter the neutron
  void scatterNeutron( NeutronState& neutron,
		       const double temperature ) const;
    
private:

  // (A+1)/A * |Q|
  double d_param_a;
  
  // (A/(A+1))^2
  double d_param_b;
  
  // The incoming energy dependent angular scattering distribution
  Teuchos::RCP<NeutronScatteringAngularDistribution> 
  d_angular_scattering_distribution;
};

} // End facemc namespace

#endif // FACEMC_INELASTIC_LEVEL_NEUTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_InelasticLevelNeutronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
