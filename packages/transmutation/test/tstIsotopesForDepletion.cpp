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
// Check read ENDF Fission Yields Header
TEUCHOS_UNIT_TEST( IsotopesForDepletion, getIsotopes )
{

   Transmutation::IsotopesForDepletion::getIsotopes(); 

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
