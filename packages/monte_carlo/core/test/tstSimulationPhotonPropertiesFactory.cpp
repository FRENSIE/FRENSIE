//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationPhotonPropertiesFactory.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation photon properties factory unit tests
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
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "MonteCarlo_SimulationPhotonPropertiesFactory.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::ParameterList properties;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the properties can be parsed and set
TEUCHOS_UNIT_TEST( SimulationPhotonPropertiesFactory,
		   initializeSimulationPhotonProperties )
{
  Teuchos::ParameterList photon_properties = 
      properties.get<Teuchos::ParameterList>( "Photon Properties" );

  MonteCarlo::SimulationPhotonPropertiesFactory::initializeSimulationPhotonProperties( 
						photon_properties );

  TEST_EQUALITY_CONST( MonteCarlo::SimulationPhotonProperties::getMinPhotonEnergy(),
		       1e-2 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationPhotonProperties::getMaxPhotonEnergy(),
		       10.0 );
  TEST_EQUALITY_CONST( 
	       MonteCarlo::SimulationPhotonProperties::getKahnSamplingCutoffEnergy(),
	       2.5 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationPhotonProperties::getNumberOfPhotonHashGridBins(),
		       500 );
  TEST_EQUALITY_CONST( 
	       MonteCarlo::SimulationPhotonProperties::getIncoherentModelType(),
	       MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL );
  TEST_ASSERT( !MonteCarlo::SimulationPhotonProperties::isAtomicRelaxationModeOn() );
  TEST_ASSERT( MonteCarlo::SimulationPhotonProperties::isDetailedPairProductionModeOn() );
  TEST_ASSERT( MonteCarlo::SimulationPhotonProperties::isPhotonuclearInteractionModeOn() );
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
// end tstSimulationPhotonPropertiesFactory.cpp
//---------------------------------------------------------------------------//
