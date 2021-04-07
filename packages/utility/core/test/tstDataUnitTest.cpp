//---------------------------------------------------------------------------//
//!
//! \file   tstDataUnitTest.cpp
//! \author Alex Robinson
//! \brief  Data unit test tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// FRENSIE Includes
#include "Utility_DataUnitTest.hpp"

//---------------------------------------------------------------------------//
// Testing structs
//---------------------------------------------------------------------------//
class TestDataUnitTest : public Utility::DataUnitTest
{

public:

  // Constructor
  TestDataUnitTest( const std::string& group_name,
                    const std::string& test_name,
                    const std::string& data_name,
                    const std::shared_ptr<const Utility::UnitTestDataTable>& data_table )
    : Utility::DataUnitTest( group_name, test_name, data_name, data_table )
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

struct DataTableFixture
{
  DataTableFixture()
  {
    if( !data_table )
    {
      std::shared_ptr<Utility::UnitTestDataTable> tmp_data_table(
                              new Utility::UnitTestDataTable( "test_table" ) );

      tmp_data_table->columns()          << "Input" << "Expected Output";
      tmp_data_table->addRow( "float" )  << 0.0f    << 1.0f;
      tmp_data_table->addRow( "int" )    << 0       << 1;
      tmp_data_table->addRow( "string" ) << "in"    << "out";

      data_table = tmp_data_table;
    }
  }

  static std::shared_ptr<const Utility::UnitTestDataTable> data_table;
};

std::shared_ptr<const Utility::UnitTestDataTable> DataTableFixture::data_table;

// Register the DataTableFixture with the test suite
BOOST_FIXTURE_TEST_SUITE( DataUnitTest, DataTableFixture )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a data unit test can be constructed
BOOST_AUTO_TEST_CASE( constructor )
{
  std::unique_ptr<Utility::DataUnitTest> unit_test( new TestDataUnitTest( "TestGroup", "TestName", "float", data_table ) );

  BOOST_CHECK_EQUAL( unit_test->getGroupName(), "TestGroup" );
  BOOST_CHECK_EQUAL( unit_test->getTestName(), "TestName" );
  BOOST_CHECK_EQUAL( unit_test->getDataName(), "float" );
  BOOST_CHECK_EQUAL( unit_test->getDataTableElement( "Input" ).toFloat(), 0.0f );
  BOOST_CHECK_EQUAL( unit_test->getDataTableElement( "Expected Output" ).toFloat(), 1.0f );

  unit_test.reset( new TestDataUnitTest( "TestGroup", "TestName", "int", data_table ) );

  BOOST_CHECK_EQUAL( unit_test->getGroupName(), "TestGroup" );
  BOOST_CHECK_EQUAL( unit_test->getTestName(), "TestName" );
  BOOST_CHECK_EQUAL( unit_test->getDataName(), "int" );
  BOOST_CHECK_EQUAL( unit_test->getDataTableElement( "Input" ).toInt(), 0 );
  BOOST_CHECK_EQUAL( unit_test->getDataTableElement( "Expected Output" ).toInt(), 1 );

  unit_test.reset( new TestDataUnitTest( "TestGroup", "TestName", "string", data_table ) );

  BOOST_CHECK_EQUAL( unit_test->getGroupName(), "TestGroup" );
  BOOST_CHECK_EQUAL( unit_test->getTestName(), "TestName" );
  BOOST_CHECK_EQUAL( unit_test->getDataName(), "string" );
  BOOST_CHECK_EQUAL( unit_test->getDataTableElement( "Input" ).toString(), "in" );
  BOOST_CHECK_EQUAL( unit_test->getDataTableElement( "Expected Output" ).toString(), "out" );

  unit_test.reset( new TestDataUnitTest( "TestGroup", "TestName", "dummy", data_table ) );

  BOOST_CHECK_THROW( unit_test->getDataTableElement( "Input" ),
                     Utility::BadUnitTestDataTable );
  BOOST_CHECK_THROW( unit_test->getDataTableElement( "Expected Output" ),
                     Utility::BadUnitTestDataTable );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// end tstDataUnitTest.cpp
//---------------------------------------------------------------------------//
