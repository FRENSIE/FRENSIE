//---------------------------------------------------------------------------//
//!
//! \file   Facemc_IndependentEnergyAngleNeutronScatteringDistribution.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The independent energy-angle scattering distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_INDEPENDENT_ENERGY_ANGLE_NEUTRON_SCATTERING_DISTRIBUTION_HPP
#define FACEMC_INDEPENDENT_ENERGY_ANGLE_NEUTRON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringDistribution.hpp"
#include "Facemc_NeutronScatteringAngularDistribution.hpp"
#include "Facemc_NeutronScatteringEnergyDistribution.hpp"

namespace Facemc{

//! The independent energy angle neutron scattering distribution class
/*! \detials The system conversion policy will convert the sampled energy and
 * scattering angle cosine from the current system to the lab system.
 */
template<typename SystemConversionPolicy>
class IndependentEnergyAngleNeutronScatteringDistribution : public NeutronScatteringDistribution
{

public:

  //! Constructor
  IndependentEnergyAngleNeutronScatteringDistribution( 
		      const double atomic_weight_ratio,
		      const Teuchos::RCP<NeutronScatteringEnergyDistribution>&
		      energy_scattering_distribution,
		      const Teuchos::RCP<NeutronScatteringAngularDistribution>&
		      angular_scattering_distribution );

  //! Destructor
  ~IndependentEnergyAngleNeutronScatteringDistribution()
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

} // end Facemc namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Facemc_IndependentEnergyAngleNeutronScatteringDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif//end FACEMC_INDEPENDENT_ENERGY_ANGLE_NEUTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_IndependentEnergyAngleNeutronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
