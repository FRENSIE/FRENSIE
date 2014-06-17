//---------------------------------------------------------------------------//
//!
//! \file   tstISCDecayData.cpp
//! \author Alex Bennett
//! \brief  ISC Decay Data Unit Test
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
#include "Data_ISC.hpp"

//---------------------------------------------------------------------------//
// Testing Variables 
//---------------------------------------------------------------------------//
 
std::string test_decay_data_file_name, zaid_name_input;

Teuchos::RCP<data::DecayFile> decay_file;
Teuchos::RCP<data::DecayLib> decay_lib;
Teuchos::RCP<data::DecayData> decay_data;

//---------------------------------------------------------------------------//
// Tests 
//---------------------------------------------------------------------------//
// Tests the half life
TEUCHOS_UNIT_TEST( ISCDecayData, getHalfLife )
{
    TEST_COMPARE( decay_data->GetHalfLife(), ==, 760854000000)
}

// Tests the half life error
TEUCHOS_UNIT_TEST( ISCDecayData, GetHalfLifeErr )
{
    TEST_COMPARE( decay_data->GetHalfLifeErr(), ==, 946728000)
}

// Tests the decay constant
TEUCHOS_UNIT_TEST( ISCDecayData, GetDecayConst )
{
    TEST_FLOATING_EQUALITY( decay_data->GetDecayConst(), 9.1101207401149934e-13, 1e-15)
}

// Tests the decay constant error
TEUCHOS_UNIT_TEST( ISCDecayData, GetDecayContErr )
{
    TEST_FLOATING_EQUALITY( decay_data->GetDecayConstErr(), 1.1335691720156017e-15, 1e-15)
}

// Tests the number of daughter nuclides
TEUCHOS_UNIT_TEST( ISCDecayData, GetNumber )
{
    TEST_COMPARE( decay_data->GetNumber(), ==, 3)
}

// Tests the branching ratios
TEUCHOS_UNIT_TEST( ISCDecayData, GetBranchingRatio )
{
    TEST_FLOATING_EQUALITY( decay_data->GetBranchingRatio(0), 3.1000000000000001e-12, 1e-15)
    TEST_FLOATING_EQUALITY( decay_data->GetBranchingRatio(1), 0.00046266999999999999, 1e-15)
    TEST_FLOATING_EQUALITY( decay_data->GetBranchingRatio(2), 0.99953729999999996, 1e-15)
}

// Tests the branching ratios error
TEUCHOS_UNIT_TEST( ISCDecayData, GetBranchingRatioErr )
{
    TEST_FLOATING_EQUALITY( decay_data->GetBranchingRatioErr(0), 5.9999999999999997e-13, 1e-15)
    TEST_FLOATING_EQUALITY( decay_data->GetBranchingRatioErr(1), 3.7876870000000001e-05, 1e-15)
    TEST_FLOATING_EQUALITY( decay_data->GetBranchingRatioErr(2), 3.7876870000000001e-05, 1e-15)
}

// Tests the daughter nuclides
TEUCHOS_UNIT_TEST( ISCDecayData, GetDaughter )
{
    TEST_COMPARE( decay_data->GetDaughter(0), ==, 0)
    TEST_COMPARE( decay_data->GetDaughter(1), ==, 92235)
    TEST_COMPARE( decay_data->GetDaughter(2), ==, 1092235)
}

// Tests the decay type
TEUCHOS_UNIT_TEST( ISCDecayData, GetDecayType )
{
    TEST_COMPARE( decay_data->GetDecayType(0), ==, 6)
    TEST_COMPARE( decay_data->GetDecayType(1), ==, 4)
    TEST_COMPARE( decay_data->GetDecayType(2), ==, 4)
}


//---------------------------------------------------------------------------//
// Custom Main Function 
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
   Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
   
   clp.setOption( "test_decay_data_file",
                  &test_decay_data_file_name,
                  "Test file for checking ISC decay data." );

   clp.setOption( "zaid_name",
                  &zaid_name_input,
                  "Zaid to test." );

   const Teuchos::RCP<Teuchos::FancyOStream> out =
      Teuchos::VerboseObjectBase::getDefaultOStream();

   Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
     clp.parse(argc,argv);

   if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
     *out << "\nEnd Result: TEST FAILED" << std::endl;
     return parse_return;
   }

   int zaid_name;

   std::istringstream iss( zaid_name_input );
   iss >> zaid_name;

   decay_file.reset(new data::DecayFile( test_decay_data_file_name.c_str() ));
   decay_lib.reset(new data::DecayLib(*decay_file));

   decay_data.reset(new data::DecayData);
   *decay_data = decay_lib->GetDecayData(zaid_name);

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
// end tstISCDecayData.cpp 
//---------------------------------------------------------------------------//
