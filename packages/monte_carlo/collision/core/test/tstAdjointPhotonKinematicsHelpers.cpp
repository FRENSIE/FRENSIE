//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotonKinematicsHelpers.cpp
//! \author Alex Robinson
//! \brief  Adjoint photon kinematics helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonKinematicsHelpers.hpp"
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the adjoint Compton line energy can be calculated
TEUCHOS_UNIT_TEST( AdjointPhotonKinematicsHelpers, 
		   calculateAdjointComptonLineEnergy )
{
  double adjoint_compton_line = 
    MonteCarlo::calculateAdjointComptonLineEnergy( 0.1, -1.0 );
  
  TEST_FLOATING_EQUALITY( adjoint_compton_line, 0.16430890703649043, 1e-15 );

  adjoint_compton_line = 
    MonteCarlo::calculateAdjointComptonLineEnergy( 0.1, 0.0 );
  
  TEST_FLOATING_EQUALITY( adjoint_compton_line, 0.12433096476298923, 1e-15 );

  adjoint_compton_line = 
    MonteCarlo::calculateAdjointComptonLineEnergy( 0.1, 1.0 );

  TEST_FLOATING_EQUALITY( adjoint_compton_line, 0.1, 1e-15 );

  // Above E = 0.5*me the min scattering angle cosine increases from -1.0
  adjoint_compton_line = MonteCarlo::calculateAdjointComptonLineEnergy( 
		       Utility::PhysicalConstants::electron_rest_mass_energy/2,
		       -0.99999 );

  TEST_FLOATING_EQUALITY( adjoint_compton_line, 51099.89101266523, 1e-15 );

  adjoint_compton_line = MonteCarlo::calculateAdjointComptonLineEnergy( 
		       Utility::PhysicalConstants::electron_rest_mass_energy/2,
		       0.0 );

  TEST_FLOATING_EQUALITY( adjoint_compton_line, 0.51099891013, 1e-15 );

  adjoint_compton_line = MonteCarlo::calculateAdjointComptonLineEnergy( 
		       Utility::PhysicalConstants::electron_rest_mass_energy/2,
		       1.0 );

  TEST_FLOATING_EQUALITY( 
		       adjoint_compton_line, 
		       Utility::PhysicalConstants::electron_rest_mass_energy/2,
		       1e-15 );

  adjoint_compton_line = 
    MonteCarlo::calculateAdjointComptonLineEnergy( 1.0, 0.48901 );

  TEST_FLOATING_EQUALITY( adjoint_compton_line, 57350.33160410301, 1e-15 );

  adjoint_compton_line = 
    MonteCarlo::calculateAdjointComptonLineEnergy( 1.0, 0.9 );

  TEST_FLOATING_EQUALITY( adjoint_compton_line, 1.243309647629892, 1e-15 );

  adjoint_compton_line = 
    MonteCarlo::calculateAdjointComptonLineEnergy( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( adjoint_compton_line, 1.0, 1e-15 );

  adjoint_compton_line = 
    MonteCarlo::calculateAdjointComptonLineEnergy( 10.0, 0.948901 );

  TEST_FLOATING_EQUALITY( adjoint_compton_line, 573503.3160410301, 1e-15 );

  adjoint_compton_line = 
    MonteCarlo::calculateAdjointComptonLineEnergy( 10.0, 0.99 );

  TEST_FLOATING_EQUALITY( adjoint_compton_line, 12.433096476298923, 1e-15 );

  adjoint_compton_line = 
    MonteCarlo::calculateAdjointComptonLineEnergy( 10.0, 1.0 );
    
  TEST_FLOATING_EQUALITY( adjoint_compton_line, 10.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the absolute min scattering angle cosine can be calculated
TEUCHOS_UNIT_TEST( AdjointPhotonKinematicsHelpers,
		   calculateAbsoluteMinScatteringAngleCosine )
{
  double mu_min = MonteCarlo::calculateAbsoluteMinScatteringAngleCosine( 0.1 );

  TEST_FLOATING_EQUALITY( mu_min, -1.0, 1e-15 );

  mu_min = MonteCarlo::calculateAbsoluteMinScatteringAngleCosine(
		   Utility::PhysicalConstants::electron_rest_mass_energy/2.0 );
							 
  TEST_FLOATING_EQUALITY( mu_min, -1.0, 1e-15 );

  mu_min = MonteCarlo::calculateAbsoluteMinScatteringAngleCosine( 1.0 );

  TEST_FLOATING_EQUALITY( mu_min, 0.48900108987, 1e-15 );

  mu_min = MonteCarlo::calculateAbsoluteMinScatteringAngleCosine( 10.0 );
  
  TEST_FLOATING_EQUALITY( mu_min, 0.948900108987, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the min scattering angle cosine can be calculated
TEUCHOS_UNIT_TEST( AdjointPhotonKinematicsHelpers,
		   calculateMinScatteringAngleCosine )
{
  double mu_min = MonteCarlo::calculateMinScatteringAngleCosine( 0.01, 0.1 );

  TEST_FLOATING_EQUALITY( mu_min, -1.0, 1e-15 );

  mu_min = 
    MonteCarlo::calculateMinScatteringAngleCosine( 0.0718705616632476, 0.1 );

  TEST_FLOATING_EQUALITY( mu_min, -1.0, 1e-15 );

  mu_min = MonteCarlo::calculateMinScatteringAngleCosine( 0.09, 0.1 );

  TEST_FLOATING_EQUALITY( mu_min, 0.4322234331888879, 1e-14 );

  mu_min = MonteCarlo::calculateMinScatteringAngleCosine( 0.1, 0.1 );
  
  TEST_FLOATING_EQUALITY( mu_min, 1.0, 1e-15 );

  mu_min = MonteCarlo::calculateMinScatteringAngleCosine( 0.1, 1.0 );

  TEST_FLOATING_EQUALITY( mu_min, -1.0, 1e-15 );

  mu_min = 
    MonteCarlo::calculateMinScatteringAngleCosine( 0.20350423413905203, 1.0 );

  TEST_FLOATING_EQUALITY( mu_min, -1.0, 1e-15 );

  mu_min = MonteCarlo::calculateMinScatteringAngleCosine( 0.5, 1.0 );

  TEST_FLOATING_EQUALITY( mu_min, 0.48900108987, 1e-15 );

  mu_min = MonteCarlo::calculateMinScatteringAngleCosine( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( mu_min, 1.0, 1e-15 );

  mu_min = MonteCarlo::calculateMinScatteringAngleCosine( 0.1, 10.0 );

  TEST_FLOATING_EQUALITY( mu_min, -1.0, 1e-15 );

  mu_min =
    MonteCarlo::calculateMinScatteringAngleCosine( 0.24913409257587504, 10.0 );

  TEST_FLOATING_EQUALITY( mu_min, -1.0, 1e-15 );

  mu_min = MonteCarlo::calculateMinScatteringAngleCosine( 0.3, 10.0 );

  TEST_FLOATING_EQUALITY( mu_min, -0.6522298094203334, 1e-15 );

  mu_min = MonteCarlo::calculateMinScatteringAngleCosine( 10.0, 10.0 );

  TEST_FLOATING_EQUALITY( mu_min, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the absolute min inverse energy gain ratio can be calculated
TEUCHOS_UNIT_TEST( AdjointPhotonKinematicsHelpers, 
		   calculateAbsoluteMinInverseEnergyGainRatio )
{
  double x_min = MonteCarlo::calculateAbsoluteMinInverseEnergyGainRatio( 0.1 );
  
  TEST_FLOATING_EQUALITY( x_min, 0.6086097327504685, 1e-15 );
  
  x_min = MonteCarlo::calculateAbsoluteMinInverseEnergyGainRatio(
		     Utility::PhysicalConstants::electron_rest_mass_energy/2 );
  
  UTILITY_TEST_FLOATING_EQUALITY( x_min, 0.0, 1e-15 );
  
  x_min = MonteCarlo::calculateAbsoluteMinInverseEnergyGainRatio( 1.0 );
  
  UTILITY_TEST_FLOATING_EQUALITY( x_min, 0.0, 1e-15 );

  x_min = MonteCarlo::calculateAbsoluteMinInverseEnergyGainRatio( 10.0 );
  
  UTILITY_TEST_FLOATING_EQUALITY( x_min, 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the min inverse energy gain ratio can be calculated
TEUCHOS_UNIT_TEST( AdjointPhotonKinematicsHelpers, 
		   calculateMinInverseEnergyGainRatio )
{
  double x_min = MonteCarlo::calculateMinInverseEnergyGainRatio( 0.01, 0.1 );

  TEST_FLOATING_EQUALITY( x_min, 0.9608609732750468, 1e-15 );

  x_min = 
    MonteCarlo::calculateMinInverseEnergyGainRatio( 0.0718705616632476, 0.1 );

  TEST_FLOATING_EQUALITY( x_min, 0.7187056166324759, 1e-15 );

  x_min = MonteCarlo::calculateMinInverseEnergyGainRatio( 0.09, 0.1 );

  TEST_FLOATING_EQUALITY( x_min, 0.8999999999999999, 1e-14 );

  x_min = MonteCarlo::calculateMinInverseEnergyGainRatio( 0.1, 0.1 );
  
  TEST_FLOATING_EQUALITY( x_min, 1.0, 1e-15 );

  x_min = MonteCarlo::calculateMinInverseEnergyGainRatio( 0.1, 1.0 );

  TEST_FLOATING_EQUALITY( x_min, 0.6086097327504685, 1e-15 );

  x_min = 
    MonteCarlo::calculateMinInverseEnergyGainRatio( 0.20350423413905203, 1.0 );
  
  TEST_FLOATING_EQUALITY( x_min, 0.20350423413905205, 1e-15 );

  x_min = MonteCarlo::calculateMinInverseEnergyGainRatio( 0.5, 1.0 );

  TEST_FLOATING_EQUALITY( x_min, 0.5, 1e-15 );

  x_min = MonteCarlo::calculateMinInverseEnergyGainRatio( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( x_min, 1.0, 1e-15 );

  x_min = MonteCarlo::calculateMinInverseEnergyGainRatio( 0.1, 10.0 );

  TEST_FLOATING_EQUALITY( x_min, 0.6086097327504685, 1e-15 );

  x_min =
    MonteCarlo::calculateMinInverseEnergyGainRatio( 0.24913409257587504, 10.0 );

  TEST_FLOATING_EQUALITY( x_min, 0.02491340925758756, 1e-14 );

  x_min = MonteCarlo::calculateMinInverseEnergyGainRatio( 0.3, 10.0 );

  TEST_FLOATING_EQUALITY( x_min, 0.03, 1e-15 );

  x_min = MonteCarlo::calculateMinInverseEnergyGainRatio( 10.0, 10.0 );

  TEST_FLOATING_EQUALITY( x_min, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the electron momentum projection can be calculated
TEUCHOS_UNIT_TEST( AdjointPhotonKinematicsHelpers, 
		   calculateElectronMomentumProjectionAdjoint )
{
  double pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.01,
								      0.01001,
								      -1.0 );
								      
  TEST_FLOATING_EQUALITY( pz, 0.019079543104286924, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.01,
							       0.05,
							       -1.0 );

  TEST_FLOATING_EQUALITY( pz, -0.6340508110625389, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.01,
							       0.1,
							       -1.0 );

  TEST_FLOATING_EQUALITY( pz, -0.7826008847954972, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.01,
							       1.0,
							       -1.0 );

  TEST_FLOATING_EQUALITY( pz, -0.9414465081931157, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.01,
							       0.01001,
							       0.0 );
								      
  TEST_FLOATING_EQUALITY( pz, 0.013137895968144289, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.01,
							       0.05,
							       0.0 );

  TEST_FLOATING_EQUALITY( pz, -0.7652750539168163, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.01,
							       0.1,
							       0.0 );

  TEST_FLOATING_EQUALITY( pz, -0.8760610775990149, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.01,
							       1.0,
							       0.0 );

  TEST_FLOATING_EQUALITY( pz, -0.9703819687520027, 1e-15 );
	
  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.01,
							       0.01001,
							       1.0 );

  TEST_FLOATING_EQUALITY( pz, -0.9999999999649817, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.01,
							       0.05,
							       1.0 );

  TEST_FLOATING_EQUALITY( pz, -1.0, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.01,
							       0.1,
							       1.0 );

  TEST_FLOATING_EQUALITY( pz, -1.0, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.01,
							       1.0,
							       1.0 );

  TEST_FLOATING_EQUALITY( pz, -1.0, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 
						       0.5,
						       0.50001,
						       -0.021997820259999967 );

  TEST_FLOATING_EQUALITY( pz, 0.6994483893792213, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 
						       0.5,
						       1.0,
						       -0.021997820259999967 );
  
  TEST_FLOATING_EQUALITY( pz, 0.4433296936845972, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint(
						       0.5,
						       10.0,
						       -0.021997820259999967 );

  TEST_FLOATING_EQUALITY( pz, 0.0498829179830664, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.5,
							       0.50001,
							       0.5 );

  TEST_FLOATING_EQUALITY( pz, 0.48922272651794774, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.5,
							       1.0,
							       0.5 );

  TEST_FLOATING_EQUALITY( pz, -0.012427078802834349, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.5,
							       10.0,
							       0.5 );

  TEST_FLOATING_EQUALITY( pz, -0.472111216889426, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.5,
							       0.50001,
							       1.0 );

  TEST_FLOATING_EQUALITY( pz, -0.999999958625266, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.5,
							       1.0,
							       1.0 );

  TEST_FLOATING_EQUALITY( pz, -1.0, 1e-15 );

  pz = MonteCarlo::calculateElectronMomentumProjectionAdjoint( 0.5,
							       10.0,
							       1.0 );

  TEST_FLOATING_EQUALITY( pz, -1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the maximum electron momentum projection can be calculated
TEUCHOS_UNIT_TEST( AdjointPhotonKinematicsHelpers,
		   calculateMaxElectronMomentumProjectionAdjoint )
{
  // Use small binding energy
  double pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 
									0.01,
									1e-5,
									-1.0 );

  TEST_FLOATING_EQUALITY( pz_max, 0.019079543104286924, 1e-14 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 0.01,
								      1e-5,
								      0.0 );

  TEST_FLOATING_EQUALITY( pz_max, 0.013137895968144289, 1e-14 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint(
							  0.01,
							  1e-5,
							  0.9489511578291708 );

  UTILITY_TEST_FLOATING_EQUALITY( pz_max, 0.0, 1e-15 );
  
  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 0.01,
								      1e-5,
								      1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( pz_max, -1.0, 1e-15 );
									
  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 0.1,
								      1e-5,
								      -1.0 );

  TEST_FLOATING_EQUALITY( pz_max, 0.19565492039210863, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 0.1, 
								      1e-5, 
								      0.0 );

  TEST_FLOATING_EQUALITY( pz_max, 0.13831356723751873, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 
							  0.1, 
							  1e-5, 
							  0.9994890521846516 );

  UTILITY_TEST_FLOATING_EQUALITY( pz_max, 0.0, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 0.1, 
								      1e-5, 
								      1.0 );
    
  TEST_FLOATING_EQUALITY( pz_max, -1.0, 1e-15 );
  
  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 1.0, 
								      1e-5, 
								      -1.0 );
  
  TEST_FLOATING_EQUALITY( pz_max, 1.956956120980415, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 1.0,
								      1e-5,
								      0.0 );

  TEST_FLOATING_EQUALITY( pz_max, 1.3837734080962476, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 
							   1.0,
							   1e-5,
							   0.999994890061998 );
  
  UTILITY_TEST_FLOATING_EQUALITY( pz_max, 0.0, 1e-13 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 1.0,
								      1e-5,
								      1.0 );

  TEST_FLOATING_EQUALITY( pz_max, -1.0, 1e-15 );

  // Use large binding energy
  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 0.1,
								      0.09,
								      -1.0 );

  TEST_FLOATING_EQUALITY( pz_max, -0.05391672145720348, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 0.1, 
  								      0.09, 
  								      0.0 );

  TEST_FLOATING_EQUALITY( pz_max, -0.24599759977332783, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 0.1, 
  								      0.09, 
  								      1.0 );
    
  TEST_FLOATING_EQUALITY( pz_max, -1.0, 1e-15 );
  
  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 1.0, 
  								      0.09, 
  								      -1.0 );
  
  TEST_FLOATING_EQUALITY( pz_max, 1.9981597669951645, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 1.0,
  								      0.09,
  								      0.0 );

  TEST_FLOATING_EQUALITY( pz_max, 1.381182739665556, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 
  							  1.0,
							  0.09,
  							  0.9578074294388074 );
  
  UTILITY_TEST_FLOATING_EQUALITY( pz_max, 0.0, 1e-15 );

  pz_max = MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint( 1.0,
  								      0.09,
  								      1.0 );

  TEST_FLOATING_EQUALITY( pz_max, -1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the minimum electron momentum projection can be calculated
TEUCHOS_UNIT_TEST( AdjointPhotonKinematicsHelpers,
		   calculateAbsoluteMinElectronMomentumProjectionAdjoint )
{
  double pz_min = 
    MonteCarlo::calculateAbsoluteMinElectronMomentumProjectionAdjoint( 0.01,
								       -1.0 );

  TEST_FLOATING_EQUALITY( pz_min, -0.9608609732750468, 1e-15 );

  pz_min = 
    MonteCarlo::calculateAbsoluteMinElectronMomentumProjectionAdjoint( 0.01,
								       0.0 );
  
  TEST_FLOATING_EQUALITY( pz_min, -0.9804304866375234, 1e-15 );

  pz_min = 
    MonteCarlo::calculateAbsoluteMinElectronMomentumProjectionAdjoint( 0.01,
								       1.0 );

  TEST_FLOATING_EQUALITY( pz_min, -1.0, 1e-15 );

  pz_min = 
    MonteCarlo::calculateAbsoluteMinElectronMomentumProjectionAdjoint( 0.1,
								       -1.0 );

  TEST_FLOATING_EQUALITY( pz_min, -0.6086097327504685, 1e-15 );

  pz_min = 
    MonteCarlo::calculateAbsoluteMinElectronMomentumProjectionAdjoint( 0.1,
								       0.0 );
  
  TEST_FLOATING_EQUALITY( pz_min, -0.8043048663752342, 1e-15 );

  pz_min = 
    MonteCarlo::calculateAbsoluteMinElectronMomentumProjectionAdjoint( 0.1,
								       1.0 );

  TEST_FLOATING_EQUALITY( pz_min, -1.0, 1e-15 );

  pz_min = 
    MonteCarlo::calculateAbsoluteMinElectronMomentumProjectionAdjoint( 
							       1.0,
							       0.48900108987 );

  TEST_FLOATING_EQUALITY( pz_min, 0.0, 1e-15 );

  pz_min = 
    MonteCarlo::calculateAbsoluteMinElectronMomentumProjectionAdjoint( 1.0,
								       0.9 );
  
  TEST_FLOATING_EQUALITY( pz_min, -0.8043048663752344, 1e-15 );

  pz_min = 
    MonteCarlo::calculateAbsoluteMinElectronMomentumProjectionAdjoint( 1.0,
								       1.0 );

  TEST_FLOATING_EQUALITY( pz_min, -1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the minimum electron momentum projection can be calculated
TEUCHOS_UNIT_TEST( AdjointPhotonKinematicsHelpers,
		   calculateMinElectronMomentumProjectionAdjoint )
{
  // Use small binding energy
  double pz_min = 
    MonteCarlo::calculateMinElectronMomentumProjectionAdjoint( 0.01,
							       0.1,
							       -1.0 );

  TEST_FLOATING_EQUALITY( pz_min, -0.7826008847954972, 1e-15 );

  pz_min = MonteCarlo::calculateMinElectronMomentumProjectionAdjoint( 0.01,
								      0.1,
								      0.0 );

  TEST_FLOATING_EQUALITY( pz_min, -0.8760610775990149, 1e-15 );
  
  pz_min = MonteCarlo::calculateMinElectronMomentumProjectionAdjoint( 0.01,
								      0.1,
								      1.0 );

  TEST_FLOATING_EQUALITY( pz_min, -1.0, 1e-15 );

  pz_min = MonteCarlo::calculateMinElectronMomentumProjectionAdjoint( 
							 0.09,
							 0.1,
							 0.4322234331888879 );

  UTILITY_TEST_FLOATING_EQUALITY( pz_min, 0.0, 1e-15 );

  pz_min = MonteCarlo::calculateMinElectronMomentumProjectionAdjoint( 0.09,
								      0.1,
								      0.9 );

  TEST_FLOATING_EQUALITY( pz_min, -0.1890097454446809, 1e-15 );

  pz_min = MonteCarlo::calculateMinElectronMomentumProjectionAdjoint( 0.09,
								      0.1,
								      1.0 );

  TEST_FLOATING_EQUALITY( pz_min, -1.0, 1e-13 );

  pz_min = MonteCarlo::calculateMinElectronMomentumProjectionAdjoint( 0.1,
								      1.0,
								      -1.0 );

  TEST_FLOATING_EQUALITY( pz_min, -0.4623724843186078, 1e-15 );

  pz_min = MonteCarlo::calculateMinElectronMomentumProjectionAdjoint( 0.1,
								      1.0, 
								      0.0 );

  TEST_FLOATING_EQUALITY( pz_min, -0.7008095352892351, 1e-15 );

  pz_min = MonteCarlo::calculateMinElectronMomentumProjectionAdjoint( 0.1,
								      1.0,
								      1.0 );

  TEST_FLOATING_EQUALITY( pz_min, -1.0, 1e-15 );

  pz_min = MonteCarlo::calculateMinElectronMomentumProjectionAdjoint( 
							       0.5,
							       1.0,
							       0.48900108987 );

  UTILITY_TEST_FLOATING_EQUALITY( pz_min, 0.0, 1e-15 );

  pz_min = MonteCarlo::calculateMinElectronMomentumProjectionAdjoint( 0.5,
								      1.0,
								      0.9 );

  TEST_FLOATING_EQUALITY( pz_min, -0.6797616799158803, 1e-15 );

  pz_min = MonteCarlo::calculateMinElectronMomentumProjectionAdjoint( 0.5,
								      1.0,
								      1.0 );

  TEST_FLOATING_EQUALITY( pz_min, -1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the Doppler broadened energy can be calculated
TEUCHOS_UNIT_TEST( AdjointPhotonKinematicsHelpers,
		   calculateDopplerBroadenedEnergyAdjoint )
{
  bool possible;

  double energy = MonteCarlo::calculateDopplerBroadenedEnergyAdjoint( 
						 0.019, 0.01, -1.0, possible );

  TEST_ASSERT( possible );
  TEST_FLOATING_EQUALITY( energy, 0.010011624370762988, 1e-14 );

  energy = MonteCarlo::calculateDopplerBroadenedEnergyAdjoint(
						   0.0, 0.01, -1.0, possible );

  TEST_ASSERT( possible );
  TEST_FLOATING_EQUALITY( energy, 0.010407332879714635, 1e-15 );

  energy = MonteCarlo::calculateDopplerBroadenedEnergyAdjoint(
						  -0.5, 0.01, -1.0, possible );

  TEST_ASSERT( possible );
  TEST_FLOATING_EQUALITY( energy, 0.032547776596062165, 1e-15 );

  energy = MonteCarlo::calculateDopplerBroadenedEnergyAdjoint(
						 -0.96, 0.01, -1.0, possible );

  TEST_ASSERT( possible );

  // Test the absolute minimum pz
  energy = MonteCarlo::calculateDopplerBroadenedEnergyAdjoint(
				   -0.9608609732750468, 0.01, -1.0, possible );

  TEST_ASSERT( !possible );
  
  energy = MonteCarlo::calculateDopplerBroadenedEnergyAdjoint(
						  -1.0, 0.01, -1.0, possible );

  TEST_ASSERT( !possible );

  energy = MonteCarlo::calculateDopplerBroadenedEnergyAdjoint( 
						  0.013, 0.01, 0.0, possible );

  TEST_ASSERT( possible );
  TEST_FLOATING_EQUALITY( energy, 0.01001197156806066, 1e-14 );

  energy = MonteCarlo::calculateDopplerBroadenedEnergyAdjoint( 
						    0.0, 0.01, 0.0, possible );
  
  TEST_ASSERT( possible );
  TEST_FLOATING_EQUALITY( energy, 0.0101996012326135629, 1e-15 );

  energy = MonteCarlo::calculateDopplerBroadenedEnergyAdjoint( 
						   -0.5, 0.01, 0.0, possible );

  TEST_ASSERT( possible );
  TEST_FLOATING_EQUALITY( energy, 0.022980907267125355, 1e-15 );

  // Test the absolute minimum pz
  energy = MonteCarlo::calculateDopplerBroadenedEnergyAdjoint( 
				    -0.9804304866375234, 0.01, 0.0, possible );
  
  TEST_ASSERT( !possible );

  energy = MonteCarlo::calculateDopplerBroadenedEnergyAdjoint(
						    -1.0, 0.1, 0.0, possible );

  TEST_ASSERT( !possible );
}

//---------------------------------------------------------------------------//
// end tstAdjointPhotonKinematicsHelpers.cpp
//---------------------------------------------------------------------------//
