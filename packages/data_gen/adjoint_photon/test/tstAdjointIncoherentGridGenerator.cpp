//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointIncoherentGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent grid generator
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

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<DataGen::AdjointIncoherentGridGenerator> grid_generator;

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
// Check that an energy grid can be generated
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator, generate )
{
  Teuchos::Array<double> initial_log_max_energy_grid( 5 );
  initial_log_max_energy_grid[0] = log( 0.001 );
  initial_log_max_energy_grid[1] = log( 0.01 );
  initial_log_max_energy_grid[2] = log( 0.1 );
  initial_log_max_energy_grid[3] = log( 1.0 );
  initial_log_max_energy_grid[4] = log( 10.0 );

  Teuchos::Array<double> log_max_energy_grid;
  Teuchos::Array<Teuchos::Array<double> > log_energy_grids;

  grid_generator->generate( log_max_energy_grid,
			    log_energy_grids,
			    initial_log_max_energy_grid,
			    0.001,
			    1e-12, 
			    1e-3 );

  std::cout << log_max_energy_grid << std::endl << std::endl;
  std::cout << log_energy_grids << std::endl;
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
  grid_generator.reset( new DataGen::AdjointIncoherentGridGenerator( 
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
