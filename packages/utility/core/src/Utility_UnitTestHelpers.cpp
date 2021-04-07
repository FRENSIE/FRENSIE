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

//! Log the location of a check
void reportCheckLocationWithPadding( const std::string& file,
                                     const size_t line_number,
                                     std::ostream& log,
                                     const std::string& line_padding )
{
  log << line_padding << "==> "
      << Utility::BoldCyan("Location: " )
      << Utility::Bold(file + ":" + Utility::toString( line_number ) );
}

// Report the check type that is being conducted
void reportCheckTypeWithPadding( const bool pass_required,
                                 std::ostream& log,
                                 const std::string& line_padding )
{
  log << line_padding;
  
  if( pass_required )
    log << "Require ";
  else
    log << "Check ";

  log << "that ";
}

// Log some extra check details
void logExtraCheckDetailsWithPadding( const bool check_result,
                                      const std::string& file,
                                      const size_t line_number,
                                      std::ostream& log,
                                      const std::string& line_padding )
{
  if( !check_result )
  {
    Utility::reportCheckLocationWithPadding( file, line_number, log, line_padding );

    log << "\n";
  }
}

// Log last checkpoint
void logLastCheckpointWithPadding( const size_t last_checkpoint,
                                   std::ostream& log,
                                   const std::string& line_padding )
{
  if( last_checkpoint > 0 )
  {
    log << "\n" << line_padding << Utility::BoldCyan("Note:") << " "
        << "Last unit test checkpoint at line " << last_checkpoint
        << std::endl;
  }
}

// Log std::exception details
void logExceptionDetailsWithPadding( const std::exception& exception,
                                     const std::string& file,
                                     const size_t line_number,
                                     std::ostream& log,
                                     const std::string& header_suffix,
                                     const std::string& line_padding )
{
  log << "\n" << line_padding
      << "... Caught unexpected std::exception " << header_suffix;

  if( !header_suffix.empty() )
    log << " ";

  log << "with message \"" << exception.what() << "\" ";

  Utility::reportCheckLocationWithPadding( file, line_number, log, "" );

  log << std::endl;
}

// Log unknown exception details
void logUnknownExceptionDetailsWithPadding( const std::string& file,
                                            const size_t line_number,
                                            std::ostream& log,
                                            const std::string& header_suffix,
                                            const std::string& line_padding )
{
  log << "\n" << line_padding << "... Caught unexpected unknown exception "
      << header_suffix;

  if( !header_suffix.empty() )
    log << " ";

  Utility::reportCheckLocationWithPadding( file, line_number, log, "" );

  log << std::endl;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_UnitTestHelpers.cpp
//---------------------------------------------------------------------------//
