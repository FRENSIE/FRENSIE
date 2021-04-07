//---------------------------------------------------------------------------//
//!
//! \file   Utility.Utility__init__.i
//! \author Alex Robinson, Luke Kersting
//! \brief  The utility module swig interface file
//!
//---------------------------------------------------------------------------//

%define %utility_docstring
"
PyFrensie.Utility.Utility__init__ will be imported directly into the
PyFrensie.Utility module (see PyFrensie.Utility.__init__.py)
"
%enddef

%module(package   = "PyFrensie.Utility",
        autodoc   = "1",
        docstring = %utility_docstring) Utility__init__

%pythonbegin
%{
  # With python 2.7.14 and swig version 3.0.10 the default generated import
  # code cannot find the ___init__.so file. Unfortunately the 'moduleimport'
  # option of the %module macro does not seem to work with this version
  # of swig either. To get the import code working we have to manually add
  # the current directory to the system path temporarily.

  import os.path
  import sys
  current_dir,file_name = os.path.split(__file__)
  sys.path.insert(0, current_dir)
%}

%pythoncode
%{
# Remove the local current directory from the sys path (added to help
# import code - see comment above)
sys.path.pop(0)

# Forward the sigint signal handler to PyFrensie
_Utility__init__.usePyFrensieSignalHandlers()

# Set up the random number generator
_Utility__init__.initFrensiePrng()

# Set up the default logs
_Utility__init__.initializeSynchronousLogs()
%}

%{
#include <iostream>
#include <fstream>
#include <csignal>

#define NO_IMPORT_ARRAY
#include "numpy_include.h"

#include "PyFrensie_PythonTypeTraits.hpp"
#include "Utility_JustInTimeInitializer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_Vector.hpp"
%}

// C++ STL support
%include <std_string.i>

%define %default_log_initializers( FUNCTION_NAME, MACRO_NAME )

%inline %{
  //! FUNCTION_NAME with cout
  void FUNCTION_NAME()
  {
    MACRO_NAME( boost::shared_ptr<std::ostream>( &std::cout, boost::null_deleter() ) );
  }

  //! FUNCTION_NAME with file
  void FUNCTION_NAME( const std::string& filename,
                      const bool append = false )
  {
    boost::shared_ptr<std::ostream> file;

    if( append )
      file = boost::make_shared<std::ofstream>( filename, std::ofstream::app );
    else
      file = boost::make_shared<std::ofstream>( filename );

    MACRO_NAME( file );
  }
%}

%enddef

%default_log_initializers( initializeSynchronousLogs, FRENSIE_SETUP_STANDARD_SYNCHRONOUS_LOGS )
%default_log_initializers( initializeAsynchronousLogs, FRENSIE_SETUP_STANDARD_ASYNCHRONOUS_LOGS )
%default_log_initializers( initializeSynchronousErrorLog, FRENSIE_SETUP_SYNCHRONOUS_ERROR_LOG )
%default_log_initializers( initializeAsynchronousErrorLog, FRENSIE_SETUP_ASYNCHRONOUS_ERROR_LOG )
%default_log_initializers( initializeSynchronousWarningLog, FRENSIE_SETUP_SYNCHRONOUS_WARNING_LOG )
%default_log_initializers( initializeAsynchronousWarningLog, FRENSIE_SETUP_ASYNCHRONOUS_WARNING_LOG )
%default_log_initializers( initializeSynchronousNotificationLog, FRENSIE_SETUP_SYNCHRONOUS_NOTIFICATION_LOG )
%default_log_initializers( initializeAsynchronousNotificationLog, FRENSIE_SETUP_ASYNCHRONOUS_NOTIFICATION_LOG )

// Add the shortcut for initializing the random number generator
%feature("autodoc")
initFrensiePrng
"
This method can be used to initialize the Utility.Prng.RandomNumberGenerator
instead of calling 'Utility.Prng.RandomNumberGenerator.createStreams()'.
"

%{
  // The default signal handler (cache so that it can be restored later)
  void (*__default_signal_handler__)( int );

  // The custom signal handler that will forward the python signal handler
  // into PyFrensie
  extern "C" void __custom_pyfrensie_signal_handler__( int signal )
  {
    std::exit( signal );
  }
%}

%inline %{

  //! Use the PyFrensie signal handlers
  void usePyFrensieSignalHandlers()
  {
    if( !__default_signal_handler__ )
      __default_signal_handler__ = std::signal( SIGINT, __custom_pyfrensie_signal_handler__ );
  }

  //! Use the Python signal handlers
  void usePythonSignalHandlers()
  {
    if( __default_signal_handler__ )
    {
      std::signal( SIGINT, __default_signal_handler__ );

      __default_signal_handler__ = NULL;
    }
  }

  //! Infinite loop (used to test the sigint signal handler forwarding)
  void infiniteLoop()
  { while( true ); }

  //! Initialize the random number generator
  void initFrensiePrng()
  {
    // Initialize the random number generator
    Utility::RandomNumberGenerator::createStreams();
  }

  //! Remove all FRENSIE logs
  void removeAllLogs()
  {
    FRENSIE_REMOVE_ALL_LOGS();
  }

  //! Flush all FRENSIE logs
  void flushAllLogs()
  {
    FRENSIE_FLUSH_ALL_LOGS();
  }

  //! Log an error
  void logError( std::string error_message )
  {
    FRENSIE_LOG_ERROR( error_message );
  }

  //! Log a warning
  void logWarning( std::string warning_message )
  {
    FRENSIE_LOG_WARNING( warning_message );
  }

  //! Log a notification
  void logNotification( std::string notification_message )
  {
    FRENSIE_LOG_NOTIFICATION( notification_message );
  }

  //! Log a partial notification
  void logPartialNotification( std::string notification_message )
  {
    FRENSIE_LOG_PARTIAL_NOTIFICATION( notification_message );
  }

  //! Create a list of ints from a string
  PyObject* intArrayFromString( const std::string& list_string )
  {
    return PyFrensie::convertToPython(
                    Utility::fromString<std::vector<int> >( list_string ) );
  }

  //! Create a list of doubles from a string
  PyObject* doubleArrayFromString( const std::string& list_string )
  {
    return PyFrensie::convertToPython(
                    Utility::fromString<std::vector<double> >( list_string ) );
  }

  //! Activate just-in-time initialization
  void activateJustInTimeInitialization()
  {
    Utility::JustInTimeInitializer::getInstance().activate();
  }

  //! Deactivate just-in-time initialization
  void deactivateJustInTimeInitialization()
  {
    Utility::JustInTimeInitializer::getInstance().deactivate();
  }

  //! Check if just-in-time initialization is active
  bool isJustInTimeInitializationActive()
  {
    return Utility::JustInTimeInitializer::getInstance().isActive();
  }
%}

// Add support for the OpenMPProperties class wrapper
%include "Utility_OpenMPProperties.i"

//---------------------------------------------------------------------------//
// end Utility.Utility__init__.i
//---------------------------------------------------------------------------//
