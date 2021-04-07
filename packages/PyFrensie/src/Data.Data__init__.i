//---------------------------------------------------------------------------//
//!
//! \file   Data.Data__init__.i
//! \author Luke Kersting
//! \brief  The data module swig interface file
//!
//---------------------------------------------------------------------------//

%define %data_docstring
"
PyFrensie.Data.Data__init__ will be imported directly into the
PyFrensie.Data module (see PyFrensie.Data.__init__.py).
"
%enddef

%module(package   = "PyFrensie.Data",
        autodoc   = "1",
        docstring = %data_docstring) Data__init__

%pythonbegin
%{
  # With python 2.7.14 and swig version 3.0.10 the default generated import
  # code cannot find the ___init__.so file. Unfortunately the 'moduleimport'
  # option of the %module macro does not seem to work with this version
  # of swig either. To get the import code working we have to manually add
  # the current directory to the system path temporarily.

  import os.path
  import sys
  current_dir,file_name = os.path.split(__file__)
  sys.path.insert(0, current_dir)
%}

%pythoncode
%{
# Remove the local current directory from the sys path (added to help
# import code - see comment above)
sys.path.pop(0)
%}

// Add support for different Data classes
%include "Data_SubshellType.i"
%include "Data_AtomProperties.i"
%include "Data_NuclideProperties.i"
%include "Data_ScatteringCenterPropertiesDatabase.i"
%include "Data_Xsdir.i"

//---------------------------------------------------------------------------//
// end Data.Data__init__.i
//---------------------------------------------------------------------------//
