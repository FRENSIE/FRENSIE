//---------------------------------------------------------------------------//
//!
//! \file   tstModuleInterface.cpp
//! \author Alex Robinson
//! \brief  Source module interface unit tests.
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
#include "MonteCarlo_SourceModuleInterface_Native.hpp"
#include "Geometry_DagMCHelpers.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::string test_source_xml_file_name;
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
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a particle state can be sampled
TEUCHOS_UNIT_TEST( ModuleInterface, getParticleState )
{
  typedef MonteCarlo::SourceModuleInterface<MonteCarlo::ParticleSource> SMI;

  MonteCarlo::ParticleBank bank;

  SMI::sampleParticleState( bank );

  TEST_ASSERT( bank.size() > 0 );
  TEST_ASSERT( !bank.top().is_null() );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Utility::OneDDistributionEntryConverterDB::standardInitialization();
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_source_xml_file",
		 &test_source_xml_file_name,
		 "Test source definition xml file name" );

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

  // Initialize the source handler
  Teuchos::RCP<Teuchos::ParameterList> source_rep = 
    Teuchos::getParametersFromXmlFile( test_source_xml_file_name );

  Teuchos::RCP<MonteCarlo::ParticleSourceFactory> source_factory = 
    MonteCarlo::StandardParticleSourceFactory<moab::DagMC>::getInstance();
  
  Teuchos::RCP<MonteCarlo::ParticleSource> source = 
    source_factory->createSource( *source_rep );

  setSourceHandlerInstance( source );

  // Run the unit tests
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
// end tstModuleInterface.cpp
//---------------------------------------------------------------------------//
