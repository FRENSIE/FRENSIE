//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_ArrayRCP.i
//! \author Alex Robinson
//! \brief  ArrayRCP output typemaps
//!
//---------------------------------------------------------------------------//

// The PyFrensie_ArrayRCP.i is a SWIG interface file that provides SWIG
// directives to handle Teuchos::ArrayRCP output types. This class is
// not wrapped, but instead typemaps are defined so that the python user
// can use NumPy arrays instead. Unfortunately, the Teuchos_Array.i interface
// file only provides the output typemaps for Teuchos::Array and 
// Teuchos::ArrayView. The typemaps in this file will mimic the typemaps
// in Teuchos_Array.i

%{
#include <Teuchos_ArrayRCP.hpp>
%}

%include <numpy.i>

%import <Teuchos_ArrayRCP.hpp>

// This macro takes a C++ data type (TYPE) and a corresponding NumPy typecode
// (TYPECODE) and define all of the output typemaps needed to handle 
// Teuchos::ArrayRCP<TYPE> -> numpy.array( ..., dtype=TYPECODE )
%define %teuchos_arrayrcp_typemaps(TYPE, TYPECODE)

%typemap(out) Teuchos::ArrayRCP<TYPE>
{
  npy_intp dims[1] = { $1.size() };
  $result = PyArray_SimpleNewFromData(1, dims, TYPECODE, (void*) $1.getRawPtr());
  if( !$result ) 
    SWIG_fail;
}

%typemap(out) const Teuchos::ArrayRCP<TYPE>&
{
  npy_intp dims[1] = { $1.size() };
  $result = PyArray_SimpleNewFromData(1, dims, TYPECODE, (void*) $1.getRawPtr());
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
  npy_intp dims[1] = { $1.size() };
  $result = PyArray_SimpleNewFromData(1, dims, TYPECODE, (void*) $1.getRawPtr());
  if( !$result ) 
    SWIG_fail;
}

%enddef

// Create the typemaps for the types of interest
%teuchos_arrayrcp_typemaps(signed char       , NPY_BYTE     )
%teuchos_arrayrcp_typemaps(unsigned char     , NPY_UBYTE    )
%teuchos_arrayrcp_typemaps(short             , NPY_SHORT    )
%teuchos_arrayrcp_typemaps(unsigned short    , NPY_USHORT   )
%teuchos_arrayrcp_typemaps(int               , NPY_INT      )
%teuchos_arrayrcp_typemaps(unsigned int      , NPY_UINT     )
%teuchos_arrayrcp_typemaps(long              , NPY_LONG     )
%teuchos_arrayrcp_typemaps(unsigned long     , NPY_ULONG    )
%teuchos_arrayrcp_typemaps(long long         , NPY_LONGLONG )
%teuchos_arrayrcp_typemaps(unsigned long long, NPY_ULONGLONG)
%teuchos_arrayrcp_typemaps(float             , NPY_FLOAT    )
%teuchos_arrayrcp_typemaps(double            , NPY_DOUBLE   )

//---------------------------------------------------------------------------//
// end PyFrensie_ArrayRCP.i
//---------------------------------------------------------------------------//

