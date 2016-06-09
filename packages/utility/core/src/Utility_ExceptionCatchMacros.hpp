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

// Trilinos Includes
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_stacktrace.hpp>
#include <Teuchos_TestForException.hpp>

// HDF5 Includes
#include <H5Cpp.h>

/*! \defgroup exception_macros Exception Catch Macros
 *
 * These macros are design to catch certain types of exceptions, print
 * out error messages with the file name and line where the exception
 * occurred and then exit the program.
 */

/*! Catch statement macro for catching HDF5 H5::Exception exceptions
 *
 * This macro is based off of the Teuchos_StandardCatchMacro. The only class
 * that handles the HDF5 interface is the Utility::HDF5FileHandler. This
 * macro will only appear in that class. The HDF5 library can throw a
 * variety of H5:Exception classes. This macro will be used after any
 * HDF5 library call that can throw one of these exceptions.
 * \ingroup exception_macros
 */
#define HDF5_EXCEPTION_CATCH_AND_EXIT()	\
  catch( const H5::Exception &exception )	\
  {						\
    std::ostringstream oss;			     \
    oss << " *** Caught HDF5 H5::Exception *** \n\n";	\
    oss << "File: " << __FILE__ << "\n"; \
    oss << "Line: " << __LINE__ << "\n"; \
    Teuchos::OSTab scsi_tab(oss); \
    scsi_tab.o() << exception.getFuncName() << "\n";	\
    scsi_tab.o() << exception.getDetailMsg() << "\n"; \
    std::cerr << std::flush; \
    std::cerr << oss.str(); \
    exit(EXIT_FAILURE); \
  } \

/*! \brief Catch statement macro for catching an H5::Exception and either
 * exiting with a message or throwing a new exception of user specified type.
 * \ingroup exception_macros
 */
#define HDF5_EXCEPTION_CATCH( NewException, Exit, msg )	\
  catch( const H5::Exception &exception )		\
    {							\
    std::ostringstream oss;				\
    oss << " *** Caught HDF5 H5::Exception *** \n\n";	\
    oss << "File: " << __FILE__ << "\n";		\
    oss << "Line: " << __LINE__ << "\n";		\
    oss << msg << "\n";					\
    Teuchos::OSTab scsi_tab(oss);			\
    scsi_tab.o() << exception.getFuncName() << "\n";	\
    scsi_tab.o() << exception.getDetailMsg() << "\n";	\
    if( Exit )						\
    {							\
      std::cerr << std::flush;				\
      std::cerr << oss.str();				\
      exit(EXIT_FAILURE);				\
    }							\
    else						\
      throw NewException( oss.str() );			\
  }

/*! Catch statement macro for catching std::exception Exceptions
 *
 * This macro is based off of the Teuchos_StandardCatchMacro. This macro
 * should be used anywhere that a std::exception is thrown in order to
 * properly document the exception and exit the program.
 * \ingroup exception_macros
 */
#define STD_EXCEPTION_CATCH_AND_EXIT() \
  catch( const std::exception &exception )	\
  {						\
    std::ostringstream oss;			\
    oss << " *** Caught std::exception Exception *** \n\n"; \
    oss << "File: " << __FILE__ << "\n"; \
    oss << "Line: " << __LINE__ << "\n"; \
    Teuchos::OSTab scsi_tab(oss); \
    scsi_tab.o() << exception.what() << "\n"; \
    std::cerr << std::flush; \
    std::cerr << oss.str(); \
    exit(EXIT_FAILURE); \
  } \

/*! Catch statement macro for catching of user specified exceptions
 * \ingroup exception_macros
 */
#define EXCEPTION_CATCH_AND_EXIT( Exception, msg ) \
  catch( const Exception &exception ) \
  {				      \
    std::ostringstream oss;	      \
    oss << " *** Caught " << #Exception << " Exception *** \n\n";	\
    oss << "File: " << __FILE__ << "\n";				\
    oss << "Line: " << __LINE__ << "\n";				\
    oss << msg << "\n";							\
    Teuchos::OSTab scsi_tab(oss);					\
    scsi_tab.o() << exception.what() << "\n";				\
    std::cerr << std::flush;						\
    std::cerr << oss.str();						\
    exit(EXIT_FAILURE);							\
  }

/*! Catch macro for catching exceptions, adding error info, rethrowing
 *
 * This macro should be used anywhere an exception is thrown in order to
 * properly document the exception and add additional information to it before
 * throwing it again.
 * \ingroup exception_macros
 */
#define EXCEPTION_CATCH_RETHROW( Exception, msg ) \
catch( const Exception &exception )				\
{								\
  std::ostringstream detailed_msg;				\
  detailed_msg << __FILE__ << ":" << __LINE__ << ":\n\n"	\
	       << msg << "\n"					\
	       << exception.what() << "\n";			\
  throw Exception(detailed_msg.str());				\
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
catch( const ExceptionIn &exception )					\
{									\
  std::ostringstream detailed_msg;					\
  detailed_msg << __FILE__ << ":" << __LINE__ << ":\n\n"		\
               << msg << "\n"						\
               << exception.what() << "\n";				\
  throw ExceptionOut(detailed_msg.str());				\
}

/*! Catch statement macro for catching of user specified exceptions
 * \ingroup exception_macros
 */
#define EXCEPTION_CATCH( Exception, Exit, msg )	\
  catch( const Exception &exception ) \
  {				      \
    std::ostringstream oss;	      \
    oss << " *** Caught " << #Exception << " Exception *** \n\n";	\
    oss << "File: " << __FILE__ << "\n";				\
    oss << "Line: " << __LINE__ << "\n";				\
    oss << msg << "\n";							\
    Teuchos::OSTab scsi_tab(oss);					\
    scsi_tab.o() << exception.what() << "\n";				\
    if( Exit )								\
    {									\
      std::cerr << std::flush;						\
      std::cerr << oss.str();						\
      exit(EXIT_FAILURE);						\
    }									\
    else								\
      throw Exception(oss.str());					\
  }


#endif // end UTILITY_EXCEPTION_CATCH_MACROS_HPP

//---------------------------------------------------------------------------//
// end Utility_ExceptionCatchMacros.hpp
//---------------------------------------------------------------------------//

