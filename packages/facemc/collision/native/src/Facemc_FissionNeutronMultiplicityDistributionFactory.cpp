//---------------------------------------------------------------------------//
//!
//! \file   Facemc_FissionNeutronMultiplicityDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  The fission neutron multiplicity distribution factory class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_FissionNeutronMultiplicityDistributionFactory.hpp"
#include "Facemc_CompleteFissionNeutronMultiplicityDistribution.hpp"
#include "Facemc_PartialFissionNeutronMultiplicityDistribution.hpp"
#include "Utility_PolynomialDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
FissionNeutronMultiplicityDistributionFactory::FissionNeutronMultiplicityDistributionFactory(
			    const std::string& table_name,
			    const Teuchos::ArrayView<const double>& nu_block,
			    const Teuchos::ArrayView<const double>& dnu_block )
  : d_prompt_dist_exists( false ),
    d_delayed_dist_exists( false ),
    d_total_dist_exists( false )
{
  // Make sure data is present
  testPrecondition( nu_block.size() > 0 );
  
  // Make sure that all distributions are currently given
  int location_of_total_data = static_cast<int>( nu_block[0] );
  
  TEST_FOR_EXCEPTION( location_of_total_data > 0,
		      std::runtime_error,
		      "Error: Only propmt or total nu-bar data is present in "
		      "ace table " << table_name << ", which is currently not "
		      "supported!" );

  // Parse the prompt nu-bar distribution
  Teuchos::ArrayView<const double> raw_prompt_distribution = 
    nu_block( 1, location_of_total_data );

  d_prompt_dist_exists = true;

  createPartialDistribution( table_name,
			     raw_prompt_distribution, 
			     d_prompt_multiplicity_distribution );

  // Parse the total nu-bar distribution
  Teuchos::ArrayView<const double> raw_total_distribution = 
    nu_block( 1 + location_of_total_data, 
	      nu_block.size() - 1 - location_of_total_data );

  d_total_dist_exists = true;

  createPartialDistribution( table_name,
			     raw_total_distribution,
			     d_total_multiplicity_distribution );

  // Parse the delayed nu-bar distribution
  if( dnu_block.size() > 0 )
  {
    d_delayed_dist_exists = true;

    createPartialDistribution( table_name,
			       dnu_block,
			       d_delayed_multiplicity_distribution );
  }
}

// Create the fission neutron multiplicity distribution
void FissionNeutronMultiplicityDistributionFactory::createDistribution(
     Teuchos::RCP<FissionNeutronMultiplicityDistribution>& distribution ) const
{
  if( d_prompt_dist_exists && d_delayed_dist_exists && d_total_dist_exists )
  {
    distribution.reset( new CompleteFissionNeutronMultiplicityDistribution(
					 d_prompt_multiplicity_distribution,
					 d_delayed_multiplicity_distribution,
					 d_total_multiplicity_distribution ) );
  }
  else if( d_prompt_dist_exists && d_total_dist_exists )
  {
    distribution.reset( new PartialFissionNeutronMultiplicityDistribution<PromptTotalFissionNeutronMultiplicityPolicy>(
					d_prompt_multiplicity_distribution,
					d_total_multiplicity_distribution ) );
  }
  else if( d_delayed_dist_exists && d_prompt_dist_exists )
  {
    distribution.reset( new PartialFissionNeutronMultiplicityDistribution<DelayedPromptFissionNeutronMultiplicityPolicy>(
					d_delayed_multiplicity_distribution,
				        d_prompt_multiplicity_distribution ) );
  }
  else // d_delayed_dist_exists && d_total_dist_exists
  {
    distribution.reset( new PartialFissionNeutronMultiplicityDistribution<DelayedTotalFissionNeutronMultiplicityPolicy>(
					 d_delayed_multiplicity_distribution,
					 d_total_multiplicity_distribution ) );
  }
}

// Create the partial distribution from a raw distribution array
void FissionNeutronMultiplicityDistributionFactory::createPartialDistribution(
	  const std::string& table_name,
	  const Teuchos::ArrayView<const double>& distribution_array,
	  Teuchos::RCP<Utility::OneDDistribution>& partial_distribution ) const
{
  unsigned form_flag = static_cast<unsigned>( distribution_array[0] );
  
  switch( form_flag )
  {
  case 1: // Parse a polynomial function
    {
      unsigned number_of_coeffs = 
	static_cast<unsigned>( distribution_array[1] );

      partial_distribution.reset( 
			    new Utility::PolynomialDistribution( 
				distribution_array( 2, number_of_coeffs ),
				1e-11, 
				20.0 ) );

      break;
    }
  case 2: // Parse a tabular distribution
    {
      unsigned number_of_interp_regions = 
	static_cast<unsigned>( distribution_array[1] );

      TEST_FOR_EXCEPTION( number_of_interp_regions != 0,
			  std::runtime_error,
			  "Error: multiple interpolation regions found in "
			  "nu block of ace table " << table_name <<
			  ", which is not currently supported!" );

      unsigned number_of_energies = 
	static_cast<unsigned>( distribution_array[2] );

      Teuchos::ArrayView<const double> energy_grid =
	distribution_array( 2, number_of_energies );

      Teuchos::ArrayView<const double> nu_values = 
	distribution_array( 2+number_of_energies, number_of_energies );

      partial_distribution.reset(
			     new Utility::TabularDistribution<Utility::LinLin>(
							         energy_grid,
							         nu_values ) );
    }
  default:
    THROW_EXCEPTION( std::runtime_error,
		     "Error: Unsupported form flag found in nu block of "
		     "ace table " << table_name << "!" );
  }
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_FissionNeutronMultiplicityDistributionFactory.cpp
//---------------------------------------------------------------------------//
