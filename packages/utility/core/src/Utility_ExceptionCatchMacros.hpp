//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExceptionCatchMacros.hpp
//! \author Alex Robinson
//! \brief  Macros for catching Exceptions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EXCEPTION_CATCH_MACROS_HPP
#define UTILITY_EXCEPTION_CATCH_MACROS_HPP

// Std Lib Includes
#include <stdlib.h>

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"
#include "Utility_LoggingStaticConstants.hpp"

/*! \defgroup std_exception_macros Standard Exception Catch Macros
 *
 * These macros are designed to catch std::exception exceptions (or any
 * exception type that has the same interface), log error messages with
 * some meta-data (e.g. file name, line number, etc.) and optionally exit
 * the program. 
 * \note Do not put "Error:" in a message. This will be added for you.
 * \ingroup exception_macros
 */

/*! Catch statement macro body for catching of user specified exceptions
 *
 * This macro should never be called directly outside of this header file.
 * \ingroup std_exception_macros
 */
#define __EXCEPTION_CATCH_AND_LOG_BODY__( Exception, exception, msg )   \
  FRENSIE_LOG_SCOPE();                                                  \
  FRENSIE_LOG_TAGGED_ERROR(                                             \
             "Caught Exception",                                        \
             msg << "\n"                                                \
             << FRENSIE_LOG_EXCEPTION_TYPE_MSG << #Exception );         \
  FRENSIE_LOG_NESTED_ERROR( exception.what() )

/*! \brief Catch statement macro body for catching of user specified exceptions
 * and exiting code with desired error code
 *
 * This macro should never be called directly outside of this header file.
 * \ingroup std_exception_macros
 */
#define __EXCEPTION_CATCH_AND_EXIT_BODY__( Exception, exception, msg, exit_code ) \
  __EXCEPTION_CATCH_AND_LOG_BODY__( Exception, exception, msg ); \
  exit( exit_code )

/*! Catch macro body for catching exceptions, adding error info, and rethrowing
 *
 * This macro should never be called directly outside of this header file.
 * \ingroup std_exception_macros
 */
#define __EXCEPTION_CATCH_RETHROW_AS_BODY__( file, line, msg, Exception, exception, NewException ) \
  std::ostringstream detailed_msg;					\
  detailed_msg << FRENSIE_LOG_ERROR_MSG << msg << "\n"                  \
  << FRENSIE_LOG_EXCEPTION_TYPE_MSG                                     \
  << #Exception << FRENSIE_LOG_ARROW_SEP << #NewException << "\n"       \
  << FRENSIE_LOG_LOCATION_MSG                                           \
  << file << FRENSIE_LOG_FILE_LINE_SEP << line << "\n\n"                \
  << exception.what();                                                  \
                                                                        \
  throw NewException(detailed_msg.str())

/*! \brief Catch statement macro for catching of user specified exceptions and 
 * logging of their error messages
 * \ingroup std_exception_macros
 */
#define EXCEPTION_CATCH_AND_LOG( Exception, msg )       \
catch( const Exception& exception )                   \
{                                                     \
  __EXCEPTION_CATCH_AND_LOG_BODY__( Exception, exception, msg );        \
}

/*! Catch statement macro for catching of user specified exceptions
 * \ingroup std_exception_macros
 */
#define EXCEPTION_CATCH_AND_EXIT( Exception, msg ) \
catch( const Exception& exception ) \
{				      \
  __EXCEPTION_CATCH_AND_EXIT_BODY__( Exception, exception, msg, EXIT_FAILURE ); \
}

/*! Catch macro for catching exceptions, adding error info, rethrowing
 *
 * This macro should be used anywhere an exception is thrown in order to
 * properly document the exception and add additional information to it before
 * throwing it again. Do not put "Error:" in the msg. It will be added for
 * you.
 * \ingroup std_exception_macros
 */
#define EXCEPTION_CATCH_RETHROW( Exception, msg ) \
catch( const Exception& exception )				\
{								\
  __EXCEPTION_CATCH_RETHROW_AS_BODY__( __FILE__, __LINE__, msg, Exception, exception, Exception ); \
}

/*! Catch macro for catching exceptions, adding error info, and rethrowing
 *
 * This macro should be used anywhere an exception is thrown in order to
 * properly document the exception and add additional information to it before
 * throwing it again. This macro should also be used when the exception to
 * throw is different than the caught exception. Do not put "Error:" in the
 * msg. It will be added for you.
 * \ingroup std_exception_macros
 */
#define EXCEPTION_CATCH_RETHROW_AS( ExceptionIn, ExceptionOut, msg )	\
catch( const ExceptionIn& exception )					\
{									\
  __EXCEPTION_CATCH_RETHROW_AS_BODY__( __FILE__, __LINE__, msg, ExceptionIn, exception, ExceptionOut ); \
}

/*! Catch statement macro for catching of user specified exceptions
 * \details Do not put "Error:" in the msg. It will be added for you.
 * \ingroup std_exception_macros
 */
#define EXCEPTION_CATCH( Exception, Exit, msg )	\
catch( const Exception& exception )                                     \
{                                                                       \
  if( Exit )								\
  {                                                                     \
    __EXCEPTION_CATCH_AND_EXIT_BODY__( Exception, exception, msg, EXIT_FAILURE ); \
  }                                                                     \
  else                                                                  \
  {                                                                     \
    __EXCEPTION_CATCH_RETHROW_AS_BODY__( __FILE__, __LINE__, msg, Exception, exception, ExceptionOut ); \
  }                                                                     \
}                                                                       \


#endif // end UTILITY_EXCEPTION_CATCH_MACROS_HPP

//---------------------------------------------------------------------------//
// end Utility_ExceptionCatchMacros.hpp
//---------------------------------------------------------------------------//

