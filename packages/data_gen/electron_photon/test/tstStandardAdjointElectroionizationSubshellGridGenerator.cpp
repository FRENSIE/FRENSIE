//---------------------------------------------------------------------------//
//!
//! \file   tstStandardAdjointElectroionizationSubshellGridGenerator.cpp
//! \author Luke Kersting
//! \brief  Standard adjoint electroionization subshell grid generator unit tests
//! 
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_StandardAdjointElectroionizationSubshellGridGenerator.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<DataGen::AdjointElectroionizationSubshellGridGenerator> 
  linlinlin_grid_generator_free;
Teuchos::RCP<DataGen::AdjointElectroionizationSubshellGridGenerator> 
  linloglog_grid_generator_free;
Teuchos::RCP<DataGen::AdjointElectroionizationSubshellGridGenerator> 
  logloglog_grid_generator_free;
Teuchos::RCP<DataGen::AdjointElectroionizationSubshellGridGenerator> 
  linlinlin_grid_generator_h;
Teuchos::RCP<DataGen::AdjointElectroionizationSubshellGridGenerator> 
  linloglog_grid_generator_h;
Teuchos::RCP<DataGen::AdjointElectroionizationSubshellGridGenerator> 
  logloglog_grid_generator_h;
Teuchos::RCP<DataGen::AdjointElectroionizationSubshellGridGenerator> 
  logloglog_grid_generator_pb;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that an max energy grid can be generated at a single energy
TEUCHOS_UNIT_TEST( StandardAdjointElectroionizationSubshellGridGenerator, generate_single_h )
{
  DataGen::AdjointElectroionizationSubshellGridGenerator::setMinTableEnergy( 
                                                                      0.00001 );
  DataGen::AdjointElectroionizationSubshellGridGenerator::setMaxTableEnergy( 
                                                                         20.0 );
  
  Teuchos::Array<double> max_energy_grid, cross_section;

  double max_outgoing_energy = DataGen::AdjointElectroionizationSubshellCrossSectionEvaluator::getMaxOutgoingEnergyAtEnergy(
                                                                          0.1 );

  // Generate a lin-lin max energy grid at E = 0.1
  linlinlin_grid_generator_h->generate( max_energy_grid,
					cross_section,
					0.1 );
  
  TEST_EQUALITY_CONST( max_energy_grid.size(), 36 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.front(), 
				  0.1,
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.back(), 
				  20.0,
				  1e-15 );
  TEST_EQUALITY_CONST( max_energy_grid[max_energy_grid.size()-1],
		       max_outgoing_energy );
  TEST_EQUALITY_CONST( cross_section.size(), 36 );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.front(), 
				  9.3432, 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.back(), 
				  7.01235,
				  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( 
		     cross_section[cross_section.size()-1],
		     7.0123556,
		     1e-12 );		       

  max_energy_grid.clear();
  cross_section.clear();

  // Generate a lin-log max energy grid at E = 0.1
  linloglog_grid_generator_h->generate( max_energy_grid,
					cross_section,
					0.1 );

  TEST_EQUALITY_CONST( max_energy_grid.size(), 263 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.front(), 
  				  0.1, 
  				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.back(), 
  				  20.0, 
  				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 
  		 max_energy_grid[max_energy_grid.size()-1],
		 max_outgoing_energy,
  		 1e-15 );
  TEST_EQUALITY_CONST( cross_section.size(), 263 );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.front(), 
				  9.3432, 
				  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.back(), 
  				  7.0123,
  				  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( 
  		     cross_section[cross_section.size()-1],
  		     7.0123,
  		     1e-12 );

  max_energy_grid.clear();
  cross_section.clear();

  // Generate a Log-Log max energy grid at E = 0.1
  logloglog_grid_generator_h->generate( max_energy_grid,
					cross_section,
					0.1 );
  						  
  TEST_EQUALITY_CONST( max_energy_grid.size(), 354 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.front(), 
  				  0.1, 
  				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.back(), 
  				  20.0, 
  				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 
  		 max_energy_grid[max_energy_grid.size()-1],
  		 max_outgoing_energy,
  		 1e-15 );
  
  TEST_EQUALITY_CONST( cross_section.size(), 354 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.front(), 
				  9.3432893,
  				  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.back(), 
  				  7.01235,
  				  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( 
  		     cross_section[cross_section.size()-1],
  		     7.01235,
  		     1e-12 );

  max_energy_grid.clear();
  cross_section.clear();

  // Generate a lin-lin max energy grid at E = 1.0
  linlinlin_grid_generator_h->generate( max_energy_grid,
					cross_section,
					1.0 );
  
  TEST_EQUALITY_CONST( max_energy_grid.size(), 62 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.front(), 
  				  1.0,
  				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.back(), 
  				  20.0,
  				  1e-15 );
  TEST_EQUALITY_CONST( cross_section.size(), 62 );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.front(), 
  				  9.343289, 
  				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.back(), 
  				  3.9741,
  				  1e-12 );

  max_energy_grid.clear();
  cross_section.clear();

  // Generate a lin-log max energy grid at E = 1.0
  linloglog_grid_generator_h->generate( max_energy_grid,
					cross_section,
					1.0 );
  
  TEST_EQUALITY_CONST( max_energy_grid.size(), 33 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.front(), 
  				  1.0, 
  				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.back(), 
  				  20.0, 
  				  1e-15 );
  TEST_EQUALITY_CONST( cross_section.size(), 33 );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.front(), 
  				  9.3432895, 
  				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.back(), 
  				  3.974164,
  				  1e-15 );

  max_energy_grid.clear();
  cross_section.clear();

  // Generate a log-log max energy grid at E = 1.0
  logloglog_grid_generator_h->generate( max_energy_grid,
					cross_section,
					1.0 );
  
  TEST_EQUALITY_CONST( max_energy_grid.size(), 371 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.front(), 
				  1.0,
  				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( max_energy_grid.back(), 
  				  20.0, 
  				  1e-15 );
  
  TEST_EQUALITY_CONST( cross_section.size(), 371 );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.front(), 
  				  9.343289537,
  				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section.back(), 
  				  3.97416434,
  				  1e-15 );

  max_energy_grid.clear();
  cross_section.clear();
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
TEUCHOS_UNIT_TEST( StandardAdjointElectroionizationSubshellGridGenerator, generate_h )
{
  DataGen::AdjointElectroionizationSubshellGridGenerator::setMinTableEnergy( 0.00001 );
  DataGen::AdjointElectroionizationSubshellGridGenerator::setMaxTableEnergy( 20.0 );

  Teuchos::RCP<DataGen::StandardAdjointElectroionizationSubshellGridGenerator<Utility::LogLogLog> > derived_pointer = Teuchos::rcp_dynamic_cast<DataGen::StandardAdjointElectroionizationSubshellGridGenerator<Utility::LogLogLog> >( logloglog_grid_generator_h );

  derived_pointer->setConvergenceTolerance( 0.05 );

  Teuchos::Array<double> energy_grid;
  Teuchos::Array<Teuchos::Array<double> > max_energy_grids, cross_section;

  logloglog_grid_generator_h->generate( energy_grid,
					max_energy_grids,
					cross_section );

  TEST_EQUALITY_CONST( energy_grid.size(), 110 );
  TEST_FLOATING_EQUALITY( energy_grid.front(), 0.00001, 1e-15 );
  TEST_FLOATING_EQUALITY( energy_grid.back(), 20.0, 1e-15 );

  energy_grid.clear();
  max_energy_grids.clear();
  cross_section.clear();
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
TEUCHOS_UNIT_TEST( StandardAdjointElectroionizationSubshellGridGenerator, generate_pb )
{
  DataGen::AdjointElectroionizationSubshellGridGenerator::setMinTableEnergy( 0.00001 );
  DataGen::AdjointElectroionizationSubshellGridGenerator::setMaxTableEnergy( 20.0 );
  
  Teuchos::RCP<DataGen::StandardAdjointElectroionizationSubshellGridGenerator<Utility::LogLogLog> > derived_pointer = Teuchos::rcp_dynamic_cast<DataGen::StandardAdjointElectroionizationSubshellGridGenerator<Utility::LogLogLog> >( logloglog_grid_generator_pb );

  derived_pointer->setConvergenceTolerance( 0.05 );

  Teuchos::Array<double> energy_grid;
  Teuchos::Array<Teuchos::Array<double> > max_energy_grids, cross_section;

  logloglog_grid_generator_pb->generate( energy_grid,
  					 max_energy_grids,
  					 cross_section );

  TEST_EQUALITY_CONST( energy_grid.size(), 121 );
  TEST_FLOATING_EQUALITY( energy_grid.front(), 0.00001, 1e-15 );
  TEST_FLOATING_EQUALITY( energy_grid.back(), 20.0, 1e-15 );

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
    linlinlin_grid_generator_free.reset( new DataGen::StandardAdjointElectroionizationSubshellGridGenerator<Utility::LinLinLin>( 
						       scattering_function ) );
							
    linloglog_grid_generator_free.reset( new DataGen::StandardAdjointElectroionizationSubshellGridGenerator<Utility::LinLogLog>( 
						       scattering_function ) );
    
    logloglog_grid_generator_free.reset( new DataGen::StandardAdjointElectroionizationSubshellGridGenerator<Utility::LogLogLog>( 
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
/*
    // Create the scattering function
    Teuchos::ArrayView<const double> jince_block = 
      xss_data_extractor->extractJINCEBlock();

    unsigned scatt_func_size = jince_block.size()/2;

    Teuchos::Array<double> recoil_momentum( jince_block( 0, scatt_func_size ));
    Teuchos::Array<double> scattering_func_vals( 
			     jince_block( scatt_func_size, scatt_func_size ) );

    for( unsigned i = 0; i < scatt_func_size; ++i )
      recoil_momentum[i] *= 1e8; // convert from inverse Angstrom to inverse cm

    if( recoil_momentum.front() == 0.0 )
      recoil_momentum.front() = 1e-30;
    
    if( scattering_func_vals.front() == 0.0 )
      scattering_func_vals.front() = 1e-30;
    
    Teuchos::RCP<Utility::OneDDistribution> scattering_function(
		   new Utility::TabularDistribution<Utility::LogLog>(
			   recoil_momentum,
			   scattering_func_vals ) );
    
    linlinlin_grid_generator_h.reset( new DataGen::StandardAdjointElectroionizationSubshellGridGenerator<Utility::LinLinLin>( 
							   scattering_function,
							   0.001,
							   1e-15 ) );

    linloglog_grid_generator_h.reset( new DataGen::StandardAdjointElectroionizationSubshellGridGenerator<Utility::LinLogLog>( 
						           scattering_function,
							   0.001,
							   1e-15 ) );

    logloglog_grid_generator_h.reset( new DataGen::StandardAdjointElectroionizationSubshellGridGenerator<Utility::LogLogLog>( 
							   scattering_function,
							   0.001,
							   1e-15 ) );
  }

  {
    // Create a file handler and data extractor for lead
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
    
    logloglog_grid_generator_pb.reset( new DataGen::StandardAdjointElectroionizationSubshellGridGenerator<Utility::LogLogLog>(
                                binding_energy, 
                                electroionization_subshell_reaction,
                                knock_on_distribution ) );
  }
  */
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
// end tstStandardAdjointElectroionizationSubshellGridGenerator.cpp
//---------------------------------------------------------------------------//
