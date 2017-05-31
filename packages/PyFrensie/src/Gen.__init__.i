//---------------------------------------------------------------------------//
//!
//! \file   Gen.__init__.i
//! \author Luke Kersting
//! \brief  The gen module swig interface file
//!
//---------------------------------------------------------------------------//

%define %gen_docstring
"
PyFrensie.Gen is the python interface to the FRENSIE gen package.
"
%enddef

%module(package   = "PyFrensie.Gen",
        autodoc   = "1",
        docstring = %gen_docstring) __init__

// Set the special python variables
%pythoncode
%{
__all__ = ['ElectronPhoton']
%}

//---------------------------------------------------------------------------//
// end Gen.__init__.i
//---------------------------------------------------------------------------//
