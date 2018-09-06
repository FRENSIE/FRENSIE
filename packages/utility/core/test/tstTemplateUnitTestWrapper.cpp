//---------------------------------------------------------------------------//
//!
//! \file   tstTemplateUnitTestWrapper.cpp
//! \author Alex Robinson
//! \brief  Template unit test wrapper class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// FRENSIE Includes
#include "Utility_TemplateUnitTest.hpp"
#include "Utility_TemplateUnitTestWrapper.hpp"

#define THIS_FILE __FILE__
#define THIS_LINE __LINE__

//---------------------------------------------------------------------------//
// Testing structs
//---------------------------------------------------------------------------//
template<typename... Types>
class TestTemplateUnitTest : public Utility::TemplateUnitTest<Types...>
{

public:

  // Constructor
  TestTemplateUnitTest()
    : Utility::TemplateUnitTest<Types...>( "TestGroup", "TestName" )
  { /* ... */ }

  // Return the file where the unit test object is located
  std::string getFile() const override
  { return THIS_FILE; }

  // Return the line number where the unit test object run impl. was defined
  size_t getLineNumber() const override
  { return THIS_LINE; }

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
// Check that a template unit test wrapper can be constructed
BOOST_AUTO_TEST_CASE( constructor )
{
  Utility::TemplateUnitTestWrapper<TestTemplateUnitTest,false,float,int,std::string> test_wrapper_a;

  BOOST_CHECK_EQUAL( test_wrapper_a.getNumberOfTests(), 3 );

  Utility::TemplateUnitTestWrapper<TestTemplateUnitTest,false,std::tuple<float,int,std::string> > test_wrapper_b;

  BOOST_CHECK_EQUAL( test_wrapper_b.getNumberOfTests(), 3 );

  // Do not expand inner tuples
  Utility::TemplateUnitTestWrapper<TestTemplateUnitTest,false,float,int,std::string,std::tuple<double,unsigned> > test_wrapper_c;

  BOOST_CHECK_EQUAL( test_wrapper_c.getNumberOfTests(), 4 );

  // Expand inner tuples
  Utility::TemplateUnitTestWrapper<TestTemplateUnitTest,true,std::tuple<std::string,float>,std::tuple<std::string,int>,std::tuple<std::string,std::string> > test_wrapper_d;

  BOOST_CHECK_EQUAL( test_wrapper_d.getNumberOfTests(), 3 );

  // Expand inner tuples
  Utility::TemplateUnitTestWrapper<TestTemplateUnitTest,true,std::tuple<std::tuple<std::string,float>,std::tuple<std::string,int>,std::tuple<std::string,std::string> > > test_wrapper_e;

  BOOST_CHECK_EQUAL( test_wrapper_e.getNumberOfTests(), 3 );
}

//---------------------------------------------------------------------------//
// end tstTemplateUnitTestWrapper.cpp
//---------------------------------------------------------------------------//
