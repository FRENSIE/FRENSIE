//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentScatteringDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  The coherent scattering distribution ACE factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CoherentScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_ThompsonScatteringDistribution.hpp"
#include "MonteCarlo_BasicCoherentScatteringDistribution.hpp"
#include "MonteCarlo_EfficientCoherentScatteringDistribution.hpp"
#include "MonteCarlo_StandardFormFactorSquared.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_InverseSquareAngstromUnit.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_Vector.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a basic coherent distribution
void CoherentScatteringDistributionACEFactory::createBasicCoherentDistribution(
			   const Data::XSSEPRDataExtractor& raw_photoatom_data,
			   std::shared_ptr<const CoherentScatteringDistribution>&
			   coherent_distribution )
{
  // Create the form factor squared
  std::shared_ptr<const FormFactorSquared> form_factor_squared;

  CoherentScatteringDistributionACEFactory::createFormFactorSquared(
							 raw_photoatom_data,
							 form_factor_squared );

  coherent_distribution.reset(
	      new BasicCoherentScatteringDistribution( form_factor_squared ) );
}

// Create an efficient coherent distribution
void CoherentScatteringDistributionACEFactory::createEfficientCoherentDistribution(
			   const Data::XSSEPRDataExtractor& raw_photoatom_data,
			   std::shared_ptr<const CoherentScatteringDistribution>&
			   coherent_distribution )
{
  // Create the form factor squared
  std::shared_ptr<const FormFactorSquared> form_factor_squared;

  CoherentScatteringDistributionACEFactory::createFormFactorSquared(
							 raw_photoatom_data,
							 form_factor_squared );

  coherent_distribution.reset(
	  new EfficientCoherentScatteringDistribution( form_factor_squared ) );
}

// Create the form factor distribution
void CoherentScatteringDistributionACEFactory::createFormFactorSquared(
                const Data::XSSEPRDataExtractor& raw_photoatom_data,
                std::shared_ptr<const FormFactorSquared>& form_factor_squared )
{
  Utility::ArrayView<const double> jcohe_block =
    raw_photoatom_data.extractJCOHEBlock();

  unsigned form_factor_size = jcohe_block.size()/3;

  Utility::ArrayView<const double> raw_recoil_momentum_squared =
    jcohe_block( 0, form_factor_size );

  std::vector<double> recoil_momentum_squared(
                                           raw_recoil_momentum_squared.begin(),
                                           raw_recoil_momentum_squared.end() );

  Utility::ArrayView<const double> raw_form_factor_squared =
    jcohe_block( 2*form_factor_size, form_factor_size );
  
  std::vector<double> form_factor_squared_values(
                                               raw_form_factor_squared.begin(),
                                               raw_form_factor_squared.end() );

  // Square the grid points and the form factor factor values
  // This operation is non-linear, which means that the grid is no longer
  // guaranteed to give interpolated values within the convergence tolerance
  // used to create the grid.
  for( unsigned i = 0; i < form_factor_size; ++i )
  {
    recoil_momentum_squared[i] *= recoil_momentum_squared[i];

    form_factor_squared_values[i] *= form_factor_squared_values[i];
  }

  // The stored recoil momentum squared has units of inverse square Angstroms.
  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::InverseSquareAngstrom,void> > raw_form_factor_squared_dist(
           new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseSquareAngstrom,void>(
                                                recoil_momentum_squared,
                                                form_factor_squared_values ) );

  form_factor_squared.reset(
         new StandardFormFactorSquared<Utility::Units::InverseSquareAngstrom>(
                                              raw_form_factor_squared_dist ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
