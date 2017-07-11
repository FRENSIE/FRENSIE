//---------------------------------------------------------------------------//
//!
//! \file   DataGen.__init__.i
//! \author Luke Kersting
//! \brief  The data gen module swig interface file
//!
//---------------------------------------------------------------------------//

%define %data_gen_docstring
"
PyFrensie.DataGen is the python interface to the FRENSIE data_gen package.
"
%enddef

%module(package   = "PyFrensie.DataGen",
        autodoc   = "1",
        docstring = %data_gen_docstring) __init__

// Set the special python variables
%pythoncode
%{
__all__ = ['ElectronPhoton']
%}

//---------------------------------------------------------------------------//
// end DataGen.__init__.i
//---------------------------------------------------------------------------//
