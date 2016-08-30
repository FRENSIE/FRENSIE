//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectronGridGenerator.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron grid generator unit tests
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
#include "DataGen_AdjointElectronGridGenerator.hpp"
#include "DataGen_AdjointElectronCrossSectionEvaluator.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

typedef MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>
  ElectroionizationReaction;

typedef MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> 
  BremsstrahlungReaction;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction>>
  h_brem_adjoint_cs;

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
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator, getMaxEnergy )
{
  {
    DataGen::AdjointElectronGridGenerator<Utility::LinLinLin>
    grid_generator( max_energy,
                    max_energy_nudge_value,
                    energy_to_outgoing_energy_nudge_value,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol );

    TEST_EQUALITY_CONST( grid_generator.getMaxEnergy(), 20.0 );
  }

  {
    DataGen::AdjointElectronGridGenerator<Utility::LinLinLin>
      grid_generator( 21.0 );

    TEST_EQUALITY_CONST( grid_generator.getMaxEnergy(), 21.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the max energy nudge value can be set
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator, setMaxEnergyNudgeValue )
{
  {
    DataGen::AdjointElectronGridGenerator<Utility::LinLinLin>
    grid_generator( max_energy,
                    max_energy_nudge_value,
                    energy_to_outgoing_energy_nudge_value,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol );

    TEST_EQUALITY_CONST( grid_generator.getNudgedMaxEnergy(), 20.2 );
  }

  DataGen::AdjointElectronGridGenerator<Utility::LinLinLin>
    grid_generator( 21.0, 0.3 );

  TEST_EQUALITY_CONST( grid_generator.getNudgedMaxEnergy(), 21.3 );

  grid_generator.setMaxEnergyNudgeValue( 0.5 );

  TEST_EQUALITY_CONST( grid_generator.getNudgedMaxEnergy(), 21.5 );
}

//---------------------------------------------------------------------------//
// Check that the energy to max energy nudge value can be set
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator,
                   setEnergyToOutgoingEnergyNudgeValue )
{
  {
    DataGen::AdjointElectronGridGenerator<Utility::LinLinLin>
    grid_generator( max_energy,
                    max_energy_nudge_value,
                    energy_to_outgoing_energy_nudge_value,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol );

    TEST_EQUALITY_CONST( grid_generator.getNudgedEnergy( 1.0 ), 1.0000002 );
  }

  DataGen::AdjointElectronGridGenerator<Utility::LinLinLin>
    grid_generator( 21.0, 0.2, 1e-3 );

  TEST_EQUALITY_CONST( grid_generator.getNudgedEnergy( 1.0 ), 1.001 );

  grid_generator.setEnergyToOutgoingEnergyNudgeValue( 1e-4 );

  TEST_EQUALITY_CONST( grid_generator.getNudgedEnergy( 1.0 ), 1.0001 );
}

//---------------------------------------------------------------------------//
// Check that max energy grid can be generated for a free electron
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator,
                   generateAndEvaluateSecondaryInPlace_h )
{
  DataGen::AdjointElectronGridGenerator<Utility::LinLinLin>
    grid_generator( max_energy,
                    max_energy_nudge_value,
                    energy_to_outgoing_energy_nudge_value,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol );

  Teuchos::Array<double> outgoing_energy_grid, pdf;

  // Bind the distribution to a cross section evaluator
  std::function<double(double,double)> cs_evaluator =
    grid_generator.createCrossSectionEvaluator( h_brem_adjoint_cs, 1e-6 );

  // Generate a max energy grid at E=0.1 MeV
  grid_generator.generateAndEvaluateSecondaryInPlace( outgoing_energy_grid,
                                                      pdf,
                                                      0.01,
                                                      cs_evaluator );

  // Check the generated outgoing energy grid
  TEST_EQUALITY_CONST( outgoing_energy_grid.size(), 811 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid.front(), 0.01+2e-7, 1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid.back(), 20.2, 1e-6 );

  // Check the evaluated pdf
  TEST_EQUALITY_CONST( pdf.size(), 811 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf.front(),
                                  1.5200108884210365359e6,
                                  1e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( pdf.back(), 
                                  1.3868414443414270819e-4,
                                  1e-6 );

  outgoing_energy_grid.clear();
  pdf.clear();
  
  // Generate a max energy grid at E=1.0 MeV
  grid_generator.generateAndEvaluateSecondaryInPlace( outgoing_energy_grid,
                                                      pdf,
                                                      1.0,
                                                      cs_evaluator );

  // Check the generated outgoing energy grid
  TEST_EQUALITY_CONST( outgoing_energy_grid.size(), 570 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid.front(), 1.0+2e-7, 1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid.back(), 20.2, 1e-6 );

  // Check the evaluated cross section
  TEST_EQUALITY_CONST( pdf.size(), 570 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf.front(),
                                  2.0111957945609613671e5,
                                  1e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( pdf.back(),
                                  1.4440565167576839925e-4,
                                  1e-6 );
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator,
                   generateAndEvaluateInPlace_h )
{
  DataGen::AdjointElectronGridGenerator<Utility::LinLinLin>
    grid_generator( max_energy,
                    max_energy_nudge_value,
                    energy_to_outgoing_energy_nudge_value,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol );

  Teuchos::Array<double> energy_grid( 2 );
  energy_grid[0] = 0.001;
  energy_grid[1] = 20.0;
  
  Teuchos::Array<Teuchos::Array<double> > outgoing_energy_grid, pdf;

  // Bind the distribution to a cross section evaluator
  std::function<double(double,double)> cs_evaluator =
    grid_generator.createCrossSectionEvaluator(h_brem_adjoint_cs, 0.001);

  // Generate the 2D grid
  grid_generator.generateAndEvaluateInPlace( energy_grid,
                                             outgoing_energy_grid,
                                             pdf,
                                             cs_evaluator );

  // Check the energy grid
  TEST_EQUALITY_CONST( energy_grid.size(), 159 );
  TEST_EQUALITY_CONST( energy_grid.front(), 1e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 20.0 );
}
/*
//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator,
                   generateAndEvaluateInPlace_pb )
{
  DataGen::AdjointElectronGridGenerator<Utility::LinLinLin>
    grid_generator( max_energy,
                    max_energy_nudge_value,
                    energy_to_outgoing_energy_nudge_value,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol );

  Teuchos::Array<double> energy_grid( 2 );
  energy_grid[0] = 0.001;
  energy_grid[1] = 20.0;
  
  Teuchos::Array<Teuchos::Array<double> > outgoing_energy_grid, pdf;

  // Bind the distribution to a cross section evaluator
  std::function<double(double,double)> cs_evaluator =
    grid_generator.createCrossSectionEvaluator(
                                             pb_brem_adjoint_cs, 0.001 );

  // Generate the 2D grid
  grid_generator.generateAndEvaluateInPlace( energy_grid,
                                             outgoing_energy_grid,
                                             pdf,
                                             cs_evaluator );

  // Check the energy grid
  TEST_EQUALITY_CONST( energy_grid.size(), 169 );
  TEST_EQUALITY_CONST( energy_grid.front(), 0.001 );
  TEST_ASSERT(
           std::binary_search( energy_grid.begin(),
                               energy_grid.end(),
                               DataGen::getEnergyOfMaxCrossSection( 20.2 ) ) );
  TEST_EQUALITY_CONST( energy_grid.back(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator,
                   generateAndEvaluateInPlace_pb_k_subshell )
{
  DataGen::AdjointElectronGridGenerator<Utility::LinLinLin> grid_generator(
          max_energy,
          pb_k_subshell_ionization_adjoint_cs->getSubshellBindingEnergy()*2,
          pb_k_subshell_ionization_adjoint_cs->getSubshellBindingEnergy()+1e-8,
          convergence_tol,
          absolute_diff_tol,
          distance_tol );

  Teuchos::Array<double> energy_grid( 2 );
  energy_grid[0] = 0.001;
  energy_grid[1] = 20.0;
  
  Teuchos::Array<Teuchos::Array<double> > outgoing_energy_grid, pdf;

  // Bind the distribution to a cross section evaluator
  std::function<double(double,double)> cs_evaluator =
    grid_generator.createCrossSectionEvaluator(
                                   pb_k_subshell_ionization_adjoint_cs, 0.01 );

  // Generate the 2D grid
  grid_generator.generateAndEvaluateInPlace( energy_grid,
                                             outgoing_energy_grid,
                                             pdf,
                                             cs_evaluator );

  // Check the energy grid
  TEST_EQUALITY_CONST( energy_grid.size(), 95 );
  TEST_EQUALITY_CONST( energy_grid.front(), 0.001 );

  const double nudged_max_energy = 20.0 +
    pb_k_subshell_ionization_adjoint_cs->getSubshellBindingEnergy()*2;
  
  TEST_ASSERT( std::binary_search(
                  energy_grid.begin(),
                  energy_grid.end(),
                  DataGen::getEnergyOfMaxCrossSection( nudged_max_energy ) ) );
  TEST_EQUALITY_CONST( energy_grid.back(), 20.0 );
}
*/
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

  // Create the H distribution
  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer
      data_container( test_native_h_file_name );

    // Extract the common electron energy grid
    Teuchos::ArrayRCP<double> union_energy_grid;
    union_energy_grid.assign(
      data_container.getElectronEnergyGrid().begin(),
      data_container.getElectronEnergyGrid().end() );

    Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
      new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                union_energy_grid,
                union_energy_grid[0],
                union_energy_grid[union_energy_grid.size()-1],
                union_energy_grid.size()/10 + 1 ) );

    std::shared_ptr<BremsstrahlungReaction> bremsstrahlung_reaction;

    MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
      data_container,
      union_energy_grid,
      grid_searcher,
      bremsstrahlung_reaction,
      MonteCarlo::DIPOLE_DISTRIBUTION );

    std::vector<double> brem_energy_grid =
      data_container.getBremsstrahlungEnergyGrid();

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

    double nudged_max_energy = max_energy + max_energy_nudge_value;

    // Replace the lower and upper bins with the min and max electron energies
    bremsstrahlung_integration_points.front() = min_energy;
    bremsstrahlung_integration_points.back() = max_energy;
    bremsstrahlung_integration_points.push_back( nudged_max_energy );

    h_brem_adjoint_cs.reset(
      new DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction>(
          bremsstrahlung_reaction,
          bremsstrahlung_integration_points ) );
  }

  // Create the Pb distributions
  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer
      data_container( test_native_pb_file_name );

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
// end tstAdjointElectronGridGenerator.cpp
//---------------------------------------------------------------------------//
