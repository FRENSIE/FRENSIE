//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTestHarnessExtensions.hpp
//! \author Alex Robinson
//! \brief  Extentions to the Teuchos_UnitTestHarness 
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_TEST_HARNESS_EXTENSIONS_HPP
#define UTILITY_UNIT_TEST_HARNESS_EXTENSIONS_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_FancyOStream.hpp>

// FRENSIE Includes
#include "Utility_TestingHelpers.hpp"

/*! \defgroup unit_test_harness_extensions Teuchos Unit Test Harness Extensions
 * \ingroup testing
 *
 * Several macros have been written that extend the functionality of the
 * Teuchos Unit Test Harness. This additional functionality allows some
 * objects commonly used by Utility to be tested more easily. 
 */

/*! \brief A macro for the Teuchos Unit Test Harness for creating a
 * templated unit test on one type and one template template parameter.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_DECL(TEST_GROUP, TEST_NAME, TYPE, ARRAY) \
  template<typename TYPE, template<typename> class ARRAY> \
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Teuchos::UnitTestBase \
  {									\
  public:								\
    TEST_GROUP##_##TEST_NAME##_UnitTest(				\
      const std::string& typeName,					\
      const std::string& arrayName					\
    )                                                                   \
    : Teuchos::UnitTestBase(						\
	#TEST_GROUP, std::string(#TEST_NAME)+"_Teuchos::"+arrayName+"<"+typeName+">" ) \
    {}									\
    void runUnitTestImpl( Teuchos::FancyOStream &out, bool &success ) const; \
    virtual std::string unitTestFile() const { return __FILE__; }	\
    virtual long int unitTestFileLineNumber() const { return __LINE__; } \
  };									\
									\
  template<typename TYPE, template<typename> class ARRAY>		\
  void TEST_GROUP##_##TEST_NAME##_UnitTest<TYPE,ARRAY>::runUnitTestImpl( \
                      Teuchos::FancyOStream &out, bool &success ) const \
    
/*! \brief A macro for the Teuchos Unit Test Harness for instantiating a
 * templated unit test on one type and one template template parameter.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_INSTANT(TEST_GROUP, TEST_NAME, TYPE, ARRAY) \
  template class TEST_GROUP##_##TEST_NAME##_UnitTest<TYPE, Teuchos::ARRAY >; \
  TEST_GROUP##_##TEST_NAME##_UnitTest<TYPE, Teuchos::ARRAY >		\
  instance_##TEST_GROUP##_##TYPE##_##ARRAY##_##TEST_NAME##_UnitTest(#TYPE,#ARRAY);

/*! \brief A macro for the Teuchos Unit Test Harness for creating a 
 * templated unit test on a Tuple Member and a type.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_DECL(TEST_GROUP, TEST_NAME, MEMBER, TUPLE) \
  template<Utility::TupleMember MEMBER, typename TUPLE>			\
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Teuchos::UnitTestBase \
  {									\
  public:								\
    TEST_GROUP##_##TEST_NAME##_UnitTest(				\
      const std::string& memberName,					\
      const std::string& tupleName					\
    )                                                                   \
    : Teuchos::UnitTestBase(						\
	#TEST_GROUP, std::string(#TEST_NAME)+"_"+memberName+"_"+tupleName ) \
    {}									\
    void runUnitTestImpl( Teuchos::FancyOStream &out, bool &success ) const; \
    virtual std::string unitTestFile() const { return __FILE__; }	\
    virtual long int unitTestFileLineNumber() const { return __LINE__; } \
  };									\
									\
  template<Utility::TupleMember MEMBER, typename TUPLE>			\
  void TEST_GROUP##_##TEST_NAME##_UnitTest<MEMBER,TUPLE>::runUnitTestImpl( \
         Teuchos::FancyOStream &out, bool &success ) const \

/*! \brief A macro for the Teuchos Unit Test Harness for instantiating a
 * templated unit test on a Tuple Member and a type.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT(TEST_GROUP, TEST_NAME, MEMBER, TUPLE) \
  template class TEST_GROUP##_##TEST_NAME##_UnitTest<Utility::MEMBER, TUPLE>; \
  TEST_GROUP##_##TEST_NAME##_UnitTest<Utility::MEMBER, TUPLE>		\
  instance_##TEST_GROUP##_##MEMBER##_##TUPLE##_##TEST_NAME##_UnitTest(#MEMBER,#TUPLE);

/*! \brief A macro for the Teuchos Unit Test Harness for creating a templated 
 * unit test on two Tuple Member enums, one Tuple and a Teuchos Array.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_DECL(TEST_GROUP, TEST_NAME, MEMBER1, MEMBER2, TUPLE, ARRAY) \
  template<Utility::TupleMember MEMBER1,				\
	   Utility::TupleMember MEMBER2,				\
	   typename TUPLE,						\
	   template<typename> class ARRAY>				\
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Teuchos::UnitTestBase \
  {									\
  public:								\
    TEST_GROUP##_##TEST_NAME##_UnitTest(				\
      const std::string& member1Name,					\
      const std::string& member2Name,					\
      const std::string& tupleName,					\
      const std::string& arrayName					\
    )                                                                   \
    : Teuchos::UnitTestBase(						\
	#TEST_GROUP, std::string(#TEST_NAME)+"_Teuchos::"+arrayName+"<"+tupleName+">_"+member1Name+"_"+member2Name ) \
    {}									\
    void runUnitTestImpl( Teuchos::FancyOStream &out, bool &success ) const; \
    virtual std::string unitTestFile() const { return __FILE__; }	\
    virtual long int unitTestFileLineNumber() const { return __LINE__; } \
  };									\
									\
  template<Utility::TupleMember MEMBER1,				\
	   Utility::TupleMember MEMBER2,				\
	   typename TUPLE,						\
	   template<typename> class ARRAY>				\
  void TEST_GROUP##_##TEST_NAME##_UnitTest<MEMBER1,MEMBER2,TUPLE,ARRAY>::runUnitTestImpl( \
	Teuchos::FancyOStream &out, bool &success ) const \

/*! \brief A macro for the Teuchos Unit Test Harness for instantiating a 
 * templated unit test on two Tuple Member enums, one Tuple and a Teuchos 
 * Array.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT(TEST_GROUP, TEST_NAME, MEMBER1, MEMBER2, TUPLE, ARRAY) \
  template class TEST_GROUP##_##TEST_NAME##_UnitTest<Utility::MEMBER1, Utility::MEMBER2, TUPLE, Teuchos::ARRAY>; \
  TEST_GROUP##_##TEST_NAME##_UnitTest<Utility::MEMBER1, Utility::MEMBER2, TUPLE, Teuchos::Array> \
  instance_##TEST_GROUP##_##MEMBER##_##MEMBER1##_##MEMBER2##_##TUPLE##_##ARRAY##_##TEST_NAME##_UnitTest(#MEMBER1,#MEMBER2,#TUPLE,#ARRAY);

/*! \brief A macro for the Teuchos Unit Test Harness for creating a templated
 * unit test on two Tuple Member enums, two Tuples and a Teuchos Array.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_DECL(TEST_GROUP, TEST_NAME, MEMBER1, MEMBER2, TUPLE1, TUPLE2, ARRAY) \
  template<Utility::TupleMember MEMBER1,				\
	   Utility::TupleMember MEMBER2,				\
	   typename TUPLE1,						\
	   typename TUPLE2,						\
	   template<typename> class ARRAY>				\
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Teuchos::UnitTestBase \
  {									\
  public:								\
    TEST_GROUP##_##TEST_NAME##_UnitTest(				\
      const std::string& member1Name,					\
      const std::string& member2Name,					\
      const std::string& tuple1Name,					\
      const std::string& tuple2Name,					\
      const std::string& arrayName					\
    )                                                                   \
    : Teuchos::UnitTestBase(						\
        #TEST_GROUP, std::string(#TEST_NAME)+"_Teuchos::"+arrayName+"<"+tuple1Name+">_"+member1Name+"_Teuchos::"+arrayName+"<"+tuple2Name+">_"+member2Name )\
    {}									\
    void runUnitTestImpl( Teuchos::FancyOStream &out, bool &success ) const; \
    virtual std::string unitTestFile() const { return __FILE__; }	\
    virtual long int unitTestFileLineNumber() const { return __LINE__; } \
  };						                        \
									\
    template<Utility::TupleMember MEMBER1,				\
	     Utility::TupleMember MEMBER2,				\
	     typename TUPLE1,						\
	     typename TUPLE2,						\
	     template<typename> class ARRAY>				\
    void TEST_GROUP##_##TEST_NAME##_UnitTest<MEMBER1,MEMBER2,TUPLE1,TUPLE2,ARRAY>::runUnitTestImpl( \
	Teuchos::FancyOStream &out, bool &success ) const \
  
/*! \brief A macro for the Teuchos Unit Test Harness for instantiating a 
 * templated unit test on two Tuple Member enums, two Tuples and a Teuchos 
 * Array.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT(TEST_GROUP, TEST_NAME, MEMBER1, MEMBER2, TUPLE1, TUPLE2, ARRAY) \
  template class TEST_GROUP##_##TEST_NAME##_UnitTest<Utility::MEMBER1, Utility::MEMBER2, TUPLE1, TUPLE2, Teuchos::ARRAY>; \
  TEST_GROUP##_##TEST_NAME##_UnitTest<Utility::MEMBER1, Utility::MEMBER2, TUPLE1, TUPLE2, Teuchos::Array> \
  instance_##TEST_GROUP##_##MEMBER##_##MEMBER1##_##MEMBER2##_##TUPLE1##_##TUPLE2##_##ARRAY##_##TEST_NAME##_UnitTest(#MEMBER1,#MEMBER2,#TUPLE1,#TUPLE2,#ARRAY);

/*! \brief A macro for the Teuchos Unit Test Harness for creating a templated 
 * unit test on two types and one template template parameter.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_DECL(TEST_GROUP, TEST_NAME, MEMBER, TYPE1, ARRAY) \
  template<Utility::TupleMember MEMBER, typename TYPE1, template<typename> class ARRAY> \
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Teuchos::UnitTestBase \
  {									\
  public:								\
    TEST_GROUP##_##TEST_NAME##_UnitTest(				\
      const std::string& memberName,	                                \
      const std::string& type1Name,                                     \
      const std::string& arrayName					\
    )                                                                   \
    : Teuchos::UnitTestBase(						\
	#TEST_GROUP, std::string(#TEST_NAME)+"_Teuchos::"+arrayName+"<"+type1Name+">_"+memberName )	\
    {}									\
    void runUnitTestImpl( Teuchos::FancyOStream &out, bool &success ) const; \
    virtual std::string unitTestFile() const { return __FILE__; }	\
    virtual long int unitTestFileLineNumber() const { return __LINE__; } \
  };									\
									\
  template<Utility::TupleMember MEMBER, typename TYPE1, template<typename> class ARRAY> \
  void TEST_GROUP##_##TEST_NAME##_UnitTest<MEMBER,TYPE1,ARRAY>::runUnitTestImpl(\
                      Teuchos::FancyOStream &out, bool &success ) const \

/*! \brief A macro for the Teuchos Unit Test Harness for instantiating a 
 * templated unit test on two types and one template template parameter.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT(TEST_GROUP, TEST_NAME, MEMBER, TYPE1, ARRAY) \
  template class TEST_GROUP##_##TEST_NAME##_UnitTest<Utility::MEMBER, TYPE1, Teuchos::ARRAY >; \
  TEST_GROUP##_##TEST_NAME##_UnitTest<Utility::MEMBER, TYPE1, Teuchos::ARRAY > \
  instance_##TEST_GROUP##_##MEMBER##_##TYPE1##_##ARRAY##_##TEST_NAME##_UnitTest(#MEMBER,#TYPE1,#ARRAY);

/*! \brief A macro for the Teuchos Unit Test Harness for creating a
 * templated unit test on an unsigned type.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL(TEST_GROUP, TEST_NAME, UNSIGNED_VALUE) \
  template<unsigned UNSIGNED_VALUE> \
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Teuchos::UnitTestBase \
  {									\
  public:								\
    TEST_GROUP##_##TEST_NAME##_UnitTest( const std::string& unsignedValue ) \
    : Teuchos::UnitTestBase(						\
	#TEST_GROUP, unsignedValue+"_"+std::string(#TEST_NAME) ) \
    {}								\
    void runUnitTestImpl( Teuchos::FancyOStream &out, bool &success ) const; \
    virtual std::string unitTestFile() const { return __FILE__; }	\
    virtual long int unitTestFileLineNumber() const { return __LINE__; } \
  };								       \
								       \
    template<unsigned UNSIGNED_VALUE>				       \
    void TEST_GROUP##_##TEST_NAME##_UnitTest<UNSIGNED_VALUE>::runUnitTestImpl(\
			    Teuchos::FancyOStream &out, bool &success ) const \

/*! A macro for the Teuchos Unit Test Harness for comparing ordinal data types
 * and containers of ordinal data types.
 * 
 * This macro allows tuples (Utility::Pair, Utility::Trip and Utility::Quad),
 * which are not supported by the standard Teuchos Unit Test Harness, to be
 * easily tested.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_TEST_EQUALITY( t1, t2 )					\
  {									\
    const bool result = Utility::compare(t1,#t1,t2,#t2,out,-1);		\
    (out) << TEUCHOS_PASS_FAIL(result) << "\n";				\
    if( !result ) success = false;					\
  }

/*! \brief A macro for the Teuchos Unit Test Harness for comparing floating 
 * point data types and containers of floating point data types.
 *
 * This macro allows tuples (Utility::Pair, Utility::Trip and Utility::Quad), 
 * which are not supported by the standard Teuchos Unit Test Harness, to be 
 * easily tested.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_TEST_FLOATING_EQUALITY( t1, t2, tol )			\
  {									\
    const bool result = Utility::compare(t1,#t1,t2,#t2,out,-1,tol);	\
    (out) << TEUCHOS_PASS_FAIL(result) << "\n";				\
    if( !result ) success = false;					\
  }

/*! A macro for the Teuchos Unit Test Harness for comparing arrays of ordinal 
 * data types and arrays of containers of ordinal data types.
 *
 * This macro allows arrays of tuples (Utility::Pair, Utility::Trip and
 * Utility::Quad), which are not supported by the standard Teuchos Unit Test
 * Harness, to be easily tested.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_TEST_COMPARE_ARRAYS( a1, a2 )				\
  {									\
    const bool result = Utility::compareArrays(a1,#a1,a2,#a2,out);	\
    if( !result ) success = false;					\
  }

/*! A macro for the Teuchos Unit Test Harness for comparing arrays of floating
 * point data types and arrays of containers of floating point data types.
 *
 * This macro allows arrays of tuples (Utility::Pair, Utility::Trip and
 * Utility::Quad), which are not supported by the standard Teuchos Unit Test
 * Harness, to be easily tested.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_TEST_COMPARE_FLOATING_ARRAYS( a1, a2, tol )		\
  {									\
    const bool result =	Utility::compareArrays(a1,#a1,a2,#a2,out,tol);	\
    if( !result ) success = false;					\
  }

#endif // end UTILITY_UNIT_TEST_HARNESS_EXTENSIONS_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTestHarnessExtensions.hpp 
//---------------------------------------------------------------------------//

