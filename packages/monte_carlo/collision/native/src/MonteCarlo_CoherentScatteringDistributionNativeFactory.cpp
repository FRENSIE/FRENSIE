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
#include "MonteCarlo_StandardFormFactorSquared.hpp"
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
  std::shared_ptr<const FormFactorSquared> form_factor_squared;

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
  std::shared_ptr<const FormFactorSquared> form_factor_squared;

  CoherentScatteringDistributionNativeFactory::createFormFactorSquared(
							 raw_photoatom_data,
							 form_factor_squared );

  coherent_distribution.reset(
	  new EfficientCoherentScatteringDistribution( form_factor_squared ) );
}

// Create the form factor distribution
void CoherentScatteringDistributionNativeFactory::createFormFactorSquared(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 std::shared_ptr<const FormFactorSquared>& form_factor_squared )
{
  // The stored recoil momentum squared has units of inverse squared cm.
  std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::InverseSquareCentimeter,void> > raw_form_factor_squared(
           new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseSquareCentimeter,void>(
              raw_photoatom_data.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid(),
              raw_photoatom_data.getWallerHartreeSquaredAtomicFormFactor() ) );

  form_factor_squared.reset(
        new StandardFormFactorSquared<Utility::Units::InverseSquareCentimeter>(
                                                   raw_form_factor_squared ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
