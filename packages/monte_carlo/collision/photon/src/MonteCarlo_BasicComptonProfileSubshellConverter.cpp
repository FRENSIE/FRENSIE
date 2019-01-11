//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BasicComptonProfileSubshellConverter.cpp
//! \author Alex Robinson
//! \brief  Basic Compton profile subshell converter def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_BasicComptonProfileSubshellConverter.hpp"

namespace MonteCarlo{

// Constructor
BasicComptonProfileSubshellConverter::BasicComptonProfileSubshellConverter(
                        const std::vector<Data::SubshellType>& subshell_order )
  : d_subshell_order()
{
  for( unsigned i = 0; i < subshell_order.size(); ++i )
    d_subshell_order[subshell_order[i]] = i;
}

// Convert a subshell enum to a compton profile subshell index
unsigned BasicComptonProfileSubshellConverter::convertSubshellToIndex( const Data::SubshellType subshell ) const
{
  // Make sure that the subshell is valid
  testPrecondition( this->isSubshellValid( subshell ) );
  
  return d_subshell_order.find( subshell )->second;
}

// Test if a subshell enum is valid
bool BasicComptonProfileSubshellConverter::isSubshellValid( const Data::SubshellType subshell ) const
{
  return d_subshell_order.find( subshell ) != d_subshell_order.end();
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BasicComptonProfileSubshellConverter.cpp
//---------------------------------------------------------------------------//
