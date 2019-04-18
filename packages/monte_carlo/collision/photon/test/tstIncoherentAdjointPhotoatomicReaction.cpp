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

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> adjoint_incoherent_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( IncoherentAdjointPhotoatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( adjoint_incoherent_reaction->getReactionType(),
                       MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( IncoherentAdjointPhotoatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( adjoint_incoherent_reaction->getThresholdEnergy(),
                       1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the max energy can be returned
FRENSIE_UNIT_TEST( IncoherentAdjointPhotoatomicReaction, getMaxEnergy )
{
  FRENSIE_CHECK_EQUAL( adjoint_incoherent_reaction->getMaxEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check if an energy falls within the energy grid
FRENSIE_UNIT_TEST( IncoherentAdjointPhotoatomicReaction,
                   isEnergyWithinEnergyGrid )
{
  FRENSIE_CHECK( !adjoint_incoherent_reaction->isEnergyWithinEnergyGrid( 9e-4 ) );
  FRENSIE_CHECK( adjoint_incoherent_reaction->isEnergyWithinEnergyGrid( 1e-3 ) );
  FRENSIE_CHECK( adjoint_incoherent_reaction->isEnergyWithinEnergyGrid( 1.0 ) );
  FRENSIE_CHECK( adjoint_incoherent_reaction->isEnergyWithinEnergyGrid( 20.0 ) );
  FRENSIE_CHECK( !adjoint_incoherent_reaction->isEnergyWithinEnergyGrid( 20.1 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint photons emitted from the reaction can be
// returned
FRENSIE_UNIT_TEST( IncoherentAdjointPhotoatomicReaction,
                   getNumberOfEmittedAdjointPhotons )
{
  FRENSIE_CHECK_EQUAL( adjoint_incoherent_reaction->getNumberOfEmittedAdjointPhotons( 9e-4 ),
                       0u );
  FRENSIE_CHECK_EQUAL( adjoint_incoherent_reaction->getNumberOfEmittedAdjointPhotons( 1e-3 ),
                       1u );
  FRENSIE_CHECK_EQUAL( adjoint_incoherent_reaction->getNumberOfEmittedAdjointPhotons( 20.0 ),
                       1u );
  FRENSIE_CHECK_EQUAL( adjoint_incoherent_reaction->getNumberOfEmittedAdjointPhotons( 20.1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint electrons emitted from the reaction can be
// returned
FRENSIE_UNIT_TEST( IncoherentAdjointPhotoatomicReaction,
                   getNumberOfEmittedAdjointElectrons )
{
  FRENSIE_CHECK_EQUAL( adjoint_incoherent_reaction->getNumberOfEmittedAdjointElectrons( 9e-4 ),
                       0u );
  FRENSIE_CHECK_EQUAL( adjoint_incoherent_reaction->getNumberOfEmittedAdjointElectrons( 1e-3 ),
                       0u );
  FRENSIE_CHECK_EQUAL( adjoint_incoherent_reaction->getNumberOfEmittedAdjointElectrons( 20.0 ),
                       0u );
  FRENSIE_CHECK_EQUAL( adjoint_incoherent_reaction->getNumberOfEmittedAdjointElectrons( 20.1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint positrons emitted from the reaction can be
// returned
FRENSIE_UNIT_TEST( IncoherentAdjointPhotoatomicReaction,
                   getNumberOfEmittedAdjointPositrons )
{
  FRENSIE_CHECK_EQUAL( adjoint_incoherent_reaction->getNumberOfEmittedAdjointPositrons( 9e-4 ),
                       0u );
  FRENSIE_CHECK_EQUAL( adjoint_incoherent_reaction->getNumberOfEmittedAdjointPositrons( 1e-3 ),
                       0u );
  FRENSIE_CHECK_EQUAL( adjoint_incoherent_reaction->getNumberOfEmittedAdjointPositrons( 20.0 ),
                       0u );
  FRENSIE_CHECK_EQUAL( adjoint_incoherent_reaction->getNumberOfEmittedAdjointPositrons( 20.1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( IncoherentAdjointPhotoatomicReaction, getCrossSection )
{
  double cross_section =
    adjoint_incoherent_reaction->getCrossSection( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.620920802623559753, 1e-12 );

  cross_section =
    adjoint_incoherent_reaction->getCrossSection( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.50415974966055277, 1e-12 );

  cross_section =
    adjoint_incoherent_reaction->getCrossSection( 20.0 );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned (efficiently)
FRENSIE_UNIT_TEST( IncoherentAdjointPhotoatomicReaction,
                   getCrossSection_efficient )
{
  double cross_section =
    adjoint_incoherent_reaction->getCrossSection( 1e-3, 0u );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.620920802623559753, 1e-12 );

  cross_section =
    adjoint_incoherent_reaction->getCrossSection( 20.0, 1261 );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the incoherent adjoint reaction can be simulated
FRENSIE_UNIT_TEST( IncoherentAdjointPhotoatomicReaction, react )
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

  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  0.05677765668111111,
			  1e-15 );
  FRENSIE_CHECK_SMALL( adjoint_photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Generate two probes
  adjoint_photon.setEnergy( 0.3 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  adjoint_incoherent_reaction->react( adjoint_photon,
				      bank,
				      shell_of_interaction );

  FRENSIE_CHECK_EQUAL( bank.size(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(),
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  // Due to the coarseness of the 2d test grid the weight will not be
  // exactly what it should theoretically be
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(),
			  0.401104057813784276,
			  5e-3 );

  bank.pop();

  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 1.0 );
  // Due to the coarseness of the 2d test grid the weight will not be
  // exactly what it should theoretically be
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(),
			  0.203384875392762621,
			  5e-3 );
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
  // Create the native data file container
  Data::AdjointElectronPhotonRelaxationDataContainer
    data_container( test_native_file_name );

  // Get the incoming energy grid
  std::shared_ptr<std::vector<double> > incoming_energy_grid(
      new std::vector<double>( data_container.getAdjointPhotonEnergyGrid() ) );

  // Evaluate the cross section at the energy of interest
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> two_d_cross_section;
  {
  two_d_cross_section.reset(
    new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LinLinLin> >(
        data_container.getAdjointPhotonEnergyGrid(),
        data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid(),
        data_container.getAdjointWallerHartreeIncoherentCrossSection() ) );
  }

  std::shared_ptr<std::vector<double> > cross_section(
                     new std::vector<double>( incoming_energy_grid->size() ) );

  for( size_t i = 0; i < incoming_energy_grid->size(); ++i )
  {
    (*cross_section)[i] =
      two_d_cross_section->evaluate( (*incoming_energy_grid)[i], 20.0 );
  }

  // Create the scattering distribution
  std::shared_ptr<MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
    scattering_distribution;

  MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution(
                    data_container,
                    scattering_distribution,
                    MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL,
                    MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING,
                    20.0 );

  // Create the reaction
  std::shared_ptr<MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > complete_reaction(
   new MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false>(
                                                   incoming_energy_grid,
                                                   cross_section,
                                                   0u,
                                                   scattering_distribution ) );

  // Set the critical line energies
  std::shared_ptr<std::vector<double> >
    critical_line_energies( new std::vector<double>(3) );

  (*critical_line_energies)[0] = 0.08;
  (*critical_line_energies)[1] =
    Utility::PhysicalConstants::electron_rest_mass_energy;
  (*critical_line_energies)[2] = 1.0;

  complete_reaction->setCriticalLineEnergies(critical_line_energies);

  adjoint_incoherent_reaction = complete_reaction;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstIncoherentAdjointPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
