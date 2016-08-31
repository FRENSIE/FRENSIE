//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_Array.i
//! \author Alex Robinson
//! \brief  ArrayRCP output typemaps
//!
//---------------------------------------------------------------------------//

// The PyFrensie_Array.i is a SWIG interface file that provides SWIG
// directives to handle Teuchos::ArrayRCP and std::vector output types. This
// class is not wrapped, but instead typemaps are defined so that the python
// user can use NumPy arrays instead. Unfortunately, the Teuchos_Array.i
// interface file only provides the output typemaps for Teuchos::Array and
// Teuchos::ArrayView. The typemaps in this file will mimic the typemaps
// in Teuchos_Array.i

%{
// Std Lib Includes
#include <vector>

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>
%}

// Include the std::vector class
%include <std_vector.i>

// Include Teuchos::Array and Teuchos::ArrayView support
#define TEUCHOSCORE_LIB_DLL_EXPORT
%include <Teuchos_Array.i>
#undef TEUCHOSCORE_LIB_DLL_EXPORT

// Import the Teuchos::ArrayRCP class
%import <Teuchos_ArrayRCP.hpp>

// This macro takes a C++ data type (TYPE) and a corresponding NumPy typecode
// (TYPECODE) and define all of the output typemaps needed to handle
// Teuchos::ArrayRCP<TYPE> -> numpy.array( ..., dtype=TYPECODE ) and
// std::vector<TYPE> -> numpy.array( ..., dtype=TYPECODE )
%define %array_typemaps(TYPE, TYPECODE)

%typemap(out) std::vector<TYPE>
{
  npy_intp dims[1] = { (npy_intp)$1.size() };
  $result = PyArray_SimpleNewFromData(1, dims, TYPECODE, (void*) &($1[0]));
  if( !$result )
    SWIG_fail;
}

%typemap(out) const std::vector<TYPE>&
{
  npy_intp dims[1] = { (npy_intp)$1->size() };
  $result = PyArray_SimpleNewFromData(1, dims, TYPECODE, (void*) &((*$1)[0]));
  if( !$result )
    SWIG_fail;
}

%typemap(out) Teuchos::ArrayRCP<TYPE>
{
  npy_intp dims[1] = { $1.size() };
  $result = PyArray_SimpleNewFromData(1, dims, TYPECODE, (void*) $1.getRawPtr());
  if( !$result )
    SWIG_fail;
}

%typemap(out) const Teuchos::ArrayRCP<TYPE>&
{
  npy_intp dims[1] = { $1->size() };
  $result = PyArray_SimpleNewFromData(1, dims, TYPECODE, (void*) $1->getRawPtr());
  if( !$result )
    SWIG_fail;
}

%typemap(out) Teuchos::ArrayRCP<const TYPE>
{
  npy_intp dims[1] = { $1.size() };
  $result = PyArray_SimpleNewFromData(1, dims, TYPECODE, (void*) $1.getRawPtr());
  if( !$result )
    SWIG_fail;
}

%typemap(out) const Teuchos::ArrayRCP<const TYPE>&
{
  npy_intp dims[1] = { $1->size() };
  $result = PyArray_SimpleNewFromData(1, dims, TYPECODE, (void*) $1->getRawPtr());
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

