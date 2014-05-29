//---------------------------------------------------------------------------//
//!
//! \file   tstNeutronScatteringDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  Neutron-neutron scattering distribution factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringDistributionFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_basic_ace_file_name;
std::string test_basic_ace_table_name;
// std::string test_fission_ace_file_name;
// std::string test_ptable_ace_file_name;
// std::string test_fission_ptable_ace_file_name;

Teuchos::RCP<Data::ACEFileHandler> ace_file_handler;

Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an elastic scattering distribution can be constructed
TEUCHOS_UNIT_TEST( NeutronScatteringDistributionFactory, 
		   createElasticScatteringDist )
{
  ace_file_handler.reset(new Data::ACEFileHandler( test_basic_ace_file_name,
						     test_basic_ace_table_name,
						     1u ) );
  xss_data_extractor.reset(
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				        ace_file_handler->getTableJXSArray(),
				        ace_file_handler->getTableXSSArray()));
   
  Facemc::NeutronScatteringDistributionFactory 
    factory( test_basic_ace_table_name,
	     ace_file_handler->getTableAtomicWeightRatio(),
	     xss_data_extractor->extractMTRBlock(),
	     xss_data_extractor->extractTYRBlock(),
	     xss_data_extractor->extractLANDBlock(),
	     xss_data_extractor->extractANDBlock(),
	     xss_data_extractor->extractLDLWBlock(),
	     xss_data_extractor->extractDLWBlock() );

  Teuchos::RCP<Facemc::NeutronScatteringDistribution> scattering_dist;
  
  factory.createElasticScatteringDistribution( scattering_dist );

  Facemc::NeutronState neutron( 0ull );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );

  std::cout << neutron << std::endl;
  scattering_dist->scatterNeutron( neutron, 
				   ace_file_handler->getTableTemperature() );
  
  std::cout << neutron << std::endl;
  scattering_dist->scatterNeutron( neutron, 
  				   ace_file_handler->getTableTemperature() );

  std::cout << neutron << std::endl;
  scattering_dist->scatterNeutron( neutron, 
  				   ace_file_handler->getTableTemperature() );

  std::cout << neutron << std::endl;
  scattering_dist->scatterNeutron( neutron, 
  				   ace_file_handler->getTableTemperature() );

  std::cout << neutron << std::endl;
  scattering_dist->scatterNeutron( neutron, 
  				   ace_file_handler->getTableTemperature() );

  std::cout << neutron << std::endl;
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_basic_ace_file",
		 &test_basic_ace_file_name,
		 "Test basic ACE file name" );
  clp.setOption( "test_basic_ace_table",
		 &test_basic_ace_table_name,
		 "Test basic ACE table name in basic ACE file" );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstNeutronScatteringDistributionFactory.cpp
//---------------------------------------------------------------------------//
