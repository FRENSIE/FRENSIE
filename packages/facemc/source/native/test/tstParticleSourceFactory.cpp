//---------------------------------------------------------------------------//
//!
//! \file   tstParticleSourceFactory.cpp
//! \author Alex Robinson
//! \brief  Particle source factory unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "Facemc_ParticleSourceFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::string test_simple_source_xml_file_name;
std::string test_complex_source_xml_file_name;
std::string test_compound_source_xml_file_name;

//---------------------------------------------------------------------------//
// Check that a simple source can be constructed from parameter entries
TEUCHOS_UNIT_TEST( ParticleSourceFactory, createSimpleSource )
{
  Teuchos::RCP<Teuchos::ParameterList> source_rep = 
    Teuchos::getParametersFromXmlFile( test_simple_source_xml_file_name );

  Teuchos::RCP<Facemc::ParticleSource> source = 
    Facemc::ParticleSourceFactory::createSource( source_rep );

  TEST_ASSERT( !source.is_null() );

  Facemc::ParticleBank bank;

  for( unsigned i = 0; i < 5; ++i )
  {
    source->sampleParticleState( bank );
  }

  std::cout << std::endl;
  for( unsigned i = 0; i < bank.size(); ++i )
  {
    std::cout << bank.top() << std::endl;
    
    bank.pop();
  }						
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Utility::OneDDistributionEntryConverterDB::standardInitialization();
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_simple_source_xml_file",
		 &test_simple_source_xml_file_name,
		 "Test simple source definition xml file name" );

  // clp.setOption( "test_complex_source_xml_file",
  // 		 &test_complex_source_xml_file_name,
  // 		 "Test complex source definition xml file name" );

  // clp.setOption( "test_compound_source_xml_file",
  // 		 &test_compound_source_xml_file_name,
  // 		 "Test compound source definition xml file name" );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstParticleSourceFactory.cpp
//---------------------------------------------------------------------------//
