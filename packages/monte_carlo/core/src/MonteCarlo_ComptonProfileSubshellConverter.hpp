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
#include "MonteCarlo_SubshellType.hpp"

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

  //! Convert a subshell enum to an compton profile subshell index
  unsigned convertSubshellToIndex( const SubshellType subshell ) const = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ComptonProfileSubshellConverter.hpp
//---------------------------------------------------------------------------//
