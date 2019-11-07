//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicRelaxationModelFactoryNative.cpp
//! \author Alex Robinson
//! \brief  Atomic relaxation model factory using data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::unique_ptr<const Data::ElectronPhotonRelaxationDataContainer>
  native_data_container;

std::shared_ptr<const MonteCarlo::AtomicRelaxationModel> relaxation_model;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a void relaxation model can be created
FRENSIE_UNIT_TEST( AtomicRelaxationModelFactory,
		   createAtomicRelaxationModel_native_void )
{
  MonteCarlo::AtomicRelaxationModelFactory::createAtomicRelaxationModel(
						        *native_data_container,
							relaxation_model,
                                                        1e-3,
                                                        1e-5,
							false );

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 1.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType vacancy = Data::K_SUBSHELL;

  relaxation_model->relaxAtom( vacancy, photon, bank );

  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  // Clear the relaxation model
  relaxation_model.reset();
}

//---------------------------------------------------------------------------//
// Check that a detailed relaxation model can be created
FRENSIE_UNIT_TEST( AtomicRelaxationModelFactory,
		   createAtomicRelaxationModel_native_detailed )
{
  MonteCarlo::AtomicRelaxationModelFactory::createAtomicRelaxationModel(
							*native_data_container,
							relaxation_model,
                                                        1e-3,
                                                        1e-5,
							true );

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 1.0 );
  photon.setPosition( 1.0, 1.0, 1.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType vacancy = Data::K_SUBSHELL;

  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.966; // Choose the non-radiative L1-L2 transition
  fake_stream[1] = 0.5; // direction
  fake_stream[2] = 0.5; // direction
  fake_stream[3] = 0.09809; // Chose the radiative P3 transition
  fake_stream[4] = 0.5; // direction
  fake_stream[5] = 0.5; // direction
  fake_stream[6] = 0.40361; // Chose the radiative P1 transition
  fake_stream[7] = 0.5; // direction
  fake_stream[8] = 0.5; // direction

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  relaxation_model->relaxAtom( vacancy, photon, bank );

  FRENSIE_CHECK_EQUAL( bank.size(), 3 );

  // K non-radiative transition
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 5.71919999999999998e-02 );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::ELECTRON );

  bank.pop();

  // L1 radiative transition
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 1.584170000000E-02 );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::PHOTON );

  bank.pop();

  // L2 radiative transition
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 1.523590000000E-02 );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::PHOTON );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Clear the relaxation model
  relaxation_model.reset();
}

//---------------------------------------------------------------------------//
// Check that a relaxation model gets cached
FRENSIE_UNIT_TEST( AtomicRelaxationModelFactory, cache_models )
{
  MonteCarlo::AtomicRelaxationModelFactory factory_a;

  factory_a.createAndCacheAtomicRelaxationModel( *native_data_container,
						 relaxation_model,
                                                 1e-3,
                                                 1e-5,
						 true );

  std::shared_ptr<const MonteCarlo::AtomicRelaxationModel>
    copy_a_relaxation_model;

  factory_a.createAndCacheAtomicRelaxationModel( *native_data_container,
                                                 copy_a_relaxation_model,
                                                 1e-3,
                                                 1e-5,
                                                 true );

  FRENSIE_CHECK( relaxation_model == copy_a_relaxation_model );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the native data container
  native_data_container.reset(
			      new Data::ElectronPhotonRelaxationDataContainer(
						     test_native_file_name ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAtomicRelaxationModelFactoryNative.cpp
//---------------------------------------------------------------------------//
