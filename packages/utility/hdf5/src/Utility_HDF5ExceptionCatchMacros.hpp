//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5ExceptionCatchMacros.hpp
//! \author Alex Robinson
//! \brief  Macros for catching hdf5 exceptions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HDF5_EXCEPTION_CATCH_MACROS_HPP
#define UTILITY_HDF5_EXCEPTION_CATCH_MACROS_HPP

// HDF5 Includes
#include <H5Cpp.h>

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

/*! \defgroup hdf5_exception_macros HDF5 Exception Catch Macros
 *
 * These macros are designed to catch HDF5 H5::Exception exceptions, log
 * error messages with some meta-data (e.g. file name, line number, HDF5
 * stack trace and HDF5 detailed error message) and optionally exit the
 * program.
 * \note Do not put "Error:" in a message. This will be added for you.
 * \ingroup exception_macros 
 */

#define FRENSIE_LOG_HDF5_STACK_MSG FRENSIE_LOG_DATA_LINE_START "HDF5 " FRENSIE_LOG_STACK_MSG_BASIC " "
#define FRENSIE_LOG_HDF5_ERROR_MSG FRENSIE_LOG_DATA_LINE_START "HDF5 Error Msg: "

/*! Catch statement macro body for catching of HDF5 H5::Exception exceptions
 *
 * This macro should never be called directly outside of this header file.
 * \ingroup hdf5_exception_macros
 */
#define __HDF5_EXCEPTION_CATCH_AND_LOG_BODY__( exception, msg )         \
  FRENSIE_LOG_SCOPE();                                                  \
  FRENSIE_LOG_TAGGED_ERROR( "Caught Exception",                         \
                            msg << "\n"                                 \
                            << FRENSIE_LOG_EXCEPTION_TYPE_MSG           \
                            << "H5::Exception\n"                        \
                            << FRENSIE_LOG_HDF5_STACK_MSG               \
                            << exception.getFuncName() << "\n"          \
                            << FRENSIE_LOG_HDF5_ERROR_MSG               \
                            << exception.getDetailMsg() )

/*! Catch statement macro body for catching HDF5 H5::Exception exceptions.
 *
 * This macro should never be called directly outside of this header file.
 * \ingroup hdf5_exception_macros
 */
#define __HDF5_EXCEPTION_CATCH_AND_EXIT_BODY__( exception, msg, exit_code ) \
  __HDF5_EXCEPTION_CATCH_AND_LOG_BODY__( exception, msg );              \
  exit( exit_code )

/*! \brief Catch statement body macro for catching an HDF5:Exception and 
 * rethrowing it as a new exception of the desired type.
 *
 * This macro should never be called directly outside of this header file.
 * \ingroup hdf5_exception_macros
 */
#define __HDF5_EXCEPTION_CATCH_RETHROW_AS_BODY__( file, line, msg, exception, NewException ) \
  std::ostringstream detailed_msg;					\
  detailed_msg << FRENSIE_LOG_ERROR_MSG << msg << "\n"                  \
  << FRENSIE_LOG_EXCEPTION_TYPE_MSG                                     \
  << "H5::Exception" << FRENSIE_LOG_ARROW_SEP << #NewException << "\n"  \
  << FRENSIE_LOG_HDF5_STACK_MSG << exception.getFuncName() << "\n"      \
  << FRENSIE_LOG_HDF5_ERROR_MSG << exception.getDetailMsg() << "\n"     \
  << FRENSIE_LOG_LOCATION_MSG                                           \
  << file << FRENSIE_LOG_FILE_LINE_SEP << line << "\n";                 \
                                                                        \
  throw NewException(detailed_msg.str())

/*! \brief Catch statement macro for catching HDF5 H5::Exception exceptions and
 * logging of their error messages
 * \ingroup hdf5_exception_macros
 */
#define HDF5_EXCEPTION_CATCH_AND_LOG( msg )                     \
catch( const H5::Exception& exception )                         \
{                                                               \
  __HDF5_EXCEPTION_CATCH_AND_LOG_BODY__( exception, msg );      \
}

/*! Catch statement macro for catching HDF5 H5::Exception exceptions
 *
 * This macro is based off of the Teuchos_StandardCatchMacro. The only class
 * that handles the HDF5 interface is the Utility::HDF5FileHandler. This
 * macro will only appear in that class. The HDF5 library can throw a
 * variety of H5:Exception classes. This macro will be used after any
 * HDF5 library call that can throw one of these exceptions. Do not add
 * "Error:" to the msg. This will be added for you.
 * \ingroup hdf5_exception_macros
 */
#define HDF5_EXCEPTION_CATCH_AND_EXIT( msg )                            \
catch( const H5::Exception &exception )                                 \
{                                                                       \
  __HDF5_EXCEPTION_CATCH_AND_EXIT_BODY__( exception, msg, EXIT_FAILURE ); \
}

/*! \brief Catch statement macro for catching an HDF5:Exception and rethrowing it as a new exception of the desired type.
 *
 * This macro should be used anywhere an exception is thrown in order to
 * properly document the exception and add additional information to it before
 * throwing it again. This macro should also be used when the exception to
 * throw is different than the caught exception. Do not add "Error:" to 
 * the msg. This will be added for you.
 * \ingroup hdf5_exception_macros
 */
#define HDF5_EXCEPTION_CATCH_RETHROW_AS( NewException, msg )            \
catch( const H5::Exception &exception )                                 \
{									\
  __HDF5_EXCEPTION_CATCH_RETHROW_AS_BODY__( __FILE__, __LINE__, msg, exception, NewException ); \
}

/*! \brief Catch statement macro for catching an H5::Exception and either
 * exiting with a message or throwing a new exception of user specified type.
 * Do not add "Error:" to the msg. This will be added for you.
 * \ingroup hdf5_exception_macros
 */
#define HDF5_EXCEPTION_CATCH( NewException, Exit, msg )             \
catch( const H5::Exception& exception )                             \
{                                                                   \
  if( Exit )                                                            \
  {                                                                     \
    __HDF5_EXCEPTION_CATCH_AND_EXIT_BODY__( exception, msg, EXIT_FAILURE ); \
  }                                                                     \
  else                                                                  \
  {                                                                     \
    __HDF5_EXCEPTION_CATCH_RETHROW_AS_BODY__( __FILE__, __LINE__, msg, exception, NewException ); \
  }                                                                     \
}

#endif // end UTILITY_HDF5_EXCEPTION_CATCH_MACROS_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5ExceptionCatchMacros.hpp
//---------------------------------------------------------------------------//
