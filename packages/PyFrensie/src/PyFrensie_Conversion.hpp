//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_Conversion.hpp
//! \author Alex Robinson
//! \brief  PyFrensie basic conversion helper functions
//!
//---------------------------------------------------------------------------//

#ifndef PYFRENSIE_CONVERSION_HPP
#define PYFRENSIE_CONVERSION_HPP

// Trilinos Includes
#include <numpy_include.h>
#include <PyTrilinos_Teuchos_Util.h>
#include <Teuchos_ArrayRCP.hpp>

namespace PyFrensie{

// Copy the data in a Teuchos::ArrayRCP into a new 1D NumPy array. If
// any errors occur, a Python error will be set and the function will
// return NULL. The user must specify the NumPy typecode that 
// corresponds with the template type
template<typename T>
PyObject* CopyTeuchosToNumPy( Teuchos::ArrayRCP<const T>& t_array,
                              int typecode )
{
  npy_intp dims[] = { t_array.size() };
  PyObject* py_array = PyArray_SimpleNew( 1, dims, typecode );

  T* data = (T*) PyArray_DATA((PyArrayObject*) py_array);

  // Deep copy the ArrayRCP
  for( typename Teuchos::ArrayRCP<const T>::size_type i = 0u; 
       i < t_array.size();
       ++i )
    *(data++) = t_array[i];
  
  return py_array;
}

// Copy the data in a 1D NumPy array into a Teuchos::ArrayRCP.  The
// Teuchos ArrayRCP will be resized to accommodate the data.  The user
// must verify that the NumPy data type is the same as the template
// type a priori and that the NumPy array is 1D.
template< typename T >
void CopyNumPyToTeuchos(PyObject * py_array,
                        Teuchos::ArrayRCP<T> & t_array)
{
  typedef typename Teuchos::ArrayRCP< T >::size_type size_type;
  size_type length = PyArray_DIM((PyArrayObject*) py_array, 0);
  t_array.resize(length);
  T * data = (T*) PyArray_DATA((PyArrayObject*) py_array);
  for( typename Teuchos::ArrayRCP<T>::size_type i = 0u;
       i < t_array.size();
       ++i )
    t_array[i] = *(data++);
}

} // end PyFrensie namespace

#endif // end PYFRENSIE_CONVERSION_HPP

//---------------------------------------------------------------------------//
// end PyFrensie_Conversion.hpp
//---------------------------------------------------------------------------//
