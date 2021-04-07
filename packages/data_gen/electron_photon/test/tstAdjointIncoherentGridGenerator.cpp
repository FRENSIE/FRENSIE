//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointIncoherentGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent grid generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "DataGen_AdjointIncoherentGridGenerator.hpp"
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_WHIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_KleinNishinaAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_StandardOccupationNumber.hpp"
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "Data_SubshellType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_InverseMeCMomentumUnit.hpp"
#include "Utility_InverseCentimeterUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
  klein_nishina_adjoint_cs;

std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
  h_incoherent_adjoint_cs;

std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
  pb_incoherent_adjoint_cs;

std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>
  pb_k_subshell_incoherent_adjoint_cs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the max energy can be returned
FRENSIE_UNIT_TEST( AdjointIncoherentGridGenerator, getMaxEnergy )
{
  {
    DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin> grid_generator;

    FRENSIE_CHECK_EQUAL( grid_generator.getMaxEnergy(), 20.0 );
  }

  {
    DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin>
      grid_generator( 21.0 );

    FRENSIE_CHECK_EQUAL( grid_generator.getMaxEnergy(), 21.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the max energy nudge value can be set
FRENSIE_UNIT_TEST( AdjointIncoherentGridGenerator, setMaxEnergyNudgeValue )
{
  {
    DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin> grid_generator;

    FRENSIE_CHECK_EQUAL( grid_generator.getNudgedMaxEnergy(), 20.2 );
  }

  DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( 21.0, 0.3 );

  FRENSIE_CHECK_EQUAL( grid_generator.getNudgedMaxEnergy(), 21.3 );

  grid_generator.setMaxEnergyNudgeValue( 0.5 );

  FRENSIE_CHECK_EQUAL( grid_generator.getNudgedMaxEnergy(), 21.5 );
}

//---------------------------------------------------------------------------//
// Check that the energy to max energy nudge value can be set
FRENSIE_UNIT_TEST( AdjointIncoherentGridGenerator,
                   setEnergyToMaxEnergyNudgeValue )
{
  {
    DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin> grid_generator;

    FRENSIE_CHECK_EQUAL( grid_generator.getNudgedEnergy( 1.0 ), 1.000001 );
  }

  DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( 21.0, 0.2, 1e-3 );

  FRENSIE_CHECK_EQUAL( grid_generator.getNudgedEnergy( 1.0 ), 1.001 );

  grid_generator.setEnergyToMaxEnergyNudgeValue( 1e-4 );

  FRENSIE_CHECK_EQUAL( grid_generator.getNudgedEnergy( 1.0 ), 1.0001 );
}

//---------------------------------------------------------------------------//
// Check that max energy grid can be generated for a free electron
FRENSIE_UNIT_TEST( AdjointIncoherentGridGenerator,
                   generateAndEvaluateSecondaryInPlace_free )
{
  DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( 20.0, 0.2, 0.0 );
  grid_generator.throwExceptionOnDirtyConvergence();

  std::vector<double> max_energy_grid, cross_section;

  // Bind the distribution to a cross section evaluator
  std::function<double(double,double)> cs_evaluator =
    grid_generator.createCrossSectionEvaluator(
                                             klein_nishina_adjoint_cs, 0.001 );

  // Generate a max energy grid at E=0.1 MeV
  double max_energy_of_max_cs =
    DataGen::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy( 0.1 );

  grid_generator.generateAndEvaluateSecondaryInPlace( max_energy_grid,
                                                      cross_section,
                                                      0.1,
                                                      cs_evaluator );

  // Check the generated max energy grid
  FRENSIE_CHECK_EQUAL( max_energy_grid.size(), 43 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.front(), 0.1, 1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.back(), 20.2, 1e-6 );
  FRENSIE_CHECK_EQUAL( max_energy_grid[max_energy_grid.size()-2],
                       max_energy_of_max_cs );

  // Check the evaluated cross section
  FRENSIE_CHECK_EQUAL( cross_section.size(), 43 );
  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(),
                                   0.701697560627866257,
                                   1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section[cross_section.size()-2],
                                   0.701697560627866257,
                                   1e-6 );

  max_energy_grid.clear();
  cross_section.clear();

  // Generate a max energy grid at E=1.0 MeV
  grid_generator.generateAndEvaluateSecondaryInPlace( max_energy_grid,
                                                      cross_section,
                                                      1.0,
                                                      cs_evaluator );
  // Check the generated max energy grid
  FRENSIE_CHECK_EQUAL( max_energy_grid.size(), 64 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.front(), 1.0, 1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.back(), 20.2, 1e-6 );

  // Check the evaluated cross section
  FRENSIE_CHECK_EQUAL( cross_section.size(), 64 );
  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(),
                                   0.397416434130255625,
                                   1e-6 );
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
FRENSIE_UNIT_TEST( AdjointIncoherentGridGenerator,
                   generateAndEvaluateInPlace_free )
{
  DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( 20.0, 0.2, 0.0, 0.01, 1e-20 );
  grid_generator.throwExceptionOnDirtyConvergence();
  grid_generator.setDistanceTolerance( 1e-20 );

  std::vector<double> energy_grid( 2 );
  energy_grid[0] = 0.001;
  energy_grid[1] = 20.0;

  std::vector<std::vector<double> > max_energy_grid, cross_section;

  // Bind the distribution to a cross section evaluator
  std::function<double(double,double)> cs_evaluator =
    grid_generator.createCrossSectionEvaluator(
                                             klein_nishina_adjoint_cs, 0.001 );

  // Generate the 2D grid
  grid_generator.generateAndEvaluateInPlace( energy_grid,
                                             max_energy_grid,
                                             cross_section,
                                             cs_evaluator );

  // Check the energy grid
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 584 );
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 0.001 );
  FRENSIE_CHECK(
           std::binary_search( energy_grid.begin(),
                               energy_grid.end(),
                               DataGen::getEnergyOfMaxCrossSection( 20.2 ) ) );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
FRENSIE_UNIT_TEST( AdjointIncoherentGridGenerator,
                   generateAndEvaluateInPlace_h )
{
  DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( 20.0, 0.2, 1e-8, 0.05, 1e-20 );
  grid_generator.throwExceptionOnDirtyConvergence();
  grid_generator.setDistanceTolerance( 1e-20 );

  std::vector<double> energy_grid( 3 );
  energy_grid[0] = 0.001;
  energy_grid[1] = DataGen::getEnergyOfMaxCrossSection( 20.2 );
  energy_grid[2] = 20.0;

  std::vector<std::vector<double> > max_energy_grid, cross_section;

  // Bind the distribution to a cross section evaluator
  std::function<double(double,double)> cs_evaluator =
    grid_generator.createCrossSectionEvaluator(h_incoherent_adjoint_cs, 0.001);

  // Generate the 2D grid
  grid_generator.generateAndEvaluateInPlace( energy_grid,
                                             max_energy_grid,
                                             cross_section,
                                             cs_evaluator );

  // Check the energy grid
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 159 );
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 0.001 );
  FRENSIE_CHECK_EQUAL(
                std::count( energy_grid.begin(),
                            energy_grid.end(),
                            DataGen::getEnergyOfMaxCrossSection( 20.2 ) ), 1 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
FRENSIE_UNIT_TEST( AdjointIncoherentGridGenerator,
                   generateAndEvaluateInPlace_pb )
{
//  NOTE: The orginal test took too long and these parameters were changed
//  DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin>
//    grid_generator( 20.0, 0.2, 1e-8, 0.05, 1e-20 );
//  grid_generator.setConvergenceTolerance( 1e-2 );

  DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( 20.0, 0.2, 1e-8, 0.01, 1e-20 );
  grid_generator.throwExceptionOnDirtyConvergence();

  FRENSIE_CHECK_EQUAL( grid_generator.getConvergenceTolerance(), 0.01 );

  grid_generator.setConvergenceTolerance( 0.05 );
  FRENSIE_CHECK_EQUAL( grid_generator.getConvergenceTolerance(), 0.05 );

  std::vector<double> energy_grid( 2 );
  energy_grid[0] = 0.001;
  energy_grid[1] = 20.0;

  std::vector<std::vector<double> > max_energy_grid, cross_section;

  // Bind the distribution to a cross section evaluator
//  std::function<double(double,double)> cs_evaluator =
//    grid_generator.createCrossSectionEvaluator(
//                                             pb_incoherent_adjoint_cs, 0.01 );
  std::function<double(double,double)> cs_evaluator =
    grid_generator.createCrossSectionEvaluator(
                                             pb_incoherent_adjoint_cs, 0.01 );

  // Generate the 2D grid
  grid_generator.generateAndEvaluateInPlace( energy_grid,
                                             max_energy_grid,
                                             cross_section,
                                             cs_evaluator );

  // Check the energy grid
//  FRENSIE_CHECK_EQUAL( energy_grid.size(), 1009 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 169 );
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 0.001 );
  FRENSIE_CHECK(
           std::binary_search( energy_grid.begin(),
                               energy_grid.end(),
                               DataGen::getEnergyOfMaxCrossSection( 20.2 ) ) );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
FRENSIE_UNIT_TEST( AdjointIncoherentGridGenerator,
                   generateAndEvaluateInPlace_pb_k_subshell )
{
  DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin> grid_generator(
          20.0,
          pb_k_subshell_incoherent_adjoint_cs->getSubshellBindingEnergy()*2,
          pb_k_subshell_incoherent_adjoint_cs->getSubshellBindingEnergy()+1e-8,
          0.05,
          1e-20 );
  //grid_generator.throwExceptionOnDirtyConvergence();

  std::vector<double> energy_grid( 2 );
  energy_grid[0] = 0.001;
  energy_grid[1] = 20.0;

  std::vector<std::vector<double> > max_energy_grid, cross_section;

  // Bind the distribution to a cross section evaluator
  std::function<double(double,double)> cs_evaluator =
    grid_generator.createCrossSectionEvaluator(
                                   pb_k_subshell_incoherent_adjoint_cs, 0.01 );

  // Generate the 2D grid
  grid_generator.generateAndEvaluateInPlace( energy_grid,
                                             max_energy_grid,
                                             cross_section,
                                             cs_evaluator );

  // Check the energy grid
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 146 );
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 0.001 );

  const double nudged_max_energy = 20.0 +
    pb_k_subshell_incoherent_adjoint_cs->getSubshellBindingEnergy()*2;

  FRENSIE_CHECK( std::binary_search(
                  energy_grid.begin(),
                  energy_grid.end(),
                  DataGen::getEnergyOfMaxCrossSection( nudged_max_energy ) ) );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 20.0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_pb_file_name, test_native_h_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_pb_file",
                                        test_native_pb_file_name, "",
                                        "Test Native Pb file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_h_file",
                                        test_native_h_file_name, "",
                                        "Test Native H file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the Klein-Nishina distribution
  klein_nishina_adjoint_cs.reset(
     new MonteCarlo::KleinNishinaAdjointPhotonScatteringDistribution( 20.0 ) );

  // Create the H distribution
  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer
      data_container( test_native_h_file_name );

    // Extract the scattering function
    const std::vector<double>& momentum_grid =
      data_container.getWallerHartreeScatteringFunctionMomentumGrid();

    const std::vector<double>& scattering_function_values =
      data_container.getWallerHartreeScatteringFunction();

    std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::InverseCentimeter,void> > raw_scattering_function(
        new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseCentimeter,void>(
                                                momentum_grid,
                                                scattering_function_values ) );

    std::shared_ptr<MonteCarlo::ScatteringFunction> scattering_function(
           new MonteCarlo::StandardScatteringFunction<Utility::Units::InverseCentimeter>(
                                                   raw_scattering_function ) );

    h_incoherent_adjoint_cs.reset(
             new MonteCarlo::WHIncoherentAdjointPhotonScatteringDistribution(
                                                 20.0, scattering_function ) );
  }

  // Create the Pb distributions
  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer
      data_container( test_native_pb_file_name );

    // Extract the scattering function
    const std::vector<double>& momentum_grid =
      data_container.getWallerHartreeScatteringFunctionMomentumGrid();

    const std::vector<double>& scattering_function_values =
      data_container.getWallerHartreeScatteringFunction();

    std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::InverseCentimeter,void> > raw_scattering_function(
        new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseCentimeter,void>(
                                                momentum_grid,
                                                scattering_function_values ) );

    std::shared_ptr<MonteCarlo::ScatteringFunction> scattering_function(
           new MonteCarlo::StandardScatteringFunction<Utility::Units::InverseCentimeter>(
                                                   raw_scattering_function ) );

    pb_incoherent_adjoint_cs.reset(
             new MonteCarlo::WHIncoherentAdjointPhotonScatteringDistribution(
                                                 20.0, scattering_function ) );

    // Extract the K subshell occupation number
    const std::vector<double>& occupation_number_grid =
      data_container.getOccupationNumberMomentumGrid( 1 );

    const std::vector<double>& occupation_number_values =
      data_container.getOccupationNumber( 1 );

    std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::MeCMomentum,void> > raw_occupation_number(
              new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,void>(
                                                  occupation_number_grid,
                                                  occupation_number_values ) );

    std::shared_ptr<MonteCarlo::OccupationNumber> occupation_number( new MonteCarlo::StandardOccupationNumber<Utility::Units::MeCMomentum>( raw_occupation_number ) );

    pb_k_subshell_incoherent_adjoint_cs.reset(
         new MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution(
                                20.0,
                                Data::convertENDFDesignatorToSubshellEnum( 1 ),
                                data_container.getSubshellOccupancy( 1 ),
                                data_container.getSubshellBindingEnergy( 1 ),
                                occupation_number ) );
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointIncoherentGridGenerator.cpp
//---------------------------------------------------------------------------//
