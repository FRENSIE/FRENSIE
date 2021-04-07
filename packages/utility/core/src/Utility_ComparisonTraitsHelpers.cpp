//---------------------------------------------------------------------------//
//!
//! \file   Utility_ComparisonTraitsHelpers.cpp
//! \author Alex Robinson
//! \brief  Comparison traits helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_ComparisonTraitsHelpers.hpp"
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
// end Utility_ComparisonTraitsHelpers.cpp
//---------------------------------------------------------------------------//
