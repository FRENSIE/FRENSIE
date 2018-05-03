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

// Set the special python variables
%pythoncode
%{
# Remove the local current directory from the sys path (added to help
# import code - see comment above)
sys.path.pop(0)

__all__ = ['Collision']
%}

// Add support for the simulation properties classes
%include "MonteCarlo_SimulationProperties.i"

//---------------------------------------------------------------------------//
// end MonteCarlo.__init__.i
//---------------------------------------------------------------------------//
