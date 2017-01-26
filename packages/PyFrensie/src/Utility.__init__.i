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
__all__ = ['Distribution',
           'Prng',
           'Interpolation'
           ]
%}


%{
#include "Utility_RandomNumberGenerator.hpp"
%}

// Add the shortcut for initializing the random number generator
%feature("autodoc")
initFrensiePrng
"
This method can be used to initialize the Utility.Prng.RandomNumberGenerator
instead of calling 'Utility.Prng.RandomNumberGenerator.createStreams()'.
"

%inline %{
//! Initialize the random number generator
void initFrensiePrng()
{
  // Initilize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}
%}

//---------------------------------------------------------------------------//
// end Utility.__init__.i
//---------------------------------------------------------------------------//
