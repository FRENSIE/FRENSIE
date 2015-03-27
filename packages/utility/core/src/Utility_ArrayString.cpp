//---------------------------------------------------------------------------//
//!
//! \file   Utility_ArrayString.cpp
//! \author Alex Robinson
//! \brief  Generic array string parser class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "Utility_ArrayString.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Replace all occurances of pi with the number
void ArrayString::locateAndReplacePi( std::string& array_string )
{
  // Loop through all element tokens of the array string
  std::string::size_type elem_start_pos = array_string.find( "{" );
  ++elem_start_pos;
  
  std::string::size_type elem_end_pos = array_string.find( "," );

  std::string::size_type pi_pos;
  
  while( elem_start_pos < array_string.size() )
  {
    ArrayString::replacePiInSubstring( elem_start_pos, elem_end_pos - 1 );

    elem_start_pos = elem_end_pos+1;

    elem_end_pos = array_string.find_first_of( ",}" );
  }
  
  // // Search for and replace "2pi"
  // {
  //   std::ostringstream oss;
  //   oss.precision( 18 );
  //   oss << 2*Utility::PhysicalConstants::pi;
    
  //   std::string::size_type pos = 0;
  
  //   while( pos < array_string.size() )
  //   {
  //     pos = array_string.find( "2pi" );

  //     if( pos < array_string.size() )
  // 	array_string.replace( pos, 3, oss.str() );
  //   }
  // }

  // // Search for and replace "pi"
  // {
  //   std::ostringstream oss;
  //   oss.precision( 18 );
  //   oss << Utility::PhysicalConstants::pi;
    
  //   std::string::size_type pos = 0;
    
  //   while( pos < array_string.size() )
  //   {
  //     pos = array_string.find( "pi" );
      
  //     if( pos < array_string.size() )
  // 	array_string.replace( pos, 2, oss.str() );
  //   }
  // }
}

void ArrayString::replacePiInSubstring( const std::string::size_type start,
					const std::string::size_type true_end,
					std::string& array_string )
{
  
}

// Replace all occurances of i with an appropriate subarray
void ArrayString::locateAndReplaceIntervalOperator( std::string& array_string )
{
  
}

// Replace all occurances of ilog with an appropriate subarray
void ArrayString::locateAndReplaceLogIntervalOperator( 
						    std::string& array_string )
{

}

// Default constructor
ArrayString::ArrayString()
{ /* ... */ }

// Constructor
ArrayString::ArrayString( const std::string& array_string )
  : d_array_string( array_string )
{
  // Make sure the array rep is valid
  testPrecondition( array_string.size() >= 2 );

  // Replace all occurances of pi with the number
  locateAndReplacePi( d_array_string );

  // Replace all occurances of i with an appropriate subarray
  locateAndReplaceIntervalOperator( d_array_string );

  // Replace all occurances of ilog with an appropriate subarray
  locateAndReplaceLogIntervalOperator( d_array_string );
}

// Copy constructor
ArrayString::ArrayString( const ArrayString& other )
  : d_array_string( other.d_array_string )
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
  d_array_string.find_first_not_of( "01" ) > d_array_string.size();
}

// Test if floating point data is present
bool ArrayString::isFloatingPointDataPresent() const
{
  d_array_string.find_first_of( ".eE" ) < d_array_string.size();
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
  is >> d_array_string;

  // Replace all occurances of pi with the number
  locateAndReplacePi( d_array_string );

  // Replace all occurances of i with an appropriate subarray
  locateAndReplaceIntervalOperator( d_array_string );

  // Replace all occurances of ilog with an appropriate subarray
  locateAndReplaceLogIntervalOperator( d_array_string );
}

// Method for testing if two objects are equivalent
bool ArrayString::isEqual( const ArrayString& other ) const
{
  return d_array_string == other.d_array_string;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_ArrayString.cpp
//---------------------------------------------------------------------------//
