//---------------------------------------------------------------------------//
//!
//! \file   tstKinematicHelpers.cpp
//! \author Alex Bennett
//! \brief  Kinematic Helpers unit test
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>

// FRENSIE Includes
#include "Utility_PhysicalConstants.hpp"
#include "Utility_KinematicHelpers.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( KinematicHelpers, calculateRelativisticKineticEnergy )
{
  double energy = Utility::calculateRelativisticKineticEnergy(1.0,1.0);
  double speed_of_light = Utility::PhysicalConstants::speed_of_light;
  double result = speed_of_light * speed_of_light * ( speed_of_light /
        sqrt( speed_of_light * speed_of_light - 1 ) - 1 );
  TEST_FLOATING_EQUALITY(energy, result, 1e-15);
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( KinematicHelpers, calculateKineticEnergy )
{
  double energy = Utility::calculateKineticEnergy(8.0,1.0);
  double speed_of_light = Utility::PhysicalConstants::speed_of_light;
  TEST_FLOATING_EQUALITY(energy, 4.0/( speed_of_light * speed_of_light ), 1e-15);
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( KinematicHelpers, calculateDimensionlessRelativisticSpeedSquared )
{
  double speed_squared =
               Utility::calculateDimensionlessRelativisticSpeedSquared(1.0,1.0);
  double result = 3.0 / 4.0;
  TEST_FLOATING_EQUALITY(speed_squared, result, 1e-15);
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( KinematicHelpers, calculateRelativisticSpeed )
{
  double speed = Utility::calculateRelativisticSpeed(1.0,1.0);
  double speed_of_light = Utility::PhysicalConstants::speed_of_light;
  double result = speed_of_light * sqrt( 3.0 / 4.0 );
  TEST_FLOATING_EQUALITY(speed, result, 1e-15);
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( KinematicHelpers, calculateSpeed )
{
  double speed = Utility::calculateSpeed(8.0,1.0);
  double result = Utility::PhysicalConstants::speed_of_light/2.0;
  TEST_FLOATING_EQUALITY(speed, result, 1e-15);
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( KinematicHelpers, calculateRelativisticMomentumEnergySquared )
{
  double momentum_squared =
               Utility::calculateRelativisticMomentumEnergySquared( 1.0, 1.0 );
  double result = 3.0;
  TEST_FLOATING_EQUALITY( momentum_squared, result, 1e-15 );
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( KinematicHelpers, calculateDimensionlessRelativisticMomentumSquared )
{
  double momentum_squared =
         Utility::calculateDimensionlessRelativisticMomentumSquared( 1.0, 1.0 );
  double result = 3.0;
  TEST_FLOATING_EQUALITY( momentum_squared, result, 1e-15 );
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( KinematicHelpers, calculateRelativisticMomentum )
{
  double momentum_squared =
               Utility::calculateRelativisticMomentum( 1.0, 1.0 );
  double result = sqrt( 3.0 )/Utility::PhysicalConstants::speed_of_light;
  TEST_FLOATING_EQUALITY( momentum_squared, result, 1e-15 );
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( KinematicHelpers, calculateBetaMin )
{
  double E = 1e-6;
  double kT = 2.53010e-8;

  double beta_min = Utility::calculateBetaMin( E, kT );

  TEST_FLOATING_EQUALITY( beta_min, -E/kT, 1e-12 );
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( KinematicHelpers, calculateAlphaMin )
{
  double E = 1e-6;
  double kT = 2.53010e-8;
  double beta = -9.9e-7/2.53010e-8;
  double A = 0.999167;

  double alpha_min = Utility::calculateAlphaMin( E, beta, A, kT );

  TEST_FLOATING_EQUALITY( alpha_min, 32.041235228594, 1e-12 );

  beta = 0.0;
  alpha_min = Utility::calculateAlphaMin( E, beta, A, kT );

  TEST_FLOATING_EQUALITY( alpha_min, 0.0, 1e-12 );

  beta = 1e-6/2.53010e-8;
  alpha_min = Utility::calculateAlphaMin( E, beta, A, kT );

  TEST_FLOATING_EQUALITY( alpha_min, 6.7869220430292, 1e-12 );
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( KinematicHelpers, calculateAlphaMax )
{
  double E = 1e-6;
  double kT = 2.53010e-8;
  double beta = -9.9e-7/2.53010e-8;
  double A = 0.999167;

  double alpha_max = Utility::calculateAlphaMax( E, beta, A, kT );

  TEST_FLOATING_EQUALITY( alpha_max, 47.864067440246, 1e-12 );

  beta = 0.0;
  alpha_max = Utility::calculateAlphaMax( E, beta, A, kT );

  TEST_FLOATING_EQUALITY( alpha_max, 158.22832211652, 1e-12 );

  beta = 1e-6/2.53010e-8;
  alpha_max = Utility::calculateAlphaMax( E, beta, A, kT );

  TEST_FLOATING_EQUALITY( alpha_max, 230.55556113174, 1e-12 );
}


//---------------------------------------------------------------------------//
// end tstKinematicHelpers.cpp
//---------------------------------------------------------------------------//

