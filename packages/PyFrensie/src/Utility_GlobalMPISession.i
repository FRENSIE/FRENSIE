//---------------------------------------------------------------------------//
//!
//! \file   Utility_GlobalMPISession.i
//! \author Luke Kersting
//! \brief  The GlobalMPISession class interface file
//!
//---------------------------------------------------------------------------//

%{
// Std Includes
#include <fstream>

// FRENSIE Includes
#include "Utility_GlobalMPISession.hpp"

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

// Macro to extend GlobalMPISession functionality for initializing logs
%define %extend_log_initializers( FUNCTION_NAME )

  %extend Utility::GlobalMPISession
  {
    //! FUNCTION_NAME with cout
    void FUNCTION_NAME( const int root_process = 0,
                        const bool limit_logging_to_root = false,
                        const bool synchronous_logging = true )
    {
      $self->FUNCTION_NAME( boost::shared_ptr<std::ostream>( &std::cout, boost::null_deleter() ), root_process, limit_logging_to_root, synchronous_logging );
    }

    //! FUNCTION_NAME with file
    void FUNCTION_NAME( std::string filename,
                        const int root_process = 0,
                        const bool limit_logging_to_root = false,
                        const bool synchronous_logging = true )
    {
      boost::shared_ptr<std::ofstream> file = boost::make_shared<std::ofstream>(filename);

      $self->FUNCTION_NAME( file, root_process, limit_logging_to_root, synchronous_logging );
    }
  }

%enddef

// Extend GlobalMPISession functionality for initializing different logs
%extend_log_initializers( initializeLogs )
%extend_log_initializers( initializeErrorLog )
%extend_log_initializers( initializeWarningLog )
%extend_log_initializers( initializeNotificationLog )
%extend_log_initializers( initializeLogs )

// Extend GlobalMPISession functionality for initializing/restoring output stream
%extend Utility::GlobalMPISession
{
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

// Macro for adding functions to return the thread support level object as an int
%define %inline_level_tag_function( FUNCTION_NAME )

  %inline %{
    //! The mpi FUNCTION_NAME support level tag function
    int FUNCTION_NAME()
    {
      return Utility::GlobalMPISession::FUNCTION_NAME;
    }
  %}

%enddef

// Add functions to return the thread support level object as an int
%inline_level_tag_function( SingleThreading )
%inline_level_tag_function( FunneledThreading )
%inline_level_tag_function( SerializedThreading )
%inline_level_tag_function( MultipleThreading )

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end Utility_GlobalMPISession.i
//---------------------------------------------------------------------------//
