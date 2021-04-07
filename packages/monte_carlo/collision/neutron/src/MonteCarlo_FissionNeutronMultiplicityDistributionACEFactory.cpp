//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FissionNeutronMultiplicityDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  The fission neutron multiplicity distribution factory class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_FissionNeutronMultiplicityDistributionACEFactory.hpp"
#include "MonteCarlo_CompleteFissionNeutronMultiplicityDistribution.hpp"
#include "MonteCarlo_PartialFissionNeutronMultiplicityDistribution.hpp"
#include "Utility_PolynomialDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
FissionNeutronMultiplicityDistributionACEFactory::FissionNeutronMultiplicityDistributionACEFactory(
			    const std::string& table_name,
			    const Utility::ArrayView<const double>& nu_block,
			    const Utility::ArrayView<const double>& dnu_block )
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
		      "Only prompt or total nu-bar data is present in "
		      "ace table " << table_name << ", which is currently not "
		      "supported!" );

  // Parse the prompt nu-bar distribution
  Utility::ArrayView<const double> raw_prompt_distribution =
    nu_block( 1, abs(location_of_total_data) );

  d_prompt_dist_exists = true;

  createPartialDistribution( table_name,
			     raw_prompt_distribution,
			     d_prompt_multiplicity_distribution );

  // Parse the total nu-bar distribution
  Utility::ArrayView<const double> raw_total_distribution =
    nu_block( 1 + abs(location_of_total_data),
	      nu_block.size() - 1 - abs(location_of_total_data) );

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
void FissionNeutronMultiplicityDistributionACEFactory::createDistribution(
     std::shared_ptr<const FissionNeutronMultiplicityDistribution>& distribution ) const
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
void FissionNeutronMultiplicityDistributionACEFactory::createPartialDistribution(
	  const std::string& table_name,
	  const Utility::ArrayView<const double>& distribution_array,
	  std::shared_ptr<const Utility::UnivariateDistribution>& partial_distribution ) const
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
			  "multiple interpolation regions found in "
			  "nu block of ace table " << table_name <<
			  ", which is not currently supported!" );

      unsigned number_of_energies =
	static_cast<unsigned>( distribution_array[2] );

      Utility::ArrayView<const double> energy_grid =
	distribution_array( 3, number_of_energies );

      Utility::ArrayView<const double> nu_values =
	distribution_array( 3+number_of_energies, number_of_energies );

      partial_distribution.reset(
			     new Utility::TabularDistribution<Utility::LinLin>(
							         energy_grid,
							         nu_values ) );
      break;
    }
  default:
    THROW_EXCEPTION( std::runtime_error,
		     "Unsupported form flag " << form_flag <<
		     " found in nu block of ace table " << table_name << "!" );
  }
}

// Return if a prompt distribution exists
bool FissionNeutronMultiplicityDistributionACEFactory::doesPromptDistExist() const
{
  return d_prompt_dist_exists;
}

// Return if a delayed distribution exists
bool
FissionNeutronMultiplicityDistributionACEFactory::doesDelayedDistExist() const
{
  return d_delayed_dist_exists;
}

// Return if a total distribution exists
bool FissionNeutronMultiplicityDistributionACEFactory::doesTotalDistExist() const
{
  return d_total_dist_exists;
}

// Return the prompt multiplicity distribution
const std::shared_ptr<const Utility::UnivariateDistribution>&
FissionNeutronMultiplicityDistributionACEFactory::getPromptMultDist() const
{
  return d_prompt_multiplicity_distribution;
}

// Return the delayed multiplicity distribution
const std::shared_ptr<const Utility::UnivariateDistribution>&
FissionNeutronMultiplicityDistributionACEFactory::getDelayedMultDist() const
{
  return d_delayed_multiplicity_distribution;
}

// Return the total multiplicity distribution
const std::shared_ptr<const Utility::UnivariateDistribution>&
FissionNeutronMultiplicityDistributionACEFactory::getTotalMultDist() const
{
  return d_total_multiplicity_distribution;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_FissionNeutronMultiplicityDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
