//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_TeuchosArrayConversionHelpers.hpp
//! \author Alex Robinson
//! \brief  PyFrensie basic conversion helper functions
//!
//---------------------------------------------------------------------------//

#ifndef PYFRENSIE_CONVERSION_HPP
#define PYFRENSIE_CONVERSION_HPP

// Trilinos Includes
#include <PyTrilinos_Teuchos_Util.h>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "PyFrensie_NumPyTypeTraits.hpp"

namespace PyFrensie{

/*! Copy the data in a Teuchos::ArrayRCP into a new 1D NumPy array. 
 * \details If any errors occur, a Python error will be set and the function 
 * will return NULL. 
 */
template<typename T>
PyObject* CopyTeuchosToNumPy( Teuchos::ArrayRCP<const T>& t_array )
{
  npy_intp dims[] = { t_array.size() };
  int typecode = numpyTypecode( T() );
  
  PyObject* py_array = PyArray_SimpleNew( 1, dims, typecode );

  T* data = (T*) PyArray_DATA((PyArrayObject*) py_array);

  // Deep copy the ArrayRCP
  for( typename Teuchos::ArrayRCP<const T>::size_type i = 0u; 
       i < t_array.size();
       ++i )
    *(data++) = t_array[i];
  
  return py_array;
}

/*! Copy the data in a Teuchos::Array into a new 1D NumPy array. 
 * \details If any errors occur, a Python error will be set and the function 
 * will return NULL. 
 */
template<typename T>
PyObject* CopyTeuchosToNumPy( Teuchos::Array<T>& t_array )
{
  return PyTrilinos::CopyTeuchosToNumPy( t_array, numpyTypecode( T() ) );
}

/*! Check that the Python object is a NumPy array with the correct data type.
 * \details If the object is either not a NumPy array or has an incorrect
 * data type a Python exception will be thrown. 
 */
template<typename T>
PyObject* isValidNumPyArray( PyObject* py_obj )
{
  PyObject* py_array;

  // Make sure the Python object is a NumPy array
  if( PyArray_Check( py_obj ) || PySequence_Check( py_obj ) )
  {
    py_array = PyArray_CheckFromAny( py_obj,
                                     NULL,
                                     1,
                                     1,
                                     NPY_ARRAY_DEFAULT | NPY_ARRAY_NOTSWAPPED,
                                     NULL );

    if( !py_array )
    {
      PyErr_Format( PyExc_ValueError,
                    "The input object is not a valid NumPy array!" );
    }
  }
  else
  {
    PyErr_Format( PyExc_ValueError,
                  "The input object is not a NumPy array!" );
  }

  // Make sure the NumPy array has the correct type
  if( PyArray_TYPE((PyArrayObject*) py_array) != numpyTypecode( T() ) )
  {
    PyErr_Format( PyExc_ValueError,
                  "The input array and output array types do not match!" );
  }
  
  return py_array;
}

/*! Copy the data in a 1D NumPy array into a Teuchos::ArrayRCP.  
 * \details The Teuchos ArrayRCP will be resized to accommodate the data.  The 
 * user must verify that the NumPy data type is the same as the template
 * type a priori and that the NumPy array is 1D.
 */
template<typename T>
void CopyNumPyToTeuchosWithCheck(PyObject * py_obj,
                                 Teuchos::ArrayRCP<T> & t_array)
{
  PyObject* py_array = isValidNumPyArray<T>( py_obj );
  
  typedef typename Teuchos::ArrayRCP<T>::size_type size_type;
  size_type length = PyArray_DIM((PyArrayObject*) py_array, 0);

  t_array.resize(length);

  T * data = (T*) PyArray_DATA((PyArrayObject*) py_array);

  for( size_type i = 0u; i < t_array.size(); ++i )
    t_array[i] = *(data++);
}

/*! Copy the data in a 1D NumPy array into a Teuchos::Array.  
 * \details The Teuchos ArrayRCP will be resized to accommodate the data.  The 
 * user must verify that the NumPy data type is the same as the template
 * type a priori and that the NumPy array is 1D.
 */
template<typename T>
void CopyNumPyToTeuchosWithCheck(PyObject * py_obj,
                                 Teuchos::Array<T> & t_array)
{
  PyObject* py_array = isValidNumPyArray<T>( py_obj );
  
  PyTrilinos::CopyNumPyToTeuchos( py_array, t_array );
}

} // end PyFrensie namespace

#endif // end PYFRENSIE_CONVERSION_HPP

//---------------------------------------------------------------------------//
// end PyFrensie_TeuchosArrayConversionHelpers.hpp
//---------------------------------------------------------------------------//
