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
  Teuchos::Array<double> recoil_momentum_squared =
    raw_photoatom_data.getWallerHartreeAtomicFormFactorMomentumGrid();

  Teuchos::Array<double> form_factor_squared_values =
    raw_photoatom_data.getWallerHartreeAtomicFormFactor();

  // Square the grid points and the form factor factor values
  // This operation is non-linear, which means that the grid is no longer
  // guaranteed to give interpolated values within the convergence tolerance
  // used to create the grid.
  for( unsigned i = 0; i < recoil_momentum_squared.size(); ++i )
  {
    recoil_momentum_squared[i] *= recoil_momentum_squared[i];

    form_factor_squared_values[i] *= form_factor_squared_values[i];
  }

  // The stored recoil momentum squared has units of inverse squared cm.
  std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::InverseSquareCentimeter,void> > raw_form_factor_squared(
           new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseSquareCentimeter,void>(
                                                recoil_momentum_squared,
                                                form_factor_squared_values ) );

  form_factor_squared.reset(
        new StandardFormFactorSquared<Utility::Units::InverseSquareCentimeter>(
                                                   raw_form_factor_squared ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
