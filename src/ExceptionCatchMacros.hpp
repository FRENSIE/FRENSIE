//---------------------------------------------------------------------------//
//!
//! \file   ExceptionCatchMacros.hpp
//! \author Alex Robinson
//! \brief  Macros for catching Exceptions
//!
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

// This macro is based off of the Teuchos_StandardCatchMacro
//! Catch statement macro for catching HDF5 Exceptions
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

//! Catch statement macro for catching std::exception Exceptions
// This macro is based off of the Teuchos_StandardCatchMacro
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

#endif // end EXCEPTION_CATCH_MACROS_HPP

//---------------------------------------------------------------------------//
// end ExceptionCatchMacros.hpp
//---------------------------------------------------------------------------//

