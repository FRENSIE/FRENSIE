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

// FRENSIE Includes
#include "MonteCarlo_SubshellIncoherentAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> incoherent_adjoint_reaction;

std::shared_ptr<MonteCarlo::SubshellIncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > subshell_incoherent_adjoint_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction, getSubshell )
{
  FRENSIE_CHECK_EQUAL( subshell_incoherent_adjoint_reaction->getSubshell(),
                       Data::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energy can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getSubshellBindingEnergy )
{
  FRENSIE_CHECK_EQUAL( subshell_incoherent_adjoint_reaction->getSubshellBindingEnergy(),
                       1.8285e-3 );
}

//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getReactionType )
{
  FRENSIE_CHECK_EQUAL( incoherent_adjoint_reaction->getReactionType(),
                       MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getThresholdEnergy )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( incoherent_adjoint_reaction->getThresholdEnergy(),
                                   0.0018155071938000074,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the max energy can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getMaxEnergy )
{
  FRENSIE_CHECK_EQUAL( incoherent_adjoint_reaction->getMaxEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check if an energy falls within the energy grid
FRENSIE_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   isEnergyWithinEnergyGrid )
{
  FRENSIE_CHECK( !incoherent_adjoint_reaction->isEnergyWithinEnergyGrid( 9e-4 ) );
  FRENSIE_CHECK( incoherent_adjoint_reaction->isEnergyWithinEnergyGrid( 1e-3 ) );
  FRENSIE_CHECK( incoherent_adjoint_reaction->isEnergyWithinEnergyGrid( 1.0 ) );
  FRENSIE_CHECK( incoherent_adjoint_reaction->isEnergyWithinEnergyGrid( 20.0 ) );
  FRENSIE_CHECK( !incoherent_adjoint_reaction->isEnergyWithinEnergyGrid( 20.1 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint photons emitted from the reaction can
// be returned
FRENSIE_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getNumberOfEmittedAdjointPhotons )
{
  FRENSIE_CHECK_EQUAL( incoherent_adjoint_reaction->getNumberOfEmittedAdjointPhotons( 9e-4 ),
                       0u );
  FRENSIE_CHECK_EQUAL( incoherent_adjoint_reaction->getNumberOfEmittedAdjointPhotons( 0.00181551 ),
                       1u );
  FRENSIE_CHECK_EQUAL( incoherent_adjoint_reaction->getNumberOfEmittedAdjointPhotons( 20.0 ),
                       1u );
  FRENSIE_CHECK_EQUAL( incoherent_adjoint_reaction->getNumberOfEmittedAdjointPhotons( 20.1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint electrons emitted from the reaction can
// be returned
FRENSIE_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getNumberOfEmittedAdjointElectrons )
{
  FRENSIE_CHECK_EQUAL( incoherent_adjoint_reaction->getNumberOfEmittedAdjointElectrons( 9e-4 ),
                       0u );
  FRENSIE_CHECK_EQUAL( incoherent_adjoint_reaction->getNumberOfEmittedAdjointElectrons( 1e-3 ),
                       0u );
  FRENSIE_CHECK_EQUAL( incoherent_adjoint_reaction->getNumberOfEmittedAdjointElectrons( 20.0 ),
                       0u );
  FRENSIE_CHECK_EQUAL( incoherent_adjoint_reaction->getNumberOfEmittedAdjointElectrons( 20.1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint positrons emitted from the reaction can
// be returned
FRENSIE_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getNumberOfEmittedAdjointPositrons )
{
  FRENSIE_CHECK_EQUAL( incoherent_adjoint_reaction->getNumberOfEmittedAdjointPositrons( 9e-4 ),
                       0u );
  FRENSIE_CHECK_EQUAL( incoherent_adjoint_reaction->getNumberOfEmittedAdjointPositrons( 1e-3 ),
                       0u );
  FRENSIE_CHECK_EQUAL( incoherent_adjoint_reaction->getNumberOfEmittedAdjointPositrons( 20.0 ),
                       0u );
  FRENSIE_CHECK_EQUAL( incoherent_adjoint_reaction->getNumberOfEmittedAdjointPositrons( 20.1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getCrossSection )
{
  double cross_section = incoherent_adjoint_reaction->getCrossSection( 1e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = incoherent_adjoint_reaction->getCrossSection( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.7848264280276896487, 1e-12 );

  // The cross section must go to zero at E_max - E_b
  cross_section =
    incoherent_adjoint_reaction->getCrossSection( 20.0 - 1.8285e-3 );
  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section = incoherent_adjoint_reaction->getCrossSection( 20.0 );
  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction,
                   getCrossSection_efficient )
{
  double cross_section = 
    incoherent_adjoint_reaction->getCrossSection( 1e-3, 0u );
  
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    incoherent_adjoint_reaction->getCrossSection( 20.0 - 1.8285e-3, 1261 );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section =
    incoherent_adjoint_reaction->getCrossSection( 20.0, 1261u );
  
  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the subshell incoherent adjoint reaction can be simulated
FRENSIE_UNIT_TEST( SubshellIncoherentAdjointPhotoatomicReaction, react )
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

  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
                          0.053789358961052636, 
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getZDirection(), 0.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::K_SUBSHELL );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Generate two probes
  adjoint_photon.setEnergy( 0.3 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  incoherent_adjoint_reaction->react( adjoint_photon,
                                      bank,
                                      shell_of_interaction );

  FRENSIE_CHECK_EQUAL( bank.size(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(),
                                   0.4039891155897157304,
                                   1e-15 );
  
  bank.pop();

  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(),
                                   0.2043705800099769043,
                                   1e-15 );
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

  unsigned threshold_index = data_container.getAdjointImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( Data::K_SUBSHELL );

  // Evaluate the cross section at the energy of interest
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> two_d_cross_section;
  
  {
    std::vector<double> cut_energy_grid( data_container.getAdjointPhotonEnergyGrid().begin()+threshold_index,
                                         data_container.getAdjointPhotonEnergyGrid().end() );
    
    two_d_cross_section.reset(
     new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LinLinLin> >(
      cut_energy_grid,
      data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid( Data::K_SUBSHELL ),
      data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection( Data::K_SUBSHELL ) ) );
  }

  std::shared_ptr<std::vector<double> > cross_section(
   new std::vector<double>( incoming_energy_grid->size() - threshold_index ) );
  
  for( size_t i = 0; i < cross_section->size(); ++i )
  {
    (*cross_section)[i] =
      two_d_cross_section->evaluate( (*incoming_energy_grid)[i+threshold_index], 20.0 );
  }

  // Create the scattering distribution
  std::shared_ptr<MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>
    scattering_distribution;

  MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistribution(
                    data_container,
                    scattering_distribution,
                    MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL,
                    MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING,
                    20.0,
                    Data::K_SUBSHELL );

  // Create the reaction
  subshell_incoherent_adjoint_reaction.reset(
   new MonteCarlo::SubshellIncoherentAdjointPhotoatomicReaction<Utility::LinLin,false>(
                                                   incoming_energy_grid,
                                                   cross_section,
                                                   threshold_index,
                                                   scattering_distribution ) );

  // Set the critical line energies
  std::shared_ptr<std::vector<double> >
    critical_line_energies( new std::vector<double>(3) );

  (*critical_line_energies)[0] = 0.08;
  (*critical_line_energies)[1] =
    Utility::PhysicalConstants::electron_rest_mass_energy;
  (*critical_line_energies)[2] = 1.0;

  subshell_incoherent_adjoint_reaction->setCriticalLineEnergies(critical_line_energies);
  
  incoherent_adjoint_reaction = subshell_incoherent_adjoint_reaction;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstSubshellIncoherentAdjointPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
