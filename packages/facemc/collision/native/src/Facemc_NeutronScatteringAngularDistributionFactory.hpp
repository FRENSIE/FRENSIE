//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_NeutronScatteringAngularDistributionFactory.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  Neutron scattering angular distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_NEUTRON_SCATTERING_ANGULAR_DISTRIBUTION_FACTORY
#define FACEMC_NEUTRON_SCATTERING_ANGULAR_DISTRIBUTION_FACTORY

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringAngularDistribution.hpp"
#include "Facemc_NuclearReactionType.hpp"

namespace Facemc{

//! The scattering angular distribution factory class
class NeutronScatteringAngularDistributionFactory
{

public:

  //! Create the angular distribution
  static void createDistribution( 
	    const Teuchos::ArrayView<const double>& and_block_array,
	    const unsigned and_block_array_start_index,
	    const bool is_cm_dist,
	    const std::string& table_name,
	    const NuclearReactionType reaction,
	    Teuchos::RCP<NeutronScatteringAngularDistribution>& distribution );

  //! Create an isotropic angular distribution
  static void createIsotropicDistribution(
	    const bool is_cm_dist,
	    Teuchos::RCP<NeutronScatteringAngularDistribution>& distribution );

private:

  //! Constructor
  NeutronScatteringAngularDistributionFactory();

  // The default (isotropic) angle cosine distribution
  static Teuchos::RCP<Utility::OneDDistribution> isotropic_angle_cosine_dist;
};

} // end Facemc namespace

#endif // end FACEMC_NEUTRON_SCATTERING_ANGULAR_DISTRIBUTION_FACTORY

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringAngularDistributionFactory.hpp
//---------------------------------------------------------------------------//
