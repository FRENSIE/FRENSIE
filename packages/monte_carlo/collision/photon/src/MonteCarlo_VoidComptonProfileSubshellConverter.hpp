//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidComptonProfileSubshellConverter.hpp
//! \author Alex Robinson
//! \brief  Void Compton profile subshell-to-index converter
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP
#define MONTE_CARLO_VOID_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP

// FRENSIE Includes
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"

namespace MonteCarlo{

//! The void Compton profile subshell-to-index converter
class VoidComptonProfileSubshellConverter : public ComptonProfileSubshellConverter
{

public:

  //! Default Constructor
  VoidComptonProfileSubshellConverter()
  { /* ... */ }

  //! Destructor
  ~VoidComptonProfileSubshellConverter()
  { /* ... */ }

  //! Convert a subshell enum to a compton profile subshell index
  unsigned convertSubshellToIndex( const Data::SubshellType subshell ) const;

  //! Test if a subshell enum is valid
  bool isSubshellValid( const Data::SubshellType subshell ) const;
};

// Convert a subshell enum to a compton profile subshell index
inline unsigned VoidComptonProfileSubshellConverter::convertSubshellToIndex(
					    const Data::SubshellType subshell ) const
{
  return (unsigned)subshell - 1u;
}

// Test if a subshell enum is valid
inline bool VoidComptonProfileSubshellConverter::isSubshellValid(
					    const Data::SubshellType subshell ) const
{
  return true;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_VOID_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidComptonProfileSubshellConverter.hpp
//---------------------------------------------------------------------------//
