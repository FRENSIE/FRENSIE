//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardComptonProfileSubshellConverter.hpp
//! \author Alex Robinson
//! \brief  Standard Compton profile subshell-to-index converter decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP
#define MONTE_CARLO_STANDARD_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

//! The standard Compton profile subshell-to-index converter
template<unsigned Z>
class StandardComptonProfileSubshellConverter : public ComptonProfileSubshellConverter
{

public:

  //! Default Constructor
  StandardComptonProfileSubshellConverter()
  { /* ... */ }

  //! Destructor
  ~StandardComptonProfileSubshellConverter()
  { /* ... */ }

  //! Convert a subshell enum to an compton profile subshell index
  unsigned convertSubshellToIndex( const Data::SubshellType subshell ) const;
};

//! Compton profile traits struct
template<unsigned Z>
struct ComptonProfileTraits
{
  //! Convert a subshell enum to a compton profile index
  static unsigned convertToIndex( const Data::SubshellType subshell )
  {
    THROW_EXCEPTION( std::logic_error,
		     "Z (" << Z << ") is invalid!" )
  }
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardComptonProfileSubshellConverter_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardComptonProfileSubshellConverter.hpp
//---------------------------------------------------------------------------//
