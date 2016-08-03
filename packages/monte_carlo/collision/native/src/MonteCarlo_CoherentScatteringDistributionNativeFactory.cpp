//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentScatteringDistributionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  The coherent scattering distribution native factory definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_CoherentScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ThompsonScatteringDistribution.hpp"
#include "MonteCarlo_BasicCoherentScatteringDistribution.hpp"
#include "MonteCarlo_EfficientCoherentScatteringDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a basic coherent distribution
void CoherentScatteringDistributionNativeFactory::createBasicCoherentDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const CoherentScatteringDistribution>&
	 coherent_distribution )
{
  // Create the form factor squared
  Teuchos::RCP<const Utility::TabularOneDDistribution> form_factor_squared;

  CoherentScatteringDistributionNativeFactory::createFormFactorSquared(
							 raw_photoatom_data,
							 form_factor_squared );

  coherent_distribution.reset(
	      new BasicCoherentScatteringDistribution( form_factor_squared ) );
}

// Create an efficient coherent distribution
void CoherentScatteringDistributionNativeFactory::createEfficientCoherentDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const CoherentScatteringDistribution>&
	 coherent_distribution )
{
  // Create the form factor squared
  Teuchos::RCP<const Utility::TabularOneDDistribution> form_factor_squared;

  CoherentScatteringDistributionNativeFactory::createFormFactorSquared(
							 raw_photoatom_data,
							 form_factor_squared );

  coherent_distribution.reset(
	  new EfficientCoherentScatteringDistribution( form_factor_squared ) );
}

// Create the form factor distribution
void CoherentScatteringDistributionNativeFactory::createFormFactorSquared(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const Utility::TabularOneDDistribution>& form_factor )
{
  Teuchos::Array<double> recoil_momentum_squared =
    raw_photoatom_data.getWallerHartreeAtomicFormFactorMomentumGrid();

  Teuchos::Array<double> form_factor_squared =
    raw_photoatom_data.getWallerHartreeAtomicFormFactor();

  for( unsigned i = 0; i < recoil_momentum_squared.size(); ++i )
  {
    recoil_momentum_squared[i] *= recoil_momentum_squared[i];

    form_factor_squared[i] *= form_factor_squared[i];
  }

  form_factor.reset( new Utility::TabularDistribution<Utility::LinLin>(
						       recoil_momentum_squared,
						       form_factor_squared ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
