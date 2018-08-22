//---------------------------------------------------------------------------//
//!
//! \file   Utility.GlobalMPISession.i
//! \author Alex Robinson
//! \brief  The Utility.GlobalMPISession sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %utility_global_mpi_session_docstring
"
PyFrensie.Utility.GlobalMPISession is the python inteface to the
FRENSIE utility/core GlobalMPISession class. Before using classes in other
PyFrensie modules (e.g. the ParticleSimulationManager classes in
PyFrensie.MonteCarlo.ParticleSimulationManager), make sure to initialize the
GlobalMPISession proxy class.
"
%enddef

%module(package   = "PyFrensie.Utility",
        autodoc   = "1",
        docstring = %utility_global_mpi_session_docstring) GlobalMPISession

%{
#include <fstream>
#include "Utility_LoggingMacros.hpp"

// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Utility_GlobalMPISession.hpp"

// Add the Utility namespace to the global lookup scope
using namespace Utility;
%}

// C++ STL support
%include <stl.i>
%include <std_string.i>
%include <std_vector.i>
%include <std_except.i>
%include <std_shared_ptr.i>

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

// Add some general templates
%template(StringVector) std::vector<std::string>;
%template(BoolVector) std::vector<bool>;
%template(IntVector) std::vector<int>;
%template(DoubleVector) std::vector<double>;

// ---------------------------------------------------------------------------//
// Add support for the Threading Tags
// ---------------------------------------------------------------------------//

// Ignore Tag structs
%ignore *::SingleThreadingTag;
%ignore *::FunneledThreadingTag;
%ignore *::SerializedThreadingTag;
%ignore *::MultipleThreadingTag;

// ---------------------------------------------------------------------------//
// Add support for the GlobalMPISession
// ---------------------------------------------------------------------------//

// Add typemaps for converting Energy to and from Python float
%typemap(in) int& ( int temp ){
  temp = PyInt_AsLong( $input );
  $1 = &temp;
}

%typemap(typecheck, precedence=70) (int&) {
  $1 = (PyInt_Check($input)) ? 1 : 0;
}

// This tells SWIG to treat char ** as a special case
%typemap(in) char**& ( char ** temp ) {
  temp = PyFrensie::convertFromPython<char**>($input);
  $1 = &temp;
}

%typemap(typecheck, precedence=70) (char**&) {
  $1 = (PyList_Check($input)) ? 1 : 0;
}

// This cleans up the char ** array we malloc'd before the function call
%typemap(freearg) char**& { free((char *) *$1); }


%extend Utility::GlobalMPISession
{
  //! Initialize logs with cout
  void initializeLogs( const int root_process = 0,
                       const bool limit_logging_to_root = false,
                       const bool synchronous_logging = true )
  {
    $self->initializeLogs( boost::shared_ptr<std::ostream>( &std::cout, boost::null_deleter() ), root_process, limit_logging_to_root, synchronous_logging );
  }

  //! Initialize error log with cout
  void initializeErrorLog( const int root_process = 0,
                           const bool limit_logging_to_root = false,
                           const bool synchronous_logging = true )
  {
    $self->initializeErrorLog( boost::shared_ptr<std::ostream>( &std::cout, boost::null_deleter() ), root_process, limit_logging_to_root, synchronous_logging );
  }

  //! Initialize warning log with cout
  void initializeWarningLog( const int root_process = 0,
                             const bool limit_logging_to_root = false,
                             const bool synchronous_logging = true )
  {
    $self->initializeWarningLog( boost::shared_ptr<std::ostream>( &std::cout, boost::null_deleter() ), root_process, limit_logging_to_root, synchronous_logging );
  }

  //! Initialize notification log with cout
  void initializeNotificationLog( const int root_process = 0,
                                  const bool limit_logging_to_root = false,
                                  const bool synchronous_logging = true )
  {
    $self->initializeLogs( boost::shared_ptr<std::ostream>( &std::cout, boost::null_deleter() ), root_process, limit_logging_to_root, synchronous_logging );
  }

  //! Initialize an output stream with cout
  static void initializeOutputStream( const int root_process = 0,
                                      const bool limit_logging_to_root = false )
  {
    Utility::GlobalMPISession::initializeOutputStream( boost::shared_ptr<std::ostream>( &std::cout, boost::null_deleter() ), root_process, limit_logging_to_root );
  }

  //! Restore an output stream with cout
  static void restoreOutputStream()
  {
    Utility::GlobalMPISession::restoreOutputStream( boost::shared_ptr<std::ostream>( &std::cout, boost::null_deleter() ) );
  }

  //! Initialize logs with file
  void initializeLogs( std::string filename,
                       const int root_process = 0,
                       const bool limit_logging_to_root = false,
                       const bool synchronous_logging = true )
  {
    boost::shared_ptr<std::ofstream> file = boost::make_shared<std::ofstream>(filename);

    $self->initializeLogs( file, root_process, limit_logging_to_root, synchronous_logging );
  }

  //! Initialize error log with file
  void initializeErrorLog( std::string filename,
                           const int root_process = 0,
                           const bool limit_logging_to_root = false,
                           const bool synchronous_logging = true )
  {
    boost::shared_ptr<std::ostream> file = boost::make_shared<std::ofstream>(filename);

    $self->initializeErrorLog( file, root_process, limit_logging_to_root, synchronous_logging );
  }

  //! Initialize warning log with file
  void initializeWarningLog( std::string filename,
                             const int root_process = 0,
                             const bool limit_logging_to_root = false,
                             const bool synchronous_logging = true )
  {
    boost::shared_ptr<std::ostream> file = boost::make_shared<std::ofstream>(filename);

    $self->initializeWarningLog( file, root_process, limit_logging_to_root, synchronous_logging );
  }

  //! Initialize notification log with file
  void initializeNotificationLog( std::string filename,
                                  const int root_process = 0,
                                  const bool limit_logging_to_root = false,
                                  const bool synchronous_logging = true )
  {
    boost::shared_ptr<std::ostream> file = boost::make_shared<std::ofstream>(filename);

    $self->initializeNotificationLog( file, root_process, limit_logging_to_root, synchronous_logging );
  }

  //! Initialize an output stream with file
  static void initializeOutputStream( std::string filename,
                                      const int root_process = 0,
                                      const bool limit_logging_to_root = false )
  {
    boost::shared_ptr<std::ostream> file = boost::make_shared<std::ofstream>(filename);

    Utility::GlobalMPISession::initializeOutputStream( file, root_process, limit_logging_to_root );
  }

  //! Restore an output stream with file
  static void restoreOutputStream( std::string filename )
  {
    boost::shared_ptr<std::ostream> file = boost::make_shared<std::ofstream>(filename);

    Utility::GlobalMPISession::restoreOutputStream( file );
  }
};

%ignore *::initializeLogs;
%ignore *::initializeErrorLog;
%ignore *::initializeWarningLog;
%ignore *::initializeNotificationLog;
%ignore *::initializeOutputStream;


// Allow shared pointers of GlobalMPISession objects
%shared_ptr( Utility::GlobalMPISession );

// Wrap GlobalMPISession
%include "Utility_GlobalMPISession.hpp"

// Add functions to return the thread support level object as an int
%inline %{
  //! The mpi single thread support level tag function
  int SingleThreading()
  {
    return Utility::GlobalMPISession::SingleThreading;
  }

  //! The mpi funneled thread support level tag function
  int FunneledThreading()
  {
    return Utility::GlobalMPISession::FunneledThreading;
  }

  //! The mpi serialized thread support level tag function
  int SerializedThreading()
  {
    return Utility::GlobalMPISession::SerializedThreading;
  }

  //! The mpi multiple thread support level tag function
  int MultipleThreading()
  {
    return Utility::GlobalMPISession::MultipleThreading;
  }

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
// end Utility.GlobalMPISession.i
//---------------------------------------------------------------------------//
