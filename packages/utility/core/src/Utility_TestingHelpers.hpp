//---------------------------------------------------------------------------//
//!
//! \file   Utility_TestingHelpers.hpp
//! \author Alex Robinson
//! \brief  Functions that aid in the testing of various classes
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TESTING_HELPERS_HPP
#define UTILITY_TESTING_HELPERS_HPP

// Std Lib Includes
#include <iostream>
#include <list>
#include <utility>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_FancyOStream.hpp>

// FRENSIE Includes
#include "Utility_Tuple.hpp"
#include "Utility_ComparisonTraits.hpp"
#include "Utility_ArrayTraits.hpp"

/*! \defgroup print_format Object Printing Format
 * \ingroup testing
 *
 * This group defines how some types used by Utility are output when printed to
 * the terminal using the stream operator.
 */

/*! Stream operator for std::list
 * \ingroup print_format
 */
template<typename T, template<typename,typename> class List>
std::ostream& operator<<( std::ostream& out,
			  List<T,std::allocator<T> >& list)
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

namespace Utility{

/*! \brief A function for comparing arrays of types.
 *
 * This function is used by the Teuchos Unit Test Harness extension testing
 * macros (see \ref unit_test_harness_extensions). It allows any type commonly
 * used by Utility in an array to be tested. The generality is made possible
 * through the Utility::ComparisonTraits. Refer to the
 * Utility::ComparisonTraits to gain a better understanding of how this
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
bool compareArrays( const Array1& a1,
		    const std::string& a1_name,
		    const Array2& a2,
		    const std::string& a2_name,
		    Teuchos::FancyOStream& out,
		    const double tol = 0.0 )
{
  typedef typename Utility::ArrayTraits<Array1>::value_type value_type;

  bool success = true;

  out << "Comparing " << a1_name << " == " << a2_name << " ... " << "\n";

  // ArrayViews are used so that TwoDArrays will be linearized
  Teuchos::ArrayView<const value_type> view1 = Utility::getArrayView( a1 );
  Teuchos::ArrayView<const value_type> view2 = Utility::getArrayView( a2 );

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
    bool local_success =
      Utility::compare( view1[i], a1_name, view2[i], a2_name, out, i, tol );
    
    if( !local_success )
      success = false;
  }

  return success;
}

} // end Utility namespace

#endif // end UTILITY_TESTING_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_TestingHelpers.hpp
//---------------------------------------------------------------------------//
