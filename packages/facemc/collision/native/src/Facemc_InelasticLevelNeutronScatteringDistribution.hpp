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
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringDistribution.hpp"
#include "Facemc_NeutronScatteringAngularDistribution.hpp"
#include "Facemc_NeutronScatteringEnergyDistribution.hpp"

namespace Facemc{

//! The inelastic level neutron scattering distribution class
class InelasticLevelNeutronScatteringDistribution : public NeutronScatteringDistribution
{

public:

  //! Constructor
  InelasticLevelNeutronScatteringDistribution( 
		      const double atomic_weight_ratio,
		      const Teuchos::RCP<NeutronScatteringEnergyDistribution>&
		      energy_scattering_distribution, 
		      const Teuchos::RCP<NeutronScatteringAngularDistribution>&
		      angular_scattering_distribution );
                                              
  //! Destructor
  ~InelasticLevelNeutronScatteringDistribution()
  { /* ... */ }
  
  //! Randomly scatter the neutron
  void scatterNeutron( NeutronState& neutron,
		       const double temperature ) const;
    
private:

  // The energy scattering distribution
  Teuchos::RCP<NeutronScatteringEnergyDistribution>
  d_energy_scattering_distribution;
  
  // The angular scattering distribution
  Teuchos::RCP<NeutronScatteringAngularDistribution> 
  d_angular_scattering_distribution;
};

} // End facemc namespace

#endif // FACEMC_INELASTIC_LEVEL_NEUTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_InelasticLevelNeutronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
