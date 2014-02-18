//---------------------------------------------------------------------------//
//!
//! \file   FACEMC_TestingHelpers.hpp
//! \author Alex Robinson
//! \brief  Functions that aid in the testing of FACEMC classes
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_TESTING_HELPERS_HPP
#define FACEMC_TESTING_HELPERS_HPP

// Std Lib Includes
#include <iostream>
#include <list>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_FancyOStream.hpp>

// FACEMC Includes
#include "Tuple.hpp"
#include "ComparePolicy.hpp"
#include "ArrayTraits.hpp"

/*! \defgroup print_format Object Printing Format
 * \ingroup testing
 *
 * This group defines how some types used by FACEMC are output when printed to
 * the terminal using the stream operator.
 */ 

/*! \brief Stream operator for Pair
 * \ingroup print_format
 */
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream &out, const FACEMC::Pair<T1,T2> &p)
{
  out << "{ " << p.first << ", " << p.second << " }";
  return out;
}

/*! Stream operator for Trip
 * \ingroup print_format
 */
template<typename T1, typename T2, typename T3>
std::ostream& operator<<(std::ostream &out, const FACEMC::Trip<T1,T2,T3> &p)
{
  out << "{ " << p.first << ", " << p.second << ", " << p.third << " }";
  return out;
}

/*! Stream operator for Quad
 * \ingroup print_format
 */
template<typename T1, typename T2, typename T3, typename T4>
std::ostream& operator<<(std::ostream &out, const FACEMC::Quad<T1,T2,T3,T4> &p)
{
  out << "{ " << p.first << ", " << p.second << ", " << p.third 
      << ", " << p.fourth << " }";
  return out;
}

/*! Stream operator for std::list
 * \ingroup print_format
 */
template<typename T, template<typename,typename> class List>
std::ostream& operator<<( std::ostream &out, 
			  List<T,std::allocator<T> > &list)
{
  typename List<T,std::allocator<T> >::const_iterator element, end_element;
  element = list.begin();
  end_element = list.end();

  out << "{";

  while( element != end_element )
  {
    out << *element;
    
    ++element;
    if( element != end_element )
      out << ", ";
  }

  out << "}";
  
  return out;
}

namespace FACEMC{

/*! \brief A function for comparing individual types.
 *
 * This function is used by the Teuchos Unit Test Harness extension testing
 * macros (see \ref unit_test_harness_extensions). It allows any type commonly 
 * used by FACEMC to be tested. The generality is made possible through the
 * FACEMC::Policy::ComparePolicy. Refer to the FACEMC::Policy::ComparePolicy 
 * to gain a better understanding of how this function operates.
 * \tparam T A data type that will be tested.
 * \param[in] first_value The first value that will be tested.
 * \param[in] first_name The name given to the first value, which will be 
 * used to refer to the value if the test fails.
 * \param[in] second_value The second value that will be tested.
 * \param[in] second_name The name given to the second value, which will be 
 * used to refer to the value if the test fails.
 * \param[in,out] out The output stream that will be used to output the
 * results of the test.
 * \param[in] index The index in the array that corresponds to the values
 * being tested. An index of -1 indicates that the values are not part
 * of an array.
 * \param[in] tol The testing tolerance used to compare floating point
 * values. This will be ignored with integer comparisons.
 * \ingroup unit_test_harness_extensions
 */
template<typename T>
bool compare( const T &first_value,
	      const std::string &first_name,
	      const T &second_value,
	      const std::string &second_name,
	      Teuchos::FancyOStream &out,
	      const int index = -1,
	      const double tol = 0.0 )
{
  bool success = Policy::ComparePolicy<T>::compare( first_value,
						    first_name,
						    second_value,
						    second_name,
						    out,
						    index,
						    tol );
  return success;
}
  
/*! \brief A function for comparing arrays of types.
 * 
 * This function is used by the Teuchos Unit Test Harness extension testing
 * macros (see \ref unit_test_harness_extensions). It allows any type commonly
 * used by FACEMC in an array to be tested. The generality is made possible
 * through the FACEMC::Policy::ComparePolicy. Refer to the 
 * FACEMC::Policy::ComparePolicy to gain a better understanding of how this 
 * function operates.
 * \tparam T A data type that will be tested.
 * \tparam Array1 The first array type containing data that will be tested.
 * \tparam Array2 The second array type containing data that will be tested.
 * \param[in] a1 The first array containing data that needs to be tested.
 * \param[in] a1_name The name given to the first array, which will be used
 * to refer to the array if the test fails.
 * \param[in] a2 The second array containing data that needs to be tested.
 * \param[in] a2_name The name given to the second array, which will be used
 * to refer to the array if the test fails.
 * \param[in,out] out The output stream that will be used to output the 
 * results of the test.
 * \param[in] tol The testing tolerance used to compare floating point values
 * in the arrays. This will be ignored with integer comparisons.
 * \ingroup unit_test_harness_extensions
 */
template<typename T,
	 template<typename> class Array1,
	 template<typename> class Array2>
bool compareSingleTemplateParameterArrays( const Array1<T> &a1,
					   const std::string &a1_name,
					   const Array2<T> &a2,
					   const std::string &a2_name,
					   Teuchos::FancyOStream &out,
					   const double tol = 0.0 )
{
  return compareArrays( a1,
			a1_name,
			a2,
			a2_name,
			out,
			tol );
}

/*! \brief A function for comparing arrays of types.
 * 
 * This function is used by the Teuchos Unit Test Harness extension testing
 * macros (see \ref unit_test_harness_extensions). It allows any type commonly
 * used by FACEMC in an array to be tested. The generality is made possible
 * through the FACEMC::Policy::ComparePolicy. Refer to the 
 * FACEMC::Policy::ComparePolicy to gain a better understanding of how this 
 * function operates.
 * \tparam Array1 The first array type containing data that will be tested.
 * \tparam Array2 The second array type containing data that will be tested.
 * \param[in] a1 The first array containing data that needs to be tested.
 * \param[in] a1_name The name given to the first array, which will be used
 * to refer to the array if the test fails.
 * \param[in] a2 The second array containing data that needs to be tested.
 * \param[in] a2_name The name given to the second array, which will be used
 * to refer to the array if the test fails.
 * \param[in,out] out The output stream that will be used to output the 
 * results of the test.
 * \param[in] tol The testing tolerance used to compare floating point values
 * in the arrays. This will be ignored with integer comparisons.
 * \ingroup unit_test_harness_extensions
 */
template<typename Array1, typename Array2>
bool compareArrays( const Array1 &a1,
		    const std::string &a1_name,
		    const Array2 &a2,
		    const std::string &a2_name,
		    Teuchos::FancyOStream &out,
		    const double tol = 0.0 )
{
  typedef typename FACEMC::Traits::ArrayTraits<Array1>::value_type value_type;
  
  bool success = true;

  out << "Comparing " << a1_name << " == " << a2_name << " ... ";
  
  // ArrayViews are used so that TwoDArrays will be linearized
  Teuchos::ArrayView<const value_type> view1 = FACEMC::getArrayView( a1 );
  Teuchos::ArrayView<const value_type> view2 = FACEMC::getArrayView( a2 );
  
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
    bool local_success = Policy::ComparePolicy<value_type>::compare( view1[i], 
								     a1_name, 
								     view2[i], 
								     a2_name,
								     out,
								     i,
								     tol );
    if( !local_success )
      success = false;
  }
  
  return success;
}

} // end FACEMC namespace

#endif // end FACEMC+TESTING_HELPERS_HPP

//---------------------------------------------------------------------------//
// end FACEMC_TestingHelpers.hpp
//---------------------------------------------------------------------------//
