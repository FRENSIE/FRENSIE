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
#include <iostream>
#include <sstream>

// HDF5 Includes
#include <H5Cpp.h>

// FRENSIE Includes
#include "Utility_StaticOutputFormatter.hpp"
#include "Utility_DynamicOutputFormatter.hpp"

/*! \defgroup exception_macros Exception Catch Macros
 *
 * These macros are design to catch certain types of exceptions, print
 * out error messages with the file name and line where the exception
 * occurred and then exit the program.
 */

/*! Catch statement body macro for catching HDF5 H5:Exception exceptions.
 *
 * This macro should never be called directly outside of this header file.
 * \ingroup exception_macros
 */
#define __HDF5_EXCEPTION_CATCH_AND_EXIT_BODY__( file, line, msg, exception ) \
  std::cerr << "\n "                                                    \
            << Utility::Underlined( "*** Caught Exception of Type " )   \
            << Utility::Underlined( "H5::Exception" )                   \
            << Utility::Underlined( " ***" )                            \
            << " \n\n"                                                  \
            << Utility::BoldCyan( "File: " ) << Utility::Bold( file ) << "\n" \
            << Utility::BoldCyan( "Line: " ) << line << "\n";           \
                                                                        \
  std::ostringstream oss;                                               \
  oss << msg << "\n";                                                   \
                                                                        \
  Utility::DynamicOutputFormatter formatter( oss.str() );               \
  formatter.formatStandardErrorKeywords();                              \
  formatter.formatStandardWarningKeywords();                            \
  formatter.formatStandardFilenameKeywords();                           \
  formatter.boldCyanKeyword( "\\s*File:" );                             \
  formatter.boldCyanKeyword( "\\s*Line:" );                             \
                                                                        \
  std::cerr << formatter << "\n"                                        \
            << "\t" << exception.getFuncName() << "\n"                  \
            << "\t" << exception.getDetailMsg() << std::endl;           \
                                                                        \
  exit(EXIT_FAILURE)

/*! \brief Catch statement body macro for catching an HDF5:Exception and rethrowing it as a new exception of the desired type.
 *
 * This macro should never be called directly outside of this header file.
 * \ingroup exception_macros
 */
#define __HDF5_EXCEPTION_CATCH_RETHROW_AS_BODY__( file, line, msg, exception, NewException ) \
  std::ostringstream detailed_msg;					\
  detailed_msg << "\n" << "File: " << file << "\n"                      \
               << "Line: " << line << "\n"                              \
               << msg << "\n"						\
               << exception.getFuncName() << "\n"                       \
               << exception.getDetailMsg() << "\n";                     \
                                                                        \
  throw NewException(detailed_msg.str())

/*! Catch statement macro body for catching of user specified exceptions
 *
 * This macro should never be called directly outside of this header file.
 * \ingroup exception_macros
 */
#define __EXCEPTION_CATCH_AND_LOG_BODY__( Exception, exception, msg )\
  FRENSIE_LOG_SCOPE();                                                  \
  FRENSIE_LOG_TAGGED_ERROR( "Caught Exception",                         \
                            msg << "\n  Exception Type: " << #Exception ); \
  FRENSIE_LOG_NESTED_ERROR( exception.what() )

/*! \brief Catch statement macro body for catching of user specified exceptions
 * and exiting code with desired error code
 *
 * This macro should never be called directly outside of this header file.
 * \ingroup exception_macros
 */
#define __EXCEPTION_CATCH_AND_EXIT_BODY__( Exception, exception, msg, exit_code ) \
  __EXCEPTION_CATCH_AND_LOG_BODY__( Exception, exception, msg ); \
  exit( exit_code )

/*! Catch macro body for catching exceptions, adding error info, and rethrowing
 *
 * This macro should never be called directly outside of this header file.
 * \ingroup exception_macros
 */
#define __EXCEPTION_CATCH_RETHROW_AS_BODY__( file, line, msg, Exception, exception, NewException ) \
  std::ostringstream detailed_msg;					\
  detailed_msg << "\n" << msg                                           \
  << "\n  Exception Type: " << #Exception << " -> " << #NewException    \
  << "\n  Location: " << file << ":" << line                            \
  << "\n"                                                               \
  << exception.what();                                                  \
                                                                        \
  throw NewException(detailed_msg.str())

/*! Catch statement macro for catching HDF5 H5::Exception exceptions
 *
 * This macro is based off of the Teuchos_StandardCatchMacro. The only class
 * that handles the HDF5 interface is the Utility::HDF5FileHandler. This
 * macro will only appear in that class. The HDF5 library can throw a
 * variety of H5:Exception classes. This macro will be used after any
 * HDF5 library call that can throw one of these exceptions.
 * \ingroup exception_macros
 */
#define HDF5_EXCEPTION_CATCH_AND_EXIT( msg )                            \
catch( const H5::Exception &exception )                                 \
{                                                                       \
  __HDF5_EXCEPTION_CATCH_AND_EXIT_BODY__( __FILE__, __LINE__, msg, exception ); \
}

/*! \brief Catch statement macro for catching an HDF5:Exception and rethrowing it as a new exception of the desired type.
 *
 * This macro should be used anywhere an exception is thrown in order to
 * properly document the exception and add additional information to it before
 * throwing it again. This macro should also be used when the exception to
 * throw is different than the caught exception.
 * \ingroup exception_macros
 */
#define HDF5_EXCEPTION_CATCH_RETHROW_AS( NewException, msg )            \
catch( const H5::Exception &exception )                                 \
{									\
  __HDF5_EXCEPTION_CATCH_RETHROW_AS_BODY__( __FILE__, __LINE__, msg, exception, NewException ); \
}

/*! \brief Catch statement macro for catching an H5::Exception and either
 * exiting with a message or throwing a new exception of user specified type.
 * \ingroup exception_macros
 */
#define HDF5_EXCEPTION_CATCH( NewException, Exit, msg )             \
catch( const H5::Exception& exception )                             \
{                                                                   \
  if( Exit )                                                            \
  {                                                                     \
    __HDF5_EXCEPTION_CATCH_AND_EXIT_BODY__( __FILE__, __LINE__, msg, exception ); \
  }                                                                     \
  else                                                                  \
  {                                                                     \
    __HDF5_EXCEPTION_CATCH_RETHROW_AS_BODY__( __FILE__, __LINE__, msg, exception, NewException ); \
  }                                                                     \
}

/*! \brief Catch statement macro for catching of user specified exceptions and 
 * logging of their error messages
 * \ingroup exception_macros
 */
#define EXCEPTION_CATCH_AND_LOG( Exception, msg )       \
catch( const Exception& exception )                   \
{                                                     \
  __EXCEPTION_CATCH_AND_LOG_BODY__( Exception, exception, msg );        \
}

/*! Catch statement macro for catching of user specified exceptions
 * \ingroup exception_macros
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
 * throwing it again.
 * \ingroup exception_macros
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
 * throw is different than the caught exception.
 * \ingroup exception_macros
 */
#define EXCEPTION_CATCH_RETHROW_AS( ExceptionIn, ExceptionOut, msg )	\
catch( const ExceptionIn& exception )					\
{									\
  __EXCEPTION_CATCH_RETHROW_AS_BODY__( __FILE__, __LINE__, msg, ExceptionIn, exception, ExceptionOut ); \
}

/*! Catch statement macro for catching of user specified exceptions
 * \ingroup exception_macros
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

