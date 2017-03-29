//---------------------------------------------------------------------------//
//!
//! \file   tstAnalogElasticAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Analog Elastic adjoint electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_AnalogElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::AnalogElasticAdjointElectroatomicReaction<Utility::LinLin> > analog_elastic_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( AnalogElasticAdjointElectroatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( analog_elastic_reaction->getReactionType(),
		       MonteCarlo::ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( AnalogElasticAdjointElectroatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( analog_elastic_reaction->getThresholdEnergy(),
                       1.0e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( AnalogElasticAdjointElectroatomicReaction, getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( analog_elastic_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( analog_elastic_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( AnalogElasticAdjointElectroatomicReaction, getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( analog_elastic_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( analog_elastic_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the analog cross section can be returned
TEUCHOS_UNIT_TEST( AnalogElasticAdjointElectroatomicReaction,
                   getCrossSection )
{

  double cross_section =
    analog_elastic_reaction->getCrossSection( 1.0E-05 );

  TEST_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  cross_section =
    analog_elastic_reaction->getCrossSection( 1.0E-03 );

  TEST_FLOATING_EQUALITY( cross_section, 2.80490481543817E+06, 1e-12 );

  cross_section =
    analog_elastic_reaction->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 1.3022122514987E+04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
TEUCHOS_UNIT_TEST( AnalogElasticAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  analog_elastic_reaction->react( electron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( electron.getEnergy(), 20.0 );
  TEST_ASSERT( electron.getZDirection() < 2.0 );
  TEST_ASSERT( electron.getZDirection() > 0.0 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
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
  // Create reaction
  {
    // Get native data container
    Data::AdjointElectronPhotonRelaxationDataContainer data_container =
        Data::AdjointElectronPhotonRelaxationDataContainer( test_native_file_name );

    // Get the energy grid
    std::vector<double> angular_energy_grid =
        data_container.getAdjointElasticAngularEnergyGrid();

    // Get size of paramters
    int size = angular_energy_grid.size();

    // Create the scattering function
    Utility::FullyTabularTwoDDistribution::DistributionType function_data( size );

    for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
    {
    function_data[n].first = angular_energy_grid[n];

    // Get the cutoff elastic scattering angles at the energy
    Teuchos::Array<double> angles(
        data_container.getAdjointCutoffElasticAngles( angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    Teuchos::Array<double> pdf(
        data_container.getAdjointCutoffElasticPDF( angular_energy_grid[n] ) );

    function_data[n].second.reset(
      new const Utility::TabularDistribution<Utility::LinLin>( angles, pdf ) );
    }

    double atomic_number = data_container.getAtomicNumber();

    // Create the scattering function
    std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function(
        new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>(
            function_data,
            1e-6 ) );

    // Create cutoff distribution
    std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution>
        analog_elastic_distribution(
            new MonteCarlo::AnalogElasticElectronScatteringDistribution(
                scattering_function,
                atomic_number ) );

    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.assign(
        data_container.getAdjointElectronEnergyGrid().begin(),
        data_container.getAdjointElectronEnergyGrid().end() );

    Teuchos::ArrayRCP<double> cutoff_cross_section;
    cutoff_cross_section.assign(
        data_container.getAdjointCutoffElasticCrossSection().begin(),
        data_container.getAdjointCutoffElasticCrossSection().end() );

    // Cutoff elastic cross section threshold energy bin index
    unsigned cutoff_threshold_energy_index =
      data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

    Teuchos::ArrayRCP<double> sr_cross_section;
    sr_cross_section.assign(
        data_container.getAdjointScreenedRutherfordElasticCrossSection().begin(),
        data_container.getAdjointScreenedRutherfordElasticCrossSection().end() );

    // Screened Rutherford elastic cross section threshold energy bin index
    unsigned sr_threshold_energy_index =
      data_container.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

    // Calculate the analog cross section
    unsigned analog_threshold_energy_index =
      std::min( sr_threshold_energy_index, cutoff_threshold_energy_index );

    unsigned sr_threshold_diff =
      sr_threshold_energy_index - analog_threshold_energy_index;
    unsigned cutoff_threshold_diff =
      cutoff_threshold_energy_index - analog_threshold_energy_index;

    Teuchos::Array<double> combined_cross_section(
                             energy_grid.size() - analog_threshold_energy_index );

    for (unsigned i = 0; i < combined_cross_section.size(); ++i )
    {
      double energy = energy_grid[i + analog_threshold_energy_index];

      if ( i < sr_threshold_diff )
      {
        combined_cross_section[i] = cutoff_cross_section[i];
      }
      else if ( i < cutoff_threshold_diff )
      {
        combined_cross_section[i] = sr_cross_section[i];
      }
      else
      {
        combined_cross_section[i] =
          cutoff_cross_section[i-cutoff_threshold_diff] +
          sr_cross_section[i-sr_threshold_diff];
      }
    }

    Teuchos::ArrayRCP<double> analog_cross_section;
    analog_cross_section.assign( combined_cross_section.begin(),
                                 combined_cross_section.end() );

    // Create the reaction
    analog_elastic_reaction.reset(
      new MonteCarlo::AnalogElasticAdjointElectroatomicReaction<Utility::LinLin>(
                energy_grid,
                analog_cross_section,
                analog_threshold_energy_index,
                analog_elastic_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END(); 

//---------------------------------------------------------------------------//
// end tstAnalogElasticAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
