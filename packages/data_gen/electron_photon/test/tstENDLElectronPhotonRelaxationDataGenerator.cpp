//---------------------------------------------------------------------------//
//!
//! \file   tstENDLElectronPhotonRelaxationDataGenerator.cpp
//! \author Alex Robinson
//! \brief  ENDL electron-photon-relaxation data generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "DataGen_ENDLElectronPhotonRelaxationDataGenerator.hpp"
#include "Data_ElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Data::ENDLDataContainer>
  h_endl_data_container, c_endl_data_container;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a data generator can be constructed
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   basic_constructor )
{
  
}

//---------------------------------------------------------------------------//
// Check that a data generator can be constructed
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator, constructor )
{

}

//---------------------------------------------------------------------------//
// Check that the default grid convergence tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setDefaultPhotonGridConvergenceTolerance )
{

}

//---------------------------------------------------------------------------//
// Check that the default grid absolute difference tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setDefaultPhotonGridAbsoluteDifferenceTolerance )
{

}

//---------------------------------------------------------------------------//
// Check that the default grid distance tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setDefaultPhotonGridDistanceTolerance )
{

}

//---------------------------------------------------------------------------//
// Check that the default grid convergence tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setDefaultElectronGridConvergenceTolerance )
{

}

//---------------------------------------------------------------------------//
// Check that the default grid absolute difference tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setDefaultElectronGridAbsoluteDifferenceTolerance )
{

}

//---------------------------------------------------------------------------//
// Check that the default grid distance tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setDefaultElectronGridDistanceTolerance )
{

}

//---------------------------------------------------------------------------//
// Check that the occupation number evaluation tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setOccupationNumberEvaluationTolerance )
{

}

//---------------------------------------------------------------------------//
// Check that the incoherent evaluation tolerance can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setSubshellIncoherentEvaluationTolerance )
{

}

//---------------------------------------------------------------------------//
// Check that the photon threshold energy nudge factor can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setPhotonThresholdEnergyNudgeFactor )
{

}

//---------------------------------------------------------------------------//
// Check that the electron total elastic integrated cross section mode can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setElectronTotalElasticIntegratedCrossSectionMode )
{

}

//---------------------------------------------------------------------------//
// Check that the cutoff angle cosine can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setCutoffAngleCosine )
{

}

//---------------------------------------------------------------------------//
// Check that the number of moment preserving angles can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setNumberOfMomentPreservingAngles )
{

}

//---------------------------------------------------------------------------//
// Check that the cutoff angle cosine can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setTabularEvaluationTolerance )
{

}

//---------------------------------------------------------------------------//
// Check that the electron TwoDInterpPolicy can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setElectronTwoDInterpPolicy )
{

}

//---------------------------------------------------------------------------//
// Check that the electron TwoDGridPolicy can be set
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   setElectronTwoDGridPolicy )
{

}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   populateEPRDataContainer_h_lin )
{

}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   populateEPRDataContainer_h )
{

}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   repopulateMomentPreservingData_h )
{

}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
FRENSIE_UNIT_TEST( ENDLElectronPhotonRelaxationDataGenerator,
                   repopulateElectronElasticData_h )
{

}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_h_endl_file_name, test_c_endl_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h_endl_file",
                                        test_h_endl_file_name, "",
                                        "Test ENDL file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_c_endl_file",
                                        test_c_endl_file_name, "",
                                        "Test ENDL file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the endl data container for hydrogen
  h_endl_data_container.reset(
                        new Data::ENDLDataContainer( test_h_endl_file_name ) );
  
  c_endl_data_container.reset(
                        new Data::ENDLDataContainer( test_c_endl_file_name ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstENDLElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
