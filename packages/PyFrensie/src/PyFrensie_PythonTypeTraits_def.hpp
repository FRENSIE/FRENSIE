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
  bool is_valid = false;
  
  if( py_obj && (PyArray_Check( py_obj ) || PySequence_Check( py_obj )) )
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
        is_valid = true;
      else
        is_valid = false;

      Py_DECREF( py_array );
    }
    else
      is_valid = false;
  }
  else
    is_valid = false;

  return is_valid;
}

// Get the NumPy array object
template<typename T>
inline PyArrayObject* getNumPyArray( PyObject* py_obj,
                                     int* is_new_object )
{
  PyArrayObject* py_array = NULL;

  int typecode = numpyTypecode( T() );

  // Make sure the Python object is a NumPy array
  if( py_obj && PyArray_Check( py_obj ) &&
      (typecode == NPY_NOTYPE ||
       PyArray_EquivTypenums(PyArray_TYPE((PyArrayObject*)py_obj), typecode)) )
  {
    py_array = (PyArrayObject*)py_obj;
  }
  else
  {
    PyObject* new_py_obj =
      PyArray_FROMANY( py_obj, typecode, 0, 0, NPY_ARRAY_DEFAULT );

    // An exception will be thrown if the conversion fails (no need to check
    // (for a NULL return)
    py_array = (PyArrayObject*)new_py_obj;

    *is_new_object = 1;
  }

  return py_array;
}

// Get the type code string (useful for exception messages)
const char* typecodeString( int typecode );

// Get the PyObject type string (useful for exception messages)_
const char* pytypeString( PyObject* py_obj );

// Get the NumPy array object without performing a type conversion
template<typename T>
PyArrayObject* getNumPyArrayWithoutConversion( PyObject* py_obj )
{
  PyArrayObject* py_array = NULL;

  int typecode = numpyTypecode( T() );

  if( py_obj && PyArray_Check( py_obj ) &&
      (typecode == NPY_NOTYPE ||
       PyArray_EquivTypenums(PyArray_TYPE((PyArrayObject*)py_obj), typecode)) )
  {
    py_array = (PyArrayObject*)py_obj;
  }
  else if( PyArray_Check( py_obj ) )
  {
    const char* desired_type = typecodeString(typecode);
    const char* actual_type = typecodeString(PyArray_TYPE((PyArrayObject*)py_obj));
    PyErr_Format(PyExc_TypeError,
                 "Array of type '%s' required but array of type '%s' given",
                 desired_type, actual_type);
    py_array = NULL;
  }
  else
  {
    const char* desired_type = typecodeString(typecode);
    const char* actual_type = pytypeString(py_obj);
    PyErr_Format(PyExc_TypeError,
                 "Array of type '%s' required but a '%s' was given",
                 desired_type,
                 actual_type);
    py_array = NULL;
  }

  return py_array;
}

template<typename... Types>
struct IsValidTupleElementHelper;

template<typename T, typename... Types>
struct IsValidTupleElementHelper<T,Types...>
{
  template<size_t element_index>
  static inline bool areElementsConvertable( PyObject* py_obj )
  {
    PyObject* py_obj_element = PyTuple_GetItem( py_obj, element_index );
    
    if( !PythonTypeTraits<T>::isConvertable( py_obj_element  ) )
      return false;

    return IsValidTupleElementHelper<Types...>::areElementsConvertable<element_index+1>( py_obj );
  }
};

template<typename T>
struct IsValidTupleElementHelper<T>
{
  template<size_t element_index>
  static inline bool areElementsConvertable( PyObject* py_obj )
  {
    PyObject* py_obj_element = PyTuple_GetItem( py_obj, element_index );
    
    if( !PythonTypeTraits<T>::isConvertable( py_obj_element ) )
      return false;

    return true;
  }
};

// Check if the PyObject is a valid tuple
template<typename... Types>
inline bool isValidTuple( PyObject* py_obj )
{
  if( PyTuple_Check( py_obj ) )
  {
    if( PyTuple_Size( py_obj ) == Utility::TupleSize<std::tuple<Types...> >::value )
    {
      return IsValidTupleElementHelper<Types...>::areElementsConvertable<0>( py_obj );
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

// Create a Python (NumPy) object from a STLCompliantArray object
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
  int is_new_array = 0;
  
  PyArrayObject* py_array =
    Details::getNumPyArray<typename STLCompliantArray::value_type>( py_obj, &is_new_array );
  
  typename STLCompliantArray::size_type length = PyArray_DIM(py_array, 0);
  
  typename STLCompliantArray::value_type* data =
    (typename STLCompliantArray::value_type*)PyArray_DATA(py_array);
  
  STLCompliantArray output_array( length );
  
  for( typename STLCompliantArray::size_type i = 0; i < length; ++i )
    output_array[i] = *(data++);

  if( is_new_array )
    Py_DECREF(py_array);
  
  return output_array;
}

// Create an array object from a Python object without a type conversion
template<typename STLCompliantArray>
STLCompliantArray convertPythonToArrayWithoutConversion( PyObject* py_obj )
{
  // An exception will be thrown if this fails
  PyArrayObject* py_array =
    Details::getNumPyArrayWithoutConversion<typename STLCompliantArray::value_type>( py_obj );

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

  // Delete the temporary set
  Py_DECREF( tmp_py_obj );
  
  return output_set;
}

template<typename... Types>
struct ConvertTupleElementsToPythonHelper;

template<typename T, typename... Types>
struct ConvertTupleElementsToPythonHelper<T,Types...>
{
  template<size_t element_index, typename... TupleTypes>
  static inline void convert( const std::tuple<TupleTypes...>& obj,
                              PyObject* py_tuple )
  {
    int return_value = PyTuple_SetItem(
          py_tuple,
          element_index,
          PythonTypeTraits<T>::convertToPython(std::get<element_index>(obj)) );

    if( return_value != 0 )
    {
      PyErr_Format( PyExc_RuntimeError,
                    "Could not set element %i of the tuple!",
                    element_index );
    }

    ConvertTupleElementsToPythonHelper<Types...>::template convert<element_index+1>( obj, py_tuple );
  }
};

template<typename T>
struct ConvertTupleElementsToPythonHelper<T>
{
  template<size_t element_index, typename... TupleTypes>
  static inline void convert( const std::tuple<TupleTypes...>& obj,
                              PyObject* py_tuple )
  {
    int return_value = PyTuple_SetItem(
          py_tuple,
          element_index,
          PythonTypeTraits<T>::convertToPython(std::get<element_index>(obj)) );

    if( return_value != 0 )
    {
      PyErr_Format( PyExc_RuntimeError,
                    "Could not set element %i of the tuple!",
                    element_index );
    }
  }
};

// Create a Python (tuple) object from a std::tuple object
template<typename... Types>
inline PyObject* convertTupleToPython( const std::tuple<Types...>& obj )
{
  PyObject* py_tuple =
    PyTuple_New( Utility::TupleSize<std::tuple<Types...> >::value );

  ConvertTupleElementsToPythonHelper<Types...>::convert<0>( obj, py_tuple );
  
  return py_tuple;
}

template<typename... Types>
struct ConvertPythonToTupleElementsHelper;

template<typename T, typename... Types>
struct ConvertPythonToTupleElementsHelper<T,Types...>
{
  template<size_t element_index, typename... TupleTypes>
  static inline void convert( PyObject* py_obj,
                              std::tuple<TupleTypes...>& tuple )
  {
    PyObject* element = PyTuple_GetItem( py_obj, element_index );

    std::get<element_index>( tuple ) =
      PythonTypeTraits<T>::convertFromPython( element );

    ConvertPythonToTupleElementsHelper<Types...>::template convert<element_index+1>( py_obj, tuple );
  }
};

template<typename T>
struct ConvertPythonToTupleElementsHelper<T>
{
  template<size_t element_index, typename... TupleTypes>
  static inline void convert( PyObject* py_obj,
                              std::tuple<TupleTypes...>& tuple )
  {
    PyObject* element = PyTuple_GetItem( py_obj, element_index );

    std::get<element_index>( tuple ) =
      PythonTypeTraits<T>::convertFromPython( element );
  }
};

//! Create a std::tuple object from a Python object
template<typename... Types>
inline std::tuple<Types...> convertPythonToTuple( PyObject* py_obj )
{
  std::tuple<Types...> output_tuple;

  ConvertPythonToTupleElementsHelper<Types...>::convert<0>( py_obj, output_tuple );
  
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
