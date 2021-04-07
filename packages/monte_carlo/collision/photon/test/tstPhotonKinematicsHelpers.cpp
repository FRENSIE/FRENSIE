//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonKinematicsHelpers.cpp
//! \author Alex Robinson
//! \brief  Photon kinematics helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the Compton line energy can be calculated
FRENSIE_UNIT_TEST( PhotonKinematicsHelpers, calculateComptonLineEnergy )
{
  double compton_line = MonteCarlo::calculateComptonLineEnergy( 0.1, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_line, 0.0718705616632476, 1e-15 );

  compton_line = MonteCarlo::calculateComptonLineEnergy( 0.1, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_line, 0.0836333586947441, 1e-15 );

  compton_line = MonteCarlo::calculateComptonLineEnergy( 0.1, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_line, 0.1, 1e-15 );

  compton_line = MonteCarlo::calculateComptonLineEnergy( 1.0, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_line, 0.20350423413905203, 1e-15 );

  compton_line = MonteCarlo::calculateComptonLineEnergy( 1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_line, 0.3381861540098899, 1e-15 );

  compton_line = MonteCarlo::calculateComptonLineEnergy( 1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_line, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the electron momentum projection can be calculated
FRENSIE_UNIT_TEST( PhotonKinematicsHelpers, calculateElectronMomentumProjection )
{
  double pz =
    MonteCarlo::calculateElectronMomentumProjection( 1.0, 0.5, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pz, 0.9713008908317715, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 1.0, 0.5, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pz, 0.42796164780180407, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 1.0, 0.5, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pz, -1.0, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 0.5, 0.1, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pz, -0.34050811062539044, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 0.5, 0.1, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pz, -0.5925696741935385, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 0.5, 0.1, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pz, -1.0, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 0.1, 0.001, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pz, -0.9763228686410937, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 0.1, 0.001, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pz, -0.9879936502161719, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjection( 0.1, 0.001, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pz, -1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the max electron momentum projection can be calculated
FRENSIE_UNIT_TEST( PhotonKinematicsHelpers,
		   calculateMaxElectronMomentumProjection )
{
  double pz_max =
    MonteCarlo::calculateMaxElectronMomentumProjection(1.0, 0.03, -1.0);

  FRENSIE_CHECK_FLOATING_EQUALITY( pz_max, 1.9119216204672362, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjection(1.0, 0.03, 0.0);

  FRENSIE_CHECK_FLOATING_EQUALITY( pz_max, 1.3410091350301137, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjection(1.0, 0.03, 1.0);

  FRENSIE_CHECK_FLOATING_EQUALITY( pz_max, -1.0, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjection(0.1, 0.03, -1.0);

  FRENSIE_CHECK_FLOATING_EQUALITY( pz_max, -0.015309889956075224, 1e-14 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjection(0.1, 0.03, 0.0);

  FRENSIE_CHECK_FLOATING_EQUALITY( pz_max, -0.13354578604675912, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjection(0.1, 0.03, 1.0);

  FRENSIE_CHECK_FLOATING_EQUALITY( pz_max, -1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the Doppler broadened energy can be calculated
FRENSIE_UNIT_TEST( PhotonKinematicsHelpers, calculateDopplerBroadenedEnergy )
{
  bool possible;

  double energy = MonteCarlo::calculateDopplerBroadenedEnergy(
						    1.0, 1.0, -1.0, possible );

  FRENSIE_CHECK( possible );
  FRENSIE_CHECK_FLOATING_EQUALITY( energy, 0.5109989101300001, 1e-15 );

  energy = MonteCarlo::calculateDopplerBroadenedEnergy(
						     1.0, 1.0, 0.0, possible );

  FRENSIE_CHECK( possible );
  FRENSIE_CHECK_FLOATING_EQUALITY( energy, 0.7637187226885975, 1e-15 );

  energy = MonteCarlo::calculateDopplerBroadenedEnergy(
						    -1.0, 1.0, 1.0, possible );

  FRENSIE_CHECK( !possible );
  FRENSIE_CHECK_EQUAL( energy, 0.0 );

  energy = MonteCarlo::calculateDopplerBroadenedEnergy(
						 -0.016, 0.1, -1.0, possible );

  FRENSIE_CHECK( possible );
  FRENSIE_CHECK_FLOATING_EQUALITY( energy, 0.06991664095581886, 1e-14 );

  energy = MonteCarlo::calculateDopplerBroadenedEnergy(
						   -0.14, 0.1, 0.0, possible );

  FRENSIE_CHECK( possible );
  FRENSIE_CHECK_FLOATING_EQUALITY( energy, 0.06938244760315788, 1e-15 );

  energy = MonteCarlo::calculateDopplerBroadenedEnergy(
						    -1.0, 0.1, 1.0, possible );

  FRENSIE_CHECK( !possible );
  FRENSIE_CHECK_EQUAL( energy, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering angle can be calculated
FRENSIE_UNIT_TEST( PhotonKinematicsHelpers, calculateScatteringAngleCosine )
{
  bool possible;

  double mu = MonteCarlo::calculateScatteringAngleCosine(
                                      1.0, 0.5109989101300001, 1.0, possible );

  FRENSIE_CHECK( possible );
  FRENSIE_CHECK_FLOATING_EQUALITY( mu, -1.0, 1e-15 );

  mu = MonteCarlo::calculateScatteringAngleCosine(
                                      1.0, 0.7637187226885975, 1.0, possible );

  FRENSIE_CHECK( possible );
  FRENSIE_CHECK_SMALL( mu, 1e-15 );

  mu = MonteCarlo::calculateScatteringAngleCosine( 1.0, 0.0, -1.0, possible );

  FRENSIE_CHECK( !possible );
  FRENSIE_CHECK_EQUAL( mu, 0.0 );

  mu = MonteCarlo::calculateScatteringAngleCosine( 0.1, 0.06991664095581906491, -0.016, possible );

  FRENSIE_CHECK( possible );
  FRENSIE_CHECK_FLOATING_EQUALITY( mu, -1.0, 1e-15 );

  mu = MonteCarlo::calculateScatteringAngleCosine( 0.1, 0.06938244760315788, -0.14, possible );

  FRENSIE_CHECK( possible );
  FRENSIE_CHECK_SMALL( mu, 1e-14 );
}

//---------------------------------------------------------------------------//
// end tstPhotonKinematicsHelpers.cpp
//---------------------------------------------------------------------------//
