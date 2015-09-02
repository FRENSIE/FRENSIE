//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_NuclearScatteringAngularDistributionACEFactory.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  Nuclear scattering angular distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_SCATTERING_ANGULAR_DISTRIBUTION_ACE_FACTORY
#define MONTE_CARLO_NUCLEAR_SCATTERING_ANGULAR_DISTRIBUTION_ACE_FACTORY

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringAngularDistribution.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The scattering angular distribution factory class
class NuclearScatteringAngularDistributionACEFactory
{

public:

  //! Create the angular distribution
  static void createDistribution( 
	   const Teuchos::ArrayView<const double>& and_block_array,
	   const unsigned and_block_array_start_index,
	   const std::string& table_name,
	   const unsigned reaction,
	   Teuchos::RCP<NuclearScatteringAngularDistribution>& distribution );
  
  //! Create an isotropic angular distribution
  static void createIsotropicDistribution(
	   Teuchos::RCP<NuclearScatteringAngularDistribution>& distribution );

private:

  //! Constructor
  NuclearScatteringAngularDistributionACEFactory();

  // The default (isotropic) angle cosine distribution
  static Teuchos::RCP<Utility::TabularOneDDistribution> 
  isotropic_angle_cosine_dist;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLEAR_SCATTERING_ANGULAR_DISTRIBUTION_ACE_FACTORY

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringAngularDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
