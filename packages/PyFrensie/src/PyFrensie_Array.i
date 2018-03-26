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
#include "Utility_ArrayView.hpp"
%}

// Include the std::vector class
%include <std_vector.i>

// This macro takes a C++ data type (TYPE) and a corresponding NumPy typecode
// (TYPECODE) and define all of the output typemaps needed to handle
// std::vector<TYPE> -> numpy.array( ..., dtype=TYPECODE )
%define %array_typemaps(TYPE, TYPECODE)

// If an ArrayView argument has a const TYPE, then we know that the
// argument is input only.  Therefore we allow any type of sequence to
// be converted to a PyArrayObject and then extract the resulting data
// pointer to construct the ArrayView.  If the conversion creates a
// new PyArrayObject, then we have to be sure to decrement its
// reference count once the ArrayView has been used.
%typemap(in) Utility::ArrayView< const TYPE > (int is_new = 0,
                                               PyArrayObject* np_array = NULL)
{
  np_array = Details::getNumPyArray<TYPE>( $input, &is_new );

  if( !np_array )
    SWIG_fail;
  
  $1 = Utility::arrayView( (TYPE*)PyArray_DATA(np_array), PyArray_DIM(np_array, 0) );
}

%typemap(freearg) Utility::ArrayView< const TYPE >
{
  if( is_new$argnum )
    Py_DECREF(np_array$argnum)
}

// // If an ArrayView argument has a non-const TYPE, then the default
// // behavior is to assume that the array is input/output.  Therefore
// // the input python argument must be a NumPy array.
%typemap(in) Utility::ArrayView< TYPE >
{
  PyArrayObject* np_array =
    Details::getNumPyArrayWithoutConversion<TYPE>( $input );

  if (!np_array)
    SWIG_fail;
  
  $1 = Utility::arrayView( (TYPE*)PyArray_DATA(np_array), PyArray_DIM(np_array, 0) );
}

// If an ArrayView is output, with either a const or non-const TYPE,
// convert the underlying data to a NumPy array of correct type.
%typemap(out) Utility::ArrayView< TYPE >
{
  npy_intp dims[1] = { $1.size() };
  
  $result = PyArray_SimpleNewFromData( 1, dims, TYPECODE, (void*)$1.data() );
  
  if( !$result )
    SWIG_fail;
}

%typemap(out) Utility::ArrayView< const TYPE >
{
  npy_intp dims[1] = { $1.size() };
  
  $result = PyArray_SimpleNewFromData( 1, dims, TYPECODE, (void*)$1.data() );
  
  if( !$result )
    SWIG_fail;
}

// The supplied std_vector.i interface file does not provide support for
// NumPy arrays - these output typemaps do.
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

