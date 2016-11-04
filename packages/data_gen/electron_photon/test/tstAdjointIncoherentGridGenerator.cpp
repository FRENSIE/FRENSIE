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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

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
#include "Utility_UnitTestHarnessExtensions.hpp"

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
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator, getMaxEnergy )
{
  {
    DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin> grid_generator;

    TEST_EQUALITY_CONST( grid_generator.getMaxEnergy(), 20.0 );
  }

  {
    DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin>
      grid_generator( 21.0 );

    TEST_EQUALITY_CONST( grid_generator.getMaxEnergy(), 21.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the max energy nudge value can be set
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator, setMaxEnergyNudgeValue )
{
  {
    DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin> grid_generator;

    TEST_EQUALITY_CONST( grid_generator.getNudgedMaxEnergy(), 20.2 );
  }

  DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( 21.0, 0.3 );

  TEST_EQUALITY_CONST( grid_generator.getNudgedMaxEnergy(), 21.3 );

  grid_generator.setMaxEnergyNudgeValue( 0.5 );

  TEST_EQUALITY_CONST( grid_generator.getNudgedMaxEnergy(), 21.5 );
}

//---------------------------------------------------------------------------//
// Check that the energy to max energy nudge value can be set
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator,
                   setEnergyToMaxEnergyNudgeValue )
{
  {
    DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin> grid_generator;

    TEST_EQUALITY_CONST( grid_generator.getNudgedEnergy( 1.0 ), 1.000001 );
  }

  DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( 21.0, 0.2, 1e-3 );

  TEST_EQUALITY_CONST( grid_generator.getNudgedEnergy( 1.0 ), 1.001 );

  grid_generator.setEnergyToMaxEnergyNudgeValue( 1e-4 );

  TEST_EQUALITY_CONST( grid_generator.getNudgedEnergy( 1.0 ), 1.0001 );
}

//---------------------------------------------------------------------------//
// Check that max energy grid can be generated for a free electron
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator,
                   generateAndEvaluateSecondaryInPlace_free )
{
  DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( 20.0, 0.2, 0.0 );
  grid_generator.throwExceptionOnDirtyConvergence();
  
  Teuchos::Array<double> max_energy_grid, cross_section;

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
  TEST_EQUALITY_CONST( max_energy_grid.size(), 43 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.front(), 0.1, 1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.back(), 20.2, 1e-6 );
  TEST_EQUALITY_CONST( max_energy_grid[max_energy_grid.size()-2],
                       max_energy_of_max_cs );

  // Check the evaluated cross section
  TEST_EQUALITY_CONST( cross_section.size(), 43 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.front(),
                                  2.54954928358413249e-08,
				  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.back(), 
				  0.701697560627866257,
				  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section[cross_section.size()-2],
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
  TEST_EQUALITY_CONST( max_energy_grid.size(), 64 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.front(), 1.0, 1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.back(), 20.2, 1e-6 );

  // Check the evaluated cross section
  TEST_EQUALITY_CONST( cross_section.size(), 64 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.front(),
                                  2.54954930897518544e-09,
				  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.back(),
				  0.397416434130255625,
				  1e-6 );
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator,
                   generateAndEvaluateInPlace_free )
{
  DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( 20.0, 0.2, 0.0, 0.01, 1e-20 );
  grid_generator.throwExceptionOnDirtyConvergence();
  grid_generator.setDistanceTolerance( 1e-20 );

  Teuchos::Array<double> energy_grid( 2 );
  energy_grid[0] = 0.001;
  energy_grid[1] = 20.0;
  
  Teuchos::Array<Teuchos::Array<double> > max_energy_grid, cross_section;

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
  TEST_EQUALITY_CONST( energy_grid.size(), 584 );
  TEST_EQUALITY_CONST( energy_grid.front(), 0.001 );
  TEST_ASSERT(
           std::binary_search( energy_grid.begin(),
                               energy_grid.end(),
                               DataGen::getEnergyOfMaxCrossSection( 20.2 ) ) );
  TEST_EQUALITY_CONST( energy_grid.back(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator,
                   generateAndEvaluateInPlace_h )
{
  DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( 20.0, 0.2, 1e-8, 0.05, 1e-20 );
  grid_generator.throwExceptionOnDirtyConvergence();
  grid_generator.setDistanceTolerance( 1e-20 );

  Teuchos::Array<double> energy_grid( 3 );
  energy_grid[0] = 0.001;
  energy_grid[1] = DataGen::getEnergyOfMaxCrossSection( 20.2 );
  energy_grid[2] = 20.0;
  
  Teuchos::Array<Teuchos::Array<double> > max_energy_grid, cross_section;

  // Bind the distribution to a cross section evaluator
  std::function<double(double,double)> cs_evaluator =
    grid_generator.createCrossSectionEvaluator(h_incoherent_adjoint_cs, 0.001);

  // Generate the 2D grid
  grid_generator.generateAndEvaluateInPlace( energy_grid,
                                             max_energy_grid,
                                             cross_section,
                                             cs_evaluator );

  // Check the energy grid
  TEST_EQUALITY_CONST( energy_grid.size(), 159 );
  TEST_EQUALITY_CONST( energy_grid.front(), 0.001 );
  TEST_EQUALITY_CONST(
                std::count( energy_grid.begin(),
                            energy_grid.end(),
                            DataGen::getEnergyOfMaxCrossSection( 20.2 ) ), 1 );
  TEST_EQUALITY_CONST( energy_grid.back(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator,
                   generateAndEvaluateInPlace_pb )
{
  DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( 20.0, 0.2, 1e-8, 0.05, 1e-20 );
  grid_generator.throwExceptionOnDirtyConvergence();
  grid_generator.setConvergenceTolerance( 1e-2 );

  Teuchos::Array<double> energy_grid( 2 );
  energy_grid[0] = 0.001;
  energy_grid[1] = 20.0;
  
  Teuchos::Array<Teuchos::Array<double> > max_energy_grid, cross_section;

  // Bind the distribution to a cross section evaluator
  std::function<double(double,double)> cs_evaluator =
    grid_generator.createCrossSectionEvaluator(
                                             pb_incoherent_adjoint_cs, 0.01 );

  // Generate the 2D grid
  grid_generator.generateAndEvaluateInPlace( energy_grid,
                                             max_energy_grid,
                                             cross_section,
                                             cs_evaluator );

  // Check the energy grid
  TEST_EQUALITY_CONST( energy_grid.size(), 1009 );
  TEST_EQUALITY_CONST( energy_grid.front(), 0.001 );
  TEST_ASSERT(
           std::binary_search( energy_grid.begin(),
                               energy_grid.end(),
                               DataGen::getEnergyOfMaxCrossSection( 20.2 ) ) );
  TEST_EQUALITY_CONST( energy_grid.back(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator,
                   generateAndEvaluateInPlace_pb_k_subshell )
{
  
  DataGen::AdjointIncoherentGridGenerator<Utility::LinLinLin> grid_generator(
          20.0,
          pb_k_subshell_incoherent_adjoint_cs->getSubshellBindingEnergy()*2,
          pb_k_subshell_incoherent_adjoint_cs->getSubshellBindingEnergy()+1e-8,
          0.05,
          1e-20 );
  grid_generator.throwExceptionOnDirtyConvergence();

  Teuchos::Array<double> energy_grid( 2 );
  energy_grid[0] = 0.001;
  energy_grid[1] = 20.0;
  
  Teuchos::Array<Teuchos::Array<double> > max_energy_grid, cross_section;

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
  TEST_EQUALITY_CONST( energy_grid.size(), 95 );
  TEST_EQUALITY_CONST( energy_grid.front(), 0.001 );

  const double nudged_max_energy = 20.0 +
    pb_k_subshell_incoherent_adjoint_cs->getSubshellBindingEnergy()*2;
  
  TEST_ASSERT( std::binary_search(
                  energy_grid.begin(),
                  energy_grid.end(),
                  DataGen::getEnergyOfMaxCrossSection( nudged_max_energy ) ) );
  TEST_EQUALITY_CONST( energy_grid.back(), 20.0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_h_file_name, test_native_pb_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_h_file",
                   &test_native_h_file_name,
                   "Test Native H file name" );
  clp().setOption( "test_native_pb_file",
                   &test_native_pb_file_name,
                   "Test Native Pb file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
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

    std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::InverseCentimeter,void> > raw_scattering_function(
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

    std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::InverseCentimeter,void> > raw_scattering_function(
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

    std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::MeCMomentum,void> > raw_occupation_number(
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

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointIncoherentGridGenerator.cpp
//---------------------------------------------------------------------------//
