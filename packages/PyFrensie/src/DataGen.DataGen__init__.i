//---------------------------------------------------------------------------//
//!
//! \file   DataGen.DataGen__init__.i
//! \author Luke Kersting
//! \brief  The data gen module swig interface file
//!
//---------------------------------------------------------------------------//

%define %data_gen_docstring
"
PyFrensie.DataGen.DataGen__init__ will be imported directly into the
PyFrensie.DataGen module (see PyFrensie.DataGen.__init__.py)
"
%enddef

%module(package   = "PyFrensie.DataGen",
        autodoc   = "1",
        docstring = %data_gen_docstring) DataGen__init__

//---------------------------------------------------------------------------//
// end DataGen.DataGen__init__.i
//---------------------------------------------------------------------------//
