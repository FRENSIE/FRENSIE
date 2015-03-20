//---------------------------------------------------------------------------//
//!
//! \file   tstDecayDataContainer.cpp
//! \author Alex Bennett
//! \brief  Decay Data Unit Test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Data_DecayDataContainer.hpp"
#include "Data_DecayVolatileDataContainer.hpp"

//---------------------------------------------------------------------------//
// Testing Variables 
//---------------------------------------------------------------------------//
 
Teuchos::RCP<Data::DecayDataContainer> decay_data;

//---------------------------------------------------------------------------//
// Tests 
//---------------------------------------------------------------------------//
// Tests the half life
TEUCHOS_UNIT_TEST( DecayDataContainer, getHalfLife )
{
  TEST_EQUALITY_CONST( decay_data->getDecayNuclide(94239).getHalfLife(), 
		       760854000000 );
}

//---------------------------------------------------------------------------//
// Tests the half life error
TEUCHOS_UNIT_TEST( DecayDataContainer, getHalfLifeError )
{
  TEST_EQUALITY_CONST( decay_data->getDecayNuclide(94239).getHalfLifeError(), 
		       946728000 );
}

//---------------------------------------------------------------------------//
// Tests the decay constant
TEUCHOS_UNIT_TEST( DecayDataContainer, getDecayConstant )
{
  TEST_FLOATING_EQUALITY( decay_data->getDecayNuclide(94239).getDecayConstant(), 
			  9.1101207401149934e-13, 
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Tests the decay constant error
TEUCHOS_UNIT_TEST( DecayDataContainer, getDecayContantError )
{
  TEST_FLOATING_EQUALITY( decay_data->getDecayNuclide(94239).getDecayConstantError(), 
			  1.1335691720156017e-15, 
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Tests the number of daughter nuclides
TEUCHOS_UNIT_TEST( DecayDataContainer, getNumberOfDecayBranches )
{
  TEST_EQUALITY_CONST( decay_data->getDecayNuclide(94239).getNumberOfDecayBranches(),
		       3 );
}

//---------------------------------------------------------------------------//
// Tests the branching ratios
TEUCHOS_UNIT_TEST( DecayDataContainer, getBranchingRatio )
{
  const Data::DecayNuclide& nuclide = decay_data->getDecayNuclide(94239);
  
  TEST_FLOATING_EQUALITY( nuclide.getBranchingRatio(0), 
			  3.1000000000000001e-12, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( nuclide.getBranchingRatio(1), 
			  0.00046266999999999999, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( nuclide.getBranchingRatio(2), 
			  0.99953729999999996, 
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Tests the branching ratios error
TEUCHOS_UNIT_TEST( DecayDataContainer, getBranchingRatioError )
{
  const Data::DecayNuclide& nuclide = decay_data->getDecayNuclide(94239);
  
  TEST_FLOATING_EQUALITY( nuclide.getBranchingRatioError(0), 
			  5.9999999999999997e-13, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( nuclide.getBranchingRatioError(1), 
			  3.7876870000000001e-05, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( nuclide.getBranchingRatioError(2), 
			  3.7876870000000001e-05, 
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Tests the daughter nuclides
TEUCHOS_UNIT_TEST( DecayDataContainer, getDaughter )
{
  const Data::DecayNuclide& nuclide = decay_data->getDecayNuclide(94239);
  
  TEST_EQUALITY_CONST( nuclide.getDaughter(0), 0 );
  TEST_EQUALITY_CONST( nuclide.getDaughter(1), 92235 );
  TEST_EQUALITY_CONST( nuclide.getDaughter(2), 1092235 );
}

//---------------------------------------------------------------------------//
// Tests the decay type
TEUCHOS_UNIT_TEST( DecayData, GetDecayType )
{
  const Data::DecayNuclide& nuclide = decay_data->getDecayNuclide(94239);
  
  TEST_EQUALITY_CONST( nuclide.getDecayType(0), 6 );
  TEST_EQUALITY_CONST( nuclide.getDecayType(1), 4 );
  TEST_EQUALITY_CONST( nuclide.getDecayType(2), 4 );
}


//---------------------------------------------------------------------------//
// Custom Main Function 
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_native_decay_data_file_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
   
  clp.setOption( "test_native_decay_data_file",
		 &test_native_decay_data_file_name,
		 "Test file for checking decay data." );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  decay_data.reset( new Data::DecayDataContainer( 
					  test_native_decay_data_file_name ) );
    
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
// end tstDecayData.cpp 
//---------------------------------------------------------------------------//
