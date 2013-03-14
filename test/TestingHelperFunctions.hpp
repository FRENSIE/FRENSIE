//---------------------------------------------------------------------------//
// \file   TestingHelperFunctions.hpp
// \author Alex Robinson
// \brief  Functions that aid in the testing of FACEMC class
//---------------------------------------------------------------------------//

#ifndef TESTING_HELPER_FUNCTIONS_HPP
#define TESTING_HELPER_FUNCITONS_HPP

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_FancyOStream.hpp>

// FACEMC Includes
#include "Tuple.hpp"
#include "ComparePolicy.hpp"
#include "ArrayTestingPolicy.hpp"
#include "TypeTestingPolicy.hpp"

// Define a new Macro for the Teuchos Unit Test Harness for creating a
// templated unit test on one type and one template template parameter
#define FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_DECL(TEST_GROUP, TEST_NAME, TYPE1, ARRAY) \
  template<typename TYPE1, template<typename> class ARRAY> \
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Teuchos::UnitTestBase \
  {									\
  public:								\
    TEST_GROUP##_##TEST_NAME##_UnitTest(				\
      const std::string& type1Name,					\
      const std::string& arrayName					\
    )                                                                   \
    : Teuchos::UnitTestBase(						\
	std::string(#TEST_GROUP)+"_Teuchos::"+arrayName+"<"+type1Name+">", #TEST_NAME ) \
    {}									\
    void runUnitTestImpl( Teuchos::FancyOStream &out, bool &success ) const; \
    virtual std::string unitTestFile() const { return __FILE__; }	\
    virtual long int unitTestFileLineNumber() const { return __LINE__; } \
  };									\
									\
  template<typename TYPE1, template<typename> class ARRAY>		\
  void TEST_GROUP##_##TEST_NAME##_UnitTest<TYPE1,ARRAY>::runUnitTestImpl( \
                      Teuchos::FancyOStream &out, bool &success ) const \

// Define a new Macro for the Teuchos Unit Test Harness for instantiating a
// templated unit test on one type and one template template parameter
#define FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT(TEST_GROUP, TEST_NAME, TYPE1, ARRAY) \
  template class TEST_GROUP##_##TEST_NAME##_UnitTest<TYPE1, Teuchos::ARRAY >; \
  TEST_GROUP##_##TEST_NAME##_UnitTest<TYPE1, Teuchos::ARRAY >		\
  instance_##TEST_GROUP##_##TYPE1##_##ARRAY##_##TEST_NAME##_UnitTest(#TYPE1,#ARRAY);

// Define a new Macro for the Teuchos Unit Test Harness for creating a
// templated unit test on two types and one template template parameter
#define FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_DECL(TEST_GROUP, TEST_NAME, MEMBER, TYPE1, ARRAY) \
  template<FACEMC::TupleMember MEMBER, typename TYPE1, template<typename> class ARRAY> \
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Teuchos::UnitTestBase \
  {									\
  public:								\
    TEST_GROUP##_##TEST_NAME##_UnitTest(				\
      const std::string& MemberName,	                                \
      const std::string& type1Name,                                     \
      const std::string& arrayName					\
    )                                                                   \
    : Teuchos::UnitTestBase(						\
	std::string(#TEST_GROUP)+"_Teuchos::"+arrayName+"<"+type1Name+">_"+MemberName, #TEST_NAME ) \
    {}									\
    void runUnitTestImpl( Teuchos::FancyOStream &out, bool &success ) const; \
    virtual std::string unitTestFile() const { return __FILE__; }	\
    virtual long int unitTestFileLineNumber() const { return __LINE__; } \
  };									\
									\
  template<FACEMC::TupleMember MEMBER, typename TYPE1, template<typename> class ARRAY> \
  void TEST_GROUP##_##TEST_NAME##_UnitTest<MEMBER,TYPE1,ARRAY>::runUnitTestImpl(\
                      Teuchos::FancyOStream &out, bool &success ) const \

// Define a new Macro for the Teuchos Unit Test Harness for instantiating a
// templated unit test on two type and one template template parameter
#define FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT(TEST_GROUP, TEST_NAME, MEMBER, TYPE1, ARRAY) \
  template class TEST_GROUP##_##TEST_NAME##_UnitTest<FACEMC::MEMBER, TYPE1, Teuchos::ARRAY >; \
  TEST_GROUP##_##TEST_NAME##_UnitTest<FACEMC::MEMBER, TYPE1, Teuchos::ARRAY > \
  instance_##TEST_GROUP##_##MEMBER##_##TYPE1##_##ARRAY##_##TEST_NAME##_UnitTest(#MEMBER,#TYPE1,#ARRAY);

// Define a new Macro for the Teuchos Unit Test Harness for comparing
// Tuples of ordinal data types or ordinal data types
#define FACEMC_TEST_EQUALITY( t1, t2 )					\
  {									\
    const bool result = FACEMC::compare(t1,#t1,t2,#t2,out,-1);		\
    (out) << TEUCHOS_PASS_FAIL(result) << "\n";				\
    if( !result ) success = false;					\
  }

// Define a new Macro for the Teuchos Unit Test Harness for comparing
// Tuples of floating point data types
#define FACEMC_TEST_FLOATING_EQUALITY( t1, t2, tol )			\
  {									\
    const bool result = FACEMC::compare(t1,#t1,t2,#t2,out,-1,tol);	\
    (out) << TEUCHOS_PASS_FAIL(result) << "\n";				\
    if( !result ) success = false;					\
  }

// Define a new Macro for the Teuchos Unit Test Harness for comparing arrays
// of Tuples of ordinal data types
#define FACEMC_TEST_COMPARE_ARRAYS( a1, a2 )				\
  {									\
    const bool result = FACEMC::compareArrays(a1,#a1,a2,#a2,out);	\
    if( !result ) success = false;					\
  }

// Define a new Macro for the Teuchos Unit Test Harness for comparing arrays
// of Tuples of floating point data types
#define FACEMC_TEST_COMPARE_FLOATING_ARRAYS( a1, a2, tol )		\
  {									\
    const bool result =	FACEMC::compareArrays(a1,#a1,a2,#a2,out,tol);	\
    if( !result ) success = false;					\
  }

namespace Teuchos{

// Stream operator for Tuple: this must be defined in the Teuchos namespace to 
// work properly with the Teuchos Unit Test Harness.
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream &out, const FACEMC::Pair<T1,T2> &p)
{
  out << "{ " << p.first << ", " << p.second << " }";
  return out;
}

template<typename T1, typename T2, typename T3>
std::ostream& operator<<(std::ostream &out, const FACEMC::Trip<T1,T2,T3> &p)
{
  out << "{ " << p.first << ", " << p.second << ", " << p.third << " }";
  return out;
}

template<typename T1, typename T2, typename T3, typename T4>
std::ostream& operator<<(std::ostream &out, const FACEMC::Quad<T1,T2,T3,T4> &p)
{
  out << "{ " << p.first << ", " << p.second << ", " << p.third 
      << ", " << p.fourth << " }";
  return out;
}  

} // end Teuchos namespace

namespace FACEMC{

// Function for comparing individual types
template<typename T>
bool compare( const T &first_value,
	      const std::string &first_name,
	      const T &second_value,
	      const std::string &second_name,
	      Teuchos::FancyOStream &out,
	      const int index = 0,
	      const double tol = 0.0 )
{
  bool success = ComparePolicy<T>::compare( first_value,
					    first_name,
					    second_value,
					    second_name,
					    out,
					    index,
					    tol );
  if( success )
    out << "passed\n";

  return success;
}
  
// Function for comparing arrays of types
template<typename T,
	 template<typename> class Array1,
	 template<typename> class Array2>
bool compareArrays( const Array1<T> &a1,
		    const std::string &a1_name,
		    const Array2<T> &a2,
		    const std::string &a2_name,
		    Teuchos::FancyOStream &out,
		    const double tol = 0.0 )
{
  bool success = true;

  out << "Comparing " << a1_name << " == " << a2_name << " ... ";
  
  // ArrayViews are used so that TwoDArrays will be linearized
  Teuchos::ArrayView<const T> view1 = ArrayTestingPolicy<T,Array1>::view( a1 );
  Teuchos::ArrayView<const T> view2 = ArrayTestingPolicy<T,Array2>::view( a2 );
  
  const int n = view1.size();
  const int m = view2.size();
  
  // Compare sizes
  if( m != n )
  {
    out << "\nError, " << a1_name << ".size() = " << n << " == "
	<< a2_name << ".size() = " << m << " : failed!\n";
    return false;
  }

  // Compare Elements
  for( int i = 0; i < n; ++i )
  {
    bool local_success = ComparePolicy<T>::compare( view1[i], 
						    a1_name, 
						    view2[i], 
						    a2_name,
						    out,
						    i,
						    tol );
    if( !local_success )
      success = false;
  }

  if( success )
    out << "passed\n";

  return success;
}

// Simple equality operator for comparing tuples. Avoid using these since
// they will not give as much info when a test fails.
template<typename T1, typename T2>
inline bool operator==( const FACEMC::Pair<T1,T2> &left,
			const FACEMC::Pair<T1,T2> &right )
{
  return ( (left.first == right.first) && (left.second == right.second) );
}

template<typename T1, typename T2, typename T3>
inline bool operator==( const FACEMC::Trip<T1,T2,T3> &left,
			const FACEMC::Trip<T1,T2,T3> &right )
{
  return ( (left.first == right.first) && 
	   (left.second == right.second) &&
	   (left.third == right.third) );
}

template<typename T1, typename T2, typename T3, typename T4>
inline bool operator==( const FACEMC::Quad<T1,T2,T3,T4> &left,
			const FACEMC::Quad<T1,T2,T3,T4> &right )
{
  return ( (left.first == right.first) &&
	   (left.second == right.second) &&
	   (left.third == right.third) &&
	   (left.fourth == right.fourth) );
}

} // end FACEMC namespace

#endif // end TESTING_HELPER_FUNCTIONS_HPP

//---------------------------------------------------------------------------//
// end TestingHelperFunctions.hpp
//---------------------------------------------------------------------------//
