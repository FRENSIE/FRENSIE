//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringAngularDistributionACEFactory.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  Nuclear scattering angular distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_SCATTERING_ANGULAR_DISTRIBUTION_ACE_FACTORY
#define MONTE_CARLO_NUCLEAR_SCATTERING_ANGULAR_DISTRIBUTION_ACE_FACTORY

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringAngularDistribution.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_ArrayView.hpp"

namespace MonteCarlo{

//! The scattering angular distribution factory class
class NuclearScatteringAngularDistributionACEFactory
{

public:

  //! Create the angular distribution
  static void createDistribution(
	   const Utility::ArrayView<const double>& and_block_array,
	   const unsigned and_block_array_start_index,
	   const std::string& table_name,
	   const unsigned reaction,
	   std::shared_ptr<const NuclearScatteringAngularDistribution>& distribution );

  //! Create an isotropic angular distribution
  static void createIsotropicDistribution(
   std::shared_ptr<const NuclearScatteringAngularDistribution>& distribution );

  //! Return the isotropic_angle_cosine_dist
  static std::shared_ptr<const Utility::TabularUnivariateDistribution>
  getIsotropicDistribution();

  //! Create the angular distribution
  static void createSAlphaBetaDistribution( 
	    const Teuchos::ArrayView<const double>& energy_grid,
	    const Teuchos::ArrayView<const double>& itca_block,
	    Teuchos::RCP<NuclearScatteringAngularDistribution>& distribution );
  
  //! Create an isotropic angular distribution
  static void createSAlphaBetaIsotropicDistribution(
    const Teuchos::ArrayView<const double>& energy_grid,
	   Teuchos::RCP<NuclearScatteringAngularDistribution>& distribution );

private:

  //! Constructor
  NuclearScatteringAngularDistributionACEFactory();
  
  // The default (isotropic) angle cosine distribution
  static std::shared_ptr<const Utility::TabularUnivariateDistribution>
  isotropic_angle_cosine_dist;
  
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLEAR_SCATTERING_ANGULAR_DISTRIBUTION_ACE_FACTORY

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringAngularDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
