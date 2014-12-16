//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationPropertiesFactory.cpp
//! \author Alex Robinson
//! \brief  Simulation properties factory unit tests
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
#include "MonteCarlo_SimulationProperties.hpp"
#include "MonteCarlo_SimulationPropertiesFactory.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::ParameterList properties;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the properties can be parsed and set
TEUCHOS_UNIT_TEST( SimulationPropertiesFactory,
		   initializeSimulationProperties )
{
  MonteCarlo::SimulationPropertiesFactory::initializeSimulationProperties( 
								  properties );

  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getParticleMode(),
		       MonteCarlo::NEUTRON_PHOTON_MODE );
  TEST_EQUALITY_CONST(MonteCarlo::SimulationProperties::getNumberOfHistories(),
		      10 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getFreeGasThreshold(),
		       600.0 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getMinNeutronEnergy(),
		       1e-2 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getMaxNeutronEnergy(),
		       10.0 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getMinPhotonEnergy(),
		       1e-2 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getMaxPhotonEnergy(),
		       10.0 );
  TEST_EQUALITY_CONST(MonteCarlo::SimulationProperties::getMinElectronEnergy(),
		      1e-2 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getMaxPhotonEnergy(),
		       10.0 );
  TEST_ASSERT( MonteCarlo::SimulationProperties::isImplicitCaptureModeOn() );
  TEST_ASSERT( !MonteCarlo::SimulationProperties::isPhotonDopplerBroadeningModeOn() );
  TEST_ASSERT( !MonteCarlo::SimulationProperties::isAtomicRelaxationModeOn() );
  TEST_ASSERT( MonteCarlo::SimulationProperties::isDetailedPairProductionModeOn() );
  TEST_ASSERT( MonteCarlo::SimulationProperties::isPhotonuclearInteractionModeOn() );
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
// end tstSimulationPropertiesFactory.cpp
//---------------------------------------------------------------------------//
