//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentScatteringDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  The coherent scattering distribution ACE factory definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_CoherentScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_ThompsonScatteringDistribution.hpp"
#include "MonteCarlo_BasicCoherentScatteringDistribution.hpp"
#include "MonteCarlo_EfficientCoherentScatteringDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a basic coherent distribution
void CoherentScatteringDistributionACEFactory::createBasicCoherentDistribution(
			   const Data::XSSEPRDataExtractor& raw_photoatom_data,
			   Teuchos::RCP<const CoherentScatteringDistribution>&
			   coherent_distribution )
{
  // Create the form factor squared
  Teuchos::RCP<const Utility::TabularOneDDistribution> form_factor_squared;

  CoherentScatteringDistributionACEFactory::createFormFactorSquared( 
							 raw_photoatom_data,
							 form_factor_squared );

  coherent_distribution.reset( 
	      new BasicCoherentScatteringDistribution( form_factor_squared ) );
}

// Create an efficient coherent distribution
void CoherentScatteringDistributionACEFactory::createEfficientCoherentDistribution(
			   const Data::XSSEPRDataExtractor& raw_photoatom_data,
			   Teuchos::RCP<const CoherentScatteringDistribution>&
			   coherent_distribution )
{
  // Create the form factor squared
  Teuchos::RCP<const Utility::TabularOneDDistribution> form_factor_squared;

  CoherentScatteringDistributionACEFactory::createFormFactorSquared( 
							 raw_photoatom_data,
							 form_factor_squared );
  
  coherent_distribution.reset( 
	  new EfficientCoherentScatteringDistribution( form_factor_squared ) );
}

// Create the form factor distribution
void CoherentScatteringDistributionACEFactory::createFormFactorSquared(
	   const Data::XSSEPRDataExtractor& raw_photoatom_data,
           Teuchos::RCP<const Utility::TabularOneDDistribution>& form_factor )
{
  Teuchos::ArrayView<const double> jcohe_block = 
    raw_photoatom_data.extractJCOHEBlock();

  unsigned form_factor_size = jcohe_block.size()/3;

  Teuchos::Array<double> recoil_momentum_squared(
					  jcohe_block( 0, form_factor_size ) );

  Teuchos::Array<double> form_factor_squared(
			 jcohe_block( 2*form_factor_size, form_factor_size ) );

  // The stored recoil momentum has units of inverse Angstroms - convert to
  // inverse cm^2
  for( unsigned i = 0; i < form_factor_size; ++i )
  {
    recoil_momentum_squared[i] *= recoil_momentum_squared[i]*1e16;
    
    form_factor_squared[i] *= form_factor_squared[i];
  }

  form_factor.reset( new Utility::TabularDistribution<Utility::LinLin>(
						      recoil_momentum_squared,
						      form_factor_squared ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
