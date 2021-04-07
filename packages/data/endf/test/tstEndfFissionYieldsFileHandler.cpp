//---------------------------------------------------------------------------//
//!
//! \file   tstEndfFissionYieldsFileHandler.cpp
//! \author Alex Bennett
//! \brief  ENDF Fission Yields File Handler unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <memory>

// FRENSIE Includes
#include "Data_ENDFFissionYieldsFileHandler.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::unique_ptr<Data::ENDFFissionYieldsFileHandler> file_handler;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check read ENDF Fission Yields Header
FRENSIE_UNIT_TEST( EndfFissionYieldsFileHandler, getZaid )
{
  FRENSIE_CHECK_EQUAL( file_handler->getZaid(), 92235 );
}

FRENSIE_UNIT_TEST( EndfFissionYieldsFileHandler, getEnergyIndependentYields )
{
    FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getEnergyIndependentYields()[0], 0.0253 , 1e-15 )
    FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getEnergyIndependentYields()[1], 0.5e6 , 1e-15 )
    FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getEnergyIndependentYields()[2], 14e6 , 1e-15 )
}

FRENSIE_UNIT_TEST( EndfFissionYieldsFileHandler, getZaidFissionProductsIndependentYields )
{
     // Test Array Length
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsIndependentYields()[0].size(), 998);
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsIndependentYields()[1].size(), 1016);
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsIndependentYields()[2].size(), 1170);

     // Test First and Last Zaids
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsIndependentYields()[0].front(), 23066);
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsIndependentYields()[0].back(), 69172);
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsIndependentYields()[1].front(), 23066);
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsIndependentYields()[1].back(), 69172);
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsIndependentYields()[2].front(), 23066);
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsIndependentYields()[2].back(), 1071172);
}

FRENSIE_UNIT_TEST( EndfFissionYieldsFileHandler, getMetaStateFissionProductsIndependentYields )
{
     // Test Array Length
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsIndependentYields()[0].size(), 998);
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsIndependentYields()[1].size(), 1016);
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsIndependentYields()[2].size(), 1170);

     // Test First and Last Zaids
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsIndependentYields()[0].front(), 0);
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsIndependentYields()[0].back(),  0);
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsIndependentYields()[1].front(), 0);
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsIndependentYields()[1].back(),  0);
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsIndependentYields()[2].front(), 0);
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsIndependentYields()[2].back(),  1);
}

FRENSIE_UNIT_TEST( EndfFissionYieldsFileHandler, getYieldFissionProductsIndependentYields )
{
     // Test Array Length
     FRENSIE_CHECK_EQUAL(file_handler->getYieldFissionProductsIndependentYields()[0].size(), 998);
     FRENSIE_CHECK_EQUAL(file_handler->getYieldFissionProductsIndependentYields()[1].size(), 1016);
     FRENSIE_CHECK_EQUAL(file_handler->getYieldFissionProductsIndependentYields()[2].size(), 1170);

     // Test First and Last Yields
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getYieldFissionProductsIndependentYields()[0].front(),2.05032e-19,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getYieldFissionProductsIndependentYields()[0].back(), 1.67988e-14,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getYieldFissionProductsIndependentYields()[1].front(),4.48456e-18,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getYieldFissionProductsIndependentYields()[1].back(), 1.12999e-14,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getYieldFissionProductsIndependentYields()[2].front(),3.32530e-13,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getYieldFissionProductsIndependentYields()[2].back(), 1.53983e-13,1e-15);
}

FRENSIE_UNIT_TEST( EndfFissionYieldsFileHandler, getStdYieldFissionProductsIndependentYields )
{
     // Test Array Length
     FRENSIE_CHECK_EQUAL(file_handler->getStdYieldFissionProductsIndependentYields()[0].size(), 998);
     FRENSIE_CHECK_EQUAL(file_handler->getStdYieldFissionProductsIndependentYields()[1].size(), 1016);
     FRENSIE_CHECK_EQUAL(file_handler->getStdYieldFissionProductsIndependentYields()[2].size(), 1170);

     // Test First and Last Standard Deviation of the Yield
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getStdYieldFissionProductsIndependentYields()[0].front(),1.31220e-19,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getStdYieldFissionProductsIndependentYields()[0].back(), 1.07512e-14,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getStdYieldFissionProductsIndependentYields()[1].front(),2.87012e-18,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getStdYieldFissionProductsIndependentYields()[1].back(), 7.23194e-15,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getStdYieldFissionProductsIndependentYields()[2].front(),2.12819e-13,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getStdYieldFissionProductsIndependentYields()[2].back(), 9.85488e-14,1e-15);
}

FRENSIE_UNIT_TEST( EndfFissionYieldsFileHandler, getEnergyCumulativeYields )
{
    FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getEnergyCumulativeYields()[0], 0.0253 , 1e-15 )
    FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getEnergyCumulativeYields()[1], 0.5e6 , 1e-15 )
    FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getEnergyCumulativeYields()[2], 14e6 , 1e-15 )
}

FRENSIE_UNIT_TEST( EndfFissionYieldsFileHandler, getZaidFissionProductsCumulativeYields )
{
     // Test Array Length
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsCumulativeYields()[0].size(), 1038);
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsCumulativeYields()[1].size(), 1050);
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsCumulativeYields()[2].size(), 1166);

     // Test First and Last Zaids
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsCumulativeYields()[0].front(), 23066);
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsCumulativeYields()[0].back(),  70172);
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsCumulativeYields()[1].front(), 23066);
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsCumulativeYields()[1].back(),  70172);
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsCumulativeYields()[2].front(), 23066);
     FRENSIE_CHECK_EQUAL(file_handler->getZaidFissionProductsCumulativeYields()[2].back(),  1071172);
}

FRENSIE_UNIT_TEST( EndfFissionYieldsFileHandler, getMetaStateFissionProductsCumulativeYields )
{
     // Test Array Length
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsCumulativeYields()[0].size(), 1038);
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsCumulativeYields()[1].size(), 1050);
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsCumulativeYields()[2].size(), 1166);

     // Test First and Last Zaids
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsCumulativeYields()[0].front(), 0);
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsCumulativeYields()[0].back(),  0);
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsCumulativeYields()[1].front(), 0);
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsCumulativeYields()[1].back(),  0);
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsCumulativeYields()[2].front(), 0);
     FRENSIE_CHECK_EQUAL(file_handler->getMetaStateFissionProductsCumulativeYields()[2].back(),  1);
}

FRENSIE_UNIT_TEST( EndfFissionYieldsFileHandler, getYieldFissionProductsCumulativeYields )
{
     // Test Array Length
     FRENSIE_CHECK_EQUAL(file_handler->getYieldFissionProductsCumulativeYields()[0].size(), 1038);
     FRENSIE_CHECK_EQUAL(file_handler->getYieldFissionProductsCumulativeYields()[1].size(), 1050);
     FRENSIE_CHECK_EQUAL(file_handler->getYieldFissionProductsCumulativeYields()[2].size(), 1166);

     // Test First and Last Yields
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getYieldFissionProductsCumulativeYields()[0].front(),2.05032e-19,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getYieldFissionProductsCumulativeYields()[0].back(), 7.68946e-12,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getYieldFissionProductsCumulativeYields()[1].front(),4.48456e-18,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getYieldFissionProductsCumulativeYields()[1].back(), 1.91998e-11,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getYieldFissionProductsCumulativeYields()[2].front(),3.32530e-13,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getYieldFissionProductsCumulativeYields()[2].back(), 1.53983e-13,1e-15);
}

FRENSIE_UNIT_TEST( EndfFissionYieldsFileHandler, getStdYieldFissionProductsCumulativeYields )
{
     // Test Array Length
     FRENSIE_CHECK_EQUAL(file_handler->getStdYieldFissionProductsCumulativeYields()[0].size(), 1038);
     FRENSIE_CHECK_EQUAL(file_handler->getStdYieldFissionProductsCumulativeYields()[1].size(), 1050);
     FRENSIE_CHECK_EQUAL(file_handler->getStdYieldFissionProductsCumulativeYields()[2].size(), 1166);

     // Test First and Last Standard Deviation of the Yield
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getStdYieldFissionProductsCumulativeYields()[0].front(),1.31220e-19,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getStdYieldFissionProductsCumulativeYields()[0].back(), 2.46063e-12,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getStdYieldFissionProductsCumulativeYields()[1].front(),2.87012e-18,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getStdYieldFissionProductsCumulativeYields()[1].back(), 4.41596e-12,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getStdYieldFissionProductsCumulativeYields()[2].front(),2.12819e-13,1e-15);
     FRENSIE_CHECK_FLOATING_EQUALITY(file_handler->getStdYieldFissionProductsCumulativeYields()[2].back(), 9.85488e-14,1e-15);
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_endf_file_name;
unsigned zaid;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_endf_file",
                                        test_endf_file_name, "",
                                        "Test file for checking ENDF fission yields helpers." );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "zaid_name",
                                        zaid, 0u,
                                        "Expected zaid name in test file." );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  file_handler.reset( new Data::ENDFFissionYieldsFileHandler( test_endf_file_name.c_str(), zaid ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstEndfFissionYieldsHelpers.cpp
//---------------------------------------------------------------------------//
