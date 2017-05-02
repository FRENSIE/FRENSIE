//---------------------------------------------------------------------------//
//!
//! \file   Data.__init__.i
//! \author Alex Robinson
//! \brief  The data module swig interface file
//!
//---------------------------------------------------------------------------//

%define %data_docstring
"
PyFrensie.Data is the python interface to the FRENSIE data package.
"
%enddef

%module(package   = "PyFrensie.Data",
        autodoc   = "1",
        docstring = %data_docstring) __init__

// Set the special python variables
%pythoncode
%{
__all__ = ['ACE',
           'Native',
           'ENDL'
           ]
%}

//---------------------------------------------------------------------------//
// end Data.__init__.i
//---------------------------------------------------------------------------//
