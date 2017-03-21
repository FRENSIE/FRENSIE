//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_PythonTypeTraits_def.hpp
//! \author Alex Robinson
//! \brief  The Python type traits class template function definitions
//!
//---------------------------------------------------------------------------//

#ifndef PYFRENSIE_PYTHON_TYPE_TRAITS_DEF_HPP
#define PYFRENSIE_PYTHON_TYPE_TRAITS_DEF_HPP

namespace PyFrensie{

namespace Details{

// Check the PyObject is a valid NumPy array
template<typename T>
inline bool isValidNumPyArray( PyObject* py_obj )
{
  if( PyArray_Check( py_obj ) || PySequence_Check( py_obj ) )
  {
    PyObject* py_array = PyArray_CheckFromAny(
                                      py_obj,
                                      NULL,
                                      1,
                                      1,
                                      NPY_ARRAY_DEFAULT | NPY_ARRAY_NOTSWAPPED,
                                      NULL );

    if( py_array )
    {
      if( PyArray_TYPE((PyArrayObject*) py_array) == numpyTypecode( T() ) )
        return true;
      else
        return false;
    }
    else
      return false;
  }
  else
    return false;
}

// Get the NumPy array object
template<typename T>
inline PyArrayObject* getNumPyArray( PyObject* py_obj )
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

  return (PyArrayObject*)py_array;
}

// Check if the PyObject is a valid tuple
template<typename T1, typename T2, typename T3>
inline bool isValidTuple( PyObject* py_obj )
{
  if( PyTuple_Check( py_obj ) )
  {
    if( PyTuple_Size( py_obj ) == 3 )
    {
      PyObject* element = PyTuple_GetItem( py_obj, 0 );
      
      if( !PythonTypeTraits<T1>::isConvertable( element ) )
        return false;
      
      element = PyTuple_GetItem( py_obj, 1 );
      
      if( !PythonTypeTraits<T2>::isConvertable( element ) )
        return false;
      
      element = PyTuple_GetItem( py_obj, 2 );
      
      if( !PythonTypeTraits<T3>::isConvertable( element ) )
        return false;
      
      return true;
    }
    else
      return false;
  }
  else
    return false;
}

// Check if the PyObject is a valid set
template<typename T>
inline bool isValidSet( PyObject* py_obj )
{
  bool valid;
  
  if( PySet_Check( py_obj ) )
  {
    if( PySet_Size( py_obj ) > 0 )
    {
      PyObject* tmp_py_obj = PySet_New(NULL);

      valid = true;
      
      // Break down the set and check each element
      while( PySet_Size( py_obj ) > 0 )
      {
        PyObject* py_elem = PySet_Pop( py_obj );
        PySet_Add( tmp_py_obj, py_elem );

        if( !PythonTypeTraits<T>::isConvertable( py_elem ) )
        {
          valid = false;
          break;
        }
      }

      // Rebuild the original set
      while( PySet_Size( tmp_py_obj ) > 0 )
      {
        PySet_Add( py_obj, PySet_Pop( tmp_py_obj ) );
      }
    }
    // Empty sets are always convertable
    else
      valid = true;
  }
  else
    valid = false;
}

// Check if the PyObject is a valid dictionary
template<typename KeyType, typename ValueType>
inline bool isValidDictionary( PyObject* py_obj )
{
  if( PyDict_Check( py_obj ) )
  {
    PyObject* py_key, * py_value;
    Py_ssize_t pos = 0;

    while(PyDict_Next(py_obj, &pos, &py_key, &py_value))
    {
      if( !PythonTypeTraits<KeyType>::isConvertable( py_key ) )
        return false;
      
      if( !PythonTypeTraits<ValueType>::isConvertable( py_value ) )
        return false;
    }

    return true;
  }
  else
    return false;
}

// Create a Python (NumPy) object from a Teuchos::Array<T> object
template<typename STLCompliantArray>
inline PyObject* convertArrayToPython( const STLCompliantArray& obj )
{
  typedef typename std::remove_const<typename STLCompliantArray::value_type>::type ValueType;
  
  npy_intp dims[] = { obj.size() };
  int typecode = numpyTypecode( ValueType() );
  
  PyArrayObject* py_array =
    (PyArrayObject*)PyArray_SimpleNew( 1, dims, typecode );
  
  ValueType* data = (ValueType*)PyArray_DATA(py_array);
  
  // Deep copy the NumPy array
  for( typename STLCompliantArray::const_iterator it = obj.begin();
       it != obj.end();
       ++it )
  {
    *(data++) = *it;
  }

  return (PyObject*)py_array;
}

// Create an array object from a Python object
template<typename STLCompliantArray>
inline STLCompliantArray convertPythonToArray( PyObject* py_obj )
{
  // An exception will be thrown if this fails
  PyArrayObject* py_array =
    Details::getNumPyArray<typename STLCompliantArray::value_type>( py_obj );
  
  typename STLCompliantArray::size_type length = PyArray_DIM(py_array, 0);
  
  typename STLCompliantArray::value_type* data =
    (typename STLCompliantArray::value_type*)PyArray_DATA(py_array);
  
  STLCompliantArray output_array( length );
  
  for( typename STLCompliantArray::size_type i = 0; i < length; ++i )
    output_array[i] = *(data++);
  
  return output_array;
}

// Create a Python (set) object from a set object
template<typename STLCompliantSet>
inline PyObject* convertSetToPython( const STLCompliantSet& obj )
{
  // Create a new Python set
  PyObject* py_set = PySet_New(NULL);

  // Copy the set elements into the Python set
  typename STLCompliantSet::const_iterator it = obj.begin();

  while( it != obj.end() )
  {
    PyObject* py_elem = PythonTypeTraits<typename STLCompliantSet::value_type>::convertToPython( *it );

    int return_value = PySet_Add( py_set, py_elem );

    if( return_value != 0 )
    {
      PyErr_Format( PyExc_RuntimeError,
                    "Could not convert a set element to Python!" );
    }
    
    ++it;
  }

  return py_set;
}

// Create a set object from a Python object
template<typename STLCompliantSet>
inline STLCompliantSet convertPythonToSet( PyObject* py_obj )
{
  STLCompliantSet output_set;
  
  PyObject* tmp_py_obj = PySet_New(NULL);

  // Break down the set and convert each element
  while( PySet_Size( py_obj ) > 0 )
  {
    PyObject* py_elem = PySet_Pop( py_obj );
    PySet_Add( tmp_py_obj, py_elem );

    output_set.insert( PythonTypeTraits<typename STLCompliantSet::value_type>::convertFromPython( py_elem ) );
  }

  // Rebuild the original set
  while( PySet_Size( tmp_py_obj ) > 0 )
  {
    PySet_Add( py_obj, PySet_Pop( tmp_py_obj ) );
  }

  return output_set;
}

// Create a Python (tuple) object from a std::tuple object
template<typename T1, typename T2, typename T3>
inline PyObject* convertTupleToPython( const std::tuple<T1,T2,T3>& obj )
{
  PyObject* py_tuple = PyTuple_New( 3 );

  int return_value = PyTuple_SetItem(
        py_tuple, 0, PythonTypeTraits<T1>::convertToPython(std::get<0>(obj)) );
    
  if( return_value != 0 )
  {
    PyErr_Format( PyExc_RuntimeError,
                  "Could not set the first element of the tuple!" );
  }

  return_value = PyTuple_SetItem(
        py_tuple, 1, PythonTypeTraits<T2>::convertToPython(std::get<1>(obj)) );

  if( return_value != 0 )
  {
    PyErr_Format( PyExc_RuntimeError,
                  "Could not set the second element of the tuple!" );
  }

  return_value = PyTuple_SetItem(
        py_tuple, 2, PythonTypeTraits<T3>::convertToPython(std::get<2>(obj)) );

  if( return_value != 0 )
  {
    PyErr_Format( PyExc_RuntimeError,
                  "Could not set the third element of the tuple!" );
  }
  
  return py_tuple;
}

//! Create a std::tuple object from a Python object
template<typename T1, typename T2, typename T3>
inline std::tuple<T1,T2,T3> convertPythonToTuple3( PyObject* py_obj )
{
  std::tuple<T1,T2,T3> output_tuple;

  PyObject* element = PyTuple_GetItem( py_obj, 0 );

  std::get<0>( output_tuple ) =
    PythonTypeTraits<T1>::convertFromPython( element );

  element = PyTuple_GetItem( py_obj, 1 );
  
  std::get<1>( output_tuple ) =
    PythonTypeTraits<T2>::convertFromPython( element );

  element = PyTuple_GetItem( py_obj, 2 );
  
  std::get<2>( output_tuple ) =
    PythonTypeTraits<T3>::convertFromPython( element );
  
  return output_tuple;
}

// Create a Python (dictionary) object from a map object
template<typename STLCompliantMap>
inline PyObject* convertMapToPython( const STLCompliantMap& obj )
{
  PyObject* py_dict = PyDict_New();

  typename STLCompliantMap::const_iterator it = obj.begin();

  while( it != obj.end() )
  {
    PyObject* py_dict_key =
      PythonTypeTraits<typename STLCompliantMap::key_type>::convertToPython( it->first );
    
    PyObject* py_dict_value =
      PythonTypeTraits<typename STLCompliantMap::mapped_type>::convertToPython( it->second );
    
    int return_value = PyDict_SetItem( py_dict, py_dict_key, py_dict_value );
    
    if( return_value != 0 )
    {
      PyErr_Format( PyExc_RuntimeError,
                    "Could not set a key-value pair in the Python "
                    "dictionary!" );
    }
    
    ++it;
  }

  return py_dict;
}

// Create a map object from a Python object
template<typename STLCompliantMap>
inline STLCompliantMap convertPythonToMap( PyObject* py_obj )
{
  PyObject* py_key, * py_value;
  Py_ssize_t pos = 0;

  STLCompliantMap output_map;

  while(PyDict_Next(py_obj, &pos, &py_key, &py_value))
  {
    typename STLCompliantMap::key_type key =
      PythonTypeTraits<typename STLCompliantMap::key_type>::convertFromPython( py_key );

    output_map[key] =
      PythonTypeTraits<typename STLCompliantMap::mapped_type>::convertFromPython( py_value );
  }

  return output_map;
}
  
} // end Details namespace
  
} // end PyFrensie namespace

#endif // end PYFRENSIE_PYTHON_TYPE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end PyFrensie_PythonTypeTraits_def.hpp
//---------------------------------------------------------------------------//
