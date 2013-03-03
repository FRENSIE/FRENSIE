//---------------------------------------------------------------------------//
// \file   ExceptionCatchMacros.hpp
// \author Alex Robinson
// \brief  Macros for catching Exceptions
//---------------------------------------------------------------------------//

#ifndef EXCEPTION_CATCH_MACROS_HPP
#define EXCEPTION_CATCH_MACROS_HPP

// Std Lib Includes
#include <stdlib.h>
#include <iostream>
#include <sstream>

// Trilinos Includes
#include "Teuchos_FancyOStream.hpp"
#include "Teuchos_stacktrace.hpp"
#include "Teuchos_TestForException.hpp"

// HDF5 Includes
#include <H5Cpp.h>

// Return the stacktrace
# define TEUCHOS_GET_STORED_STACKTRACE() \
  (Teuchos::TestForException_getEnableStacktrace() \
    ? Teuchos::get_stored_stacktrace() + "\n" \
    : std::string() )

//! Catch statement macro for catching HDF5 Exceptions
// \brief This macro is based off of the Teuchos_StandardCatchMacro
#define HDF5_EXCEPTION_CATCH_AND_EXIT()	\
  catch( const H5::Exception &exception )	\
  {						\
    std::ostringstream oss;			     \
    oss << " *** Caught HDF5 H5::Exception *** \n\n";	\
    oss << "File: " << __FILE__ << "\n"; \
    oss << "Line: " << __LINE__ << "\n"; \
    Teuchos::OSTab scsi_tab(oss); \
    scsi_tab.o() << TEUCHOS_GET_STORED_STACKTRACE(); \
    scsi_tab.o() << exception.getFuncName() << "\n";	\
    scsi_tab.o() << exception.getDetailMsg() << "\n"; \
    std::cerr << std::flush; \
    std::cerr << oss.str(); \
    exit(EXIT_FAILURE); \
  } \

//! Catch statement macro for catching std::exception Exceptions
// \brief This macro is based off of the Teuchos_StandardCatchMacro
#define STD_EXCEPTION_CATCH_AND_EXIT() \
  catch( const std::exception &exception )	\
  {						\
    std::ostringstream oss;			\
    oss << " *** Caught std::exception Exception *** \n\n"; \
    oss << "File: " << __FILE__ << "\n"; \
    oss << "Line: " << __LINE__ << "\n"; \
    Teuchos::OSTab scsi_tab(oss); \
    scsi_tab.o() << TEUCHOS_GET_STORED_STACKTRACE(); \
    scsi_tab.o() << exception.what() << "\n"; \
    std::cerr << std::flush; \
    std::cerr << oss.str(); \
    exit(EXIT_FAILURE); \
  } \

#endif // end EXCEPTION_CATCH_MACROS_HPP

//---------------------------------------------------------------------------//
// end ExceptionCatchMacros.hpp
//---------------------------------------------------------------------------//

