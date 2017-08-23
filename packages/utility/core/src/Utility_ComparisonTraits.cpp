//---------------------------------------------------------------------------//
//!
//! \file   Utility_ComparisonTraits.cpp
//! \author Alex Robinson
//! \brief  Comparison traits helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_ComparisonTraits.hpp"
#include "Utility_StaticOutputFormatter.hpp"

namespace Utility{

// Check the comparison result and add "passed" or "failed!" to the log
void reportComparisonPassFail( const bool result, std::ostream& log )
{
  if( result )
    log << Utility::Green("passed") << "\n";
  else
    log << Utility::Red("failed") << "!\n";
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_ComparisonTraits.cpp
//---------------------------------------------------------------------------//
