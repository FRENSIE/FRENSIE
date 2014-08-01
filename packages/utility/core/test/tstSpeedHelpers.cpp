//---------------------------------------------------------------------------//
//!
//! \file   tstSpeedHelpers.cpp
//! \author Alex Bennett
//! \brief  Speed Helpers unit test
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>

// FRENSIE Includes
#include "Utility_PhysicalConstants.hpp"
#include "Utility_SpeedHelpers.hpp"

//---------------------------------------------------------------------------//
// Tests 
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( SpeedHelpers, calculateSpeed )
{
  double speed = Utility::calculateSpeed(8.0,1.0);
  TEST_FLOATING_EQUALITY(speed, Utility::PhysicalConstants::speed_of_light/2.0, 1e-15);
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( SpeedHelpers, calculateKineticEnergy )
{
  double energy = Utility::calculateKineticEnergy(8.0,1.0);
  double speed_of_light = Utility::PhysicalConstants::speed_of_light;
  TEST_FLOATING_EQUALITY(energy, 4.0/( speed_of_light * speed_of_light ), 1e-15);
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( SpeedHelpers, calculateRelativisticSpeed )
{
  double speed = Utility::calculateRelativisticSpeed(1.0,1.0);
  double speed_of_light = Utility::PhysicalConstants::speed_of_light;
  double result = speed_of_light * sqrt( 3.0 / 4.0 ); 
  TEST_FLOATING_EQUALITY(speed, result, 1e-15);
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( SpeedHelpers, calculateRelativisticKineticEnergy )
{
  double energy = Utility::calculateRelativisticKineticEnergy(1.0,1.0);
  double speed_of_light = Utility::PhysicalConstants::speed_of_light;
  double result = speed_of_light * speed_of_light * ( speed_of_light /
        sqrt( speed_of_light * speed_of_light - 1 ) - 1 );
  TEST_FLOATING_EQUALITY(energy, result, 1e-15);
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
// end tstSpeedHelpers.cpp
//---------------------------------------------------------------------------//
 
