//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_PythonTypeTraits.hpp
//! \author Alex Robinson
//! \brief  The Python type traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef PYFRENSIE_PYTHON_TYPE_TRAITS_HPP
#define PYFRENSIE_PYTHON_TYPE_TRAITS_HPP

// Std Lib Includes
#include <utility>
#include <tuple>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <type_traits>

// Trilinos Includes
#include <PyTrilinos_Teuchos_Util.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "PyFrensie_NumPyTypeTraits.hpp"
#include "PyFrensie_PythonTypeTraitsDecl.hpp"

namespace PyFrensie{

namespace Details{

// Check the PyObject is a valid NumPy array
template<typename T>
bool isValidNumPyArray( PyObject* py_obj );

// Get the NumPy array object
template<typename T>
PyArrayObject* getNumPyArray( PyObject* py_obj );

// Check if the PyObject is a valid tuple
template<typename T1, typename T2, typename T3>
bool isValidTuple( PyObject* py_obj );

// Check if the PyObject is a valid set
template<typename T>
bool isValidSet( PyObject* py_obj );

// Check if the PyObject is a valid dictionary
template<typename KeyType, typename ValueType>
bool isValidDictionary( PyObject* py_obj );

// Create a Python (NumPy) object from an array object
template<typename STLCompliantArray>
PyObject* convertArrayToPython( const STLCompliantArray& obj );

// Create an array object from a Python object
template<typename STLCompliantArray>
STLCompliantArray convertPythonToArray( PyObject* py_obj );

// Create a Python (set) object from a set object
template<typename STLCompliantSet>
PyObject* convertSetToPython( const STLCompliantSet& obj );
  
// Create a set object from a Python object
template<typename STLCompliantSet>
STLCompliantSet convertPythonToSet( PyObject* py_obj );

// Create a Python (tuple) object from a std::tuple object
template<typename T1, typename T2, typename T3>
PyObject* convertTupleToPython( const std::tuple<T1,T2,T3>& obj );

//! Create a std::tuple object from a Python object
template<typename T1, typename T2, typename T3>
std::tuple<T1,T2,T3> convertPythonToTuple3( PyObject* py_obj );

// Create a Python (dictionary) object from a map object
template<typename STLCompliantMap>
PyObject* convertMapToPython( const STLCompliantMap& obj );

// Create a map object from a Python object
template<typename STLCompliantMap>
STLCompliantMap convertPythonToMap( PyObject* py_obj );

} // end Details namespace

/*! \brief The partial specialization of PyFrensie::PythonTypeTraits for
 * all const types
 * \ingroup python_type_traits
 */
template<typename T>
struct PythonTypeTraits<T,typename std::enable_if<std::is_const<T>::value>::type> : public PythonTypeTraits<typename std::remove_const<T>::type>
{ /* ... */ };

/*! \brief The partial specialization of PyFrensie::PythonTypeTraits for
 * floating point types
 * \ingroup python_type_traits
 */
template<typename T>
struct PythonTypeTraits<T,typename std::enable_if<std::is_floating_point<T>::value>::type>
{
  // Create a Python object from a T object
  static inline PyObject* convertToPython( const T obj )
  { return PyFloat_FromDouble( obj ); }

  //! Create a T object from a Python object
  static inline T convertFromPython( PyObject* py_obj )
  { return PyFloat_AsDouble( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return PyFloat_Check( py_obj ); }
};

/*! \brief The specialization of PyFrensie::PythonTypeTraits for int
 * \ingroup python_type_traits
 */
template<>
struct PythonTypeTraits<int>
{
  // Create a Python object from an int object
  static inline PyObject* convertToPython( const int obj )
  { return PyInt_FromLong( obj ); }

  //! Create an int object from a Python object
  static inline int convertFromPython( PyObject* py_obj )
  { return PyInt_AS_LONG( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return PyInt_Check( py_obj ); }
};

/*! \brief The specialization of PyFrensie::PythonTypeTraits for unsigned
 * \ingroup python_type_traits
 */
template<>
struct PythonTypeTraits<unsigned>
{
  // Create a Python object from an unsigned object
  static inline PyObject* convertToPython( const unsigned obj )
  { return PyInt_FromSize_t( obj ); }

  //! Create an unsigned object from a Python object
  static inline unsigned convertFromPython( PyObject* py_obj )
  { return PyInt_AsLong( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return PyInt_Check( py_obj ); }
};

/*! \brief The specialization of PyFrensie::PythonTypeTraits for long
 * \ingroup python_type_traits
 */
template<>
struct PythonTypeTraits<long>
{
  // Create a Python object from a long object
  static inline PyObject* convertToPython( const long obj )
  { return PyLong_FromLong( obj ); }

  //! Create a long object from a Python object
  static inline long convertFromPython( PyObject* py_obj )
  { return PyLong_AsLong( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return PyLong_Check( py_obj ); }
};

/*! \brief The specialization of PyFrensie::PythonTypeTraits for unsigned long
 * \ingroup python_type_traits
 */
template<>
struct PythonTypeTraits<unsigned long>
{
  // Create a Python object from an unsigned long object
  static inline PyObject* convertToPython( const unsigned long obj )
  { return PyLong_FromUnsignedLong( obj ); }

  //! Create an unsigned long object from a Python object
  static inline unsigned long convertFromPython( PyObject* py_obj )
  { return PyLong_AsUnsignedLong( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return PyLong_Check( py_obj ); }
};

/*! \brief The specialization of PyFrensie::PythonTypeTraits for long long
 * \ingroup python_type_traits
 */
template<>
struct PythonTypeTraits<long long>
{
  // Create a Python object from a long long object
  static inline PyObject* convertToPython( const long long obj )
  { return PyLong_FromLongLong( obj ); }

  //! Create a long long object from a Python object
  static inline long long convertFromPython( PyObject* py_obj )
  { return PyLong_AsLongLong( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return PyLong_Check( py_obj ); }
};

/*! \brief The specialization of PyFrensie::PythonTypeTraits for unsigned long
 * long
 * \ingroup python_type_traits
 */
template<>
struct PythonTypeTraits<unsigned long long>
{
  // Create a Python object from an unsigned long long object
  static inline PyObject* convertToPython( const unsigned long long obj )
  { return PyLong_FromUnsignedLongLong( obj ); }

  //! Create an unsigned long long object from a Python object
  static inline unsigned long long convertFromPython( PyObject* py_obj )
  { return PyLong_AsUnsignedLongLong( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return PyLong_Check( py_obj ); }
};

/*! \brief The partial specialization of PyFrensie::PythonTypeTraits for
 * enumeration types
 * \ingroup python_type_traits
 */
template<typename T>
struct PythonTypeTraits<T,typename std::enable_if<std::is_enum<T>::value>::type> : public PythonTypeTraits<long>
{ /* ... */ };

/*! \brief The specialization of PyFrensie::PythonTypeTraits for std::string
 * \ingroup python_type_traits
 */
template<>
struct PythonTypeTraits<std::string>
{
  // Create a Python object from a std::string object
  static inline PyObject* convertToPython( const std::string& obj )
  { return PyString_FromString( obj.c_str() ); }

  //! Create a std::string object from a Python object
  static inline std::string convertFromPython( PyObject* py_obj )
  { return PyString_AsString( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return PyString_Check( py_obj ); }
};

/*! \brief The specialization of PyFrensie::PythonTypeTraits for std::string
 * \ingroup python_type_traits
 */
template<>
struct PythonTypeTraits<char*>
{
  // Create a Python object from a char* object
  static inline PyObject* convertToPython( const char* obj )
  { return PyString_FromString( obj ); }

  //! Create a char* object from a Python object
  static inline char* convertFromPython( PyObject* py_obj )
  { return PyString_AsString( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return PyString_Check( py_obj ); }
};

/*! \brief The partial specialization of PyFrensie::PythonTypeTraits for 
 * std::set
 * \ingroup python_type_traits
 */
template<typename T>
struct PythonTypeTraits<std::set<T> >
{
  //! Create a Python (NumPy) object from a std::set<T> object
  static inline PyObject* convertToPython( const std::set<T>& obj )
  { return Details::convertSetToPython( obj ); }

  //! Create a std::set<T> object from a Python object
  static inline std::set<T> convertFromPython( PyObject* py_obj )
  { return Details::convertPythonToSet<std::set<T> >( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return Details::isValidSet<T>( py_obj ); }
};

/*! \brief The partial specialization of PyFrensie::PythonTypeTraits for 
 * std::unordered_set
 * \ingroup python_type_traits
 */
template<typename T>
struct PythonTypeTraits<std::unordered_set<T> >
{
  //! Create a Python (NumPy) object from a std::unordered_set<T> object
  static inline PyObject* convertToPython( const std::unordered_set<T>& obj )
  { return Details::convertSetToPython( obj ); }    

  //! Create a std::unordered_set<T> object from a Python object
  static inline std::unordered_set<T> convertFromPython( PyObject* py_obj )
  { return Details::convertPythonToSet<std::unordered_set<T> >( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return Details::isValidSet<T>( py_obj ); }
};

/*! \brief The partial specialization of PyFrensie::PythonTypeTraits for 
 * std::vector
 * \ingroup python_type_traits
 */
template<typename T>
struct PythonTypeTraits<std::vector<T> >
{
  //! Create a Python (NumPy) object from a std::vector<T> object
  static inline PyObject* convertToPython( const std::vector<T>& obj )
  { return Details::convertArrayToPython( obj ); }

  //! Create a std::vector<T> object from a Python object
  static inline std::vector<T> convertFromPython( PyObject* py_obj )
  { return Details::convertPythonToArray<std::vector<T> >( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return Details::isValidNumPyArray<T>( py_obj ); }
};

/*! \brief The partial specialization of PyFrensie::PythonTypeTraits for 
 * Teuchos::Array
 * \ingroup python_type_traits
 */
template<typename T>
struct PythonTypeTraits<Teuchos::Array<T> >
{
  //! Create a Python (NumPy) object from a Teuchos::Array<T> object
  static inline PyObject* convertToPython( const Teuchos::Array<T>& obj )
  { return Details::convertArrayToPython( obj ); }

  //! Create a Teuchos::Array<T> object from a Python object
  static inline Teuchos::Array<T> convertFromPython( PyObject* py_obj )
  { return Details::convertPythonToArray<Teuchos::Array<T> >( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return Details::isValidNumPyArray<T>( py_obj ); }
};

/*! \brief The partial specialization of PyFrensie::PythonTypeTraits for 
 * Teuchos::ArrayRCP
 * \ingroup python_type_traits
 */
template<typename T>
struct PythonTypeTraits<Teuchos::ArrayRCP<T> >
{
  //! Create a Python (NumPy) object from a Teuchos::Array<T> object
  static inline PyObject* convertToPython( const Teuchos::ArrayRCP<T>& obj )
  { return Details::convertArrayToPython( obj ); }

  //! Create a Teuchos::Array<T> object from a Python object
  static inline Teuchos::ArrayRCP<T> convertFromPython( PyObject* py_obj )
  { return Details::convertPythonToArray<Teuchos::ArrayRCP<T> >( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return Details::isValidNumPyArray<T>( py_obj ); }
};

/*! \brief The partial specialization of PyFrensie::PythonTypeTraits for 
 * Teuchos::ArrayRCP of const
 * \ingroup python_type_traits
 */
template<typename T>
struct PythonTypeTraits<Teuchos::ArrayRCP<const T> >
{
  //! Create a Python (NumPy) object from a Teuchos::Array<T> object
  static inline PyObject* convertToPython( const Teuchos::ArrayRCP<const T>& obj )
  { return Details::convertArrayToPython( obj ); }

  //! Create a Teuchos::Array<T> object from a Python object
  static inline Teuchos::ArrayRCP<const T> convertFromPython( PyObject* py_obj )
  { return Details::convertPythonToArray<Teuchos::ArrayRCP<T> >( py_obj ).getConst(); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return Details::isValidNumPyArray<T>( py_obj ); }
};

/*! \brief The partial specialization of PyFrensie::PythonTypeTraits for 
 * Teuchos::ArrayView
 * \ingroup python_type_traits
 */
template<typename T>
struct PythonTypeTraits<Teuchos::ArrayView<T> >
{
  //! Create a Python (NumPy) object from a Teuchos::Array<T> object
  static inline PyObject* convertToPython( const Teuchos::ArrayView<T>& obj )
  { return Details::convertArrayToPython( obj ); }

  //! Create a Teuchos::Array<T> object from a Python object
  static inline Teuchos::ArrayView<T> convertFromPython( PyObject* py_obj )
  { return Teuchos::ArrayView<T>(); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return false; }
};

/*! \brief The partial specialization of PyFrensie::PythonTypeTraits for 
 * Teuchos::ArrayView of const
 * \ingroup python_type_traits
 */
template<typename T>
struct PythonTypeTraits<Teuchos::ArrayView<const T> >
{
  //! Create a Python (NumPy) object from a Teuchos::Array<T> object
  static inline PyObject* convertToPython( const Teuchos::ArrayView<const T>& obj )
  { return Details::convertArrayToPython( obj ); }

  //! Create a Teuchos::Array<T> object from a Python object
  static inline Teuchos::ArrayView<const T> convertFromPython( PyObject* py_obj )
  { return Teuchos::ArrayView<const T>(); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return false; }
};

/*! \brief The partial specialization of PyFrensie::PythonTypeTraits for
 * std::tuple<T1,T2,T3>
 */
template<typename T1, typename T2, typename T3>
struct PythonTypeTraits<std::tuple<T1,T2,T3> >
{
  //! Create a Python (tuple) object from a std::tuple<T1,T2,T3> object
  static inline PyObject* convertToPython( const std::tuple<T1,T2,T3>& obj )
  { return Details::convertTupleToPython( obj ); }

  //! Create a std::tuple<T1,T2,T3> object from a Python object
  static inline std::tuple<T1,T2,T3> convertFromPython( PyObject* py_obj )
  { return Details::convertPythonToTuple3<T1,T2,T3>( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return Details::isValidTuple<T1,T2,T3>( py_obj ); }
};

/*! \brief The partial specialization of PyFrensie::PythonTypeTraits for 
 * std::map
 * \ingroup python_type_traits
 */
template<typename KeyType, typename ValueType>
struct PythonTypeTraits<std::map<KeyType,ValueType> >
{
  //! Create a Python (NumPy) object from a Teuchos::Array<T> object
  static inline PyObject* convertToPython( const std::map<KeyType,ValueType>& obj )
  { return Details::convertMapToPython( obj ); }

  //! Create a Teuchos::Array<T> object from a Python object
  static inline std::map<KeyType,ValueType> convertFromPython( PyObject* py_obj )
  { return Details::convertPythonToMap<std::map<KeyType,ValueType> >( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return Details::isValidDictionary<KeyType,ValueType>( py_obj ); }
};

/*! \brief The partial specialization of PyFrensie::PythonTypeTraits for 
 * std::unordered_map
 * \ingroup python_type_traits
 */
template<typename KeyType, typename ValueType>
struct PythonTypeTraits<std::unordered_map<KeyType,ValueType> >
{
  //! Create a Python (NumPy) object from a Teuchos::Array<T> object
  static inline PyObject* convertToPython( const std::unordered_map<KeyType,ValueType>& obj )
  { return Details::convertMapToPython( obj ); }

  //! Create a Teuchos::Array<T> object from a Python object
  static inline std::unordered_map<KeyType,ValueType> convertFromPython( PyObject* py_obj )
  { return Details::convertPythonToMap<std::unordered_map<KeyType,ValueType> >( py_obj ); }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { return Details::isValidDictionary<KeyType,ValueType>( py_obj ); }
};
  
} // end PyFrensie namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "PyFrensie_PythonTypeTraits_def.hpp"

//---------------------------------------------------------------------------//

#endif // end PYFRENSIE_PYTHON_TYPE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end PyFrensie_PythonTypeTraits.hpp
//---------------------------------------------------------------------------//
