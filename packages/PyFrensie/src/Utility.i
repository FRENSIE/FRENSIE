//---------------------------------------------------------------------------//
//!
//! \file   Utility.i
//! \author Alex Robinson
//! \brief  The utility module swig interface file
//!
//---------------------------------------------------------------------------//

%define %utility_docstring
"
PyFrensie.Utility is the python interface to the FRENSIE utilities package
Utility: ...
"
%enddef

%module(package    = "PyFrensie",
        autodoc    = "1",
        docstring  = %utility_docstring) Utility

// Distribution support
%include "Utility_UniformDistribution.i"



//---------------------------------------------------------------------------//
// end Utility.i
//---------------------------------------------------------------------------//
