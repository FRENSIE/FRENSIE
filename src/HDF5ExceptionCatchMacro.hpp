//---------------------------------------------------------------------------//
// \file HDF5ExceptionCatchMacro.hpp
// \author Alex Robinson
// \brief Macro for catching HDF5 Exceptions
//---------------------------------------------------------------------------//

#ifndef HDF5_EXCEPTION_CATCH_MACRO_HPP
#define HDF5_EXCEPTION_CATCH_MACRO_HPP

// Std Lib Includes
#include <stdlib.h>

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
    std::ostringstream oss;
    oss << " *** Caught HDF5 H5::Exception *** \n\n" \
    Teuchos::OSTab scsi_tab(oss); \
    scsi_tab.o() << TEUCHOS_GET_STORED_STACKTRACE(); \
    scsi_tab.o() << exception.getFuncName() << "\n";	\
    scsi_tab.o() << exception.getDetailedMsg() << "\n"; \
    std::cerr << std::flush; \
    std::cerr << oss.str(); \
    exit(EXIT_FAILURE);
  } \

#endif // end HDF5_EXCEPTION_CATCH_MACRO_HPP

//---------------------------------------------------------------------------//
// end HDF5ExceptionCatchMacro.hpp
//---------------------------------------------------------------------------//

