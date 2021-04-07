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

    if( !PythonTypeTraits<T>::isConvertable( py_obj_element ) )
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

// Check if the PyObject is a valid list
template<typename T>
inline bool isValidList( PyObject* py_obj )
{
  bool valid;

  if( PyList_Check( py_obj ) )
  {
    if( PyList_Size( py_obj ) > 0 )
    {
      valid = true;

      // Break down the list and check each element
      for( unsigned i = 0; i < PyList_Size( py_obj ); ++i )
      {
        PyObject* py_elem = PyList_GetItem( py_obj, i );
        if( !PythonTypeTraits<T>::isConvertable( py_elem ) )
        {
          valid = false;
          break;
        }
      }
    }
    // Empty lists are always convertable
    else
      valid = true;
  }
  else
    valid = false;

  return valid;
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
      PyObject* tmp_py_obj = PySet_New(0);

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

  return valid;
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

// Create a char** object from a Python object
char** convertPythonToArgv( PyObject* py_obj )
{
  char ** temp;

  // Check if is a list
  if (PyList_Check(py_obj))
  {
    int size = PyList_Size(py_obj);
    int i = 0;
    temp = (char **) malloc((size+1)*sizeof(char *));
    for (i = 0; i < size; i++)
    {
      PyObject *o = PyList_GetItem(py_obj,i);
      if (PyString_Check(o))
        temp[i] = PyString_AsString(PyList_GetItem(py_obj,i));
      else
      {
        PyErr_SetString(PyExc_TypeError,"list must contain strings");
        free(temp);
        return NULL;
      }
    }
    temp[i] = 0;
    return temp;
  }
  else
  {
    PyErr_SetString(PyExc_TypeError,"not a list");
    return NULL;
  }
}

// Create a Python (NumPy) object from a STLCompliantArray object
template<typename STLCompliantArray>
inline PyObject* convertArrayToPython( const STLCompliantArray& obj )
{
  typedef typename std::remove_const<typename STLCompliantArray::value_type>::type ValueType;

  TEST_FOR_EXCEPTION( obj.size() > std::numeric_limits<npy_intp>::max(),
                      std::runtime_error,
                      "The object is too big to convert to a numpy array ("
                      << obj.size() << " > "
                      << std::numeric_limits<npy_intp>::max() << ")!" );
    
  npy_intp dims[] = { static_cast<npy_intp>(obj.size()) };
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

// Create a Python (NumPy) object from an ArrayView object
template<typename T>
PyObject* convertArrayViewToPython( const Utility::ArrayView<T>& obj )
{
  // The type cannot be const
  testStaticPrecondition( !(std::is_const<T>::value) );
  
  TEST_FOR_EXCEPTION( obj.size() > std::numeric_limits<npy_intp>::max(),
                      std::runtime_error,
                      "The object is too big to convert to a numpy array ("
                      << obj.size() << " > "
                      << std::numeric_limits<npy_intp>::max() << ")!" );

  npy_intp dims[1] = { static_cast<npy_intp>(obj.size()) };
  int typecode = numpyTypecode( T() );
  
  return PyArray_SimpleNewFromData( 1, dims, typecode, (void*)obj.data() );
}

// Create a Python (NumPy) object from a fixed size array object
template<typename FixedSizeArray>
PyObject* convertFixedSizeArrayToPython( const FixedSizeArray& obj )
{
  typedef typename std::remove_const<typename FixedSizeArray::value_type>::type ValueType;

  TEST_FOR_EXCEPTION( obj.size() > std::numeric_limits<npy_intp>::max(),
                      std::runtime_error,
                      "The object is too big to convert to a numpy array ("
                      << obj.size() << " > "
                      << std::numeric_limits<npy_intp>::max() << ")!" );
  
  npy_intp dims[] = { static_cast<npy_intp>(obj.size()) };
  int typecode = numpyTypecode( ValueType() );

  PyArrayObject* py_array =
    (PyArrayObject*)PyArray_SimpleNew( 1, dims, typecode );

  ValueType* data = (ValueType*)PyArray_DATA(py_array);

  // Deep copy the NumPy array
  for( typename FixedSizeArray::const_iterator it = obj.begin();
       it != obj.end();
       ++it )
  {
    *(data++) = *it;
  }

  return (PyObject*)py_array;
}

// Create a fixed size array object from a Python object
template<typename FixedSizeArray>
FixedSizeArray convertPythonToFixedSizeArray( PyObject* py_obj )
{
  // An exception will be thrown if this fails
  int is_new_array = 0;

  FixedSizeArray output_array;

  PyArrayObject* py_array =
    Details::getNumPyArray<typename FixedSizeArray::value_type>( py_obj, &is_new_array );

  // Make sure the size of the array is correct
  if( output_array.size() != PyArray_DIM(py_array, 0) )
  {
    PyErr_Format( PyExc_TypeError, "Array is the wrong size!" );
  }

  typename FixedSizeArray::value_type* data =
    (typename FixedSizeArray::value_type*)PyArray_DATA(py_array);

  for( std::size_t i = 0; i < output_array.size(); ++i )
    output_array[i] = *(data++);

  if( is_new_array )
    Py_DECREF(py_array);

  return output_array;
}

// Create a Python (list of NumPy arrays) object from a 2D array object
template<typename STLCompliant2DArray>
inline PyObject* convert2DArrayToPython( const STLCompliant2DArray& obj )
{
  typedef typename std::remove_const<typename STLCompliant2DArray::value_type::value_type>::type ValueType;

  PyObject* py_array_list = PyList_New(0);

  // Create a list of arrays
  for( unsigned i = 0; i < obj.size(); ++i )
  {
    TEST_FOR_EXCEPTION( obj[i].size() > std::numeric_limits<npy_intp>::max(),
                        std::runtime_error,
                        "The object at index " << i << " is too big to "
                        "convert to a numpy array ("
                        << obj[i].size() << " > "
                        << std::numeric_limits<npy_intp>::max() << ")!" );
    
    npy_intp dims[] = { static_cast<npy_intp>(obj[i].size()) };
    int typecode = numpyTypecode( ValueType() );

    PyArrayObject* py_array =
      (PyArrayObject*)PyArray_SimpleNew( 1, dims, typecode );

    ValueType* data = (ValueType*)PyArray_DATA(py_array);

    // Deep copy the NumPy array
    for( typename STLCompliant2DArray::value_type::const_iterator it = obj[i].begin();
        it != obj[i].end();
        ++it )
    {
      *(data++) = *it;
    }
    PyList_Append( py_array_list, (PyObject*)py_array );
  }

  return py_array_list;
}

// Create a list of arrays object from a Python object (list of Numpy arrays)
template<typename STLCompliant2DArray>
inline STLCompliant2DArray convertPythonTo2DArray( PyObject* py_obj )
{
  // An exception will be thrown if this fails
  int is_list = 0;
  int is_new_array = 0;

  is_list = PyList_Check(py_obj);

  typename STLCompliant2DArray::size_type dimensions = PyList_Size(py_obj);

  STLCompliant2DArray output_array( dimensions );

  for( typename STLCompliant2DArray::size_type i = 0; i < dimensions; ++i )
  {
    PyObject* py_elem = PyList_GetItem( py_obj, i );

    PyArrayObject *py_array =
      Details::getNumPyArray<typename STLCompliant2DArray::value_type::value_type>( py_elem, &is_new_array );

    typename STLCompliant2DArray::value_type::size_type length = PyArray_DIM(py_array, 0);

    typename STLCompliant2DArray::value_type::value_type* data =
      (typename STLCompliant2DArray::value_type::value_type*)PyArray_DATA(py_array);

    typename STLCompliant2DArray::value_type output_array_i( length );
    for( typename STLCompliant2DArray::size_type j = 0; j < length; ++j )
    {
      output_array_i[j] = *(data++);
    }

    if( is_new_array )
      Py_DECREF(py_array);

    output_array[i] = output_array_i;
  }

  return output_array;
}

// Create a Python (list of NumPy arrays) object from a vector set object
template<typename STLCompliantVectorSet>
inline PyObject* convertVectorSetToPython( const STLCompliantVectorSet& obj )
{
  typedef typename std::remove_const<typename STLCompliantVectorSet::value_type::value_type>::type ValueType;

  PyObject* py_array_list = PyList_New(0);

  // Create a list of arrays
  for( unsigned i = 0; i < obj.size(); ++i )
  {
    // Create a new Python set
    PyObject* py_set_i = PySet_New(0);

    // Copy the set elements into the Python set
    typename STLCompliantVectorSet::value_type::const_iterator it = obj[i].begin();

    while( it != obj[i].end() )
    {
      PyObject* py_elem = PythonTypeTraits<typename STLCompliantVectorSet::value_type::value_type>::convertToPython( *it );

      int return_value = PySet_Add( py_set_i, py_elem );

      if( return_value != 0 )
      {
        PyErr_Format( PyExc_RuntimeError,
                      "Could not convert a vector of sets to Python!" );
      }

      ++it;
    }

    PyList_Append( py_array_list, (PyObject*)py_set_i );
  }

  return py_array_list;
}

// Create a list of arrays object from a Python object (list of Numpy arrays)
template<typename STLCompliantVectorSet>
inline STLCompliantVectorSet convertPythonToVectorSet( PyObject* py_obj )
{
  // An exception will be thrown if this fails
  int is_list = 0;
  int is_new_array = 0;

  is_list = PyList_Check(py_obj);

  typename STLCompliantVectorSet::size_type dimensions = PyList_Size(py_obj);
  
  STLCompliantVectorSet output_array( dimensions );

  for( typename STLCompliantVectorSet::size_type i = 0; i < dimensions; ++i )
  {
    PyObject* py_elem = PyList_GetItem( py_obj, i );

    output_array[i] = PythonTypeTraits<typename STLCompliantVectorSet::value_type::value_type>::convertFromPython( py_elem );
  }

  return output_array;
}

// Create a Python (set) object from a set object
template<typename STLCompliantSet>
inline PyObject* convertSetToPython( const STLCompliantSet& obj )
{
  // Create a new Python set
  PyObject* py_set = PySet_New(0);

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

  PyObject* tmp_py_obj = PySet_New(0);

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
                    "Could not set element %lu of the tuple!",
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
                    "Could not set element %lu of the tuple!",
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

  ConvertTupleElementsToPythonHelper<Types...>::template convert<0>( obj, py_tuple );

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

// Create a Python (list of tuples) object from a vector of tuples object
template<typename... Types>
inline PyObject* convertVectorTupleToPython( const std::vector<std::tuple<Types...> >& obj )
{
  PyObject* py_array_list = PyList_New(0);

  // Create a list of arrays
  for( unsigned i = 0; i < obj.size(); ++i )
  {
    // Create a new Python tuple
    PyObject* py_tuple_i = PyTuple_New( Utility::TupleSize<std::tuple<Types...> >::value );

    ConvertTupleElementsToPythonHelper<Types...>::template convert<0>( obj[i], py_tuple_i );

    PyList_Append( py_array_list, (PyObject*)py_tuple_i );
  }

  return py_array_list;
}

// Create a list of arrays object from a Python object (list of Numpy arrays)
template<typename... Types>
inline std::vector<std::tuple<Types...> > convertPythonToVectorTuple( PyObject* py_obj )
{
  // An exception will be thrown if this fails
  int is_list = 0;
  int is_new_array = 0;

  is_list = PyList_Check(py_obj);

  typename std::vector<std::tuple<Types...> >::size_type dimensions = PyList_Size(py_obj);

  std::vector<std::tuple<Types...> > output_array( dimensions );

  for( typename std::vector<std::tuple<Types...> >::size_type i = 0; i < dimensions; ++i )
  {
    PyObject* py_elem = PyList_GetItem( py_obj, i );

    std::tuple<Types...> output_tuple_i;

    ConvertPythonToTupleElementsHelper<Types...>::convert<0>( py_elem, output_tuple_i );

    output_array[i] = output_tuple_i;
  }

  return output_array;
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
