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
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardParticleSourceFactory.hpp"
#include "Geometry_DagMCHelpers.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ParticleModeType.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::string test_simple_source_xml_file_name;
std::string test_complex_source_xml_file_name;
std::string test_compound_source_xml_file_name;
std::string test_geometry_file_name;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize DagMC
void initializeDagMC()
{
  // Set up the valid property names
  std::vector<std::string> property_names( 1 );
  property_names[0] = "graveyard";

  Geometry::initializeDagMC( test_geometry_file_name,
			     property_names,
			     1e-3 );

  Geometry::ModuleInterface<moab::DagMC>::initialize();
}

//---------------------------------------------------------------------------//
// Check that a simple source can be constructed from parameter entries
TEUCHOS_UNIT_TEST( ParticleSourceFactory, createSimpleSource )
{
  Teuchos::RCP<Teuchos::ParameterList> source_rep = 
    Teuchos::getParametersFromXmlFile( test_simple_source_xml_file_name );

  std::shared_ptr<MonteCarlo::ParticleSourceFactory> source_factory = 
    MonteCarlo::StandardParticleSourceFactory<moab::DagMC>::getInstance();
  
  std::shared_ptr<MonteCarlo::ParticleSource> source = 
    source_factory->createSource( *source_rep, MonteCarlo::NEUTRON_MODE );

  TEST_ASSERT( source.get() );

  MonteCarlo::ParticleBank bank;

  for( unsigned i = 0; i < 5; ++i )
  {
    source->sampleParticleState( bank, i );
  }

  std::cout << std::endl;
  while( bank.size() > 0 )
  {
    std::cout << bank.top() << std::endl;
    
    bank.pop();
  }						
}

//---------------------------------------------------------------------------//
// Check that a complex source can be constructed from parameter entries
TEUCHOS_UNIT_TEST( ParticleSourceFactory, createComplexSource )
{
  Teuchos::RCP<Teuchos::ParameterList> source_rep = 
    Teuchos::getParametersFromXmlFile( test_complex_source_xml_file_name );

  std::shared_ptr<MonteCarlo::ParticleSourceFactory> source_factory = 
    MonteCarlo::StandardParticleSourceFactory<moab::DagMC>::getInstance();
  
  std::shared_ptr<MonteCarlo::ParticleSource> source = 
    source_factory->createSource( *source_rep, MonteCarlo::NEUTRON_MODE );

  TEST_ASSERT( source.get() );

  MonteCarlo::ParticleBank bank;

  for( unsigned i = 0; i < 5; ++i )
  {
    source->sampleParticleState( bank, i );
  }

  std::cout << std::endl;
  while( bank.size() > 0 )
  {
    std::cout << bank.top() << std::endl;
    
    bank.pop();
  }	
}

//---------------------------------------------------------------------------//
// Check that a compound source can be constructed from parameter entries
TEUCHOS_UNIT_TEST( ParticleSourceFactory, createCompoundSource )
{
  Teuchos::RCP<Teuchos::ParameterList> source_rep = 
    Teuchos::getParametersFromXmlFile( test_compound_source_xml_file_name );

  std::shared_ptr<MonteCarlo::ParticleSourceFactory> source_factory = 
    MonteCarlo::StandardParticleSourceFactory<moab::DagMC>::getInstance();
  
  std::shared_ptr<MonteCarlo::ParticleSource> source = 
    source_factory->createSource( *source_rep, MonteCarlo::NEUTRON_PHOTON_MODE );

  TEST_ASSERT( source.get() );

  MonteCarlo::ParticleBank bank;

  for( unsigned i = 0; i < 5; ++i )
  {
    source->sampleParticleState( bank, i );
  }

  std::cout << std::endl;
  while( bank.size() > 0 )
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
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_simple_source_xml_file",
		 &test_simple_source_xml_file_name,
		 "Test simple source definition xml file name" );

  clp.setOption( "test_complex_source_xml_file",
  		 &test_complex_source_xml_file_name,
  		 "Test complex source definition xml file name" );

  clp.setOption( "test_compound_source_xml_file",
  		 &test_compound_source_xml_file_name,
  		 "Test compound source definition xml file name" );

  clp.setOption( "test_sat_file",
		 &test_geometry_file_name,
		 "Test sat file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();
  
  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Initialize DagMC with the test geometry
  initializeDagMC();

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstParticleSourceFactory.cpp
//---------------------------------------------------------------------------//
