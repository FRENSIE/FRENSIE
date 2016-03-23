//---------------------------------------------------------------------------//
//!
//! \file   tstParticleSourceFactory_DagMC.cpp
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
#include "MonteCarlo_ParticleModeType.hpp"
#include "Geometry_DagMCInstanceFactory.hpp"
#include "Geometry_ModuleInterface_DagMC.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"
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

  typedef Geometry::ModuleInterface<Geometry::DagMC> GMI;

  std::shared_ptr<MonteCarlo::ParticleSourceFactory> source_factory = 
    MonteCarlo::StandardParticleSourceFactory<GMI>::getInstance();
  
  std::shared_ptr<MonteCarlo::ParticleSource> source; 

  TEST_NOTHROW( source = source_factory->createSource( *source_rep, 
                                                       MonteCarlo::PHOTON_MODE,
                                                       std::cerr ) );

  TEST_ASSERT( source.get() );

  if( source.get() )
  {
    MonteCarlo::ParticleBank bank;
    
    for( unsigned i = 0; i < 3; ++i )
    {
      source->sampleParticleState( bank, i );
    }

    TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
    TEST_EQUALITY_CONST( bank.top().getXPosition(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getYPosition(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getZPosition(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getXDirection(), 0.0 );
    TEST_EQUALITY_CONST( bank.top().getYDirection(), 0.0 );
    TEST_EQUALITY_CONST( bank.top().getZDirection(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getEnergy(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getTime(), 0.0 );
    TEST_EQUALITY_CONST( bank.top().getWeight(), 1.0 );
    
    bank.pop();
    
    TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
    TEST_EQUALITY_CONST( bank.top().getXPosition(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getYPosition(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getZPosition(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getXDirection(), 0.0 );
    TEST_EQUALITY_CONST( bank.top().getYDirection(), 0.0 );
    TEST_EQUALITY_CONST( bank.top().getZDirection(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getEnergy(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getTime(), 0.0 );
    
    bank.pop();
  
    TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
    TEST_EQUALITY_CONST( bank.top().getXPosition(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getYPosition(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getZPosition(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getXDirection(), 0.0 );
    TEST_EQUALITY_CONST( bank.top().getYDirection(), 0.0 );
    TEST_EQUALITY_CONST( bank.top().getZDirection(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getEnergy(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getTime(), 0.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a complex source can be constructed from parameter entries
TEUCHOS_UNIT_TEST( ParticleSourceFactory, createComplexSource )
{
  Teuchos::RCP<Teuchos::ParameterList> source_rep = 
    Teuchos::getParametersFromXmlFile( test_complex_source_xml_file_name );

  typedef Geometry::ModuleInterface<Geometry::DagMC> GMI;
  
  std::shared_ptr<MonteCarlo::ParticleSourceFactory> source_factory = 
    MonteCarlo::StandardParticleSourceFactory<GMI>::getInstance();
  
  std::shared_ptr<MonteCarlo::ParticleSource> source; 
  TEST_NOTHROW( source = source_factory->createSource(*source_rep, 
                                                      MonteCarlo::NEUTRON_MODE,
                                                      std::cerr ) );

  TEST_ASSERT( source.get() );

  if( source.get() )
  {
    MonteCarlo::ParticleBank bank;

    for( unsigned i = 0; i < 3; ++i )
    {
      source->sampleParticleState( bank, i );
    }

    TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
    TEST_COMPARE( bank.top().getXPosition(), >=, 0.0 );
    TEST_COMPARE( bank.top().getXPosition(), <=, 1.0 );
    TEST_COMPARE( bank.top().getYPosition(), >=, 0.0 );
    TEST_COMPARE( bank.top().getYPosition(), <=, 1.0 );
    TEST_COMPARE( bank.top().getZPosition(), >=, 0.0 );
    TEST_COMPARE( bank.top().getZPosition(), <=, 1.0 );
    TEST_COMPARE( bank.top().getXDirection(), >=, -1.0 );
    TEST_COMPARE( bank.top().getXDirection(), <=, 1.0 );
    TEST_COMPARE( bank.top().getYDirection(), >=, -1.0 );
    TEST_COMPARE( bank.top().getYDirection(), <=, 1.0 );
    TEST_COMPARE( bank.top().getZDirection(), >=, -1.0 );
    TEST_COMPARE( bank.top().getZDirection(), <=, 1.0 );
    TEST_COMPARE( bank.top().getEnergy(), >=, 1e-5 );
    TEST_COMPARE( bank.top().getEnergy(), <=, 1.0 );
    TEST_COMPARE( bank.top().getTime(), >=, 0.0 );
    TEST_COMPARE( bank.top().getTime(), <=, 10.0 );
    TEST_COMPARE( bank.top().getWeight(), !=, 1.0 );
    
    bank.pop();
    
    TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
    TEST_COMPARE( bank.top().getXPosition(), >=, 0.0 );
    TEST_COMPARE( bank.top().getXPosition(), <=, 1.0 );
    TEST_COMPARE( bank.top().getYPosition(), >=, 0.0 );
    TEST_COMPARE( bank.top().getYPosition(), <=, 1.0 );
    TEST_COMPARE( bank.top().getZPosition(), >=, 0.0 );
    TEST_COMPARE( bank.top().getZPosition(), <=, 1.0 );
    TEST_COMPARE( bank.top().getXDirection(), >=, -1.0 );
    TEST_COMPARE( bank.top().getXDirection(), <=, 1.0 );
    TEST_COMPARE( bank.top().getYDirection(), >=, -1.0 );
    TEST_COMPARE( bank.top().getYDirection(), <=, 1.0 );
    TEST_COMPARE( bank.top().getZDirection(), >=, -1.0 );
    TEST_COMPARE( bank.top().getZDirection(), <=, 1.0 );
    TEST_COMPARE( bank.top().getEnergy(), >=, 1e-5 );
    TEST_COMPARE( bank.top().getEnergy(), <=, 1.0 );
    TEST_COMPARE( bank.top().getTime(), >=, 0.0 );
    TEST_COMPARE( bank.top().getTime(), <=, 10.0 );
    TEST_COMPARE( bank.top().getWeight(), !=, 1.0 );
    
    bank.pop();
    
    TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
    TEST_COMPARE( bank.top().getXPosition(), >=, 0.0 );
    TEST_COMPARE( bank.top().getXPosition(), <=, 1.0 );
    TEST_COMPARE( bank.top().getYPosition(), >=, 0.0 );
    TEST_COMPARE( bank.top().getYPosition(), <=, 1.0 );
    TEST_COMPARE( bank.top().getZPosition(), >=, 0.0 );
    TEST_COMPARE( bank.top().getZPosition(), <=, 1.0 );
    TEST_COMPARE( bank.top().getXDirection(), >=, -1.0 );
    TEST_COMPARE( bank.top().getXDirection(), <=, 1.0 );
    TEST_COMPARE( bank.top().getYDirection(), >=, -1.0 );
    TEST_COMPARE( bank.top().getYDirection(), <=, 1.0 );
    TEST_COMPARE( bank.top().getZDirection(), >=, -1.0 );
    TEST_COMPARE( bank.top().getZDirection(), <=, 1.0 );
    TEST_COMPARE( bank.top().getEnergy(), >=, 1e-5 );
    TEST_COMPARE( bank.top().getEnergy(), <=, 1.0 );
    TEST_COMPARE( bank.top().getTime(), >=, 0.0 );
    TEST_COMPARE( bank.top().getTime(), <=, 10.0 );
    TEST_COMPARE( bank.top().getWeight(), !=, 1.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a compound source can be constructed from parameter entries
TEUCHOS_UNIT_TEST( ParticleSourceFactory, createCompoundSource )
{
  Teuchos::RCP<Teuchos::ParameterList> source_rep = 
    Teuchos::getParametersFromXmlFile( test_compound_source_xml_file_name );

  typedef Geometry::ModuleInterface<Geometry::DagMC> GMI;

  std::shared_ptr<MonteCarlo::ParticleSourceFactory> source_factory = 
    MonteCarlo::StandardParticleSourceFactory<GMI>::getInstance();
  
  std::shared_ptr<MonteCarlo::ParticleSource> source;
  TEST_NOTHROW( source = source_factory->createSource( 
                                               *source_rep, 
                                               MonteCarlo::NEUTRON_PHOTON_MODE,
                                               std::cerr ) );

  TEST_ASSERT( source.get() );

  if( source.get() )
  {
    MonteCarlo::ParticleBank bank;
    
    std::vector<double> fake_stream( 1 );
    fake_stream[0] = 0.199;
    
    Utility::RandomNumberGenerator::setFakeStream( fake_stream );
    
    source->sampleParticleState( bank, 0 );
    
    TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
    TEST_EQUALITY_CONST( bank.top().getXPosition(), 0.0 );
    TEST_EQUALITY_CONST( bank.top().getYPosition(), 0.0 );
    TEST_EQUALITY_CONST( bank.top().getZPosition(), 0.0 );
    TEST_EQUALITY_CONST( bank.top().getEnergy(), 1.0 );
    TEST_EQUALITY_CONST( bank.top().getTime(), 0.0 );
    
    bank.pop();
    
    fake_stream[0] = 0.21;
    
    Utility::RandomNumberGenerator::setFakeStream( fake_stream );
    
    source->sampleParticleState( bank, 1 );
    
    TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
    TEST_EQUALITY_CONST( bank.top().getXPosition(), 0.0 );
    TEST_EQUALITY_CONST( bank.top().getYPosition(), 0.0 );
    TEST_EQUALITY_CONST( bank.top().getZPosition(), 0.0 );
    TEST_EQUALITY_CONST( bank.top().getEnergy(), 2.0 );
    TEST_EQUALITY_CONST( bank.top().getTime(), 0.0 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  std::string test_geometry_xml_file_name;

  clp.setOption( "test_simple_source_xml_file",
		 &test_simple_source_xml_file_name,
		 "Test simple source definition xml file name" );

  clp.setOption( "test_complex_source_xml_file",
  		 &test_complex_source_xml_file_name,
  		 "Test complex source definition xml file name" );

  clp.setOption( "test_compound_source_xml_file",
  		 &test_compound_source_xml_file_name,
  		 "Test compound source definition xml file name" );

  clp.setOption( "test_geom_xml_file",
		 &test_geometry_xml_file_name,
                 "Test DagMC geom xml file name" );

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
  
  // Initialize DagMC
  Teuchos::RCP<Teuchos::ParameterList> geom_rep = 
    Teuchos::getParametersFromXmlFile( test_geometry_xml_file_name );

  Geometry::DagMCInstanceFactory::initializeDagMC( *geom_rep );

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
// end tstParticleSourceFactory_DagMC.cpp
//---------------------------------------------------------------------------//
