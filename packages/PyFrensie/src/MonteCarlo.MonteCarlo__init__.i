//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo.MonteCarlo__init__.i
//! \author Alex Robinson
//! \brief  The monte carlo module swig interface file
//!
//---------------------------------------------------------------------------//

%define %monte_carlo_docstring
"
PyFrensie.MonteCarlo.MonteCarlo__init__ will be imported directly into the
PyFrensie.MonteCarlo module (see PyFrensie.MonteCarlo.__init__.py)
"
%enddef

%module(package   = "PyFrensie.MonteCarlo",
        autodoc   = "1",
        docstring = %monte_carlo_docstring) MonteCarlo__init__

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

// Add support for the particle state classes
%include "MonteCarlo_ParticleState.i"

// Add support for the simulation properties classes
%include "MonteCarlo_SimulationProperties.i"

//---------------------------------------------------------------------------//
// end MonteCarlo.__init__.i
//---------------------------------------------------------------------------//
