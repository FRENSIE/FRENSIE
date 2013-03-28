//---------------------------------------------------------------------------//
// \file   TestingHelperFunctions.hpp
// \author Alex Robinson
// \brief  Functions that aid in the testing of FACEMC class
//---------------------------------------------------------------------------//

#ifndef TESTING_HELPER_FUNCTIONS_HPP
#define TESTING_HELPER_FUNCITONS_HPP

// Std Lib Includes
#include <iostream>
#include <list>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_FancyOStream.hpp>

// FACEMC Includes
#include "Tuple.hpp"
#include "ComparePolicy.hpp"
#include "ArrayTestingPolicy.hpp"
#include "TypeTestingPolicy.hpp"

namespace Teuchos{

} // end Teuchos namespace 


// Stream operator for Pair
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream &out, const FACEMC::Pair<T1,T2> &p)
{
  out << "{ " << p.first << ", " << p.second << " }";
  return out;
}

// Stream operator for Trip
template<typename T1, typename T2, typename T3>
std::ostream& operator<<(std::ostream &out, const FACEMC::Trip<T1,T2,T3> &p)
{
  out << "{ " << p.first << ", " << p.second << ", " << p.third << " }";
  return out;
}

// Stream operator for Quad
template<typename T1, typename T2, typename T3, typename T4>
std::ostream& operator<<(std::ostream &out, const FACEMC::Quad<T1,T2,T3,T4> &p)
{
  out << "{ " << p.first << ", " << p.second << ", " << p.third 
      << ", " << p.fourth << " }";
  return out;
}

// Stream operator for std::list
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

} // end FACEMC namespace

#endif // end TESTING_HELPER_FUNCTIONS_HPP

//---------------------------------------------------------------------------//
// end TestingHelperFunctions.hpp
//---------------------------------------------------------------------------//
