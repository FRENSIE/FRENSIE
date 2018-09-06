//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTestHelpers.hpp
//! \author Alex Robinson
//! \brief  Unit test helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_TEST_HELPERS_HPP
#define UTILITY_UNIT_TEST_HELPERS_HPP

// Std Lib Includes
#include <iostream>
#include <iterator>
#include <type_traits>

namespace Utility{

//! Check the result and add "Passed" or "FAILED" to the log
void reportPassFail( const bool result, std::ostream& log );

//! Report the location of a check
void reportCheckLocationWithPadding( const std::string& file,
                                     const size_t line_number,
                                     std::ostream& log,
                                     const std::string& line_padding = "" );

//! Report the location of a check
template<size_t RightShift>
inline void reportCheckLocation( const std::string& file,
                                 const size_t line_number,
                                 std::ostream& log )
{
  Utility::reportCheckLocationWithPadding( file, line_number, log, std::string( RightShift, ' ' ) );
}

//! Report the check type that is being conducted
void reportCheckTypeWithPadding( const bool pass_required,
                                 std::ostream& log,
                                 const std::string& line_padding = "" );

//! Report the check type that is being conducted
template<size_t RightShift>
inline void reportCheckType( const bool pass_required,
                             std::ostream& log )
{
  Utility::reportCheckTypeWithPadding( pass_required, log, std::string( RightShift, ' ' ) );
}

//! Log some extra check details
void logExtraCheckDetailsWithPadding( const bool check_result,
                                      const std::string& file,
                                      const size_t line_number,
                                      std::ostream& log,
                                      const std::string& line_padding = "" );

//! Log some extra check details
template<size_t RightShift>
inline void logExtraCheckDetails( const bool check_result,
                                  const std::string& file,
                                  const size_t line_number,
                                  std::ostream& log )
{
  Utility::logExtraCheckDetailsWithPadding( check_result, file, line_number, log, std::string( RightShift, ' ' ) );
}

//! Log last checkpoint
void logLastCheckpointWithPadding( const size_t last_checkpoint,
                                   std::ostream& log,
                                   const std::string& line_padding = "" );

//! Log last checkpoint
template<size_t RightShift>
inline void logLastCheckpoint( const size_t last_checkpoint,
                               std::ostream& log )
{
  Utility::logLastCheckpointWithPadding( last_checkpoint, log, std::string( RightShift, ' ' ) );
}

//! Log std::exception details
void logExceptionDetailsWithPadding(
                                 const std::exception& exception,
                                 const std::string& file,
                                 const size_t line_number,
                                 std::ostream& log,
                                 const std::string& header_suffix = "",
                                 const std::string& line_padding = "" );

//! Log std::exception details
template<size_t RightShift>
inline void logExceptionDetails( const std::exception& exception,
                                 const std::string& file,
                                 const size_t line_number,
                                 std::ostream& log,
                                 const std::string& header_suffix = "" )
{
  Utility::logExceptionDetailsWithPadding( exception, file, line_number, log, header_suffix, std::string( RightShift, ' ' ) );
}

//! Log unknown exception details
void logUnknownExceptionDetailsWithPadding( const std::string& file,
                                            const size_t line_number,
                                            std::ostream& log,
                                            const std::string& header_suffix = "",
                                            const std::string& line_padding = "" );

//! Log unknown exception details
template<size_t RightShift>
inline void logUnknownExceptionDetails( const std::string& file,
                                        const size_t line_number,
                                        std::ostream& log,
                                        const std::string& header_suffix = "" )
{
  Utility::logUnknownExceptionDetailsWithPadding( file, line_number, log, header_suffix, std::string( RightShift, ' ' ) );
}

} // end Utility namespace

#endif // end UTILITY_TESTING_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTestHelpers.hpp
//---------------------------------------------------------------------------//
