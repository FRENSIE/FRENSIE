//---------------------------------------------------------------------------//
//!
//! \file   tstDataUnitTestWrapper.cpp
//! \author Alex Robinson
//! \brief  Data unit test wrapper tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// FRENSIE Includes
#include "Utility_DataUnitTest.hpp"
#include "Utility_DataUnitTestWrapper.hpp"

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
void createDataTable( Utility::UnitTestDataTable& data_table )
{
  data_table.columns()            << "Input" << "Expected Output";
  data_table.addRow( "float" )    << 0.0f    << 1.0f;
  data_table.addRow( "double" )   << 0.0     << 1.0;
  data_table.addRow( "int" )      << 0       << 1;
  data_table.addRow( "unsigned" ) << 0u      << 1u;
  data_table.addRow( "string" )   << "input" << "output";
}

//---------------------------------------------------------------------------//
// Testing structs
//---------------------------------------------------------------------------//
class TestDataUnitTest : public Utility::DataUnitTest
{

public:

  // Constructor
  TestDataUnitTest( const std::string& data_name,
                    const std::shared_ptr<const Utility::UnitTestDataTable>& data_table )
    : Utility::DataUnitTest( "Test Group", "Test Name", data_name, data_table )
  { /* ... */ }

  // Destructor
  ~TestDataUnitTest()
  { /* ... */ }

  // Return the file where the unit test object is located
  std::string getFile() const override
  { return "tstUnitTest.cpp"; }

  // Return the line number where the unit test object run impl. was defined
  size_t getLineNumber() const override
  { return 0; }

  // Unit test definition
  void runImpl( std::ostream& os,
                bool& success,
                size_t& number_of_checks,
                size_t& number_of_passed_checks,
                size_t& last_checkpoint_line_number ) const override
  {
    success = true;
    number_of_checks = 0;
    number_of_passed_checks = 0;
    last_checkpoint_line_number = 0;
  }
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a DataUnitTestWrapper can be constructed
BOOST_AUTO_TEST_CASE( constructor )
{
  Utility::DataUnitTestWrapper<TestDataUnitTest>
    data_unit_test_wrapper( "Test Table", &createDataTable );

  BOOST_CHECK_EQUAL( data_unit_test_wrapper.getNumberOfTests(), 5 );
}

//---------------------------------------------------------------------------//
// end tstDataUnitTestWrapper.cpp
//---------------------------------------------------------------------------//
