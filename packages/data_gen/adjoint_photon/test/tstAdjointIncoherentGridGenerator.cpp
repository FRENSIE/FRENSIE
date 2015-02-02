//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointIncoherentGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent grid generator unit tests
//! 
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointIncoherentGridGenerator.cpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<DataGen::AdjointIncoherentGridGenerator> grid_generator_free;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the min table energy can be set
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator, setMinTableEnergy )
{
  double min_table_energy = 
    DataGen::AdjointIncoherentGridGenerator::getMinTableEnergy();

  TEST_EQUALITY_CONST( min_table_energy, 0.0001 );
  
  DataGen::AdjointIncoherentGridGenerator::setMinTableEnergy( 0.00001 );

  min_table_energy = 
    DataGen::AdjointIncoherentGridGenerator::getMinTableEnergy();

  TEST_EQUALITY_CONST( min_table_energy, 0.00001 );
}

//---------------------------------------------------------------------------//
// Check that the max table energy can be set
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator, setMaxTableEnergy )
{
  double max_table_energy = 
    DataGen::AdjointIncoherentGridGenerator::getMaxTableEnergy();

  TEST_EQUALITY_CONST( max_table_energy, 20.0 );

  DataGen::AdjointIncoherentGridGenerator::setMaxTableEnergy( 30.0 );

  max_table_energy = 
    DataGen::AdjointIncoherentGridGenerator::getMaxTableEnergy();

  TEST_EQUALITY_CONST( max_table_energy, 30.0 );
}

//---------------------------------------------------------------------------//
// Check that the processed cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator,
		   evaluateProcessedCrossSection_free )
{
  DataGen::AdjointIncoherentCrossSectionEvaluator cs_evaluator;
  
  double true_cross_sec = cs_evaluator.evaluateCrossSection( 0.1, 20.0 );
  
  double processed_cross_sec = 
    grid_generator_free->evaluateProcessedCrossSection<Utility::LinLinLin>(
									0.1,
									20.0 );

  UTILITY_TEST_FLOATING_EQUALITY( true_cross_sec, processed_cross_sec, 1e-14 );

  processed_cross_sec = 
    grid_generator_free->evaluateProcessedCrossSection<Utility::LinLogLog>(
								 log( 0.1 ),
								 log( 20.0 ) );
  
  UTILITY_TEST_FLOATING_EQUALITY( true_cross_sec, processed_cross_sec, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that an max energy grid can be generated at a single energy
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator, generate_single_free )
{
  DataGen::AdjointIncoherentGridGenerator::setMinTableEnergy( 0.001 );
  DataGen::AdjointIncoherentGridGenerator::setMaxTableEnergy( 20.0 );
  
  Teuchos::Array<double> processed_max_energy_grid;
  Teuchos::Array<double> processed_cross_section;

  double max_energy_of_max_cs = DataGen::AdjointIncoherentCrossSectionEvaluator::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy( 0.1 );

  // Generate a lin-lin max energy grid at E = 0.1
  grid_generator_free->generate<Utility::LinLinLin>( processed_max_energy_grid,
						     processed_cross_section,
						     0.1,
						     0.001,
						     1e-33,
						     1e-6 );
  
  TEST_EQUALITY_CONST( processed_max_energy_grid.size(), 43 );
  TEST_EQUALITY_CONST( processed_max_energy_grid.front(), 0.1 );
  TEST_EQUALITY_CONST( processed_max_energy_grid.back(), 20.2 );
  TEST_EQUALITY_CONST( 
		 processed_max_energy_grid[processed_max_energy_grid.size()-2],
		 max_energy_of_max_cs );
  TEST_EQUALITY_CONST( processed_cross_section.size(), 43 );
  TEST_FLOATING_EQUALITY( processed_cross_section.front(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.back(), 
				  7.01697560627867675e-25,
				  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( 
		     processed_cross_section[processed_cross_section.size()-2],
		     7.01697560627867675e-25,
		     1e-12 );		       

  processed_max_energy_grid.clear();
  processed_cross_section.clear();

  // Generate a lin-log max energy grid at E = 0.1
  grid_generator_free->generate<Utility::LinLogLog>( processed_max_energy_grid,
						     processed_cross_section,
						     log( 0.1 ),
						     0.001,
						     1e-33,
						     1e-6 );

  TEST_EQUALITY_CONST( processed_max_energy_grid.size(), 40 );
  TEST_FLOATING_EQUALITY( processed_max_energy_grid.front(), log(0.1), 1e-15 );
  TEST_FLOATING_EQUALITY( processed_max_energy_grid.back(), log(20.2), 1e-15 );
  TEST_FLOATING_EQUALITY( 
		 processed_max_energy_grid[processed_max_energy_grid.size()-2],
		 log(max_energy_of_max_cs),
		 1e-15 );
  TEST_EQUALITY_CONST( processed_cross_section.size(), 40 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.front(), 0.0, 1e-15);
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.back(), 
				  7.01697560627867675e-25,
				  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( 
		     processed_cross_section[processed_cross_section.size()-2],
		     7.01697560627867675e-25,
		     1e-12 );

  processed_max_energy_grid.clear();
  processed_cross_section.clear();

  // Generate a lin-lin max energy grid at E = 1.0
  grid_generator_free->generate<Utility::LinLinLin>( processed_max_energy_grid,
						     processed_cross_section,
						     1.0,
						     0.001,
						     1e-33,
						     1e-6 );
  
  TEST_EQUALITY_CONST( processed_max_energy_grid.size(), 64 );
  TEST_EQUALITY_CONST( processed_max_energy_grid.front(), 1.0 );
  TEST_EQUALITY_CONST( processed_max_energy_grid.back(), 20.2 );
  TEST_EQUALITY_CONST( processed_cross_section.size(), 64 );
  TEST_FLOATING_EQUALITY( processed_cross_section.front(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( processed_cross_section.back(), 
			  3.97416434118362081e-25,
			  1e-12 );

  processed_max_energy_grid.clear();
  processed_cross_section.clear();

  // Generate a lin-log max energy grid at E = 1.0
  grid_generator_free->generate<Utility::LinLogLog>( processed_max_energy_grid,
						     processed_cross_section,
						     log( 1.0 ),
						     0.001,
						     1e-33,
						     1e-6 );

  TEST_EQUALITY_CONST( processed_max_energy_grid.size(), 35 );
  TEST_FLOATING_EQUALITY( processed_max_energy_grid.front(), log(1.0), 1e-15 );
  TEST_FLOATING_EQUALITY( processed_max_energy_grid.back(), log(20.2), 1e-15 );
  TEST_EQUALITY_CONST( processed_cross_section.size(), 35 );
  TEST_FLOATING_EQUALITY( processed_cross_section.front(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( processed_cross_section.back(), 
			  3.97416434118362081e-25,
			  1e-15 );

  processed_max_energy_grid.clear();
  processed_cross_section.clear();
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator, generate_free )
{
  DataGen::AdjointIncoherentGridGenerator::setMinTableEnergy( 0.19 );
  DataGen::AdjointIncoherentGridGenerator::setMaxTableEnergy( 1.0 );

  Teuchos::Array<double> energy_grid;
  Teuchos::Array<Teuchos::Array<double> > max_energy_grids, cross_section;

  grid_generator_free->generate<Utility::LinLinLin>( energy_grid,
  						     max_energy_grids,
  						     cross_section,
  						     0.001,
  						     1e-40,
  						     1e-9 );

  TEST_EQUALITY_CONST( energy_grid.size(), 239 );
  TEST_FLOATING_EQUALITY( energy_grid.front(), 0.19, 1e-15 );
  TEST_FLOATING_EQUALITY( energy_grid.back(), 1.0, 1e-15 );

  energy_grid.clear();
  max_energy_grids.clear();
  cross_section.clear();
  
  grid_generator_free->generate<Utility::LinLogLog>( energy_grid,
						     max_energy_grids,
  						     cross_section,
  						     0.001,
  						     1e-40,
  						     1e-9 );

  TEST_EQUALITY_CONST( energy_grid.size(), 273 );
  TEST_FLOATING_EQUALITY( energy_grid.front(), log(0.19), 1e-15 );
  TEST_FLOATING_EQUALITY( energy_grid.back(), log(1.0), 1e-15 );

  energy_grid.clear();
  max_energy_grids.clear();
  cross_section.clear();
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize the dummy scattering function
  Teuchos::RCP<Utility::OneDDistribution> scattering_function(
	  new Utility::UniformDistribution( 0.0, 
					    std::numeric_limits<double>::max(),
					    1.0 ) );

  // Initialize the grid generator
  grid_generator_free.reset( new DataGen::AdjointIncoherentGridGenerator( 
						       scattering_function ) );

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
// end tstAdjointIncoherentGridGenerator.cpp
//---------------------------------------------------------------------------//
