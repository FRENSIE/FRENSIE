//---------------------------------------------------------------------------//
//!
//! \file   Utility.Interpolation.i
//! \author Luke Kersting
//! \brief  The Utility.Interpolation sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %utility_interpolation_docstring
"
PyFrensie.Utility.Interpolation is the python inteface to the FRENSIE utility/interpolation
subpackage.

The purpose of Interpolation is to provide a variety of interpolation schemes
that can be used in FRENSIE and PyFrensie.
"
%enddef

%module(package   = "PyFrensie.Utility",
        autodoc   = "1",
        docstring = %utility_interpolation_docstring) Interpolation


%{
// Std Lib Includes
#include <sstream>

// Frensie Includes
#include "Utility_Interpolator.hpp"
#include "Utility_InterpolationType.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_StandardInterpolator.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
%}

// Standard exception handling
%include "exception.i"

// Global swig features
%feature("autodoc", "1");

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
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

// Import the explicit template instantiation helpers
%import "Utility_ExplicitTemplateInstantiationMacros.hpp"

//---------------------------------------------------------------------------//
// Add suppor
//---------------------------------------------------------------------------//

// Instantiate the template constructor for double values
%include "Utility_InterpolationPolicy.hpp"
%feature("docstring")
Utility::InterpolationHelper<void>
"The"
%extend Utility::InterpolationHelper<void>
{
  %template(LogLogHelper) Utility::InterpolationHelper<LogLog>;
};

%feature("docstring")
LogLogHelper::interpolate<double>
"The"
%extend LogLogHelper::interpolate<double>
{
  %template(LogLogInterpolate) Utility::InterpolationHelper<LogLog>::interpolate<double>;
};

/*// Add more detailed docstrings*/
/*%feature("docstring")*/
/*Utility::LinLin*/
/*"The LinLin interpolator"*/

/*%feature("docstring")*/
/*Utility::LinLog*/
/*"The LinLog interpolator"*/

/*%feature("docstring")*/
/*Utility::LogLin*/
/*"The LogLin interpolator"*/

/*%feature("docstring")*/
/*Utility::LogLog*/
/*"The LogLog interpolator"*/

/*%feature("docstring")*/
/*Utility::InterpolationHelper*/
/*"The LogLog interpolator"*/

// Include InterpolationPolicy
%include "Utility_InterpolationPolicy.hpp"

// Instantiate the interpolate template method
/*%feature("docstring")*/
/*Utility::LinLin::interpolate<void>*/
/*"The"*/
/*%extend Utility::LinLin::interpolate<void>*/
/*{*/
/*  %template(interpolateLinLin) Utility::LinLin::interpolate<double>;*/
/*};*/

/*%template(LinLinHelper) Utility::InterpolationHelper<Utility::LinLin>;*/
/*%template(LinLogHelper) Utility::InterpolationHelper<Utility::LinLog>;*/
/*%template(LogLinHelper) Utility::InterpolationHelper<Utility::LogLin>;*/
//%template(LogLogHelper) Utility::InterpolationHelper<Utility::LogLog>;

// Turn off the exception handling
%exception;

//---------------------------------------------------------------------------//
// end Utility.Interpolation.i
//---------------------------------------------------------------------------//e
