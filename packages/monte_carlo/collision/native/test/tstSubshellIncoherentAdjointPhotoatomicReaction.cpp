//---------------------------------------------------------------------------//
//!
//! \file   tstSubshellIncoherentAdjointPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The subshell incoherent adjoint photoatomic reaction unit tests
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
#include "MonteCarlo_SubshellIncoherentAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_InterpolatedFullyTabularTwoDDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> incoherent_adjoint_reaction;

std::shared_ptr<MonteCarlo::SubshellIncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > subshell_incoherent_adjoint_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction, getSubshell )
{
  TEST_EQUALITY_CONST( subshell_incoherent_adjoint_reaction->getSubshell(),
                       Data::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energy can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getSubshellBindingEnergy )
{
  TEST_EQUALITY_CONST( subshell_incoherent_adjoint_reaction->getSubshellBindingEnergy(),
                       1.8285e-3 );
}

//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getReactionType )
{
  TEST_EQUALITY_CONST( incoherent_adjoint_reaction->getReactionType(),
                       MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getThresholdEnergy )
{
  TEST_EQUALITY_CONST( incoherent_adjoint_reaction->getThresholdEnergy(),
                       1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the max energy can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getMaxEnergy )
{
  TEST_EQUALITY_CONST( incoherent_adjoint_reaction->getMaxEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check if an energy falls within the energy grid
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   isEnergyWithinEnergyGrid )
{
  TEST_ASSERT( !incoherent_adjoint_reaction->isEnergyWithinEnergyGrid( 9e-4 ) );
  TEST_ASSERT( incoherent_adjoint_reaction->isEnergyWithinEnergyGrid( 1e-3 ) );
  TEST_ASSERT( incoherent_adjoint_reaction->isEnergyWithinEnergyGrid( 1.0 ) );
  TEST_ASSERT( incoherent_adjoint_reaction->isEnergyWithinEnergyGrid( 20.0 ) );
  TEST_ASSERT( !incoherent_adjoint_reaction->isEnergyWithinEnergyGrid( 20.1 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint photons emitted from the reaction can
// be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( incoherent_adjoint_reaction->getNumberOfEmittedPhotons( 9e-4 ),
                       0u );
  TEST_EQUALITY_CONST( incoherent_adjoint_reaction->getNumberOfEmittedPhotons( 1e-3 ),
                       1u );
  TEST_EQUALITY_CONST( incoherent_adjoint_reaction->getNumberOfEmittedPhotons( 20.0 ),
                       1u );
  TEST_EQUALITY_CONST( incoherent_adjoint_reaction->getNumberOfEmittedPhotons( 20.1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint electrons emitted from the reaction can
// be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( incoherent_adjoint_reaction->getNumberOfEmittedElectrons( 9e-4 ),
                       0u );
  TEST_EQUALITY_CONST( incoherent_adjoint_reaction->getNumberOfEmittedElectrons( 1e-3 ),
                       0u );
  TEST_EQUALITY_CONST( incoherent_adjoint_reaction->getNumberOfEmittedElectrons( 20.0 ),
                       0u );
  TEST_EQUALITY_CONST( incoherent_adjoint_reaction->getNumberOfEmittedElectrons( 20.1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getCrossSection )
{
  double cross_section = 
    incoherent_adjoint_reaction->getCrossSection( 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 3.36049064970995307e-05, 1e-12 );

  cross_section =
    incoherent_adjoint_reaction->getCrossSection( 1.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.720525445117274344, 1e-12 );

  cross_section =
    incoherent_adjoint_reaction->getCrossSection( 20.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getCrossSection_efficient )
{
  double cross_section = 
    incoherent_adjoint_reaction->getCrossSection( 1e-3, 0u );
  
  TEST_FLOATING_EQUALITY( cross_section, 3.36049064970995307e-05, 1e-12 );

  cross_section =
    incoherent_adjoint_reaction->getCrossSection( 20.0, 1166u );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the subshell incoherent adjoint reaction can be simulated
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction, react )
{
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy(
                  Utility::PhysicalConstants::electron_rest_mass_energy/10.0 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  // Set the fake stream
  std::vector<double> fake_stream( 8 );
  fake_stream[0] = 0.15; // branch 1
  fake_stream[1] = 0.4721647344828152; // select x = 0.9
  fake_stream[2] = 0.55; // reject
  fake_stream[3] = 0.15; // branch 1
  fake_stream[4] = 0.22986680137273696; // select x = 0.95
  fake_stream[5] = 0.245; // accept x
  fake_stream[6] = 0.31; // accept mu
  fake_stream[7] = 0.0; // azimuthal angle = 0.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  incoherent_adjoint_reaction->react( adjoint_photon, 
                                      bank, 
                                      shell_of_interaction );

  TEST_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  0.053789358961052636, 
			  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( adjoint_photon.getZDirection(), 0.5, 1e-15 );
  TEST_EQUALITY_CONST( bank.size(), 0 );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::K_SUBSHELL );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Generate two probes
  adjoint_photon.setEnergy( 0.3 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  incoherent_adjoint_reaction->react( adjoint_photon,
                                      bank,
                                      shell_of_interaction );

  TEST_EQUALITY_CONST( bank.size(), 2 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(),
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  // Due to the coarseness of the 2d test grid the weight will not be
  // exactly what it should theoretically be
  TEST_FLOATING_EQUALITY( bank.top().getWeight(),
			  0.471349591314760286,
			  5e-3 );
  
  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getEnergy(), 1.0 );
  // Due to the coarseness of the 2d test grid the weight will not be
  // exactly what it should theoretically be
  TEST_FLOATING_EQUALITY( bank.top().getWeight(),
			  0.237508288495414555,
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
                         data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid( Data::K_SUBSHELL ),
                         data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection( Data::K_SUBSHELL ) );

  Teuchos::ArrayRCP<double> cross_section( incoming_energy_grid.size() );

  for( size_t i = 0; i < incoming_energy_grid.size(); ++i )
  {
    cross_section[i] =
      two_d_cross_section.evaluate( incoming_energy_grid[i], 20.0 );
    std::cout.precision( 18 );
    std::cout << incoming_energy_grid[i] << " " << cross_section[i] << std::endl;
  }
  
  // Create the scattering distribution
  std::shared_ptr<MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>
    scattering_distribution;

  MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistribution(
                                  data_container,
                                  scattering_distribution,
                                  MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL,
                                  20.0,
                                  Data::K_SUBSHELL );

  // Create the reaction
  subshell_incoherent_adjoint_reaction.reset(
   new MonteCarlo::SubshellIncoherentAdjointPhotoatomicReaction<Utility::LinLin,false>(
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

  subshell_incoherent_adjoint_reaction->setCriticalLineEnergies(critical_line_energies);
  
  incoherent_adjoint_reaction = subshell_incoherent_adjoint_reaction;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstSubshellIncoherentAdjointPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
