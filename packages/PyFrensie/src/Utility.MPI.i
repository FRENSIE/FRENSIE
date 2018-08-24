//---------------------------------------------------------------------------//
//!
//! \file   Utility.MPI.i
//! \author Luke Kersting
//! \brief  The Utility.MPI sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %utility_mpi_docstring
"
PyFrensie.Utility.MPI is the python inteface to the
FRENSIE utility/core GlobalMPISession class and other MPI classes. Before using
classes in other PyFrensie modules (e.g. the ParticleSimulationManager classes
in PyFrensie.MonteCarlo.ParticleSimulationManager), make sure to initialize the
GlobalMPISession proxy class.
"
%enddef

%module(package   = "PyFrensie.Utility",
        autodoc   = "1",
        docstring = %utility_mpi_docstring) MPI

%include "PyFrensie_MPI_Setup.i"

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Utility_LoggingMacros.hpp"

// Add the Utility namespace to the global lookup scope
using namespace Utility;
%}

// C++ STL support
%include <stl.i>
%include <std_string.i>

// Include typemaps support
%include <typemaps.i>

// Standard exception handling
%include "exception.i"

// General exception handling
%exception
{
  try{
    $action;
    if( PyErr_Occurred() )
      SWIG_fail;
  }
  catch( Utility::ContractException& e )
  {
    SWIG_exception( SWIG_ValueError, e.what() );
  }
  catch( std::runtime_error& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

// Add support for the GlobalMPISession class wrapper
%include "MonteCarlo_GlobalMPISession.i"

// Add inline support for some Logging Macros
%inline %{
  #include "Utility_LoggingMacros.hpp"
  void removeAllLogs()
  {
    FRENSIE_REMOVE_ALL_LOGS();
  }

  void flushAllLogs()
  {
    FRENSIE_FLUSH_ALL_LOGS();
  }

  void LogError( std::string error_message )
  {
    FRENSIE_LOG_ERROR( error_message );
  }

  void LogWarning( std::string warning_message )
  {
    FRENSIE_LOG_WARNING( warning_message );
  }

  void LogNotification( std::string notification_message )
  {
    FRENSIE_LOG_NOTIFICATION( notification_message );
  }
%}

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end Utility.MPI.i
//---------------------------------------------------------------------------//
