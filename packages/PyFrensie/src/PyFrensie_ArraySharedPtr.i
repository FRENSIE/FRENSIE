//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_ArraySharedPtr.i
//! \author Alex Robinson, Luke Kersting
//! \brief  The PyFrensie_ArraySharedPtr.i is a SWIG interface file that
//!         provides macros to convert a PyObject* to a
//!         std::vector<std::shared_ptr<T> object using the internal SWIG api.
//!         A macro is necessary instead of a method since it guarantees
//!         access to the SWIG api by inlining the macro code.
//!
//---------------------------------------------------------------------------//

%{
// Std Lib Includes
#include <vector>
#include <memory>
%}

// Include the std::vector class
%include <std_vector.i>

// Include the std::shared_ptr class
%include <std_shared_ptr.i>

//---------------------------------------------------------------------------//
// Macro for converting a PyObject* to a std::vector<std::shared_ptr<T> >
%inline %{
#define CONVERT_PYOBJECT_TO_VECTOR_OF_BASE_SHARED_PTR( py_object, vector, __SWIG_PTR_NAME__, success ) \
  success = true;                                                       \
                                                                        \
  if( !PyList_Check( py_object ) )                                      \
  {                                                                   \
    SWIG_Error( SWIG_TypeError, "the python object is not a list" );    \
    success = false;                                                    \
  }                                                                     \
                                                                        \
  if( success )                                                         \
  {                                                                   \
    size_t size = PyList_Size( py_object );                               \
                                                                        \
    if( size == 0 )                                                     \
    {                                                                 \
      SWIG_Error( SWIG_ValueError, "The python list object is too small" ); \
      success = false;                                                  \
    }                                                                   \
                                                                        \
    if( success )                                                       \
    {                                                                 \
      vector.resize( size );                                            \
                                                                        \
      typedef typename decltype(vector)::value_type ElementType;        \
                                                                        \
      for( size_t i = 0; i < size; ++i )                                \
      {                                                               \
        PyObject* py_elem = PyList_GetItem( py_object, i );             \
                                                                        \
        ElementType* extracted_elem = 0;                                \
        void* extracted_void_elem;                                   \
        int elem_conversion_result = 0;                              \
        ElementType temp_elem;                                       \
                                                                        \
        {                                                               \
          int new_mem = 0;                                              \
          elem_conversion_result = SWIG_ConvertPtrAndOwn( py_elem, &extracted_void_elem, __SWIG_PTR_NAME__, 0, &new_mem ); \
                                                                        \
          if( !SWIG_IsOK(elem_conversion_result) )                   \
          {                                                           \
            std::string exception_message( "cannot convert PyList element " ); \
            exception_message += Utility::toString( i );                \
            exception_message += " to the desired base shared_ptr type"; \
                                                                        \
            SWIG_Error( SWIG_ArgError(elem_conversion_result), exception_message.c_str() ); \
            success = false;                                            \
            break;                                                      \
          }                                                             \
          if( new_mem & SWIG_CAST_NEW_MEMORY)                           \
          {                                                           \
            if( extracted_void_elem )                                 \
            {                                                         \
              temp_elem = *reinterpret_cast<ElementType*>(extracted_void_elem); \
              delete reinterpret_cast<ElementType*>(extracted_void_elem); \
              extracted_elem = &temp_elem;                                    \
            }                                                           \
            else                                                        \
            {                                                         \
              std::string exception_message( "cannot convert PyList element " ); \
              exception_message += Utility::toString( i );              \
              exception_message += " to the desired base shared_ptr type"; \
                                                                        \
              SWIG_Error( SWIG_UnknownError, exception_message.c_str() ); \
              success = false;                                         \
              break;                                                    \
            }                                                           \
          }                                                             \
          else                                                          \
          {                                                           \
            if( extracted_void_elem )                                   \
              extracted_elem = reinterpret_cast<ElementType*>(extracted_void_elem); \
            else                                                        \
            {                                                         \
              std::string exception_message( "cannot convert PyList element " ); \
              exception_message += Utility::toString( i );              \
              exception_message += " to the desired base shared_ptr type"; \
                                                                        \
              SWIG_Error( SWIG_UnknownError, exception_message.c_str() ); \
              success = false;                                         \
              break;                                                    \
            }                                                           \
          }                                                             \
        }                                                                    \
                                                                        \
        vector[i] = *extracted_elem;                                          \
      }                                                                 \
    }                                                                   \
  }
%}

//---------------------------------------------------------------------------//
// Macro for converting a PyObject* to a std::vector<std::shared_ptr<T> >
#define CONVERT_PYOBJECT_TO_VECTOR_OF_BASE_SHARED_PTR( py_object, vector, __SWIG_PTR_NAME__, success ) \
  success = true;                                                       \
                                                                        \
  if( !PyList_Check( py_object ) )                                      \
  {                                                                   \
    SWIG_Error( SWIG_TypeError, "the python object is not a list" );    \
    success = false;                                                    \
  }                                                                     \
                                                                        \
  if( success )                                                         \
  {                                                                   \
    size_t size = PyList_Size( py_object );                               \
                                                                        \
    if( size == 0 )                                                     \
    {                                                                 \
      SWIG_Error( SWIG_ValueError, "The python list object is too small" ); \
      success = false;                                                  \
    }                                                                   \
                                                                        \
    if( success )                                                       \
    {                                                                 \
      vector.resize( size );                                            \
                                                                        \
      typedef typename decltype(vector)::value_type ElementType;        \
                                                                        \
      for( size_t i = 0; i < size; ++i )                                \
      {                                                               \
        PyObject* py_elem = PyList_GetItem( py_object, i );             \
                                                                        \
        ElementType* extracted_elem = 0;                                \
        void* extracted_void_elem;                                   \
        int elem_conversion_result = 0;                              \
        ElementType temp_elem;                                       \
                                                                        \
        {                                                               \
          int new_mem = 0;                                              \
          elem_conversion_result = SWIG_ConvertPtrAndOwn( py_elem, &extracted_void_elem, __SWIG_PTR_NAME__, 0, &new_mem ); \
                                                                        \
          if( !SWIG_IsOK(elem_conversion_result) )                   \
          {                                                           \
            std::string exception_message( "cannot convert PyList element " ); \
            exception_message += Utility::toString( i );                \
            exception_message += " to the desired base shared_ptr type"; \
                                                                        \
            SWIG_Error( SWIG_ArgError(elem_conversion_result), exception_message.c_str() ); \
            success = false;                                            \
            break;                                                      \
          }                                                             \
          if( new_mem & SWIG_CAST_NEW_MEMORY)                           \
          {                                                           \
            if( extracted_void_elem )                                 \
            {                                                         \
              temp_elem = *reinterpret_cast<ElementType*>(extracted_void_elem); \
              delete reinterpret_cast<ElementType*>(extracted_void_elem); \
              extracted_elem = &temp_elem;                                    \
            }                                                           \
            else                                                        \
            {                                                         \
              std::string exception_message( "cannot convert PyList element " ); \
              exception_message += Utility::toString( i );              \
              exception_message += " to the desired base shared_ptr type"; \
                                                                        \
              SWIG_Error( SWIG_UnknownError, exception_message.c_str() ); \
              success = false;                                         \
              break;                                                    \
            }                                                           \
          }                                                             \
          else                                                          \
          {                                                           \
            if( extracted_void_elem )                                   \
              extracted_elem = reinterpret_cast<ElementType*>(extracted_void_elem); \
            else                                                        \
            {                                                         \
              std::string exception_message( "cannot convert PyList element " ); \
              exception_message += Utility::toString( i );              \
              exception_message += " to the desired base shared_ptr type"; \
                                                                        \
              SWIG_Error( SWIG_UnknownError, exception_message.c_str() ); \
              success = false;                                         \
              break;                                                    \
            }                                                           \
          }                                                             \
        }                                                                    \
                                                                        \
        vector[i] = *extracted_elem;                                          \
      }                                                                 \
    }                                                                   \
  }

//---------------------------------------------------------------------------//
// end PyFrensie_ArraySharedPtr.i
//---------------------------------------------------------------------------//
