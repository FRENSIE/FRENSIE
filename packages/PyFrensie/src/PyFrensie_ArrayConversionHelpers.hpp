//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_ArrayConversionHelpers.hpp
//! \author Alex Robinson
//! \brief  PyFrensie array conversion helper functions
//!
//---------------------------------------------------------------------------//

#ifndef PYFRENSIE_ARRAY_CONVERSION_HELPERS_HPP
#define PYFRENSIE_ARRAY_CONVERSION_HELPERS_HPP

// Std Lib Includes
#include <vector>

// Trilinos Includes
#include <PyTrilinos_Teuchos_Util.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "PyFrensie_NumPyTypeTraits.hpp"

namespace PyFrensie{

/*! Copy the data in a std::vector into a new 1D NumPy array
 * \details If any errors occur, a Python error will be set and the 
 * function will return NULL.
 */
template<typename T>
PyObject* copyVectorToNumPy( std::vector<T>& vector )
{
  npy_intp dims[] = { vector.size() };
  int typecode = numpyTypecode( T() );
  
  PyObject* py_array = PyArray_SimpleNew( 1, dims, typecode );

  T* data = (T*) PyArray_DATA((PyArrayObject*) py_array);

  // Deep copy the ArrayRCP
  for( typename Teuchos::ArrayRCP<const T>::size_type i = 0u; 
       i < vector.size();
       ++i )
    *(data++) = vector[i];
  
  return py_array;
}

/*! Copy the data in a Teuchos::ArrayRCP into a new 1D NumPy array. 
 * \details If any errors occur, a Python error will be set and the function 
 * will return NULL. 
 */
template<typename T>
PyObject* copyTeuchosToNumPy( Teuchos::ArrayRCP<const T>& t_array )
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

/*! Copy the data in a Teuchos::ArrayView into a new 1D NumPy array. 
 * \details If any errors occur, a Python error will be set and the function 
 * will return NULL. 
 */
template<typename T>
PyObject* copyTeuchosToNumPy( Teuchos::ArrayView<const T>& t_array )
{
  npy_intp dims[] = { t_array.size() };
  int typecode = numpyTypecode( T() );
  
  PyObject* py_array = PyArray_SimpleNew( 1, dims, typecode );

  T* data = (T*) PyArray_DATA((PyArrayObject*) py_array);

  // Deep copy the ArrayView
  for( typename Teuchos::ArrayView<const T>::size_type i = 0u; 
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
PyObject* copyTeuchosToNumPy( Teuchos::Array<T>& t_array )
{
  return PyTrilinos::copyTeuchosArrayToNumPy( t_array );
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

/*! Copy the data in a 1D NumPy array int a std::vector.
 * \details The std::vector will be resized to accommodate the data. The user
 * must verify that the NumPy array is 1D.
 */
template<typename T>
void copyNumPyToVectorWithCheck( PyObject * py_obj,
                                  std::vector<T> & vector )
{
  PyObject* py_array = isValidNumPyArray<T>( py_obj );
  
  typedef typename Teuchos::ArrayRCP<T>::size_type size_type;
  size_type length = PyArray_DIM((PyArrayObject*) py_array, 0);

  vector.resize(length);

  T * data = (T*) PyArray_DATA((PyArrayObject*) py_array);

  for( size_type i = 0u; i < vector.size(); ++i )
    vector[i] = *(data++);
}

/*! Copy the data in a 1D NumPy array into a Teuchos::ArrayRCP.  
 * \details The Teuchos ArrayRCP will be resized to accommodate the data.  The 
 * user must verify that the NumPy array is 1D.
 */
template<typename T>
void copyNumPyToTeuchosWithCheck( PyObject * py_obj,
                                  Teuchos::ArrayRCP<T> & t_array )
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
 * user must verify that the NumPy array is 1D.
 */
template<typename T>
void copyNumPyToTeuchosWithCheck( PyObject * py_obj,
                                  Teuchos::Array<T> & t_array )
{
  PyObject* py_array = isValidNumPyArray<T>( py_obj );
  
  PyTrilinos::copyNumPyToTeuchosArray( py_array, t_array );
}

} // end PyFrensie namespace

#endif // end PYFRENSIE_ARRAY_CONVERSION_HELPERS_HPP

//---------------------------------------------------------------------------//
// end PyFrensie_ArrayConversionHelpers.hpp
//---------------------------------------------------------------------------//
