//---------------------------------------------------------------------------//
//!
//! \file   tstAllIsotopes.cpp
//! \author Alex Bennett
//! \brief  All Isotopes unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <vector>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Transmutation_AllIsotopes.hpp"

//---------------------------------------------------------------------------//
// Testing Variables 
//---------------------------------------------------------------------------//
 
std::string z_number_input;

//---------------------------------------------------------------------------//
// Tests 
//---------------------------------------------------------------------------//
// Check the zaid limits
TEUCHOS_UNIT_TEST( AllIsotopes, getZaidLimits )
{
    int z;
 
    std::istringstream iss( z_number_input );
    iss >> z;

    std::pair<int,int> limits = Transmutation::AllIsotopes::getZaidLimits(z);

    TEST_COMPARE(limits.first, == , 99);
    TEST_COMPARE(limits.second , == , 127); 
}

TEUCHOS_UNIT_TEST( AllIsotopes, getZaids )
{
    int z;
 
    std::istringstream iss( z_number_input );
    iss >> z;

    Teuchos::Array<int> zaids;
  
    Transmutation::AllIsotopes::getZaids(z, zaids);

    TEST_COMPARE(zaids.front(), == , 49099);
    TEST_COMPARE(zaids.back(), == , 49127);
    TEST_COMPARE(zaids.size(), == , 29);
}

TEUCHOS_UNIT_TEST( AllIsotopes, getAllZaids)
{
    Teuchos::Array<int> zaids;
  
    Transmutation::AllIsotopes::getAllZaids(zaids);

    TEST_COMPARE(zaids.front(), == , 100245);
    TEST_COMPARE(zaids.back(), == , 1003);
    TEST_COMPARE(zaids.size(), == , 2137);
}

TEUCHOS_UNIT_TEST( AllIsotopes, getMetaStateZaids )
{
    int z;
 
    std::istringstream iss( z_number_input );
    iss >> z;

    Teuchos::Array<int> meta_state_zaids;
  
    Transmutation::AllIsotopes::getMetaStateZaids(z, meta_state_zaids);

    TEST_COMPARE(meta_state_zaids.front(), == , 1049115);
    TEST_COMPARE(meta_state_zaids.back(), == , 1049131);
    TEST_COMPARE(meta_state_zaids.size(), == , 25);
}

TEUCHOS_UNIT_TEST( AllIsotopes, getAllMetaStateZaids)
{
    Teuchos::Array<int> meta_state_zaids;
  
    Transmutation::AllIsotopes::getAllMetaStateZaids(meta_state_zaids);

    TEST_COMPARE(meta_state_zaids.front(), == , 1030071);
    TEST_COMPARE(meta_state_zaids.back(), == , 1048115);
    TEST_COMPARE(meta_state_zaids.size(), == , 191);
}

//---------------------------------------------------------------------------//
// Custom Main Function 
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
   Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

   clp.setOption( "z_number",
                  &z_number_input,
                  "The Z number to use for the unit tests." );

   Teuchos::GlobalMPISession mpiSession( &argc, &argv );
   return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

 
//---------------------------------------------------------------------------//
// end tstAllIsotopes.cpp 
//---------------------------------------------------------------------------//
