//---------------------------------------------------------------------------//
//!
//! \file   Utility.Distribution.i
//! \author Alex Robinson
//! \brief  The Utility.Distribution sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %utility_dist_docstring
"
PyFrensie.Utility.Distribution is the python interface to the FRENSIE
utility/distribution subpackage.

The purpose of Distribution is to provide a variety of 1-D distributions and
a variety of higher dimension distributions that can be used for both
evaluation and sampling. All distributions are compatible with the
Teuchos::ParameterList and its Python wrapper
(PyTrilinos.Teuchos.ParameterList).
"
%enddef

%module(package   = "PyFrensie.Utility",
        autodoc   = "1",
        docstring = %utility_dist_docstring) Distribution

// Standard exception handling
%include "exception.i"

// Global swig features
%feature("autodoc", "1");

// C++ STL support
%include "stl.i"
%include "std_except.i"

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
  catch( Utility::BadUnivariateDistributionParameter& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

// Distribution support
%include "Utility_UnivariateDistribution.i"
%include "Utility_BivariateDistribution.i"

// Turn off the exception handling
%exception;

//---------------------------------------------------------------------------//
// end Utility.Distribution.i
//---------------------------------------------------------------------------//
