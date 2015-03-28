//---------------------------------------------------------------------------//
//!
//! \file   Utility_ArrayString.hpp
//! \author Alex Robinson
//! \brief  Generic array string parser class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ARRAY_STRING_HPP
#define UTILITY_ARRAY_STRING_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

//! The generic array string parser class
class ArrayString : public ParameterListCompatibleObject<ArrayString>
{

public:

  //! Replace all occurances of pi with the number
  static void locateAndReplacePi( std::string& array_string );

  //! Replace all occurances of i with an appropriate subarray
  static void locateAndReplaceIntervalOperator( std::string& array_string );

  //! Default constructor
  ArrayString();

  //! Constructor
  ArrayString( const std::string& array_string );

  //! Copy constructor
  ArrayString( const ArrayString& other );

  //! Assignment operator
  ArrayString& operator=(const ArrayString& other );

  //! Destructor
  ~ArrayString()
  { /* ... */ }

  //! Return the parsed array string
  const std::string& getString() const;

  //! Return the concrete array
  template<typename T>
  const Teuchos::Array<T> getConcreteArray() const;

  //! Test if boolean data is present
  bool isBooleanDataPresent() const;

  //! Test if floating point data is present
  bool isFloatingPointDataPresent() const;

  //! Test if the string represents a multidimentional array
  bool isMultidimentionalDataPresent() const;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is );

  //! Method for testing if two objects are equivalent
  bool isEqual( const ArrayString& other ) const;

private:

  // replace occurances of pi within a substring
  static void replacePiInSubstring( const std::string::size_type start,
				    const std::string::size_type true_end,
				    std::string& array_string );

  // replace occurances of interval operator within a substring
  static void replaceIntervalOperatorInSubstring( 
					    const std::string& left_element,
					    std::string& middle_element,
					    const std::string& right_element );

  // The array representation string
  std::string d_array_string;  
};

// Return the concrete array
template<typename T>
const Teuchos::Array<T> ArrayString::getConcreteArray() const
{
  try{
    return Teuchos::fromStringToArray<T>( d_array_string );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::InvalidArrayStringRepresentation,
			   "Error converting string to array!" );
}

} // end Utility namespace

namespace Teuchos{
  
/*! Type name traits specialization for the Utility::ArrayString
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::ArrayString>
{

public:
  
  static std::string name()
  {
    return "Array";
  }
  static std::string concreteName( const Utility::ArrayString& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

#endif // end UTILITY_ARRAY_STRING_HPP

//---------------------------------------------------------------------------//
// end Utility_ArrayString.hpp
//---------------------------------------------------------------------------//
