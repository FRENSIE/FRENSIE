//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardComptonProfileSubshellConverter.hpp
//! \author Alex Robinson
//! \brief  Standard Compton profile subshell-to_index converter decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDERD_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP
#define MONTE_CARLO_STANDERD_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP

// FRENSIE Includes
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"

namespace MonteCarlo{

//! The standard Compton profile subshell-to-index converter
template<unsigned Z>
class StandardComptonProfileSubshellConverter : ComptonProfileSubshellConverter
{
 
public:

  //! Default Constructor
  StandardComptonProfileSubshellConverter()
  { /* ... */ }

  //! Destructor
  ~StandardComptonProfileSubshellConverter()
  { /* ... */ }
  
  //! Convert a subshell enum to an compton profile subshell index
  unsigned convertSubshellToIndex( const SubshellType subshell ) const;
};

//! Compton profile traits struct
template<unsigned Z>
struct ComptonProfileTraits
{
  //! Convert a subshell enum to a compton profile index
  static unsigned convertToIndex( const SubshellType subshell )
  {
    THROW_EXCEPTION( std::logic_error, 
		     "Error: Z (" Z ") is invalid!" )
  }
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardComptonProfileSubshellConverter_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDERD_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardComptonProfileSubshellConverter.hpp
//---------------------------------------------------------------------------//
