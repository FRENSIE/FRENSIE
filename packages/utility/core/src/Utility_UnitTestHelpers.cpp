//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTestHelpers.cpp
//! \author Alex Robinson
//! \brief  Unit test helper function definitions.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "Utility_UnitTestHelpers.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_StaticOutputFormatter.hpp"

namespace Utility{

// Check the result and add "Passed" or "FAILED" to the log
void reportPassFail( const bool result, std::ostream& log )
{
  if( result )
    log << Utility::Green( "Passed" );
  else
    log << Utility::Red( "FAILED" );
}

// Check the reault and add "Passed" or "FAILED" to the log with location
void reportPassFailWithLocation( const bool result,
                                 std::ostream& log,
                                 const std::string& file,
                                 const size_t line_number )
{
  Utility::reportPassFail( result, log );

  if( !result )
  {
    std::ostringstream oss;
    oss << file << ":" << line_number;
    
    log << " ==> " << Utility::BoldCyan( oss.str() );
  }
}

// Log the details and result of a check
void logCheckDetailsAndResult( const std::string& check_header,
                               const std::string& check_details,
                               const bool check_result,
                               const bool pass_required,
                               const std::string& file,
                               const size_t line_number,
                               std::ostream& log )
{
  if( pass_required )
    log << "Require";
  else
    log << "Check";

  log << " that " << check_header;

  Utility::reportPassFailWithLocation( check_result, log, file, line_number );

  log << std::endl;

  if( check_details.size() > 0 )
    log << check_details << std::endl;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_UnitTestHelpers.cpp
//---------------------------------------------------------------------------//
