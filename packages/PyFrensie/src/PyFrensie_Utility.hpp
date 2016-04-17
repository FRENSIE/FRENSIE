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
bool addToParameterList( const std::string& name,
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

} // end PyFrensie namespace

#endif // end PYFRENSIE_UTILITY_HPP

//---------------------------------------------------------------------------//
// end PyFrensie_Utility.hpp
//---------------------------------------------------------------------------//
