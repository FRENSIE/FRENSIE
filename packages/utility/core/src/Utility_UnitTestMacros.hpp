//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTestMacros.hpp
//! \author Alex Robinson
//! \brief  Unit test macro definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_TEST_MACROS_HPP
#define UTILITY_UNIT_TEST_MACROS_HPP

// Std Lib Includes
#include <iostream>
#include <string>

// FRENSIE Includes
#include "Utility_UnitTest.hpp"
#include "Utility_DataUnitTest.hpp"
#include "Utility_DataUnitTestWrapper.hpp"
#include "Utility_TemplateUnitTest.hpp"
#include "Utility_TemplateUnitTestWrapper.hpp"
#include "Utility_UnitTestHelpers.hpp"
#include "Utility_ComparisonTraits.hpp"

//! The success variable name
#define __SUCCESS__ success

//! The numer of checks variable name
#define __NUMBER_OF_CHECKS__ number_of_checks

//! The number of passed checks variable name
#define __NUMBER_OF_PASSED_CHECKS__ number_of_passed_checks

//! The checkpoint variable name
#define __CHECKPOINT__ last_checkpoint_line_number

//! The starting indentation for local checks
#define INDENT Utility::UnitTestManager::getTestDetailsStartingRightShift()

#define FRENSIE_CHECKPOINT() __CHECKPOINT__ = __LINE__

//! Start the custom unit test setup
#define FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN()  \
  class CustomUnitTestManagerInitializer : public Utility::UnitTestManager::Initializer \
  {                                                                     \
  public:                                                               \
    CustomUnitTestManagerInitializer()                                  \
      : Utility::UnitTestManager::Initializer( __LINE__ )               \
    { Utility::UnitTestManager::getInstance().setInitializer( *this ); } \
    ~CustomUnitTestManagerInitializer() { /* ... */ }                   \
  protected:                                                            \
    void __dummy__()

//! End the custom unit test setup
#define FRENSIE_CUSTOM_UNIT_TEST_SETUP_END()    \
  };                                            \
  CustomUnitTestManagerInitializer custom_initializer_instance

//! Set custom command line options for a unit test
#define FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS() \
  size_t getCustomCommandLineOptionsStartCheckpoint() const override \
  { return __LINE__; }                                                \
  void setCustomCommandLineOptions( size_t& __CHECKPOINT__ ) override     \

//! Define a custom unit test initialization
#define FRENSIE_CUSTOM_UNIT_TEST_INIT()         \
  size_t getCustomUnitTestManagerInitializationCheckpoint() const override    \
  { return __LINE__; }                                                  \
  void customUnitTestManagerInitialization( size_t& __CHECKPOINT__ ) override

//! Add a custom command line option
#define ADD_OPTION()                             \
  FRENSIE_CHECKPOINT();                          \
  setOption

//! Get a command line option
#define GET_OPTION( type, name )                      \
  FRENSIE_CHECKPOINT();                               \
  this->getOptionValue<type>( name )

//! Assign a command line option
#define ASSIGN_OPTION( value, name )            \
  FRENSIE_CHECKPOINT();                                         \
  value = this->getOptionValue<decltype(value)>( name );

//! Define a basic unit test
#define FRENSIE_UNIT_TEST( TEST_GROUP, TEST_NAME )      \
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Utility::UnitTest \
  {                                                                    \
  public:                                                              \
    TEST_GROUP##_##TEST_NAME##_UnitTest()                              \
      : Utility::UnitTest( #TEST_GROUP, #TEST_NAME ){}                 \
    std::string getFile() const override                               \
    { return __FILE__; }                                               \
    size_t getLineNumber() const override                              \
    { return __LINE__; }                                               \
  private:                                                             \
    void runImpl( std::ostream& os,                                    \
                  bool& success,                                        \
                  size_t& number_of_checks,                             \
                  size_t& number_of_passed_checks,                      \
                  size_t& last_checkpoint_line_number ) const override; \
  };                                                                   \
  TEST_GROUP##_##TEST_NAME##_UnitTest s_##TEST_GROUP##_##TEST_NAME##_UnitTest;\
                                                                        \
  void TEST_GROUP##_##TEST_NAME##_UnitTest::runImpl(                    \
                                         std::ostream& log,  \
                                         bool& __SUCCESS__,             \
                                         size_t& __NUMBER_OF_CHECKS__,  \
                                         size_t& __NUMBER_OF_PASSED_CHECKS__, \
                                         size_t& __CHECKPOINT__ ) const \

//! Define a data unit test
#define FRENSIE_DATA_UNIT_TEST( TEST_GROUP, TEST_NAME ) \
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Utility::DataUnitTest  \
  {                                                                     \
    TEST_GROUP##_##TEST_NAME##_UnitTest( const std::string& data_table_row_name, \
                                         const std::shared_ptr<const UnitTestDataTable>& data_table ) \
      : Utility::DataUnitTest( #TEST_GROUP, #TEST_NAME, data_table_row_name, data_table ){} \
    std::string getFile() const override                               \
    { return __FILE__; }                                               \
    size_t getLineNumber() const override                              \
    { return __LINE__; }                                               \
    void runImpl( std::ostream& os,                                    \
                  bool& success,                                        \
                  size_t& number_of_checks,                             \
                  size_t& number_of_passed_checks,                      \
                  size_t& last_checkpoint_line_number ) const override; \
  };                                                                    \
                                                                        \
  void TEST_GROUP##_##TEST_NAME##_UnitTest::runImpl(                    \
                                         std::ostream& log,  \
                                         bool& __SUCCESS__,             \
                                         size_t& __NUMBER_OF_CHECKS__,  \
                                         size_t& __NUMBER_OF_PASSED_CHECKS__, \
                                         size_t& __CHECKPOINT__ ) const \

//! Define the data for a data unit test
#define FRENSIE_DATA_UNIT_TEST_TABLE( TEST_GROUP, TEST_NAME )   \
  class TEST_GROUP##_##TEST_NAME##_UnitTest;                            \
  void TEST_GROUP##_##TEST_NAME##_DataTableCreator( Utility::UnitTestDataTable& data_table ); \
  Utility::DataUnitTestWrapper<TEST_GROUP##_##TEST_NAME##_UnitTest>    \
  s_##TEST_GROUP##_##TEST_NAME##_UnitTest_data_wrapper(                 \
                   std::string(#TEST_GROUP)+ "_" + #TEST_NAME + "_DataTable", \
                   &TEST_GROUP##_##TEST_NAME##_DataTableCreator );      \
  \
  void TEST_GROUP##_##TEST_NAME##_DataTableCreator( UnitTestDataTable& data_table ) \

//! Create the data table columns (use the << operator to add column names)
#define COLUMNS()                            \
  data_table.columns()

//! Add a column to the table
#define ADD_COLUMN( name )                            \
  data_table.addColumn( name )

//! Create a new row of the table
#define NEW_ROW( name )                          \
  data_table.addRow( row_name )

//! Fetch data from the table (can only be used with data unit tests)
#define FETCH_FROM_TABLE( ElementType, column_name )    \
  ElementType column_name = \
    this->getConcreteDataTableElement<ElementType>( #column_name )

//! Define a template unit test (generic)
#define __FRENSIE_UNIT_TEST_TEMPLATE_DEF__( TEST_GROUP, TEST_NAME, EXPAND_INNER_TUPLES, ... ) \
  template<typename... Types>                                           \
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Utility::TemplateUnitTest<Types...> \
  {                                                                     \
    TEST_GROUP##_##TEST_NAME##_UnitTest()                               \
      : Utility::TemplateUnitTest<T>( #TEST_GROUP, #TEST_NAME ) {} \
    std::string getFile() const override                           \
      { return __FILE__; }                                                \
    size_t getLineNumber() const override                               \
    { return __LINE__; }                                                \
    void runImpl( std::ostream& os,                                     \
                  bool& success,                                        \
                  size_t& number_of_checks,                             \
                  size_t& number_of_passed_checks,                      \
                  size_t& last_checkpoint_line_number ) const override; \
  };                                                                    \
  Utility::TemplateUnitTestWrapper<TEST_GROUP##_##TEST_NAME##_UnitTest,EXPAND_INNER_TUPLES,__VA_ARGS__> \
    s_##TEST_GROUP##_##TEST_NAME##_UnitTest_template_wrapper();           \
                                                                        \
  template<typename... Types>                                           \
  void TEST_GROUP##_##TEST_NAME##_UnitTest<Types...>::runImpl(         \
                                         std::ostream& log,             \
                                         bool& __SUCCESS__,             \
                                         size_t& __NUMBER_OF_CHECKS__,  \
                                         size_t& __NUMBER_OF_PASSED_CHECKS__, \
                                         size_t& __CHECKPOINT__ ) const \

//! Define a template unit test (expand any tuples in the type list)
#define FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( TEST_GROUP, TEST_NAME, ... ) \
  __FRENSIE_UNIT_TEST_TEMPLATE_DEF__( TEST_GROUP, TEST_NAME, true, __VA_ARGS__ )

//! Define a template unit test
#define FRENSIE_UNIT_TEST_TEMPLATE( TEST_GROUP, TEST_NAME, ... ) \
  __FRENSIE_UNIT_TEST_TEMPLATE_DEF__( TEST_GROUP, TEST_NAME, false, __VA_ARGS__ )

//! Access the first template unit test template parameter (can only be used with template unit tests)
#define _T0 typename _T<0>::get

//! Access the second template unit test template parameter (can only be used with template unit tests)
#define _T1 typename _T<1>::get

//! Access the third template unit test template parameter (can only be used with template unit tests)
#define _T2 typename _T<2>::get

//! Access the fourth template unit test template parameter (can only be used with template unit tests)
#define _T3 typename _T<3>::get

//! Access the fifth template unit test template parameter (can only be used with template unit tests)
#define _T4 typename _T<4>::get

//! Access the sixth template unit test template parameter (can only be used with template unit tests)
#define _T5 typename _T<5>::get

//! Access the seventh template unit test template parameter (can only be used with template unit tests)
#define _T6 typename _T<6>::get

//! Access the eighth template unit test template parameter (can only be used with template unit tests)
#define _T7 typename _T<7>::get

//! Access the ninth template unit test template parameter (can only be used with template unit tests)
#define _T8 typename _T<8>::get

//! Access the tenth template unit test template parameter (can only be used with template unit tests)
#define _T9 typename _T<9>::get

#define __FRENSIE_PROCESS_LOCAL_TEST_RESULT__( local_result, test_success, RETURN_ON_FAILURE ) \
  if( !local_result )                                                   \
  {                                                                   \
    test_success = false;                                                  \
                                                                      \
    if( RETURN_ON_FAILURE )                                           \
      return;                                                         \
  }                                                                   \
  else                                                                \
  {                                                                 \
    ++__NUMBER_OF_PASSED_CHECKS__;                                  \
  }                                                                 

#define __FRENSIE_COMPARE_WITH_OPTIONAL_RETURN__( ComparePolicy, lhs, rhs, extra_data, log, test_success, RETURN_ON_FAILURE ) \
  {                                                                     \
    ++__NUMBER_OF_CHECKS__;                                             \
    FRENSIE_CHECKPOINT();                                               \
                                                                        \
    Utility::reportCheckType<INDENT>( RETURN_ON_FAILURE, log );         \
                                                                        \
    const bool local_result =                                           \
      Utility::compare<ComparePolicy,0,Utility::Details::incrementRightShift(INDENT)>( lhs, #lhs, rhs, #rhs, log, extra_data, true ); \
                                                                        \
    Utility::logExtraCheckDetails<Utility::Details::incrementRightShift(INDENT)>( local_result, __FILE__, __LINE__, log ); \
                                                                        \
    __FRENSIE_PROCESS_LOCAL_TEST_RESULT__( local_result, test_success, RETURN_ON_FAILURE ); \
  }

#define __FRENSIE_CHECK_NO_THROW_WITH_OPTIONAL_RETURN__( statement, RETURN_ON_FAILURE )   \
  {                                                                     \
    ++__NUMBER_OF_CHECKS__;                                             \
    FRENSIE_CHECKPOINT();                                               \
                                                                        \
    std::ostringstream oss;                                             \
    oss << #statement << " does not throw exception: ";                 \
                                                                        \
    const bool local_result = true;                                     \
                                                                        \
    try{ statement; }                                                   \
    catch( ... ) { local_result = false; }                              \
                                                                        \
    Utility::logCheckDetailsAndResult( oss.str(),        \
                                       "",                              \
                                       local_result,                    \
                                       RETURN_ON_FAILURE,               \
                                       __FILE__,                        \
                                       __LINE__,                        \
                                       log );                           \
                                                                        \
    __FRENSIE_PROCESS_LOCAL_TEST_RESULT__( local_result, test_success, RETURN_ON_FAILURE ); \
  }

#define __FRENSIE_CHECK_THROW_WITH_OPTIONAL_RETURN__( statement, Exception, RETURN_ON_FAILURE ) \
  {                                                                     \
    ++__NUMBER_OF_CHECKS__;                                             \
    FRENSIE_CHECKPOINT();                                               \
                                                                        \
    std::ostringstream oss;                                             \
    oss << #statement << " throws exception of type " << #Exception << ": "; \
                                                                        \
    std::ostringstream local_log;                                       \
                                                                        \
    const bool local_result = false;                                    \
                                                                        \
    try{ statement; }                                                   \
    catch( Exception& exception )                                       \
    {                                                                 \
      local_result = true;                                              \
      local_log << Utility::toString( exception );                      \
    }                                                                   \
                                                                        \
    Utility::logCheckDetailsAndResult( oss.str(),                       \
                                       local_log.str(),                 \
                                       local_result,                    \
                                       RETURN_ON_FAILURE,               \
                                       __FILE__,                        \
                                       __LINE__,                        \
                                       log );                           \
                                                                        \
    __FRENSIE_PROCESS_LOCAL_TEST_RESULT__( local_result, test_success, RETURN_ON_FAILURE ); \
  }

#define __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( ComparePolicy, lhs, rhs, log, test_success ) \
  __FRENSIE_COMPARE_WITH_OPTIONAL_RETURN__( ComparePolicy, lhs, rhs, (Utility::ComparisonTraits<std::common_type<std::decay<decltype(lhs)>::type,std::decay<decltype(rhs)>::type>::type>::ExtraDataType()), log, test_success, false )

#define __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( ComparePolicy, lhs, rhs, log, test_success ) \
  __FRENSIE_COMPARE_WITH_OPTIONAL_RETURN__( ComparePolicy, lhs, rhs, (Utility::ComparisonTraits<std::common_type<std::decay<decltype(lhs)>::type,std::decay<decltype(rhs)>::type>::type>::ExtraDataType()), log, test_success, true )

#define __FRENSIE_CHECK_ADVANCED_OPERATOR_IMPL__( ComparePolicy, lhs, rhs, extra_data, log, test_success ) \
  __FRENSIE_COMPARE_WITH_OPTIONAL_RETURN__( ComparePolicy, lhs, rhs, extra_data, log, test_success, false )

#define __FRENSIE_CHECK_ADVANCED_OPERATOR_WITH_RETURN_IMPL__( ComparePolicy, lhs, rhs, extra_data, log, test_success ) \
  __FRENSIE_COMPARE_WITH_OPTIONAL_RETURN__( ComparePolicy, lhs, rhs, extra_data, log, test_success, true )

#define FRENSIE_CHECK( statement )              \
  __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( Utility::EqualityComparisonPolicy, statement, true, log, success )

#define FRENSIE_REQUIRE( statement )            \
  __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( Utility::EqualityComparisonPolicy, statement, true, log, success )

#define FRENSIE_CHECK_EQUAL( lhs, rhs )         \
  __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( Utility::EqualityComparisonPolicy, lhs, rhs, log, success )

#define FRENSIE_REQUIRE_EQUAL( lhs, rhs )       \
  __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( Utility::EqualityComparisonPolicy, lhs, rhs, log, success )

#define FRENSIE_CHECK_DIFFERENT( lhs, rhs )     \
  __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( Utility::InequalityComparisonPolicy, lhs, rhs, log, success )

#define FRENSIE_REQUIRE_DIFFERENT( lhs, rhs )   \
  __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( Utility::InequalityComparisonPolicy, lhs, rhs, log, success )

#define FRENSIE_CHECK_GREATER( lhs, rhs )       \
  __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( Utility::GreaterThanComparisonPolicy, lhs, rhs, log, success )

#define FRENSIE_REQUIRE_GREATER( lhs, rhs )       \
  __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( Utility::GreaterThanComparisonPolicy, lhs, rhs, log, success )

#define FRENSIE_CHECK_GREATER_OR_EQUAL( lhs, rhs )       \
  __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( Utility::GreaterThanOrEqualToComparisonPolicy, lhs, rhs, log, success )

#define FRENSIE_REQUIRE_GREATER_OR_EQUAL( lhs, rhs )       \
  __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( Utility::GreaterThanOrEqualToComparisonPolicy, lhs, rhs, log, success )

#define FRENSIE_CHECK_LESS( lhs, rhs )       \
  __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( Utility::GreaterThanComparisonPolicy, lhs, rhs, log, success )

#define FRENSIE_REQUIRE_LESS( lhs, rhs )       \
  __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( Utility::GreaterThanComparisonPolicy, lhs, rhs, log, success )

#define FRENSIE_CHECK_LESS_OR_EQUAL( lhs, rhs )       \
  __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( Utility::GreaterThanOrEqualToComparisonPolicy, lhs, rhs, log, success )

#define FRENSIE_REQUIRE_LESS_OR_EQUAL( lhs, rhs )       \
  __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( Utility::GreaterThanOrEqualToComparisonPolicy, lhs, rhs, log, success )

#define FRENSIE_CHECK_CLOSE( lhs, rhs, tol )    \
  __FRENSIE_CHECK_ADVANCED_OPERATOR_IMPL__( Utility::CloseComparisonPolicy, lhs, rhs, tol, log, success )

#define FRENSIE_REQUIRE_CLOSE( lhs, rhs, tol )    \
  __FRENSIE_CHECK_ADVANCED_OPERATOR_WITH_RETURN_IMPL__( Utility::CloseComparisonPolicy, lhs, rhs, tol, log, success )

#define FRENSIE_CHECK_SMALL( value, tol )    \
  __FRENSIE_CHECK_ADVANCED_OPERATOR_WITH_RETURN_IMPL__( Utility::CloseComparisonPolicy, value, 0, tol, log, success )

#define FRENSIE_REQUIRE_SMALL( value, tol )    \
  __FRENSIE_CHECK_ADVANCED_OPERATOR_WITH_RETURN_IMPL__( Utility::CloseComparisonPolicy, value, 0, tol, log, success )

#define FRENSIE_REQUIRE_FLOATING_EQUALITY( lhs, rhs, tol ) \
  __FRENSIE_CHECK_ADVANCED_OPERATOR_WITH_RETURN_IMPL__( Utility::RelativeErrorComparisonPolicy, lhs, rhs, tol, log, success )

#define FRENSIE_CHECK_NO_THROW( statement )     \
  __FRENSIE_CHECK_NO_THROW_WITH_OPTIONAL_RETURN__( statement, false )

#define FRENSIE_REQUIRE_NO_THROW( statement )   \
  __FRENSIE_CHECK_NO_THROW_WITH_OPTIONAL_RETURN__( statement, true )

#define FRENSIE_CHECK_THROW( statement, Exception )     \
  __FRENSIE_CHECK_THROW_WITH_OPTIONAL_RETURN__( statement, Exception, false )

#define FRENSIE_REQUIRE_THROW( statement, Exception )     \
  __FRENSIE_CHECK_THROW_WITH_OPTIONAL_RETURN__( statement, Exception, true )

#endif // end UTILITY_UNIT_TEST_MACROS_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTestMacros.hpp
//---------------------------------------------------------------------------//
