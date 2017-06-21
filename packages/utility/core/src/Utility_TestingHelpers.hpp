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
#include <sstream>
#include <iterator>
#include <type_traits>
#include <algorithm>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_FancyOStream.hpp>

// FRENSIE Includes
#include "Utility_Tuple.hpp"
#include "Utility_ComparisonTraits.hpp"
#include "Utility_StreamHelpers.hpp"

namespace Utility{

/*! \brief A function for comparing container contents
 *
 * This is an ordered comparison.
 * \ingroup unit_test_harness_extensions
 */
template<typename STLCompliantContainer1, typename STLCompliantContainer2>
typename std::enable_if<std::is_same<typename STLCompliantContainer1::value_type,typename STLCompliantContainer2::value_type>::value,bool>::type
compareContainerContents( const STLCompliantContainer1& c1,
                          const std::string& c1_name,
                          const STLCompliantContainer2& c2,
                          const std::string& c2_name,
                          Teuchos::FancyOStream& out,
                          const double tol = 0.0 )
{
  bool success = true;

  // Not all stl compliant containers have a size member function - all
  // have iterators though.
  size_t c1_size = std::distance( c1.begin(), c1.end() );
  size_t c2_size = std::distance( c2.begin(), c2.end() );

  std::string size_comparison_details;

  {
    std::ostringstream oss;
    oss << c1_name << " size = " << c1_size << " == "
	<< c2_name << " size = " << c2_size << " :";

    size_comparison_details = oss.str();
  }
  
  if( c1_size != c2_size )
  {
    out << "\nError, " << size_comparison_details << " failed!\n";
    return false;
  }
  else
    out << "\n" << size_comparison_details << " passed\n";

  // Compare Elements
  typename STLCompliantContainer1::const_iterator c1_it, c1_end;
  c1_it = c1.begin();
  c1_end = c1.end();

  typename STLCompliantContainer2::const_iterator c2_it, c2_end;
  c2_it = c2.begin();
  c2_end = c2.end();

  size_t index = 0;

  while( c1_it != c1_end )
  {
    bool local_success =
      Utility::compare( *c1_it, c1_name, *c2_it, c2_name, out, index, tol );
    
    if( !local_success )
      success = false;

    ++c1_it;
    ++c2_it;
    ++index;
  }

  return success;
}

/*! \brief A function for comparing container contents
 *
 * This is an unordered comparison.
 * \ingroup unit_test_harness_extensions
 */
template<typename STLCompliantContainer1, typename STLCompliantContainer2>
typename std::enable_if<std::is_same<typename STLCompliantContainer1::value_type,typename STLCompliantContainer2::value_type>::value,bool>::type
compareUnorderedContainerContents( const STLCompliantContainer1& c1,
                                   const std::string& c1_name,
                                   const STLCompliantContainer2& c2,
                                   const std::string& c2_name,
                                   Teuchos::FancyOStream& out )
{
  bool success = true;

  // Not all stl compliant containers have a size member function - all
  // have iterators though.
  size_t c1_size = std::distance( c1.begin(), c1.end() );
  size_t c2_size = std::distance( c2.begin(), c2.end() );

  std::string size_comparison_details;

  {
    std::ostringstream oss;
    oss << c1_name << " size = " << c1_size << " == "
	<< c2_name << " size = " << c2_size << " :";

    size_comparison_details = oss.str();
  }
  
  if( c1_size != c2_size )
  {
    out << "\nError, " << size_comparison_details << " failed!\n";
    return false;
  }
  else
    out << "\n" << size_comparison_details << " passed\n";

  // Compare Elements
  std::string containment_comparison_statement;

  {
    std::ostringstream oss;
    oss << c1_name << " && " << c2_name << " contain ";

    containment_comparison_statement = oss.str();
  }
  
  typename STLCompliantContainer1::const_iterator c1_it, c1_end;
  c1_it = c1.begin();
  c1_end = c1.end();

  while( c1_it != c1_end )
  {
    typename STLCompliantContainer2::const_iterator c2_it =
      std::find( c2.begin(), c2.end(), *c1_it );
    
    if( c2_it == c2.end() )
    {
      out << "\nError, " << containment_comparison_statement << *c1_it
          << ": failed!\n";

      success = false;
    }
    else
      out << containment_comparison_statement << *c1_it << ": passed\n";
    
    ++c1_it;
  }

  return success;
}

/*! \brief A function for comparing different containers
 *
 * \ingroup unit_test_harness_extensions
 */
template<typename STLCompliantContainer1, typename STLCompliantContainer2>
typename std::enable_if<std::is_same<typename STLCompliantContainer1::value_type,typename STLCompliantContainer2::value_type>::value,bool>::type
compareContainers( const STLCompliantContainer1& c1,
                        const std::string& c1_name,
                        const STLCompliantContainer2& c2,
                        const std::string& c2_name,
                        Teuchos::FancyOStream& out,
                        const double tol = 0.0 )
{
  out << "Comparing " << c1_name << " contents == "
      << c2_name << " contents ... " << "\n";

  return compareContainerContents( c1, c1_name, c2, c2_name, out, tol );
}

/*! \brief A function for comparing different unordered containers
 *
 * \ingroup unit_test_harness_extensions
 */
template<typename STLCompliantContainer1, typename STLCompliantContainer2>
typename std::enable_if<std::is_same<typename STLCompliantContainer1::value_type,typename STLCompliantContainer2::value_type>::value,bool>::type
compareUnorderedContainers( const STLCompliantContainer1& c1,
                            const std::string& c1_name,
                            const STLCompliantContainer2& c2,
                            const std::string& c2_name,
                            Teuchos::FancyOStream& out )
{
  out << "Comparing " << c1_name << " unordered contents == "
      << c2_name << " unordered contents ... " << "\n";

  return compareUnorderedContainerContents( c1, c1_name, c2, c2_name, out );
}

/*! \brief A function for comparing containers of the same type
 *
 * \ingroup unit_test_harness_extensions
 */
template<typename STLCompliantContainer>
bool compareContainers( const STLCompliantContainer& c1,
                        const std::string& c1_name,
                        const STLCompliantContainer& c2,
                        const std::string& c2_name,
                        Teuchos::FancyOStream& out,
                        const double tol = 0.0 )
{
  out << "Comparing " << c1_name << " == " << c2_name << " ... " << "\n";

  return compareContainerContents( c1, c1_name, c2, c2_name, out, tol );
}

} // end Utility namespace

#endif // end UTILITY_TESTING_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_TestingHelpers.hpp
//---------------------------------------------------------------------------//
