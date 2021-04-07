//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ComptonProfileSubshellConverter.hpp
//! \author Alex Robinson
//! \brief  Compton profile subshell-to-index converter
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP
#define MONTE_CARLO_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP

// FRENSIE Includes
#include "Data_SubshellType.hpp"

namespace MonteCarlo{

//! The Compton profile subshell-to-index converter
class ComptonProfileSubshellConverter
{

public:

  //! Default Constructor
  ComptonProfileSubshellConverter()
  { /* ... */ }

  //! Destructor
  ~ComptonProfileSubshellConverter()
  { /* ... */ }

  //! Convert a subshell enum to a compton profile subshell index
  virtual unsigned convertSubshellToIndex(
				       const Data::SubshellType subshell ) const = 0;

  //! Test if a subshell enum is valid
  virtual bool isSubshellValid( const Data::SubshellType subshell ) const;
};

// Test if a subshell enum is valid
/*! \details The default implementation assumes that the
 * convertSubshellToIndex implementation will throw a std::logic_error when
 * the subshell is invalid.
 */
inline bool ComptonProfileSubshellConverter::isSubshellValid(
					    const Data::SubshellType subshell ) const
{
  bool valid_shell = true;

  try{
    this->convertSubshellToIndex( subshell );
  }
  catch( std::logic_error )
  {
    valid_shell = false;
  }

  return valid_shell;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ComptonProfileSubshellConverter.hpp
//---------------------------------------------------------------------------//
