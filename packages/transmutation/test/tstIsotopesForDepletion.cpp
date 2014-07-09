//---------------------------------------------------------------------------//
//!
//! \file   tstIsotopesForDepletion.cpp
//! \author Alex Bennett
//! \brief  Isotopes for depletion unit test
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Transmutation_IsotopesForDepletion.hpp"

//---------------------------------------------------------------------------//
// Testing Variables 
//---------------------------------------------------------------------------//
 

//---------------------------------------------------------------------------//
// Tests 
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( IsotopesForDepletion, getIsotopes )
{
   Teuchos::Array<int> zaids;

   Transmutation::IsotopesForDepletion::getIsotopes( zaids ); 
 
   TEST_COMPARE( zaids.front() , == , 1001 );
   TEST_COMPARE( zaids.back() , == , 100260 );
   TEST_COMPARE( zaids.length() , == , 3255 );
}

TEUCHOS_UNIT_TEST( IsotopesForDepletion, getLocation )
{
   Teuchos::Array<int> zaids;
 
   Transmutation::IsotopesForDepletion::getIsotopes( zaids );

   TEST_COMPARE( Transmutation::IsotopesForDepletion::getLocation(1001,zaids) ,==, 0);
   TEST_COMPARE( Transmutation::IsotopesForDepletion::getLocation(1007,zaids) ,==, 6);
   TEST_COMPARE( Transmutation::IsotopesForDepletion::getLocation(2006,zaids) ,==,10);
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
