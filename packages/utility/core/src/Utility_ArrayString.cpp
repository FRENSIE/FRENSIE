//---------------------------------------------------------------------------//
//!
//! \file   Utility_ArrayString.cpp
//! \author Alex Robinson
//! \brief  Generic array string parser class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// Boost Includes
#include <boost/algorithm/string.hpp>

// FRENSIE Includes
#include "Utility_ArrayString.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Initialize static member data
const bool ArrayString::s_initialized =
  ArrayString::initialize();

// Replace all occurances of pi with the number
void ArrayString::locateAndReplacePi( std::string& array_string )
{
  // Loop through all element tokens of the array string
  std::string::size_type elem_start_pos = array_string.find( "{" );
  ++elem_start_pos;

  std::string::size_type elem_end_pos = array_string.find_first_of( ",}",
							   elem_start_pos );

  std::string::size_type orig_string_size = array_string.size();

  while( elem_end_pos < array_string.size() )
  {
    ArrayString::replacePiInSubstring( elem_start_pos,
				       elem_end_pos - 1,
				       array_string );

    if( orig_string_size != array_string.size() )
    {
      elem_start_pos = array_string.find( "{" );

      elem_end_pos = array_string.find_first_of( ",}", elem_start_pos );

      orig_string_size = array_string.size();
    }
    else
    {
      elem_start_pos = elem_end_pos+1;

      elem_end_pos = array_string.find_first_of( ",}", elem_start_pos );
    }
  }
}

void ArrayString::replacePiInSubstring( const std::string::size_type start,
					const std::string::size_type true_end,
					std::string& array_string )
{
  std::string::size_type pi_pos = array_string.find( "pi", start );

  TEST_FOR_EXCEPTION( array_string.find( "pi", pi_pos+2 ) < true_end,
		      std::runtime_error,
		      "Error: 'pi' cannot occur multiple times in the same "
		      "array element!" );

  if( pi_pos >= start && pi_pos < true_end )
  {
    double front_value = 1.0, end_value = 1.0;

    std::string front_string = array_string.substr( start, pi_pos-start );

    if( front_string.find_first_of( "0123456789" ) < front_string.size() )
    {
      std::istringstream iss( front_string );

      iss >> front_value;
    }
    else if( front_string.find( "-" ) < front_string.size() )
      front_value = -1.0;

    std::string::size_type div_pos = array_string.find_first_of( "/", start );

    if( div_pos < true_end && div_pos > pi_pos )
    {
      std::string end_string =
	array_string.substr( div_pos+1, true_end - div_pos );

      if( end_string.find_first_of( "0123456789" ) <
	  end_string.size() )
      {
	std::istringstream iss( end_string );

	iss >> end_value;
      }
    }
    else if( div_pos < pi_pos )
    {
      THROW_EXCEPTION( std::runtime_error,
		       "Error: invalid array element value ("
		       << array_string.substr( start, true_end )
		       << ")! " );
    }

    std::ostringstream oss;
    oss.precision( 18 );

    oss << front_value*Utility::PhysicalConstants::pi/end_value;

    array_string.replace( start, true_end - start + 1, oss.str() );
  }
}

// Replace all occurances of i with an appropriate subarray
void ArrayString::locateAndReplaceIntervalOperator( std::string& array_string )
{
  // Loop through all array elements
  boost::trim( array_string );

  Teuchos::Array<std::string> array_elements;

  boost::split( array_elements,
		array_string,
		boost::is_any_of( "," ) );

  TEST_FOR_EXCEPTION( array_elements.front().find_first_of( "il" ) <
		      array_elements.front().size(),
		      std::runtime_error,
		      "Error: the first array element cannot have an "
		      "interval operator!" );

  TEST_FOR_EXCEPTION( array_elements.back().find_first_of( "il" ) <
		      array_elements.back().size(),
		      std::runtime_error,
		      "Error: the last array element cannot have an "
		      "interval operator!" );

  std::string::size_type bracket_pos = array_elements.front().find( "{" );

  if( bracket_pos < array_elements.front().size() )
    array_elements.front().erase( bracket_pos, 1 );

  bracket_pos = array_elements.back().find( "}" );

  if( bracket_pos < array_elements.back().size() )
    array_elements.back().erase( bracket_pos, 1 );

  for( unsigned i = 1; i < array_elements.size()-1; ++i )
  {
    ArrayString::replaceIntervalOperatorInSubstring( array_elements[i-1],
						     array_elements[i],
						     array_elements[i+1] );
  }

  // Reconstruct the array string
  array_string = "{";
  array_string += array_elements.front();

  for( unsigned i = 1; i < array_elements.size(); ++i )
  {
    array_string += ",";
    array_string += array_elements[i];
  }

  array_string += "}";
}

// replace occurances of interval operator within a substring
void ArrayString::replaceIntervalOperatorInSubstring(
					    const std::string& left_element,
					    std::string& middle_element,
					    const std::string& right_element )
{
  bool raw_left_element = left_element.find( "," ) > left_element.size();
  bool raw_right_element = right_element.find( "," ) > right_element.size();

  std::string::size_type op_pos = middle_element.find_first_of( "il" );

  if( raw_left_element && raw_right_element &&
      op_pos < middle_element.size() )
  {
    TEST_FOR_EXCEPTION( left_element.find_first_of( "il" ) <
			left_element.size(),
			std::runtime_error,
			"Error: interval operators cannot occur in "
			"consecutive array elements!" );

    TEST_FOR_EXCEPTION( right_element.find_first_of( "il" ) <
			right_element.size(),
			std::runtime_error,
			"Error: interval operators cannot occur in "
			"consecutive array elements!" );

    double left_value, right_value;

    {
      std::istringstream iss( left_element );

      iss >> left_value;
    }

    {
      std::istringstream iss( right_element );

      iss >> right_value;
    }

    TEST_FOR_EXCEPTION( left_value > right_value,
			std::runtime_error,
			"Error: the array elements must be in ascending "
			"order (" << left_value << " !<= " << right_value <<
			")!" );

    int intervals;

    {
      std::istringstream iss( middle_element.substr( 0, op_pos ) );

      iss >> intervals;
    }

    TEST_FOR_EXCEPTION( intervals <= 0,
			std::runtime_error,
			"Error: a positive integer must be specified with "
			"the interval operator!" );

    // Increment the interval value to account for the last element
    ++intervals;

    // Linear increments
    if( middle_element[op_pos] == 'i' )
    {
      double step_size = (right_value-left_value)/intervals;

      // Replace the interval operator with the new array elements
      middle_element.clear();

      for( unsigned i = 1; i < intervals; ++i )
      {
	std::ostringstream oss;
	oss.precision( 18 );

	oss << left_value + step_size*i;

	middle_element += oss.str();

	if( i < intervals-1 )
	  middle_element += ",";
      }
    }
    else // log increments
    {
      TEST_FOR_EXCEPTION( left_value <= 0.0,
			  std::runtime_error,
			  "Error: the starting value ( "
			  << left_value << ") must be positive when "
			  "using the log interval operator (l)!" );

      double step_size = log(right_value/left_value)/intervals;

      // Replace the interval operator with the new array elements
      middle_element.clear();

      for( unsigned i = 1; i < intervals; ++i )
      {
	std::ostringstream oss;
	oss.precision( 18 );

	oss << exp( log(left_value) + step_size*i );

	middle_element += oss.str();

	if( i < intervals-1 )
	  middle_element += ",";
      }
    }
  }
}

// Default constructor
ArrayString::ArrayString()
  : ParameterListCompatibleObject<ArrayString>()
{ /* ... */ }

// Constructor
ArrayString::ArrayString( const std::string& array_string )
  : ParameterListCompatibleObject<ArrayString>(),
    d_array_string( array_string )
{
  // Make sure the array rep is valid
  testPrecondition( array_string.size() >= 2 );

  // Replace all occurances of pi with the number
  locateAndReplacePi( d_array_string );

  // Replace all occurances of i with an appropriate subarray
  locateAndReplaceIntervalOperator( d_array_string );
}

// Copy constructor
ArrayString::ArrayString( const ArrayString& other )
  : ParameterListCompatibleObject<ArrayString>(),
    d_array_string( other.d_array_string )
{
  // Make sure the array rep is valid
  testPrecondition( other.d_array_string.size() >= 2 );
}


// Assignment operator
ArrayString& ArrayString::operator=( const ArrayString& other )
{
  // Make sure the
  testPrecondition( other.d_array_string.size() >= 2 );

  if( &other != this )
  {
    d_array_string = other.d_array_string;
  }

  return *this;
}

// Return the parsed array string
const std::string& ArrayString::getString() const
{
  return d_array_string;
}

// Test if boolean data is present
bool ArrayString::isBooleanDataPresent() const
{
  return d_array_string.find_first_not_of( "01,{} " ) >= d_array_string.size();
}

// Test if floating point data is present
bool ArrayString::isFloatingPointDataPresent() const
{
  return d_array_string.find_first_of( ".eE" ) < d_array_string.size();
}

// Test if the string represents a multidimentional array
bool ArrayString::isMultidimentionalDataPresent() const
{
  unsigned first_array_bound_pos =
    d_array_string.find( "{" );

  return d_array_string.find( "{", first_array_bound_pos+1 ) <
    d_array_string.size();
}

// Method for placing the object in an output stream
void ArrayString::toStream( std::ostream& os ) const
{
  os << d_array_string;
}

// Method for initializing the object from an input stream
void ArrayString::fromStream( std::istream& is )
{
  std::getline( is, d_array_string, '}' );

  if( d_array_string[d_array_string.size()-1] != '}' )
    d_array_string.push_back( '}' );

  // Replace all occurances of pi with the number
  locateAndReplacePi( d_array_string );

  // Replace all occurances of i with an appropriate subarray
  locateAndReplaceIntervalOperator( d_array_string );
}

// Method for testing if two objects are equivalent
bool ArrayString::isEqual( const ArrayString& other ) const
{
  return d_array_string == other.d_array_string;
}

// Initialize the array string class
bool ArrayString::initialize()
{
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::ArrayString );

  return true;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_ArrayString.cpp
//---------------------------------------------------------------------------//
