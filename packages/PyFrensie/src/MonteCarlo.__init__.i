//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo.__init__.i
//! \author Alex Robinson
//! \brief  The monte carlo module swig interface file
//!
//---------------------------------------------------------------------------//

%define %monte_carlo_docstring
"
PyFrensie.MonteCarlo is the python interface to the FRENSIE monte_carlo
package.
"
%enddef

%module(package   = "PyFrensie.MonteCarlo",
        autodoc   = "1",
        docstring = %monte_carlo_docstring) __init__

// Set the special python variables
%pythoncode
%{
__all__ = ['Collision']
%}

//---------------------------------------------------------------------------//
// end MonteCarlo.__init__.i
//---------------------------------------------------------------------------//
