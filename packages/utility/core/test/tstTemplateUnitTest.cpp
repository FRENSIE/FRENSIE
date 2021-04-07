//---------------------------------------------------------------------------//
//!
//! \file   tstTemplateUnitTest.cpp
//! \author Alex Robinson
//! \brief  Template unit test class tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// FRENSIE Includes
#include "Utility_TemplateUnitTest.hpp"

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
  TestTemplateUnitTest( const std::string& group_name,
                        const std::string& test_name )
    : Utility::TemplateUnitTest<Types...>( group_name, test_name )
  { /* ... */ }

  // Constructor with template parameter name
  TestTemplateUnitTest( const std::string& group_name,
                        const std::string& test_name,
                        const std::string& template_param_pack_name )
    : Utility::TemplateUnitTest<Types...>( group_name, test_name, template_param_pack_name )
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
// Tests.
//---------------------------------------------------------------------------//
// Check that a template unit test can be constructed
BOOST_AUTO_TEST_CASE( constructor )
{
  // Parameter pack
  std::unique_ptr<Utility::UnitTest> unit_test(
     new TestTemplateUnitTest<float,int,std::string>( "Test Group", "Test Name" ) );

  BOOST_CHECK_EQUAL( unit_test->getGroupName(), "Test Group" );
  BOOST_CHECK_EQUAL( unit_test->getTestName(),
                     (std::string("Test Name<") + Utility::typeName<float,int,std::string>() + ">") );
  BOOST_CHECK_EQUAL( unit_test->getDataName(), "" );
  BOOST_CHECK_EQUAL( unit_test->getCombinedGroupTestName(),
                     (std::string("Test Group/Test Name<") + Utility::typeName<float,int,std::string>() + ">") );
  BOOST_CHECK_EQUAL( unit_test->getFullName(),
                     (std::string("Test Group/Test Name<") + Utility::typeName<float,int,std::string>() + ">") );
  BOOST_CHECK_EQUAL( unit_test->getCreationOrderIndex(), 0 );

  // Tuple wrapped parameter pack
  unit_test.reset(
    new TestTemplateUnitTest<std::true_type,std::tuple<float,int,std::string> >( "Test Group", "Test Name" ) );

  BOOST_CHECK_EQUAL( unit_test->getGroupName(), "Test Group" );
  BOOST_CHECK_EQUAL( unit_test->getTestName(),
                     (std::string("Test Name<") + Utility::typeName<float,int,std::string>() + ">") );
  BOOST_CHECK_EQUAL( unit_test->getDataName(), "" );
  BOOST_CHECK_EQUAL( unit_test->getCombinedGroupTestName(),
                     (std::string("Test Group/Test Name<") + Utility::typeName<float,int,std::string>() + ">") );
  BOOST_CHECK_EQUAL( unit_test->getFullName(),
                     (std::string("Test Group/Test Name<") + Utility::typeName<float,int,std::string>() + ">") );
  BOOST_CHECK_EQUAL( unit_test->getCreationOrderIndex(), 1 );

  // Tuple - do not treat as wrapped parameter pack
  unit_test.reset(
    new TestTemplateUnitTest<std::false_type,std::tuple<float,int,std::string> >( "Test Group", "Test Name" ) );

  BOOST_CHECK_EQUAL( unit_test->getGroupName(), "Test Group" );
  BOOST_CHECK_EQUAL( unit_test->getTestName(),
                     (std::string("Test Name<") + Utility::typeName<std::tuple<float,int,std::string> >() + ">") );
  BOOST_CHECK_EQUAL( unit_test->getDataName(), "" );
  BOOST_CHECK_EQUAL( unit_test->getCombinedGroupTestName(),
                     (std::string("Test Group/Test Name<") + Utility::typeName<std::tuple<float,int,std::string> >() + ">") );
  BOOST_CHECK_EQUAL( unit_test->getFullName(),
                     (std::string("Test Group/Test Name<") + Utility::typeName<std::tuple<float,int,std::string> >() + ">") );
  BOOST_CHECK_EQUAL( unit_test->getCreationOrderIndex(), 2 );
}

//---------------------------------------------------------------------------//
// Check that the Nth template parameter can be accessed
BOOST_AUTO_TEST_CASE( _T )
{
  BOOST_CHECK( (std::is_same<float,typename TestTemplateUnitTest<float,int,std::string>::_T<0>::get>::value) );
  BOOST_CHECK( (std::is_same<int,typename TestTemplateUnitTest<float,int,std::string>::_T<1>::get>::value) );
  BOOST_CHECK( (std::is_same<std::string,typename TestTemplateUnitTest<float,int,std::string>::_T<2>::get>::value) );

  BOOST_CHECK( (std::is_same<float,typename TestTemplateUnitTest<std::true_type,std::tuple<float,int,std::string> >::_T<0>::get>::value) );
  BOOST_CHECK( (std::is_same<int,typename TestTemplateUnitTest<std::true_type,std::tuple<float,int,std::string> >::_T<1>::get>::value) );
  BOOST_CHECK( (std::is_same<std::string,typename TestTemplateUnitTest<std::true_type,std::tuple<float,int,std::string> >::_T<2>::get>::value) );

  BOOST_CHECK( (std::is_same<std::tuple<float,int,std::string>,typename TestTemplateUnitTest<std::false_type,std::tuple<float,int,std::string> >::_T<0>::get>::value) );
}

//---------------------------------------------------------------------------//
// end tstTemplateUnitTest.cpp
//---------------------------------------------------------------------------//
