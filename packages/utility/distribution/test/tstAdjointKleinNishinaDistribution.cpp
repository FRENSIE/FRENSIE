//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointKleinNishinaDistribution.cpp
//! \author Alex Robinson
//! \brief  Klein-Nishina distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_AdjointKleinNishinaDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Utility::AdjointKleinNishinaDistribution> distribution_1(
		    new Utility::AdjointKleinNishinaDistribution( 0.1, 0.5 ) );

Teuchos::RCP<Utility::OneDDistribution> distribution_1_base = distribution_1;

Teuchos::RCP<Utility::AdjointKleinNishinaDistribution> distribution_2(
		   new Utility::AdjointKleinNishinaDistribution( 0.1, 10.0 ) );

Teuchos::RCP<Utility::OneDDistribution> distribution_2_base = distribution_2;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the min energy loss ratio can be calculated
TEUCHOS_UNIT_TEST( AdjointKleinNishinaDistribution,
		   calculateMinEnergyLossRatio )
{
  double min_energy_loss_ratio = 
    Utility::AdjointKleinNishinaDistribution::calculateMinEnergyLossRatio(
									0.1,
									0.5 );

  TEST_FLOATING_EQUALITY( min_energy_loss_ratio, 0.8, 1e-15 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstAdjointKleinNishinaDistribution.cpp
//---------------------------------------------------------------------------//
