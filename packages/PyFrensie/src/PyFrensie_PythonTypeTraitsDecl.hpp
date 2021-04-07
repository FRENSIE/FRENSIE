//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_PythonTypeTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  The Python type traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PYFRENSIE_PYTHON_TYPE_TRAITS_DECL_HPP
#define PYFRENSIE_PYTHON_TYPE_TRAITS_DECL_HPP

// Python Includes
#include "Python.h"

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"

/*! \defgroup python_type_traits Python Type Traits
 * \ingroup traits
 */

namespace PyFrensie{

/*! \brief This structure defines the traits that are needed to map
 * C++ types to PyObject*
 * \ingroup python_type_traits
 */
template<typename T, typename Enabled = void>
struct PythonTypeTraits
{
  //! Create a Python object from a T object
  static inline PyObject* convertToPython( const T& obj )
  { (void)Utility::UndefinedTraits<T>::notDefined(); return 0; }

  //! Create a T object from a Python object
  static inline T convertFromPython( PyObject* py_obj )
  { (void)Utility::UndefinedTraits<T>::notDefined(); return 0; }

  //! Check if a Python object can be converted to the desired type
  static inline bool isConvertable( PyObject* py_obj )
  { (void)Utility::UndefinedTraits<T>::notDefined(); return 0; }
};

/*! Create a Python object from a T object
 * \ingroup python_type_traits
 */
template<typename T>
inline PyObject* convertToPython( const T& obj )
{
  return PythonTypeTraits<T>::convertToPython( obj );
}

/*! Create a T object from a Python object
 * \ingroup python_type_traits
 */
template<typename T>
inline T convertFromPython( PyObject* py_obj )
{
  if( !PythonTypeTraits<T>::isConvertable( py_obj ) )
  {
    PyErr_Format( PyExc_RuntimeError,
                  "Unable to convert the PyObject to the desired type!" );

    return T();
  }
  else
    return PythonTypeTraits<T>::convertFromPython( py_obj );
}

} // end PyFrensie namespace

#endif // end PYFRENSIE_PYTHON_TYPE_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end PyFrensie_PythonTypeTraitsDecl.hpp
//---------------------------------------------------------------------------//
