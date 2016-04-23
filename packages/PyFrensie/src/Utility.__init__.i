//---------------------------------------------------------------------------//
//!
//! \file   Utility.__init__.i
//! \author Alex Robinson
//! \brief  The utility module swig interface file
//!
//---------------------------------------------------------------------------//

%define %utility_docstring
"
PyFrensie.Utility is the python interface to the FRENSIE utilities package.
"
%enddef

%module(package   = "PyFrensie.Utility",
        autodoc   = "1",
        docstring = %utility_docstring) __init__

// Set the special python variables
%pythoncode
%{
__all__ = ['Distribution'
           ]
%}

//---------------------------------------------------------------------------//
// end Utility.__init__.i
//---------------------------------------------------------------------------//
