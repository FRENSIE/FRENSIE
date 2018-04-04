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

//---------------------------------------------------------------------------//
// end Utility.Interpolation.i
//---------------------------------------------------------------------------//e
