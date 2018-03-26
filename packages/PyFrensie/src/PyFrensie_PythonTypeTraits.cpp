//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_PythonTypeTraits.cpp
//! \author Alex Robinson
//! \brief  The Python type traits helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"

namespace PyFrensie{

namespace Details{

// Get the type code string (useful for exception messages)
const char* typecodeString(int typecode)
{
  static const char* type_names[25] = {"bool",
                                         "byte",
                                         "unsigned byte",
                                         "short",
                                         "unsigned short",
                                         "int",
                                         "unsigned int",
                                         "long",
                                         "unsigned long",
                                         "long long",
                                         "unsigned long long",
                                         "float",
                                         "double",
                                         "long double",
                                         "complex float",
                                         "complex double",
                                         "complex long double",
                                         "object",
                                         "string",
                                         "unicode",
                                         "void",
                                         "ntypes",
                                         "notype",
                                         "char",
                                         "unknown"};
    return typecode < 24 ? type_names[typecode] : type_names[24];
}

// Get the PyObject type string (useful for exception messages)_
const char* pytypeString( PyObject* py_obj )
{
  if (py_obj == NULL          ) return "C NULL value";
    if (py_obj == Py_None       ) return "Python None" ;
    if (PyCallable_Check(py_obj)) return "callable"    ;
    if (PyString_Check(  py_obj)) return "string"      ;
    if (PyInt_Check(     py_obj)) return "int"         ;
    if (PyFloat_Check(   py_obj)) return "float"       ;
    if (PyDict_Check(    py_obj)) return "dict"        ;
    if (PyList_Check(    py_obj)) return "list"        ;
    if (PyTuple_Check(   py_obj)) return "tuple"       ;
    if (PyFile_Check(    py_obj)) return "file"        ;
    if (PyModule_Check(  py_obj)) return "module"      ;
    if (PyInstance_Check(py_obj)) return "instance"    ;
}
  
} // end Details namespace
  
} // end PyFrensie namespace

//---------------------------------------------------------------------------//
// PyFrensie_PythonTypeTraits.cpp
//---------------------------------------------------------------------------//

