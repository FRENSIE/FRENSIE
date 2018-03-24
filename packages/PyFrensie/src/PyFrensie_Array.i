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
%typemap(in) Utility::ArrayView< const TYPE >
{
  $result = PyFrensie::convertToPython( $1 );

  if (!$result)
    SWIG_fail;
  
  if (!npArray)
    SWIG_fail;
  
  $1 = Utility::arrayView( (TYPE*) array_data(npArray), array_size(npArray, 0));
}

// // If an ArrayView argument has a non-const TYPE, then the default
// // behavior is to assume that the array is input/output.  Therefore
// // the input python argument must be a NumPy array.
// %typemap(in) Utility::ArrayView< TYPE >
// {
//   PyArrayObject * npArray = obj_to_array_no_conversion($input, TYPECODE);
//   if (!npArray) SWIG_fail;
//   $1 = Utility::arrayView( (TYPE*) array_data(npArray), array_size(npArray, 0));
// }
// PyArrayObject* obj_to_array_no_conversion(PyObject* input,
//                                             int        typecode)
//   {
//     PyArrayObject* ary = NULL;
//     if (is_array(input) && (typecode == NPY_NOTYPE ||
//                             PyArray_EquivTypenums(array_type(input), typecode)))
//     {
//       ary = (PyArrayObject*) input;
//     }
//     else if is_array(input)
//     {
//       const char* desired_type = typecode_string(typecode);
//       const char* actual_type  = typecode_string(array_type(input));
//       PyErr_Format(PyExc_TypeError,
//                    "Array of type '%s' required.  Array of type '%s' given",
//                    desired_type, actual_type);
//       ary = NULL;
//     }
//     else
//     {
//       const char* desired_type = typecode_string(typecode);
//       const char* actual_type  = pytype_string(input);
//       PyErr_Format(PyExc_TypeError,
//                    "Array of type '%s' required.  A '%s' was given",
//                    desired_type,
//                    actual_type);
//       ary = NULL;
//     }
//     return ary;
//   }

// If an ArrayView is output, with either a const or non-const TYPE,
// convert the underlying data to a NumPy array of correct type.
%typemap(out) Utility::ArrayView< TYPE >
{
  $result = PyFrensie::convertToPython( $1 );

  if (!$result)
    SWIG_fail;
}

%typemap(out) Utility::ArrayView< const TYPE >
{
  $result = PyFrensie::convertToPython( $1 );
  
  if (!$result)
    SWIG_fail;
}

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

