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
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<DataGen::AdjointIncoherentGridGenerator> grid_generator_free;
Teuchos::RCP<DataGen::AdjointIncoherentGridGenerator> grid_generator_h;
Teuchos::RCP<DataGen::AdjointIncoherentGridGenerator> grid_generator_pb;

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
  double nudge_factor = 1e-8;
  DataGen::AdjointIncoherentGridGenerator::setMinTableEnergy( 0.001 );
  DataGen::AdjointIncoherentGridGenerator::setMaxTableEnergy( 20.0 );
  DataGen::AdjointIncoherentGridGenerator::setEnergyToMaxEnergyNudgeFactor( 
							        nudge_factor );
  
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
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.front(), 
				  0.1*(1.0+nudge_factor),
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.back(), 
				  20.2,
				  1e-15 );
  TEST_EQUALITY_CONST( 
		 processed_max_energy_grid[processed_max_energy_grid.size()-2],
		 max_energy_of_max_cs );
  TEST_EQUALITY_CONST( processed_cross_section.size(), 43 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.front(), 
				  0.0, 
				  1e-15 );
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
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.front(), 
				  log(0.1*(1.0+nudge_factor)), 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.back(), 
				  log(20.2), 
				  1e-15 );
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
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.front(), 
			 1.0*(1.0+nudge_factor),
			 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.back(), 
				  20.2,
				  1e-15 );
  TEST_EQUALITY_CONST( processed_cross_section.size(), 64 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.front(), 
				  0.0, 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.back(),
				  3.97416434130254732e-25,
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
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.front(), 
				  log(1.0*(1.0+nudge_factor)), 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.back(), 
				  log(20.2), 
				  1e-15 );
  TEST_EQUALITY_CONST( processed_cross_section.size(), 35 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.front(), 
				  0.0, 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.back(), 
				  3.97416434130254732e-25,
				  1e-15 );

  processed_max_energy_grid.clear();
  processed_cross_section.clear();
}

//---------------------------------------------------------------------------//
// Check that an max energy grid can be generated at a single energy
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator, generate_single_h )
{
  double nudge_factor = 1e-8;
  DataGen::AdjointIncoherentGridGenerator::setMinTableEnergy( 0.001 );
  DataGen::AdjointIncoherentGridGenerator::setMaxTableEnergy( 20.0 );
  DataGen::AdjointIncoherentGridGenerator::setEnergyToMaxEnergyNudgeFactor( 
							        nudge_factor );
  
  Teuchos::Array<double> processed_max_energy_grid;
  Teuchos::Array<double> processed_cross_section;

  double max_energy_of_max_cs = DataGen::AdjointIncoherentCrossSectionEvaluator::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy( 0.1 );

  // Generate a lin-lin max energy grid at E = 0.1
  grid_generator_h->generate<Utility::LinLinLin>( processed_max_energy_grid,
						  processed_cross_section,
						  0.1,
						  0.001,
						  1e-33,
						  1e-6 );
  
  TEST_EQUALITY_CONST( processed_max_energy_grid.size(), 36 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.front(), 
				  0.1*(1.0+nudge_factor),
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.back(), 
				  20.2,
				  1e-15 );
  TEST_EQUALITY_CONST( 
		 processed_max_energy_grid[processed_max_energy_grid.size()-2],
		 max_energy_of_max_cs );
  TEST_EQUALITY_CONST( processed_cross_section.size(), 36 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.front(), 
				  0.0, 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.back(), 
				  7.01235561105173864e-25,
				  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( 
		     processed_cross_section[processed_cross_section.size()-2],
		     7.01235561105173864e-25,
		     1e-12 );		       

  processed_max_energy_grid.clear();
  processed_cross_section.clear();

  // Generate a lin-log max energy grid at E = 0.1
  grid_generator_h->generate<Utility::LinLogLog>( processed_max_energy_grid,
						  processed_cross_section,
						  log( 0.1 ),
						  0.001,
						  1e-33,
						  1e-6 );

  TEST_EQUALITY_CONST( processed_max_energy_grid.size(), 99 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.front(), 
				  log(0.1*(1.0+nudge_factor)), 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.back(), 
				  log(20.2), 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 
		 processed_max_energy_grid[processed_max_energy_grid.size()-2],
		 log(max_energy_of_max_cs),
		 1e-15 );
  TEST_EQUALITY_CONST( processed_cross_section.size(), 99 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.front(), 0.0, 1e-15);
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.back(), 
				  7.01235561105173864e-25,
				  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( 
		     processed_cross_section[processed_cross_section.size()-2],
		     7.01235561105173864e-25,
		     1e-12 );

  processed_max_energy_grid.clear();
  processed_cross_section.clear();

  // Generate a Log-Log max energy grid at E = 0.1
  grid_generator_h->generate<Utility::LogLogLog>( processed_max_energy_grid,
						  processed_cross_section,
						  log( 0.1 ),
						  0.001,
						  1e-33,
						  1e-6 );
  
  TEST_EQUALITY_CONST( processed_max_energy_grid.size(), 35 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.front(), 
				  log(0.1*(1.0+nudge_factor)), 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.back(), 
				  log(20.2), 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 
		 processed_max_energy_grid[processed_max_energy_grid.size()-2],
		 log(max_energy_of_max_cs),
		 1e-15 );
  TEST_EQUALITY_CONST( processed_cross_section.size(), 35 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.front(), 
				  -8.29609900690997364e+01,
				  1e-15);
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.back(), 
				  log( 7.01235561105173864e-25 ),
				  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( 
		     processed_cross_section[processed_cross_section.size()-2],
		     log( 7.01235561105173864e-25 ),
		     1e-12 );

  processed_max_energy_grid.clear();
  processed_cross_section.clear();

  // Generate a lin-lin max energy grid at E = 1.0
  grid_generator_h->generate<Utility::LinLinLin>( processed_max_energy_grid,
						  processed_cross_section,
						  1.0,
						  0.001,
						  1e-33,
						  1e-6 );
  
  TEST_EQUALITY_CONST( processed_max_energy_grid.size(), 62 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.front(), 
				  1.0*(1.0+nudge_factor),
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.back(), 
				  20.2,
				  1e-15 );
  TEST_EQUALITY_CONST( processed_cross_section.size(), 62 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.front(), 
				  0.0, 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.back(), 
				  3.97416434130254732e-25,
				  1e-12 );

  processed_max_energy_grid.clear();
  processed_cross_section.clear();

  // Generate a lin-log max energy grid at E = 1.0
  grid_generator_h->generate<Utility::LinLogLog>( processed_max_energy_grid,
						  processed_cross_section,
						  log( 1.0 ),
						  0.001,
						  1e-33,
						  1e-6 );
  
  TEST_EQUALITY_CONST( processed_max_energy_grid.size(), 33 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.front(), 
				  log(1.0*(1.0+nudge_factor)), 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.back(), 
				  log(20.2), 
				  1e-15 );
  TEST_EQUALITY_CONST( processed_cross_section.size(), 33 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.front(), 
				  0.0, 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.back(), 
				  3.97416434130254732e-25,
				  1e-15 );

  processed_max_energy_grid.clear();
  processed_cross_section.clear();

  // Generate a log-log max energy grid at E = 1.0
  grid_generator_h->generate<Utility::LogLogLog>( processed_max_energy_grid,
						  processed_cross_section,
						  log( 1.0 ),
						  0.001,
						  1e-33,
						  1e-6 );
  
  TEST_EQUALITY_CONST( processed_max_energy_grid.size(), 44 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.front(), 
				  log(1.0*(1.0+nudge_factor)), 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_max_energy_grid.back(), 
				  log(20.2), 
				  1e-15 );
  TEST_EQUALITY_CONST( processed_cross_section.size(), 44 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.front(), 
				  -8.29609900516426393e+01,
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_cross_section.back(), 
				  log(3.97416434130254732e-25),
				  1e-15 );

  processed_max_energy_grid.clear();
  processed_cross_section.clear();
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator, generate_free )
{
  DataGen::AdjointIncoherentGridGenerator::setMinTableEnergy( 0.001 );
  DataGen::AdjointIncoherentGridGenerator::setMaxTableEnergy( 20.0 );
  DataGen::AdjointIncoherentGridGenerator::setEnergyToMaxEnergyNudgeFactor( 
									1e-8 );

  Teuchos::Array<double> energy_grid;
  Teuchos::Array<Teuchos::Array<double> > max_energy_grids, cross_section;

  grid_generator_free->generate<Utility::LogLogLog>( energy_grid,
  						     max_energy_grids,
  						     cross_section,
  						     0.001,
  						     1e-40,
  						     1e-9 );

  TEST_EQUALITY_CONST( energy_grid.size(), 90 );
  TEST_FLOATING_EQUALITY( energy_grid.front(), log(0.001), 1e-15 );
  TEST_FLOATING_EQUALITY( energy_grid.back(), log(20.0), 1e-15 );

  
  energy_grid.clear();
  max_energy_grids.clear();
  cross_section.clear();
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator, generate_h )
{
  DataGen::AdjointIncoherentGridGenerator::setMinTableEnergy( 0.001 );
  DataGen::AdjointIncoherentGridGenerator::setMaxTableEnergy( 20.0 );
  DataGen::AdjointIncoherentGridGenerator::setEnergyToMaxEnergyNudgeFactor( 
									1e-8 );
  DataGen::AdjointIncoherentGridGenerator::setVerboseOff();

  Teuchos::Array<double> energy_grid;
  Teuchos::Array<Teuchos::Array<double> > max_energy_grids, cross_section;

  grid_generator_h->generate<Utility::LogLogLog>( energy_grid,
  						  max_energy_grids,
  						  cross_section,
  						  0.001,
  						  1e-37,
  						  1e-9 );

  TEST_EQUALITY_CONST( energy_grid.size(), 103 );
  TEST_FLOATING_EQUALITY( energy_grid.front(), log(0.001), 1e-15 );
  TEST_FLOATING_EQUALITY( energy_grid.back(), log(20.0), 1e-15 );

  energy_grid.clear();
  max_energy_grids.clear();
  cross_section.clear();
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator, generate_pb )
{
  DataGen::AdjointIncoherentGridGenerator::setMinTableEnergy( 0.001 );
  DataGen::AdjointIncoherentGridGenerator::setMaxTableEnergy( 20.0 );
  DataGen::AdjointIncoherentGridGenerator::setEnergyToMaxEnergyNudgeFactor( 
									1e-8 );
  DataGen::AdjointIncoherentGridGenerator::setVerboseOff();

  Teuchos::Array<double> energy_grid;
  Teuchos::Array<Teuchos::Array<double> > max_energy_grids, cross_section;

  grid_generator_pb->generate<Utility::LogLogLog>( energy_grid,
						   max_energy_grids,
						   cross_section,
						   0.001,
						   1e-37,
						   1e-9 );

  TEST_EQUALITY_CONST( energy_grid.size(), 110 );
  TEST_FLOATING_EQUALITY( energy_grid.front(), log(0.001), 1e-15 );
  TEST_FLOATING_EQUALITY( energy_grid.back(), log(20.0), 1e-15 );

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

  std::string test_h_ace_file_name, test_h_ace_table_name;
  std::string test_pb_ace_file_name, test_pb_ace_table_name;
  
  clp.setOption( "test_h_ace_file",
		 &test_h_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_h_ace_table",
		 &test_h_ace_table_name,
		 "Test ACE table name" );
  clp.setOption( "test_pb_ace_file",
		 &test_pb_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_pb_ace_table",
		 &test_pb_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    // Initialize the dummy scattering function
    Teuchos::RCP<Utility::OneDDistribution> scattering_function(
	  new Utility::UniformDistribution( 0.0, 
					    std::numeric_limits<double>::max(),
					    1.0 ) );

    // Initialize the grid generator
    grid_generator_free.reset( new DataGen::AdjointIncoherentGridGenerator( 
						       scattering_function ) );
  }

  {
    // Create a file handler and data extractor for hydrogen
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			       new Data::ACEFileHandler( test_h_ace_file_name,
							 test_h_ace_table_name,
							 1u ) );

    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

    // Create the scattering function
    Teuchos::ArrayView<const double> jince_block = 
      xss_data_extractor->extractJINCEBlock();

    unsigned scatt_func_size = jince_block.size()/2;

    Teuchos::Array<double> recoil_momentum( jince_block( 0, scatt_func_size ));

    for( unsigned i = 0; i < scatt_func_size; ++i )
      recoil_momentum[i] *= 1e8; // convert from inverse Angstrom to inverse cm

    Teuchos::RCP<Utility::OneDDistribution> scattering_function(
		   new Utility::TabularDistribution<Utility::LogLog>(
			   recoil_momentum,
			   jince_block( scatt_func_size, scatt_func_size ) ) );
    Teuchos::ArrayView<const double> func = 
      jince_block( scatt_func_size, scatt_func_size );
    
    grid_generator_h.reset( new DataGen::AdjointIncoherentGridGenerator( 
						       scattering_function ) );
  }

  {
    // Create a file handler and data extractor for hydrogen
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			      new Data::ACEFileHandler( test_pb_ace_file_name,
							test_pb_ace_table_name,
							1u ) );

    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

    // Create the scattering function
    Teuchos::ArrayView<const double> jince_block = 
      xss_data_extractor->extractJINCEBlock();

    unsigned scatt_func_size = jince_block.size()/2;

    Teuchos::Array<double> recoil_momentum( jince_block( 0, scatt_func_size ));

    for( unsigned i = 0; i < scatt_func_size; ++i )
      recoil_momentum[i] *= 1e8; // convert from inverse Angstrom to inverse cm

    Teuchos::RCP<Utility::OneDDistribution> scattering_function(
		   new Utility::TabularDistribution<Utility::LogLog>(
			   recoil_momentum,
			   jince_block( scatt_func_size, scatt_func_size ) ) );
    Teuchos::ArrayView<const double> func = 
      jince_block( scatt_func_size, scatt_func_size );
    
    grid_generator_pb.reset( new DataGen::AdjointIncoherentGridGenerator( 
						       scattering_function ) );
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
// end tstAdjointIncoherentGridGenerator.cpp
//---------------------------------------------------------------------------//
