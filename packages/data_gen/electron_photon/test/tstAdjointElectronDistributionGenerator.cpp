//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectronDistributionGenerator.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron distribution generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointElectronDistributionGenerator.hpp"
#include "DataGen_AdjointElectronCrossSectionEvaluator.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "Data_SubshellType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

typedef MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>
  ElectroionizationReaction;

typedef MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> 
  BremsstrahlungReaction;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>
  data_container_h, data_container_pb;

std::shared_ptr<const DataGen::AdjointElectronCrossSectionEvaluator<ElectroionizationReaction> >
  electroionization_adjoint_cs;

std::shared_ptr<const DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction> >
  bremsstrahlung_adjoint_cs;

double min_energy = 1e-5;
double max_energy = 20.0;
double max_energy_nudge_value = 0.2;
double energy_to_outgoing_energy_nudge_value = 2e-7;
double convergence_tol = 0.001;
double absolute_diff_tol = 1e-12;
double distance_tol = 1e-14;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the max energy can be returned 
TEUCHOS_UNIT_TEST( AdjointElectronDistributionGenerator, getMaxEnergy )
{
  {
    DataGen::AdjointElectronDistributionGenerator<Utility::LinLinLin>
      grid_generator;

    TEST_EQUALITY_CONST( grid_generator.getMaxEnergy(), 20.0 );
  }

  {
    DataGen::AdjointElectronDistributionGenerator<Utility::LinLinLin>
      grid_generator( 21.0 );

    TEST_EQUALITY_CONST( grid_generator.getMaxEnergy(), 21.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the max energy nudge value can be set
TEUCHOS_UNIT_TEST( AdjointElectronDistributionGenerator, setMaxEnergyNudgeValue )
{
  {
    DataGen::AdjointElectronDistributionGenerator<Utility::LinLinLin>
      grid_generator;

    TEST_EQUALITY_CONST( grid_generator.getNudgedMaxEnergy(), 20.2 );
  }

  DataGen::AdjointElectronDistributionGenerator<Utility::LinLinLin>
    grid_generator( 21.0, 0.3 );

  TEST_EQUALITY_CONST( grid_generator.getNudgedMaxEnergy(), 21.3 );

  grid_generator.setMaxEnergyNudgeValue( 0.5 );

  TEST_EQUALITY_CONST( grid_generator.getNudgedMaxEnergy(), 21.5 );
}

//---------------------------------------------------------------------------//
// Check that the energy to outgoing energy nudge value can be set
TEUCHOS_UNIT_TEST( AdjointElectronDistributionGenerator,
                   setEnergyToOutgoingEnergyNudgeValue )
{
  {
    DataGen::AdjointElectronDistributionGenerator<Utility::LinLinLin>
      grid_generator;

    TEST_EQUALITY_CONST( grid_generator.getNudgedEnergy( 1.0 ), 1.000001 );
  }

  DataGen::AdjointElectronDistributionGenerator<Utility::LinLinLin>
    grid_generator( 21.0, 0.2, 1e-3 );

  TEST_EQUALITY_CONST( grid_generator.getNudgedEnergy( 1.0 ), 1.001 );

  grid_generator.setEnergyToOutgoingEnergyNudgeValue( 1e-4 );

  TEST_EQUALITY_CONST( grid_generator.getNudgedEnergy( 1.0 ), 1.0001 );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung outgoing energy grid can be generated for H
TEUCHOS_UNIT_TEST( AdjointElectronDistributionGenerator,
                   generateAndEvaluateDistribution_brem_h )
{
  DataGen::AdjointElectronDistributionGenerator<Utility::LinLinLin>
    grid_generator(
      max_energy,
      max_energy_nudge_value,
      energy_to_outgoing_energy_nudge_value );


  // Set the primary energy grid
  std::vector<double> primary_energy_grid(2);
  primary_energy_grid[0] = 0.01;
  primary_energy_grid[1] = 1.0;

  grid_generator.setPrimaryEnergyGrid( primary_energy_grid );


  // cross section values
  std::vector<double> cross_sections(2);
  cross_sections[0] = 1.0;
  cross_sections[1] = 1.0;

  
  std::map<double,std::vector<double> > outgoing_energy_grid, pdf;

  // Generate an outgoing energy grid at E=0.01 MeV
  grid_generator.generateAndEvaluateDistributionOnPrimaryEnergyGrid(
          outgoing_energy_grid,
          pdf,
          bremsstrahlung_adjoint_cs,
          1e-6,
          cross_sections,
          0 );

  // Check the generated outgoing energy grid
  TEST_EQUALITY_CONST( outgoing_energy_grid[0.01].size(), 811 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[0.01].front(), 0.01+2e-7, 1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[0.01].back(), 20.2, 1e-6 );

  // Check the evaluated pdf
  TEST_EQUALITY_CONST( pdf[0.01].size(), 811 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf[0.01].front(),
                                  1.5200108884210365359e6,
                                  1e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( pdf[0.01].back(), 
                                  1.3868414443414270819e-4,
                                  1e-6 );

  // Check the generated max energy grid
  TEST_EQUALITY_CONST( outgoing_energy_grid[1.0].size(), 570 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[1.0].front(), 1.0+2e-7, 1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[1.0].back(), 20.2, 1e-6 );

  // Check the evaluated cross section
  TEST_EQUALITY_CONST( pdf[1.0].size(), 570 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf[1.0].front(),
                                  2.0111957945609613671e5,
                                  1e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( pdf[1.0].back(),
                                  1.4440565167576839925e-4,
                                  1e-6 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_native_h_file_name, test_native_pb_file_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_native_h_file",
		 &test_native_h_file_name,
		 "Test Native H file name" );
  clp.setOption( "test_native_pb_file",
                 &test_native_pb_file_name,
                 "Test Native Pb file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) 
  {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  double nudged_max_energy = max_energy + max_energy_nudge_value;

  // Create the H distributions
  {
    // Create the native data file container
    data_container_h.reset(
      new Data::ElectronPhotonRelaxationDataContainer(
        test_native_h_file_name ) );

    // Extract the common electron energy grid
    Teuchos::ArrayRCP<double> union_energy_grid;
    union_energy_grid.assign(
      data_container_h->getElectronEnergyGrid().begin(),
      data_container_h->getElectronEnergyGrid().end() );

    Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
      new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                union_energy_grid,
                union_energy_grid[0],
                union_energy_grid[union_energy_grid.size()-1],
                union_energy_grid.size()/10 + 1 ) );

    std::shared_ptr<BremsstrahlungReaction> bremsstrahlung_reaction;

    MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
      *data_container_h,
      union_energy_grid,
      grid_searcher,
      bremsstrahlung_reaction,
      MonteCarlo::DIPOLE_DISTRIBUTION );

    std::vector<double> brem_energy_grid =
      data_container_h->getBremsstrahlungEnergyGrid();

    std::vector<double>::iterator start, end;

    if ( min_energy <= brem_energy_grid.front() )
    {
      start = brem_energy_grid.begin();
    }
    else
    {
      // Find the location of the first grid point that is <= the min energy
      start = std::upper_bound(
                  brem_energy_grid.begin(),
                  brem_energy_grid.end(),
                  min_energy );
      --start;
    }

      // Find the location of the first grid point that is >= the max energy
    end = std::lower_bound(
                start,
                brem_energy_grid.end(),
                max_energy );
    ++end;

    std::vector<double> bremsstrahlung_integration_points( start, end );

    // Replace the lower and upper bins with the min and max electron energies
    bremsstrahlung_integration_points.front() = min_energy;
    bremsstrahlung_integration_points.back() = max_energy;
    bremsstrahlung_integration_points.push_back( nudged_max_energy );

    bremsstrahlung_adjoint_cs.reset(
      new DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction>(
          bremsstrahlung_reaction,
          bremsstrahlung_integration_points ) );
  }

  // Create the Pb distributions
  {
    // Create the native data file container
    data_container_pb.reset(
    new Data::ElectronPhotonRelaxationDataContainer(
      test_native_pb_file_name ) );


  }

  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);   
}

//---------------------------------------------------------------------------//
// end tstAdjointElectronDistributionGenerator.cpp
//---------------------------------------------------------------------------//
