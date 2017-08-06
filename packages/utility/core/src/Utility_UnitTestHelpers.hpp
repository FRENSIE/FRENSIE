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

//! Check the result and add "Passed" or "FAILED" to the log with location
void reportPassFailWithLocation( const bool result,
                                 std::ostream& log,
                                 const std::string& file,
                                 const size_t line_number );

//! Log the details and result of a check
void logCheckDetailsAndResult( const std::string& check_header,
                               const std::string& check_details,
                               const bool check_result,
                               const bool pass_required,
                               const std::string& file,
                               const size_t line_number,
                               std::ostream& log );

} // end Utility namespace

#endif // end UTILITY_TESTING_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTestHelpers.hpp
//---------------------------------------------------------------------------//
