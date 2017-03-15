//---------------------------------------------------------------------------//
//!
//! \file   tstDagMCModelPropertiesFactory.cpp
//! \author Alex Robinson
//! \brief  DagMC model properties factory class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Geometry_DagMCModelPropertiesFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<const Teuchos::ParameterList> basic_model_raw_properties;
Teuchos::RCP<const Teuchos::ParameterList> advanced_model_raw_properties;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the basic properties file can be parsed
TEUCHOS_UNIT_TEST( DagMCModelPropertiesFactory, createProperties_basic )
{
  std::shared_ptr<const Geometry::DagMCModelProperties> properties;
  
  TEST_NOTHROW( properties = Geometry::DagMCModelPropertiesFactory::createProperties( *basic_model_raw_properties ) );

  TEST_ASSERT( properties->getModelFileName().find( "test_basic_geom.sat" ) < properties->getModelFileName().size() );
  TEST_EQUALITY_CONST( properties->getFacetTolerance(), 1e-3 );
  TEST_ASSERT( !properties->isFastIdLookupUsed() );
  TEST_EQUALITY_CONST( properties->getTerminationCellPropertyName(),
                       "termination.cell" );
  TEST_EQUALITY_CONST( properties->getReflectingSurfacePropertyName(),
                       "reflecting.surface" );
  TEST_EQUALITY_CONST( properties->getMaterialPropertyName(),
                       "material" );
  TEST_EQUALITY_CONST( properties->getDensityPropertyName(),
                       "density" );
  TEST_EQUALITY_CONST( properties->getEstimatorPropertyName(),
                       "estimator" );
  TEST_EQUALITY_CONST( properties->getSurfaceCurrentName(),
                       "surface.current" );
  TEST_EQUALITY_CONST( properties->getSurfaceFluxName(),
                       "surface.flux" );
  TEST_EQUALITY_CONST( properties->getCellPulseHeightName(),
                       "cell.pulse.height" );
  TEST_EQUALITY_CONST( properties->getCellTrackLengthFluxName(),
                       "cell.tl.flux" );
  TEST_EQUALITY_CONST( properties->getCellCollisionFluxName(),
                       "cell.c.flux" );
  TEST_EQUALITY_CONST( properties->getPhotonName(), "p" );
  TEST_EQUALITY_CONST( properties->getNeutronName(), "n" );
  TEST_EQUALITY_CONST( properties->getElectronName(), "e" );
  TEST_EQUALITY_CONST( properties->getAdjointPhotonName(), "p*" );
  TEST_EQUALITY_CONST( properties->getAdjointNeutronName(), "n*" );
  TEST_EQUALITY_CONST( properties->getAdjointElectronName(), "e*" );
}

//---------------------------------------------------------------------------//
// Check that the advanced properties file can be parsed
TEUCHOS_UNIT_TEST( DagMCModelPropertiesFactory, createProperties_advanced )
{
  std::shared_ptr<const Geometry::DagMCModelProperties> properties;
  
  TEST_NOTHROW( properties = Geometry::DagMCModelPropertiesFactory::createProperties( *advanced_model_raw_properties ) );

  TEST_ASSERT( properties->getModelFileName().find( "test_advanced_geom.sat" ) < properties->getModelFileName().size() );
  TEST_EQUALITY_CONST( properties->getFacetTolerance(), 1e-3 );
  TEST_ASSERT( properties->isFastIdLookupUsed() );
  TEST_EQUALITY_CONST( properties->getTerminationCellPropertyName(),
                       "graveyard" );
  TEST_EQUALITY_CONST( properties->getReflectingSurfacePropertyName(),
                       "spec.reflect" );
  TEST_EQUALITY_CONST( properties->getMaterialPropertyName(),
                       "mat" );
  TEST_EQUALITY_CONST( properties->getDensityPropertyName(),
                       "rho" );
  TEST_EQUALITY_CONST( properties->getEstimatorPropertyName(),
                       "tally" );
  TEST_EQUALITY_CONST( properties->getSurfaceCurrentName(),
                       "surf.cur" );
  TEST_EQUALITY_CONST( properties->getSurfaceFluxName(),
                       "surf.flux" );
  TEST_EQUALITY_CONST( properties->getCellPulseHeightName(),
                       "c.pulse" );
  TEST_EQUALITY_CONST( properties->getCellTrackLengthFluxName(),
                       "c.tl.f" );
  TEST_EQUALITY_CONST( properties->getCellCollisionFluxName(),
                       "c.c.f" );
  TEST_EQUALITY_CONST( properties->getPhotonName(), "phot" );
  TEST_EQUALITY_CONST( properties->getNeutronName(), "neut" );
  TEST_EQUALITY_CONST( properties->getElectronName(), "elec" );
  TEST_EQUALITY_CONST( properties->getAdjointPhotonName(), "aphot" );
  TEST_EQUALITY_CONST( properties->getAdjointNeutronName(), "aneut" );
  TEST_EQUALITY_CONST( properties->getAdjointElectronName(), "aelec" );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string basic_xml_file_name, advanced_xml_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_basic_xml_file",
                   &basic_xml_file_name,
                   "Basic model properties xml file name" );
  clp().setOption( "test_advanced_xml_file",
                   &advanced_xml_file_name,
                   "Advanced model properties xml file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Load the model properties files
  basic_model_raw_properties =
    Teuchos::getParametersFromXmlFile( basic_xml_file_name );

  advanced_model_raw_properties =
    Teuchos::getParametersFromXmlFile( advanced_xml_file_name );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDagMCModelPropertiesFactory.cpp
//---------------------------------------------------------------------------//
