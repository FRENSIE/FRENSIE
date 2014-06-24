//---------------------------------------------------------------------------//
//!
//! \file   tstFissionableIsotopes.cpp
//! \author Alex Bennett
//! \brief  Fissionable Isotopes unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>

// FRENSIE Includes
#include "Transmutation_FissionableIsotopes.hpp"

//---------------------------------------------------------------------------//
// Testing Variables 
//---------------------------------------------------------------------------//
 


//---------------------------------------------------------------------------//
// Tests 
//---------------------------------------------------------------------------//
// Check read ENDF Fission Yields Header
TEUCHOS_UNIT_TEST( FissionableIsotopes, isFissionable )
{
    int zaid;

    zaid = 92235;
    TEST_ASSERT( Transmutation::FissionableIsotopes::isFissionable( zaid ) );

    zaid = 92238;
    TEST_ASSERT( Transmutation::FissionableIsotopes::isFissionable( zaid ) );

    zaid = 94239;
    TEST_ASSERT( Transmutation::FissionableIsotopes::isFissionable( zaid ) );

    zaid = 1001;
    TEST_ASSERT( !Transmutation::FissionableIsotopes::isFissionable( zaid ) );

    zaid = 8016;
    TEST_ASSERT( !Transmutation::FissionableIsotopes::isFissionable( zaid ) );

    zaid = 94237;
    TEST_ASSERT( !Transmutation::FissionableIsotopes::isFissionable( zaid ) );
}
//---------------------------------------------------------------------------//
// Custom Main Function 
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
   Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

   Teuchos::GlobalMPISession mpiSession( &argc, &argv );
   return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

 
//---------------------------------------------------------------------------//
// end tstEndfFissionYieldsHelpers.cpp 
//---------------------------------------------------------------------------//
