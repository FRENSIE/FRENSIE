//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExceptionTestMacros.hpp
//! \author Alex Robinson
//! \brief  Macros that test if an exception has occurred and throw if so
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EXCEPTION_TEST_MACROS_HPP
#define UTILITY_EXCEPTION_TEST_MACROS_HPP

// Std Lib Includes
#include <sstream>
#include <string>

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"
#include "Utility_LoggingStaticConstants.hpp"

/*! Exception test macro used to throw an exception when a required condition
 * fails.
 *
 * This macro is based off of the Teuchos_TestForException macro. This macro
 * should be used anywhere that the failure of a specified conditions
 * warrants the throwing of an exception. Do not put "Error: " in the msg.
 * This will be added for you.
 * \ingroup exception_macros
 */
#define TEST_FOR_EXCEPTION(throw_exception_test, Exception, msg)	\
{									\
 const bool throw_exception = (throw_exception_test);			\
 if( throw_exception ){							\
   FRENSIE_LOG_SCOPE();                                                 \
   std::ostringstream detailed_msg;					\
   detailed_msg << FRENSIE_LOG_ERROR_MSG << msg << "\n"                 \
                << FRENSIE_LOG_THROW_TEST_THAT_EVALUATED_TO_TRUE_MSG    \
                << #throw_exception_test << "\n"                        \
                << FRENSIE_LOG_EXCEPTION_TYPE_MSG                       \
                << #Exception << "\n"                                   \
                << FRENSIE_LOG_LOCATION_MSG                             \
                << __FILE__ << FRENSIE_LOG_FILE_LINE_SEP << __LINE__    \
                << "\n";                                                \
                                                                        \
   const std::string &detailed_msg_str = detailed_msg.str();		\
   throw Exception(detailed_msg_str);					\
 }									\
}

/*! Throw an exception always
 *
 * This macros should be used in conditional execution blocks that should never
 * be reached (e.g. default case statement). Do not put "Error: " in the msg.
 * This will be added for you.
 * \ingroup exception_macros
 */
#define THROW_EXCEPTION( Exception, msg ) \
{                                                                       \
  FRENSIE_LOG_SCOPE();                                                  \
  std::ostringstream detailed_msg;                                      \
  detailed_msg << FRENSIE_LOG_ERROR_MSG << msg << "\n"                  \
               << FRENSIE_LOG_LOCATION_MSG                              \
               << __FILE__ << FRENSIE_LOG_FILE_LINE_SEP << __LINE__     \
               << "\n";                                                 \
                                                                        \
  throw Exception(detailed_msg.str());                                  \
}

#endif // end UTILITY_EXCEPTION_TEST_MACROS_HPP

//---------------------------------------------------------------------------//
// end Utility_ExceptionTestMacros.hpp
//---------------------------------------------------------------------------//

