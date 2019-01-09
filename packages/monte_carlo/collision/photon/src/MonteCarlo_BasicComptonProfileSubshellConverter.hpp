//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BasicComptonProfileSubshellConverter.hpp
//! \author Alex Robinson
//! \brief  Basic Compton profile subshell-to-index converter decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BASIC_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP
#define MONTE_CARLO_BASIC_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP

// FRENSIE Includes
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Map.hpp"

namespace MonteCarlo{

//! The basic Compton profile subshell-to-index converter
class BasicComptonProfileSubshellConverter : public ComptonProfileSubshellConverter
{

public:

  //! Constructor
  BasicComptonProfileSubshellConverter(
                       const std::vector<Data::SubshellType>& subshell_order );

  //! Destructor
  ~BasicComptonProfileSubshellConverter()
  { /* ... */ }

  //! Convert a subshell enum to a compton profile subshell index
  unsigned convertSubshellToIndex( const Data::SubshellType subshell ) const final override;

  //! Test if a subshell enum is valid
  bool isSubshellValid( const Data::SubshellType subshell ) const final override;

private:

  // The order map
  std::map<Data::SubshellType,unsigned> d_subshell_order;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BASIC_COMPTON_PROFILE_SUBSHELL_CONVERTER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BasicComptonProfileSubshellConverter.hpp
//---------------------------------------------------------------------------//
