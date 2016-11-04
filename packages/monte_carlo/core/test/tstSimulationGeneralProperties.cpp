//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationGeneralProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation general properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationGeneralProperties.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test the simulation properties defaults
TEUCHOS_UNIT_TEST( SimulationGeneralProperties, defaults )
{
  TEST_EQUALITY_CONST( MonteCarlo::SimulationGeneralProperties::getParticleMode(),
                       MonteCarlo::NEUTRON_MODE );
  TEST_EQUALITY_CONST(MonteCarlo::SimulationGeneralProperties::getNumberOfHistories(),
                      0 );
  TEST_EQUALITY_CONST(MonteCarlo::SimulationGeneralProperties::getSurfaceFluxEstimatorAngleCosineCutoff(),
		      0.001 );
  TEST_ASSERT( MonteCarlo::SimulationGeneralProperties::displayWarnings() );
  TEST_ASSERT( !MonteCarlo::SimulationGeneralProperties::isImplicitCaptureModeOn() );

}

//---------------------------------------------------------------------------//
// Test that the particle mode can be set
TEUCHOS_UNIT_TEST( SimulationGeneralProperties, setParticleMode )
{
  MonteCarlo::ParticleModeType default_mode =
    MonteCarlo::SimulationGeneralProperties::getParticleMode();

  MonteCarlo::SimulationGeneralProperties::setParticleMode( MonteCarlo::NEUTRON_MODE);

  TEST_EQUALITY_CONST( MonteCarlo::SimulationGeneralProperties::getParticleMode(),
		       MonteCarlo::NEUTRON_MODE );

  MonteCarlo::SimulationGeneralProperties::setParticleMode( MonteCarlo::PHOTON_MODE );

  TEST_EQUALITY_CONST( MonteCarlo::SimulationGeneralProperties::getParticleMode(),
		       MonteCarlo::PHOTON_MODE );

  MonteCarlo::SimulationGeneralProperties::setParticleMode(
						   MonteCarlo::ELECTRON_MODE );

  TEST_EQUALITY_CONST( MonteCarlo::SimulationGeneralProperties::getParticleMode(),
		       MonteCarlo::ELECTRON_MODE );

  MonteCarlo::SimulationGeneralProperties::setParticleMode(
					     MonteCarlo::NEUTRON_PHOTON_MODE );

  TEST_EQUALITY_CONST( MonteCarlo::SimulationGeneralProperties::getParticleMode(),
		       MonteCarlo::NEUTRON_PHOTON_MODE );

  MonteCarlo::SimulationGeneralProperties::setParticleMode(
					    MonteCarlo::PHOTON_ELECTRON_MODE );

  TEST_EQUALITY_CONST( MonteCarlo::SimulationGeneralProperties::getParticleMode(),
		       MonteCarlo::PHOTON_ELECTRON_MODE );

  MonteCarlo::SimulationGeneralProperties::setParticleMode(
				    MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  TEST_EQUALITY_CONST( MonteCarlo::SimulationGeneralProperties::getParticleMode(),
		       MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  MonteCarlo::SimulationGeneralProperties::setParticleMode( default_mode );
}

//---------------------------------------------------------------------------//
// Test that the number of histories to run can be set
TEUCHOS_UNIT_TEST( SimulationGeneralProperties, setNumberOfHistories )
{
  unsigned long long default_value =
    MonteCarlo::SimulationGeneralProperties::getNumberOfHistories();

  MonteCarlo::SimulationGeneralProperties::setNumberOfHistories( 1000000000 );

  TEST_ASSERT( MonteCarlo::SimulationGeneralProperties::getNumberOfHistories() !=
	       default_value );
  TEST_EQUALITY_CONST(MonteCarlo::SimulationGeneralProperties::getNumberOfHistories(),
		      1000000000 );
}

//---------------------------------------------------------------------------//
// Test that the surface flux angle cosine cutoff can be set
TEUCHOS_UNIT_TEST( SimulationGeneralProperties,
		   setSurfaceFluxEstimatorAngleCosineCutoff )
{
  double default_value =
    MonteCarlo::SimulationGeneralProperties::getSurfaceFluxEstimatorAngleCosineCutoff();

  MonteCarlo::SimulationGeneralProperties::setSurfaceFluxEstimatorAngleCosineCutoff( 0.1 );

  TEST_ASSERT( MonteCarlo::SimulationGeneralProperties::getSurfaceFluxEstimatorAngleCosineCutoff() !=
	       default_value );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationGeneralProperties::getSurfaceFluxEstimatorAngleCosineCutoff(),
		       0.1 );

  // Reset to the default
  MonteCarlo::SimulationGeneralProperties::setSurfaceFluxEstimatorAngleCosineCutoff( default_value );
}

//---------------------------------------------------------------------------//
// Test that the min particle energy can be returned
TEUCHOS_UNIT_TEST( SimulationGeneralProperties, getMinParticleEnergy )
{
  double default_value_neutron =
    MonteCarlo::SimulationNeutronProperties::getMinNeutronEnergy();

  MonteCarlo::SimulationNeutronProperties::setMinNeutronEnergy( 1e-8 );

  double default_value_photon =
    MonteCarlo::SimulationPhotonProperties::getMinPhotonEnergy();

  MonteCarlo::SimulationPhotonProperties::setMinPhotonEnergy( 1e-2 );

  double default_value_electron =
    MonteCarlo::SimulationElectronProperties::getMinElectronEnergy();

  MonteCarlo::SimulationElectronProperties::setMinElectronEnergy( 1e-2 );

  TEST_EQUALITY( MonteCarlo::SimulationGeneralProperties::getMinParticleEnergy<MonteCarlo::NeutronState>(),
		 1e-8 );
  TEST_EQUALITY( MonteCarlo::SimulationGeneralProperties::getMinParticleEnergy<MonteCarlo::PhotonState>(),
		 1e-2 );
  TEST_EQUALITY( MonteCarlo::SimulationGeneralProperties::getMinParticleEnergy<MonteCarlo::ElectronState>(),
		 1e-2 );

  // Reset the default values
  MonteCarlo::SimulationNeutronProperties::setMinNeutronEnergy( default_value_neutron );
  MonteCarlo::SimulationPhotonProperties::setMinPhotonEnergy( default_value_photon );
  MonteCarlo::SimulationElectronProperties::setMinElectronEnergy( default_value_electron );
}

//---------------------------------------------------------------------------//
// Test that the max particle energy can be returned
TEUCHOS_UNIT_TEST( SimulationGeneralProperties, getMaxParticleEnergy )
{
  double default_value_neutron =
    MonteCarlo::SimulationNeutronProperties::getMaxNeutronEnergy();

  MonteCarlo::SimulationNeutronProperties::setMaxNeutronEnergy( 15.0 );

  double default_value_photon =
    MonteCarlo::SimulationPhotonProperties::getMaxPhotonEnergy();

  MonteCarlo::SimulationPhotonProperties::setMaxPhotonEnergy( 15.0 );

  double default_value_electron =
    MonteCarlo::SimulationElectronProperties::getMaxElectronEnergy();

  MonteCarlo::SimulationElectronProperties::setMaxElectronEnergy( 15.0 );

  TEST_EQUALITY( MonteCarlo::SimulationGeneralProperties::getMaxParticleEnergy<MonteCarlo::NeutronState>(),
		 15.0 );
  TEST_EQUALITY( MonteCarlo::SimulationGeneralProperties::getMaxParticleEnergy<MonteCarlo::PhotonState>(),
		 15.0 );
  TEST_EQUALITY( MonteCarlo::SimulationGeneralProperties::getMaxParticleEnergy<MonteCarlo::ElectronState>(),
		 15.0 );

  // Reset the default values
  MonteCarlo::SimulationNeutronProperties::setMaxNeutronEnergy( default_value_neutron );
  MonteCarlo::SimulationPhotonProperties::setMaxPhotonEnergy( default_value_photon );
  MonteCarlo::SimulationElectronProperties::setMaxElectronEnergy( default_value_electron );
}

//---------------------------------------------------------------------------//
// Test that warnings can be disabled
TEUCHOS_UNIT_TEST( SimulationGeneralProperties, setWarningsOff )
{
  TEST_ASSERT( MonteCarlo::SimulationGeneralProperties::displayWarnings() );

  MonteCarlo::SimulationGeneralProperties::setWarningsOff();

  TEST_ASSERT( !MonteCarlo::SimulationGeneralProperties::displayWarnings() );
}

//---------------------------------------------------------------------------//
// Test that implicit capture mode can be turned on
TEUCHOS_UNIT_TEST( SimulationGeneralProperties, setImplicitCaptureModeOn )
{
  TEST_ASSERT( !MonteCarlo::SimulationGeneralProperties::isImplicitCaptureModeOn() );

  MonteCarlo::SimulationGeneralProperties::setImplicitCaptureModeOn();

  TEST_ASSERT( MonteCarlo::SimulationGeneralProperties::isImplicitCaptureModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the number of batches per processor can be set
TEUCHOS_UNIT_TEST( SimulationGeneralProperties, setNumberOfBatchesPerProcessor )
{
  MonteCarlo::SimulationGeneralProperties::setNumberOfBatchesPerProcessor( 25 );

  TEST_EQUALITY_CONST( MonteCarlo::SimulationGeneralProperties::getNumberOfBatchesPerProcessor(),
    25 );
}

//---------------------------------------------------------------------------//
// end tstSimulationGeneralProperties.cpp
//---------------------------------------------------------------------------//
