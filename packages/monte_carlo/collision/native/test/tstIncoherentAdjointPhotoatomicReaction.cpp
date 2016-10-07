//---------------------------------------------------------------------------//
//!
//! \file   tstIncoherentAdjointPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The incoherent adjoint photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_InterpolatedFullyTabularTwoDDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> adjoint_incoherent_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotoatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( adjoint_incoherent_reaction->getReactionType(),
                       MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotoatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( adjoint_incoherent_reaction->getThresholdEnergy(),
                       1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the max energy can be returned
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotoatomicReaction, getMaxEnergy )
{
  TEST_EQUALITY_CONST( adjoint_incoherent_reaction->getMaxEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check if an energy falls within the energy grid
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotoatomicReaction,
                   isEnergyWithinEnergyGrid )
{
  TEST_ASSERT( !adjoint_incoherent_reaction->isEnergyWithinEnergyGrid( 9e-4 ) );
  TEST_ASSERT( adjoint_incoherent_reaction->isEnergyWithinEnergyGrid( 1e-3 ) );
  TEST_ASSERT( adjoint_incoherent_reaction->isEnergyWithinEnergyGrid( 1.0 ) );
  TEST_ASSERT( adjoint_incoherent_reaction->isEnergyWithinEnergyGrid( 20.0 ) );
  TEST_ASSERT( !adjoint_incoherent_reaction->isEnergyWithinEnergyGrid( 20.1 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint photons emitted from the reaction can be
// returned
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotoatomicReaction,
                   getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( adjoint_incoherent_reaction->getNumberOfEmittedPhotons( 9e-4 ),
                       0u );
  TEST_EQUALITY_CONST( adjoint_incoherent_reaction->getNumberOfEmittedPhotons( 1e-3 ),
                       1u );
  TEST_EQUALITY_CONST( adjoint_incoherent_reaction->getNumberOfEmittedPhotons( 20.0 ),
                       1u );
  TEST_EQUALITY_CONST( adjoint_incoherent_reaction->getNumberOfEmittedPhotons( 20.1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint electrons emitted from the reaction can be
// returned
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotoatomicReaction,
                   getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( adjoint_incoherent_reaction->getNumberOfEmittedElectrons( 9e-4 ),
                       0u );
  TEST_EQUALITY_CONST( adjoint_incoherent_reaction->getNumberOfEmittedElectrons( 1e-3 ),
                       0u );
  TEST_EQUALITY_CONST( adjoint_incoherent_reaction->getNumberOfEmittedElectrons( 20.0 ),
                       0u );
  TEST_EQUALITY_CONST( adjoint_incoherent_reaction->getNumberOfEmittedElectrons( 20.1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotoatomicReaction, getCrossSection )
{
  double cross_section = 
    adjoint_incoherent_reaction->getCrossSection( 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.620920802623559753, 1e-12 );

  cross_section =
    adjoint_incoherent_reaction->getCrossSection( 1.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 5.50415974966055277, 1e-12 );

  cross_section =
    adjoint_incoherent_reaction->getCrossSection( 20.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned (efficiently)
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotoatomicReaction,
                   getCrossSection_efficient )
{
  double cross_section = 
    adjoint_incoherent_reaction->getCrossSection( 1e-3, 0u );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.620920802623559753, 1e-12 );

  cross_section =
    adjoint_incoherent_reaction->getCrossSection( 20.0, 1166 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the incoherent reaction can be simulated
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotoatomicReaction, react )
{
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy(
		  Utility::PhysicalConstants::electron_rest_mass_energy/10.0 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  // Set the fake stream
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.15; // branch 1
  fake_stream[1] = 0.4721647344828152; // select x = 0.9
  fake_stream[2] = 0.49; // accept
  fake_stream[3] = 0.91; // reject based on scattering function
  fake_stream[4] = 0.15; // branch 1
  fake_stream[5] = 0.4721647344828152; // select x = 0.9
  fake_stream[6] = 0.49; // accept
  fake_stream[7] = 0.909; // accept based on scattering function
  fake_stream[8] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  adjoint_incoherent_reaction->react( adjoint_photon,
				      bank,
				      shell_of_interaction );

  TEST_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  0.05677765668111111,
			  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( adjoint_photon.getZDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( bank.size(), 0 );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Generate two probes
  adjoint_photon.setEnergy( 0.3 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  adjoint_incoherent_reaction->react( adjoint_photon,
				      bank,
				      shell_of_interaction );

  TEST_EQUALITY_CONST( bank.size(), 2 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(),
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  // Due to the coarseness of the 2d test grid the weight will not be
  // exactly what it should theoretically be
  TEST_FLOATING_EQUALITY( bank.top().getWeight(),
			  0.401104057813784276,
			  5e-3 );

  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getEnergy(), 1.0 );
  // Due to the coarseness of the 2d test grid the weight will not be
  // exactly what it should theoretically be
  TEST_FLOATING_EQUALITY( bank.top().getWeight(),
			  0.203384875392762621,
			  5e-3 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the native data file container
  Data::AdjointElectronPhotonRelaxationDataContainer
    data_container( test_native_file_name );

  // Get the incoming energy grid
  Teuchos::ArrayRCP<double> incoming_energy_grid;
  incoming_energy_grid.assign(
                           data_container.getAdjointPhotonEnergyGrid().begin(),
                           data_container.getAdjointPhotonEnergyGrid().end() );

  // Evaluate the cross section at the energy of interest
  Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>
    two_d_cross_section( data_container.getAdjointPhotonEnergyGrid(),
                         data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid(),
                         data_container.getAdjointWallerHartreeIncoherentCrossSection() );

  Teuchos::ArrayRCP<double> cross_section( incoming_energy_grid.size() );

  for( size_t i = 0; i < incoming_energy_grid.size(); ++i )
  {
    cross_section[i] =
      two_d_cross_section.evaluate( incoming_energy_grid[i], 20.0 );

    std::cout << cross_section[i] << std::endl;
  }
  
  // Create the scattering distribution
  std::shared_ptr<MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
    scattering_distribution;

  MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution(
                                       data_container,
                                       scattering_distribution,
                                       MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL,
                                       20.0 );

  // Create the reaction
  std::shared_ptr<MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > complete_reaction(
   new MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false>(
                                                   incoming_energy_grid,
                                                   cross_section,
                                                   0u,
                                                   scattering_distribution ) );

  // Set the critical line energies
  Teuchos::ArrayRCP<double> critical_line_energies( 3 );

  critical_line_energies[0] = 0.08;
  critical_line_energies[1] =
    Utility::PhysicalConstants::electron_rest_mass_energy;
  critical_line_energies[2] = 1.0;

  complete_reaction->setCriticalLineEnergies(critical_line_energies);
  
  adjoint_incoherent_reaction = complete_reaction;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstIncoherentAdjointPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
