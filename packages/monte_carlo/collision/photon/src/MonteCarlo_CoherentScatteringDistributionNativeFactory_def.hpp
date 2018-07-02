//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentScatteringDistributionNativeFactory_def.hpp
//! \author Alex Robinson
//! \brief  The coherent scattering distribution native factory definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_ThompsonScatteringDistribution.hpp"
#include "MonteCarlo_BasicCoherentScatteringDistribution.hpp"
#include "MonteCarlo_EfficientCoherentScatteringDistribution.hpp"
#include "MonteCarlo_StandardFormFactorSquared.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a basic coherent distribution
  template<typename NativeContainer, template<typename> class SmartPtr>
void CoherentScatteringDistributionNativeFactory::createBasicCoherentDistribution(
                                const NativeContainer& raw_photoatom_data,
	                        SmartPtr<const CoherentScatteringDistribution>&
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
template<typename NativeContainer, template<typename> class SmartPtr>
void CoherentScatteringDistributionNativeFactory::createEfficientCoherentDistribution(
                                const NativeContainer& raw_photoatom_data,
	                        SmartPtr<const CoherentScatteringDistribution>&
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
template<typename NativeContainer, template<typename> class SmartPtr>
void CoherentScatteringDistributionNativeFactory::createFormFactorSquared(
                       const NativeContainer& raw_photoatom_data,
                       SmartPtr<const FormFactorSquared>& form_factor_squared )
{
  // The stored recoil momentum squared has units of inverse squared cm.
  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::InverseSquareCentimeter,void> > raw_form_factor_squared(
           new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseSquareCentimeter,void>(
              raw_photoatom_data.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid(),
              raw_photoatom_data.getWallerHartreeSquaredAtomicFormFactor() ) );

  form_factor_squared.reset(
        new StandardFormFactorSquared<Utility::Units::InverseSquareCentimeter>(
                                                   raw_form_factor_squared ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentScatteringDistributionNativeFactory_def.hpp
//---------------------------------------------------------------------------//
