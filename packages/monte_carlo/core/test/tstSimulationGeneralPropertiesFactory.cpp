//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationGeneralPropertiesFactory.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation general properties factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "MonteCarlo_SimulationGeneralPropertiesFactory.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::ParameterList properties;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the properties can be parsed and set
TEUCHOS_UNIT_TEST( SimulationGeneralPropertiesFactory,
		   initializeSimulationGeneralProperties )
{

  Teuchos::ParameterList general_properties = 
      properties.get<Teuchos::ParameterList>( "General Properties" );

  MonteCarlo::SimulationGeneralPropertiesFactory::initializeSimulationGeneralProperties( 
						general_properties );
  
  TEST_EQUALITY_CONST( MonteCarlo::SimulationGeneralProperties::getParticleMode(),
		       MonteCarlo::NEUTRON_PHOTON_MODE );
  TEST_EQUALITY_CONST(MonteCarlo::SimulationGeneralProperties::getNumberOfHistories(),
		      10 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationGeneralProperties::getSurfaceFluxEstimatorAngleCosineCutoff(),
		       0.1 );
  TEST_ASSERT( !MonteCarlo::SimulationGeneralProperties::displayWarnings() );
  TEST_ASSERT( MonteCarlo::SimulationGeneralProperties::isImplicitCaptureModeOn() );	
  TEST_EQUALITY_CONST( MonteCarlo::SimulationGeneralProperties::getNumberOfBatchesPerProcessor(),
	  25 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_properties_xml_file_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_properties_xml_file",
		 &test_properties_xml_file_name,
		 "Test properties.xml file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Read in the xml file storing the simulation properties
  Teuchos::updateParametersFromXmlFile( test_properties_xml_file_name,
				       Teuchos::inoutArg( properties ) );

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
// end tstSimulationGeneralPropertiesFactory.cpp
//---------------------------------------------------------------------------//
