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

// Boost Includes
#include <boost/preprocessor/control.hpp>
#include <boost/preprocessor/variadic.hpp>

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

//! Define a custom unit test finalization
#define FRENSIE_CUSTOM_UNIT_TEST_FINAL()     \
  size_t getCustomUnitTestManagerFinalizationCheckpoint() const override \
  { return __LINE__; }                                                  \
  void customUnitTestManagerFinalization( size_t& __CHECKPOINT__ ) override

//! Add a custom command line option
#define ADD_OPTION( ... )                        \
  FRENSIE_CHECKPOINT();                          \
  setOption( __VA_ARGS__ )

//! Add a standard custom command line option
#define ADD_STANDARD_OPTION( name, type, default_val, description )   \
  FRENSIE_CHECKPOINT();                                                 \
  setOption( name, boost::program_options::value<type>()->default_value(default_val), description )

//! Add a standard custom command line option and assign it
#define ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( name, storage_variable, default_val, description ) \
  FRENSIE_CHECKPOINT();                                                 \
  setOption( name, boost::program_options::value<decltype(storage_variable)>(&storage_variable)->default_value(default_val), description )

//! Assign a command line option
#define ASSIGN_OPTION_VALUE( value, name )            \
  FRENSIE_CHECKPOINT();                                         \
  value = this->getOptionValue<decltype(value)>( name )

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

//! Declare a data unit test class only
#define __FRENSIE_DATA_UNIT_TEST_CLASS_DECL__( TEST_GROUP, TEST_NAME )  \
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Utility::DataUnitTest  \
  {                                                                     \
  public:                                                               \
    TEST_GROUP##_##TEST_NAME##_UnitTest( const std::string& data_table_row_name, \
                                         const std::shared_ptr<const Utility::UnitTestDataTable>& data_table ) \
      : Utility::DataUnitTest( #TEST_GROUP, #TEST_NAME, data_table_row_name, data_table ){} \
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
  }

//! Start the definition of the rumImpl data unit test method
#define __FRENSIE_DATA_UNIT_TEST_RUN_IMPL_DEF_START__( TEST_GROUP, TEST_NAME )\
  void TEST_GROUP##_##TEST_NAME##_UnitTest::runImpl(                    \
                                         std::ostream& log,  \
                                         bool& __SUCCESS__,             \
                                         size_t& __NUMBER_OF_CHECKS__,  \
                                         size_t& __NUMBER_OF_PASSED_CHECKS__, \
                                         size_t& __CHECKPOINT__ ) const \
  
//! Declare a data unit test
#define FRENSIE_DATA_UNIT_TEST_DECL( TEST_GROUP, TEST_NAME )            \
  __FRENSIE_DATA_UNIT_TEST_CLASS_DECL__( TEST_GROUP, TEST_NAME );       \
  __FRENSIE_DATA_UNIT_TEST_RUN_IMPL_DEF_START__( TEST_GROUP, TEST_NAME )   

//! Create the data table name
#define __FRENSIE_DATA_TABLE_NAME__( TABLE_NAME ) TABLE_NAME##_DataTableCreator
  
//! Define a generic data table
#define FRENSIE_DATA_TABLE( TABLE_NAME )                                \
  void __FRENSIE_DATA_TABLE_NAME__( TABLE_NAME )( Utility::UnitTestDataTable& data_table ) 

//! Create a data unit test wrapper
#define __FRENSIE_CREATE_DATA_UNIT_TEST_WRAPPER__( TEST_GROUP, TEST_NAME, TABLE_NAME ) \
  FRENSIE_DATA_TABLE( TABLE_NAME );                       \
  class TEST_GROUP##_##TEST_NAME##_UnitTest;                            \
  Utility::DataUnitTestWrapper<TEST_GROUP##_##TEST_NAME##_UnitTest>     \
  s_##TEST_GROUP##_##TEST_NAME##_UnitTest_data_wrapper(                   \
                  std::string(#TEST_GROUP) + "_" + #TEST_NAME + "_DataTable", \
                  &__FRENSIE_DATA_TABLE_NAME__( TABLE_NAME ) )
  
//! Instantiate a data unit test using the defined data table
#define FRENSIE_DATA_UNIT_TEST_INST( TEST_GROUP, TEST_NAME )        \
  __FRENSIE_CREATE_DATA_UNIT_TEST_WRAPPER__( TEST_GROUP, TEST_NAME, \
                                             TEST_GROUP##_##TEST_NAME \
                                             );                       \
  FRENSIE_DATA_TABLE(                                                 \
                     TEST_GROUP##_##TEST_NAME                         \
                      )

//! Define a data unit test
#define FRENSIE_DATA_UNIT_TEST( TEST_GROUP, TEST_NAME, TABLE_NAME )     \
  __FRENSIE_DATA_UNIT_TEST_CLASS_DECL__( TEST_GROUP, TEST_NAME );       \
  __FRENSIE_CREATE_DATA_UNIT_TEST_WRAPPER__( TEST_GROUP, TEST_NAME, TABLE_NAME ); \
  __FRENSIE_DATA_UNIT_TEST_RUN_IMPL_DEF_START__( TEST_GROUP, TEST_NAME ) 

//! Create the data table columns (use the << operator to add column names)
#define COLUMNS()                            \
  data_table.columns()

//! Add a column to the table
#define ADD_COLUMN( name )                            \
  data_table.addColumn( name )

//! Create a new row of the table
#define NEW_ROW( name )                          \
  data_table.addRow( name )

//! Fetch data from the table (can only be used with data unit tests)
#define FETCH_FROM_TABLE( ElementType, column_name )    \
  ElementType column_name = \
    this->getConcreteDataTableElement<ElementType>( #column_name )

//! Define a template unit test (generic)
#define __FRENSIE_UNIT_TEST_TEMPLATE_DEF__( TEST_GROUP, TEST_NAME, EXPAND_INNER_TUPLES, ... ) \
  template<typename... Types>                                           \
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Utility::TemplateUnitTest<Types...> \
  {                                                                     \
  public:                                                               \
    TEST_GROUP##_##TEST_NAME##_UnitTest()                               \
      : Utility::TemplateUnitTest<Types...>( #TEST_GROUP, #TEST_NAME ) {} \
    std::string getFile() const override                           \
    { return __FILE__; }                                                \
    size_t getLineNumber() const override                               \
    { return __LINE__; }                                                \
  private:                                                              \
    typedef Utility::TemplateUnitTest<Types...> BaseType;               \
    void runImpl( std::ostream& os,                                     \
                  bool& success,                                        \
                  size_t& number_of_checks,                             \
                  size_t& number_of_passed_checks,                      \
                  size_t& last_checkpoint_line_number ) const override; \
  };                                                                    \
  Utility::TemplateUnitTestWrapper<TEST_GROUP##_##TEST_NAME##_UnitTest,EXPAND_INNER_TUPLES,__VA_ARGS__> \
    s_##TEST_GROUP##_##TEST_NAME##_UnitTest_template_wrapper;           \
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

//! Fetch the desired template parameter from the parameter pack
#define FETCH_TEMPLATE_PARAM( TypeIndex, TypeAlias )     \
  typedef typename BaseType::template _T<TypeIndex>::get TypeAlias

#define __FRENSIE_RETURN_LINE_true return;
#define __FRENSIE_RETURN_LINE_false
  
#define __FRENSIE_PROCESS_LOCAL_TEST_RESULT__( local_result, test_success, RETURN_ON_FAILURE ) \
  if( !local_result )                                                   \
  {                                                                   \
    test_success = false;                                               \
                                                                        \
    __FRENSIE_RETURN_LINE_##RETURN_ON_FAILURE                          \
  }                                                                 \
  else                                                                \
  {                                                                 \
    ++__NUMBER_OF_PASSED_CHECKS__;                                  \
  }

#define __CREATE_LOCAL_INPUT_COPY__( input, processed_input )   \
  auto processed_input = std::forward<decltype(input)>( input )

#define __CONVERT_INPUT_TO_LVALUE_REFERENCE__( input, processed_input )    \
  typename std::add_const<typename std::add_lvalue_reference<decltype(input)>::type>::type processed_input = input

#define __DEFAULT_INPUT_PROCESSOR__( lhs, rhs )

#define __DEFAULT_INPUT_PROCESSOR____LHS_VAR__( lhs ) lhs
#define __DEFAULT_INPUT_PROCESSOR____RHS_VAR__( rhs ) rhs

#define SHOW_LHS( lhs, rhs )                                            \
  __CREATE_LOCAL_INPUT_COPY__( lhs, lhs_copy )

#define SHOW_LHS__LHS_VAR__( lhs ) lhs_copy
#define SHOW_LHS__RHS_VAR__( rhs ) rhs

#define SHOW_RHS( lhs, rhs )                    \
  __CREATE_LOCAL_INPUT_COPY__( rhs, rhs_copy )

#define SHOW_RHS__LHS_VAR__( lhs ) lhs
#define SHOW_RHS__RHS_VAR__( rhs ) rhs_copy 

#define SHOW_BOTH( lhs, rhs )                  \
  __CREATE_LOCAL_INPUT_COPY__( lhs, lhs_copy ); \
  __CREATE_LOCAL_INPUT_COPY__( rhs, rhs_copy )

#define SHOW_BOTH__LHS_VAR__( lhs ) lhs_copy
#define SHOW_BOTH__RHS_VAR__( rhs ) rhs_copy 

#define __EVALUATE_INPUT_PROCESSOR__( lhs, rhs, ... )                        \
  BOOST_PP_IF( BOOST_PP_EQUAL(1,BOOST_PP_VARIADIC_SIZE(dummy, ##__VA_ARGS__)),\
               __DEFAULT_INPUT_PROCESSOR__,                             \
               __VA_ARGS__ )( lhs, rhs )

#define __GET_PROCESSED_LHS__( lhs, ... )       \
  BOOST_PP_IF( BOOST_PP_EQUAL(1,BOOST_PP_VARIADIC_SIZE(dummy, ##__VA_ARGS__)),\
               __DEFAULT_INPUT_PROCESSOR____LHS_VAR__,                  \
               __VA_ARGS__##__LHS_VAR__ )( lhs )

#define __GET_PROCESSED_RHS__( rhs, ... )       \
  BOOST_PP_IF( BOOST_PP_EQUAL(1,BOOST_PP_VARIADIC_SIZE(dummy, ##__VA_ARGS__)),\
               __DEFAULT_INPUT_PROCESSOR____RHS_VAR__,                  \
               __VA_ARGS__##__RHS_VAR__ )( rhs )

#define __FRENSIE_COMPARE_WITH_OPTIONAL_RETURN__( ComparePolicy, lhs, rhs, extra_data, log, test_success, RETURN_ON_FAILURE, ... ) \
  {                                                                     \
    ++__NUMBER_OF_CHECKS__;                                             \
    FRENSIE_CHECKPOINT();                                               \
                                                                        \
    Utility::reportCheckType<INDENT>( RETURN_ON_FAILURE, log );         \
                                                                        \
    __EVALUATE_INPUT_PROCESSOR__( lhs, rhs, ##__VA_ARGS__ );              \
                                                                        \
    const bool local_result =                                           \
      Utility::compare<ComparePolicy,0,Utility::Details::incrementRightShift(INDENT)>( __GET_PROCESSED_LHS__( lhs, ##__VA_ARGS__ ), #lhs, \
                                                                                       __GET_PROCESSED_RHS__( rhs, ##__VA_ARGS__ ), #rhs, \
                                                                                       log, extra_data, true ); \
                                                                        \
    Utility::logExtraCheckDetails<Utility::Details::incrementRightShift(INDENT)>( local_result, __FILE__, __LINE__, log ); \
                                                                        \
    __FRENSIE_PROCESS_LOCAL_TEST_RESULT__( local_result, test_success, RETURN_ON_FAILURE ); \
  }

#define __FRENSIE_CHECK_NO_THROW_WITH_OPTIONAL_RETURN__( statement, log, test_success, RETURN_ON_FAILURE ) \
  {                                                                     \
    ++__NUMBER_OF_CHECKS__;                                             \
    FRENSIE_CHECKPOINT();                                               \
                                                                        \
    Utility::reportCheckType<INDENT>( RETURN_ON_FAILURE, log );         \
    log << "\"" << #statement << "\" does not throw exception: ";       \
                                                                        \
    bool local_result = true;                                           \
    std::ostringstream local_log;                                       \
                                                                        \
    try{ statement; }                                                   \
    catch( const std::exception& exception )                            \
    {                                                                 \
      local_result = false;                                           \
                                                                        \
      local_log << std::string( Utility::Details::incrementRightShift(INDENT), ' ' ) \
                << "Caught std::exception with the following message:\n\n" \
                << Utility::toString( exception ) << "\n"               \
                << std::string( Utility::Details::incrementRightShift(INDENT), ' ' ); \
    }                                                                   \
    catch( const int error_code )                                       \
    {                                                                 \
      local_result = false;                                           \
                                                                      \
      local_log << std::string( Utility::Details::incrementRightShift(INDENT), ' ' ) \
                << "Caught error code with value " << error_code << " "; \
    }                                                                   \
    catch( ... )                                                        \
    {                                                                 \
      local_result = false;                                             \
                                                                        \
      local_log << std::string( Utility::Details::incrementRightShift(INDENT), ' ' ) \
                << "Caught exception of unknown type ";                \
    }                                                                   \
                                                                        \
    Utility::reportComparisonPassFail( local_result, log );             \
    if( !local_log.str().empty() )                                      \
    {                                                                 \
      log << local_log.str();                                           \
      Utility::logExtraCheckDetails<0>( local_result, __FILE__, __LINE__, log ); \
    }                                                                   \
    else                                                                \
    {                                                                 \
      Utility::logExtraCheckDetails<Utility::Details::incrementRightShift(INDENT)>( local_result, __FILE__, __LINE__, log ); \
    }                                                                   \
                                                                        \
    __FRENSIE_PROCESS_LOCAL_TEST_RESULT__( local_result, test_success, RETURN_ON_FAILURE ); \
  }

#define __FRENSIE_CHECK_THROW_WITH_OPTIONAL_RETURN__( statement, Exception, log, test_success, RETURN_ON_FAILURE ) \
  {                                                                     \
    ++__NUMBER_OF_CHECKS__;                                             \
    FRENSIE_CHECKPOINT();                                               \
                                                                        \
    Utility::reportCheckType<INDENT>( RETURN_ON_FAILURE, log );         \
    log << "\"" << #statement << "\" throws exception of type "         \
        << #Exception << ": ";                                          \
                                                                        \
    bool local_result = false;                                          \
    std::ostringstream local_log;                                       \
                                                                        \
    try{ statement; }                                                   \
    catch( Exception& exception ) { local_result = true; }              \
    catch( ... )                                                        \
    {                                                                 \
      local_result = false;                                             \
                                                                        \
      local_log << std::string( Utility::Details::incrementRightShift(INDENT), ' ' ) \
                << "Caught exception of wrong type ";                 \
    }                                                                   \
                                                                        \
  Utility::reportComparisonPassFail( local_result, log );               \
  if( !local_log.str().empty() )                                        \
  {                                                                   \
      log << local_log.str();                                           \
      Utility::logExtraCheckDetails<0>( local_result, __FILE__, __LINE__, log ); \
  }                                                                     \
  else                                                                  \
  {                                                                   \
    Utility::logExtraCheckDetails<Utility::Details::incrementRightShift(INDENT)>( local_result, __FILE__, __LINE__, log ); \
  }                                                                     \
                                                                        \
    __FRENSIE_PROCESS_LOCAL_TEST_RESULT__( local_result, test_success, RETURN_ON_FAILURE ); \
  }

#define __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( ComparePolicy, lhs, rhs, log, test_success, ... ) \
  __FRENSIE_COMPARE_WITH_OPTIONAL_RETURN__( ComparePolicy, lhs, rhs, (typename Utility::ComparisonTraits<typename std::common_type<typename std::decay<decltype(lhs)>::type,typename std::decay<decltype(rhs)>::type>::type>::ExtraDataType()), log, test_success, false, ##__VA_ARGS__ )

#define __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( ComparePolicy, lhs, rhs, log, test_success, ... ) \
  __FRENSIE_COMPARE_WITH_OPTIONAL_RETURN__( ComparePolicy, lhs, rhs, (typename Utility::ComparisonTraits<typename std::common_type<typename std::decay<decltype(lhs)>::type,typename std::decay<decltype(rhs)>::type>::type>::ExtraDataType()), log, test_success, true, ##__VA_ARGS__ )

#define __FRENSIE_CHECK_ADVANCED_OPERATOR_IMPL__( ComparePolicy, lhs, rhs, extra_data, log, test_success, ... ) \
  __FRENSIE_COMPARE_WITH_OPTIONAL_RETURN__( ComparePolicy, lhs, rhs, extra_data, log, test_success, false, ##__VA_ARGS__ )

#define __FRENSIE_CHECK_ADVANCED_OPERATOR_WITH_RETURN_IMPL__( ComparePolicy, lhs, rhs, extra_data, log, test_success, ... ) \
  __FRENSIE_COMPARE_WITH_OPTIONAL_RETURN__( ComparePolicy, lhs, rhs, extra_data, log, test_success, true, ##__VA_ARGS__ )

#define FRENSIE_CHECK( statement )                                     \
  __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( Utility::EqualityComparisonPolicy, statement, true, log, success, SHOW_LHS )

#define FRENSIE_REQUIRE( statement )                                   \
  __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( Utility::EqualityComparisonPolicy, statement, true, log, success, SHOW_LHS )

#define FRENSIE_CHECK_EQUAL( lhs, rhs, ... )                                \
  __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( Utility::EqualityComparisonPolicy, lhs, rhs, log, success, ##__VA_ARGS__ )

#define FRENSIE_REQUIRE_EQUAL( lhs, rhs, ... )                              \
  __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( Utility::EqualityComparisonPolicy, lhs, rhs, log, success, ##__VA_ARGS__ )

#define FRENSIE_CHECK_DIFFERENT( lhs, rhs, ... )                            \
  __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( Utility::InequalityComparisonPolicy, lhs, rhs, log, success, ##__VA_ARGS__ )

#define FRENSIE_REQUIRE_DIFFERENT( lhs, rhs, ... )                          \
  __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( Utility::InequalityComparisonPolicy, lhs, rhs, log, success, ##__VA_ARGS__ )

#define FRENSIE_CHECK_GREATER( lhs, rhs, ... )                              \
  __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( Utility::GreaterThanComparisonPolicy, lhs, rhs, log, success, ##__VA_ARGS__ )

#define FRENSIE_REQUIRE_GREATER( lhs, rhs, ... )                            \
  __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( Utility::GreaterThanComparisonPolicy, lhs, rhs, log, success, ##__VA_ARGS__ )

#define FRENSIE_CHECK_GREATER_OR_EQUAL( lhs, rhs, ... )                     \
  __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( Utility::GreaterThanOrEqualToComparisonPolicy, lhs, rhs, log, success, ##__VA_ARGS__ )

#define FRENSIE_REQUIRE_GREATER_OR_EQUAL( lhs, rhs, ... )                   \
  __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( Utility::GreaterThanOrEqualToComparisonPolicy, lhs, rhs, log, success, ##__VA_ARGS__ )

#define FRENSIE_CHECK_LESS( lhs, rhs, ... )                                 \
  __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( Utility::LessThanComparisonPolicy, lhs, rhs, log, success, ##__VA_ARGS__ )

#define FRENSIE_REQUIRE_LESS( lhs, rhs, ... )                               \
  __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( Utility::LessThanComparisonPolicy, lhs, rhs, log, success, ##__VA_ARGS__ )

#define FRENSIE_CHECK_LESS_OR_EQUAL( lhs, rhs, ... )                        \
  __FRENSIE_CHECK_BASIC_OPERATOR_IMPL__( Utility::LessThanOrEqualToComparisonPolicy, lhs, rhs, log, success, ##__VA_ARGS__ )

#define FRENSIE_REQUIRE_LESS_OR_EQUAL( lhs, rhs, ... )                      \
  __FRENSIE_CHECK_BASIC_OPERATOR_WITH_RETURN_IMPL__( Utility::LessThanOrEqualToComparisonPolicy, lhs, rhs, log, success, ##__VA_ARGS__ )

#define FRENSIE_CHECK_CLOSE( lhs, rhs, tol, ... )                           \
  __FRENSIE_CHECK_ADVANCED_OPERATOR_IMPL__( Utility::CloseComparisonPolicy, lhs, rhs, tol, log, success, ##__VA_ARGS__ )

#define FRENSIE_REQUIRE_CLOSE( lhs, rhs, tol, ... )                         \
  __FRENSIE_CHECK_ADVANCED_OPERATOR_WITH_RETURN_IMPL__( Utility::CloseComparisonPolicy, lhs, rhs, tol, log, success, ##__VA_ARGS__ )

#define FRENSIE_CHECK_SMALL( value, tol, ... )                              \
  __FRENSIE_CHECK_ADVANCED_OPERATOR_IMPL__( Utility::CloseComparisonPolicy, value, Utility::Details::zero(value), tol, log, success, ##__VA_ARGS__ )

#define FRENSIE_REQUIRE_SMALL( value, tol, ... )                            \
  __FRENSIE_CHECK_ADVANCED_OPERATOR_WITH_RETURN_IMPL__( Utility::CloseComparisonPolicy, value, Utility::Details::zero(value), tol, log, success, ##__VA_ARGS__ )

#define FRENSIE_CHECK_FLOATING_EQUALITY( lhs, rhs, tol, ... )               \
  __FRENSIE_CHECK_ADVANCED_OPERATOR_IMPL__( Utility::RelativeErrorComparisonPolicy, lhs, rhs, tol, log, success, ##__VA_ARGS__ )

#define FRENSIE_REQUIRE_FLOATING_EQUALITY( lhs, rhs, tol, ... )             \
  __FRENSIE_CHECK_ADVANCED_OPERATOR_WITH_RETURN_IMPL__( Utility::RelativeErrorComparisonPolicy, lhs, rhs, tol, log, success, ##__VA_ARGS__ )

#define FRENSIE_CHECK_NO_THROW( statement )     \
  __FRENSIE_CHECK_NO_THROW_WITH_OPTIONAL_RETURN__( statement, log, success, false )

#define FRENSIE_REQUIRE_NO_THROW( statement )   \
  __FRENSIE_CHECK_NO_THROW_WITH_OPTIONAL_RETURN__( statement, log, success, true )

#define FRENSIE_CHECK_THROW( statement, Exception )     \
  __FRENSIE_CHECK_THROW_WITH_OPTIONAL_RETURN__( statement, Exception, log, success, false )

#define FRENSIE_REQUIRE_THROW( statement, Exception )     \
  __FRENSIE_CHECK_THROW_WITH_OPTIONAL_RETURN__( statement, Exception, log, success, true )

#endif // end UTILITY_UNIT_TEST_MACROS_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTestMacros.hpp
//---------------------------------------------------------------------------//
