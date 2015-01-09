//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_NeutronScatteringAngularDistributionACEFactory.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  Neutron scattering angular distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_SCATTERING_ANGULAR_DISTRIBUTION_ACE_FACTORY
#define MONTE_CARLO_NEUTRON_SCATTERING_ANGULAR_DISTRIBUTION_ACE_FACTORY

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_NeutronScatteringAngularDistribution.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"

namespace MonteCarlo{

//! The scattering angular distribution factory class
class NeutronScatteringAngularDistributionACEFactory
{

public:

  //! Create the angular distribution
  static void createDistribution( 
	    const Teuchos::ArrayView<const double>& and_block_array,
	    const unsigned and_block_array_start_index,
	    const std::string& table_name,
	    const NuclearReactionType reaction,
	    Teuchos::RCP<NeutronScatteringAngularDistribution>& distribution );

  //! Create an isotropic angular distribution
  static void createIsotropicDistribution(
	    Teuchos::RCP<NeutronScatteringAngularDistribution>& distribution );

private:

  //! Constructor
  NeutronScatteringAngularDistributionACEFactory();

  // The default (isotropic) angle cosine distribution
  static Teuchos::RCP<Utility::OneDDistribution> isotropic_angle_cosine_dist;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_SCATTERING_ANGULAR_DISTRIBUTION_ACE_FACTORY

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronScatteringAngularDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
