//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_Utility.hpp
//! \author Alex Robinson
//! \brief  PyFrensie utility package helper functions
//!
//---------------------------------------------------------------------------//

#ifndef PYFRENSIE_UTILITY_HPP
#define PYFRENSIE_UTILITY_HPP

// Python Includes
#include <Python.h>

// SWIG Includes
//#include <swigpyrun.h>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

namespace PyFrensie{

//! Add the OneDDistribution to the ParameterList object
template<typename Distribution>
bool addDistToParameterList( const std::string& name,
                             const Distribution& distribution,
                             PyObject* python_parameter_list )
{
  static swig_type_info* swig_TPL_ptr =
    SWIG_TypeQuery( "Teuchos::RCP< Teuchos::ParameterList >*");
  void* argp;
  int newmem = 0;

  bool success = true;
  
  // Check that the python object is a parameter list
  if( SWIG_CheckState( SWIG_Python_ConvertPtrAndOwn( python_parameter_list,
                                                     &argp,
                                                     swig_TPL_ptr,
                                                     0,
                                                     &newmem ) ) )
  {
    if( newmem & SWIG_CAST_NEW_MEMORY )
    {
      Teuchos::RCP<Teuchos::ParameterList> parameter_list = 
        *reinterpret_cast< Teuchos::RCP< Teuchos::ParameterList > * >(argp);
      delete reinterpret_cast< Teuchos::RCP< Teuchos::ParameterList > * >(argp);
      
      parameter_list->set( name, distribution );       
    }
    else
    {
      Teuchos::RCP< Teuchos::ParameterList > * parameter_list =
        reinterpret_cast< Teuchos::RCP< Teuchos::ParameterList > * >(argp);
      
      if( parameter_list )
        (*parameter_list)->set( name, distribution );
      else
        success = false;
    }
  }
  else
    success = false;

  return success;
}

//! Load the OneDDistribution from the ParameterList object
template<typename Distribution>
void getDistFromParameterList( const std::string& name,
                               PyObject* python_parameter_list,
                               Distribution& distribution )
{
  static swig_type_info * swig_TPL_ptr =
    SWIG_TypeQuery("Teuchos::RCP< Teuchos::ParameterList >*");

  void* argp;
  int newmem = 0;

  Teuchos::RCP<Teuchos::ParameterList> parameter_list;
  bool success = true;
    
  // Check that the python object is a parameter list
  if( SWIG_CheckState( SWIG_Python_ConvertPtrAndOwn( python_parameter_list,
                                                     &argp,
                                                     swig_TPL_ptr,
                                                     0,
                                                     &newmem ) ) )
  {
    if( newmem & SWIG_CAST_NEW_MEMORY )
    {
      parameter_list = 
        *reinterpret_cast< Teuchos::RCP< Teuchos::ParameterList > * >(argp);
      delete reinterpret_cast< Teuchos::RCP< Teuchos::ParameterList > * >(argp);    }
    else
    {
      Teuchos::RCP< Teuchos::ParameterList > * parameter_list_ptr =
        reinterpret_cast< Teuchos::RCP< Teuchos::ParameterList > * >(argp);
      
      if( parameter_list_ptr )
        parameter_list = *parameter_list_ptr;
      else
        success = false;
    }
  }
  else
    success = false;

  // Use the parameter list if it was successfully extracted from the PyObject
  if( success )
  {
    // If parameter does not exist, return None
    if( !parameter_list->isParameter(name) ) 
      PyErr_Format(PyExc_ValueError, "The requested parameter (%s) does not exist in the parameter list.", name.c_str() );
    else
    {
      // Make sure the parameter type is the distribution type
      if( parameter_list->isType<Distribution>( name ) )
        distribution = parameter_list->get<Distribution>( name );
      else
        PyErr_Format(PyExc_ValueError, "The requested parameter does not have the correct type (%s != %s)", parameter_list->getEntry( name ).getAny().typeName().c_str(), Teuchos::TypeNameTraits<Distribution>::name().c_str() );
    }
  }
  else
    PyErr_SetString(PyExc_TypeError, "The PyObject is not a PyTrilinos.Teuchos.ParameterList (a.k.a Teuchos::RCP<Teuchos::ParameterList>)." );
}

} // end PyFrensie namespace

#endif // end PYFRENSIE_UTILITY_HPP

//---------------------------------------------------------------------------//
// end PyFrensie_Utility.hpp
//---------------------------------------------------------------------------//
