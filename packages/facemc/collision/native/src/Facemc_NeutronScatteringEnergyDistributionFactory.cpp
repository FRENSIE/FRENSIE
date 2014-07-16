//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_NeutronScatteringEnergyDistributionFactory.cpp
//! \author Alex Robinson, Alex Bennett
//! \brief  Neutron scattering energy distribution factory class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringEnergyDistributionFactory.hpp"
#include "Facemc_InelasticLevelNeutronScatteringEnergyDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Create the energy distribution
void NeutronScatteringEnergyDistributionFactory::createDistribution(
	     const Teuchos::ArrayView<const double>& dlw_block_array,
	     const unsigned dlw_block_array_start_index,
	     const std::string& table_name,
	     const NuclearReactionType reaction,
	     Teuchos::RCP<NeutronScatteringEnergyDistribution>& distribution )
{
  // Make sure the dlw block array is valid
  testPrecondition( dlw_block_array.size() > 0 );

  // Verify that only one law is present
  TEST_FOR_EXCEPTION( dlw_block_array[0] != 0,
		      std::runtime_error,
		      "Error: MT# " << reaction << "in ACE table "
		      << table_name << " has multiple ENDF laws associated "
		      " with it, which is not currently supported!\n" );

  // Extract the ENDF law number
  unsigned endf_law = dlw_block_array[1];

  // Create the energy distribution based on the stated ENDF law
  switch( endf_law )
  {
  case 3u:
    {
      // Parse data
      double ldat1 = 0;
      double ldat2 = 0;
      
      // Create the inelastic level scattering energy distribution
      distribution.reset( 
	      new InelasticLevelNeutronScatteringEnergyDistribution( ldat1,
								     ldat2 ) );

      break;
    }
  default:
    // This law is not currently supported
    TEST_FOR_EXCEPTION( true,
			std::runtime_error,
			"Error: Unsupported ENDF law number " << endf_law <<
			" found in ACE table " << table_name << " for MT# "
			<< reaction << "!\n" );
  }
}

// Create the ENDF law 44 coupled energy-angle distribution
void NeutronScatteringEnergyDistributionFactory::createCoupledDistribution(
	            const Teuchos::ArrayView<const double>& dlw_block_array,
		    const unsigned dlw_block_array_start_index,
		    const std::string& table_name,
		    const NuclearReactionType reaction,
		    Teuchos::RCP<NeutronScatteringDistribution>& distribution )
{

}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringEnergyDistributionFactory.cpp
//---------------------------------------------------------------------------//
