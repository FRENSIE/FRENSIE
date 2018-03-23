//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_Array.i
//! \author Alex Robinson
//! \brief  vector output typemaps
//!
//---------------------------------------------------------------------------//

// The PyFrensie_Array.i is a SWIG interface file that provides SWIG directives
// to handle std::vector output types. This class is not wrapped, but instead
// typemaps are defined so that the python user can use NumPy arrays instead.

%{
// Std Lib Includes
#include <vector>

// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
%}

// Include the std::vector class
%include <std_vector.i>

// This macro takes a C++ data type (TYPE) and a corresponding NumPy typecode
// (TYPECODE) and define all of the output typemaps needed to handle
// std::vector<TYPE> -> numpy.array( ..., dtype=TYPECODE )
%define %array_typemaps(TYPE, TYPECODE)

%typemap(out) std::vector<TYPE>
{
  $result = PyFrensie::convertToPython( $1 );

  if( !$result )
    SWIG_fail;
}

%typemap(out) const std::vector<TYPE>&
{
  $result = PyFrensie::convertToPython( $1 );

  if( !$result )
    SWIG_fail;
}

%enddef

// Create the typemaps for the types of interest
%array_typemaps(signed char       , NPY_BYTE     )
%array_typemaps(unsigned char     , NPY_UBYTE    )
%array_typemaps(short             , NPY_SHORT    )
%array_typemaps(unsigned short    , NPY_USHORT   )
%array_typemaps(int               , NPY_INT      )
%array_typemaps(unsigned int      , NPY_UINT     )
%array_typemaps(long              , NPY_LONG     )
%array_typemaps(unsigned long     , NPY_ULONG    )
%array_typemaps(long long         , NPY_LONGLONG )
%array_typemaps(unsigned long long, NPY_ULONGLONG)
%array_typemaps(float             , NPY_FLOAT    )
%array_typemaps(double            , NPY_DOUBLE   )

//---------------------------------------------------------------------------//
// end PyFrensie_Array.i
//---------------------------------------------------------------------------//

