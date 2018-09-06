//---------------------------------------------------------------------------//
//!
//! \file   tstUnitTest.cpp
//! \author Alex Robinson
//! \brief  Unit test tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// FRENSIE Includes
#include "Utility_UnitTest.hpp"

//---------------------------------------------------------------------------//
// Testing structs
//---------------------------------------------------------------------------//
class TestUnitTest : public Utility::UnitTest
{

public:

  // Constructor
  TestUnitTest( const std::string& group_name,
                const std::string& test_name,
                const std::string& data_name )
    : Utility::UnitTest( group_name, test_name, data_name )
  { /* ... */ }

  // Destructor
  ~TestUnitTest()
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
// Check that a unit test can be constructed
BOOST_AUTO_TEST_CASE( constructor )
{
  std::unique_ptr<Utility::UnitTest>
    unit_test( new TestUnitTest( "TestGroup", "TestName", "" ) );

  BOOST_CHECK_EQUAL( unit_test->getGroupName(), "TestGroup" );
  BOOST_CHECK_EQUAL( unit_test->getTestName(), "TestName" );
  BOOST_CHECK_EQUAL( unit_test->getDataName(), "" );
  BOOST_CHECK_EQUAL( unit_test->getCombinedGroupTestName(), "TestGroup/TestName" );
  BOOST_CHECK_EQUAL( unit_test->getFullName(), "TestGroup/TestName" );
  BOOST_CHECK_EQUAL( unit_test->getCreationOrderIndex(), 0 );

  unit_test.reset( new TestUnitTest( "TestGroup", "TestName", "TestData" ) );

  BOOST_CHECK_EQUAL( unit_test->getGroupName(), "TestGroup" );
  BOOST_CHECK_EQUAL( unit_test->getTestName(), "TestName" );
  BOOST_CHECK_EQUAL( unit_test->getDataName(), "TestData" );
  BOOST_CHECK_EQUAL( unit_test->getCombinedGroupTestName(), "TestGroup/TestName" );
  BOOST_CHECK_EQUAL( unit_test->getFullName(), "TestGroup/TestName:TestData" );
  BOOST_CHECK_EQUAL( unit_test->getCreationOrderIndex(), 1 );
}

//---------------------------------------------------------------------------//
// tstUnitTest.cpp
//---------------------------------------------------------------------------//
