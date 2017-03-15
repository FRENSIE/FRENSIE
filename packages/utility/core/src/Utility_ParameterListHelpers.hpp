//---------------------------------------------------------------------------//
//!
//! \file   Utility_ParameterListHelpers.hpp
//! \author Alex Robinson
//! \brief  Parameter list helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PARAMETER_LIST_HELPERS_HPP
#define UTILITY_PARAMETER_LIST_HELPERS_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

namespace Utility{

//! Get the unused parameter warning messages (if any)
template<template<typename,typename...> class Array>
void getUnusedParameterWarningMessages(
                                  const Teuchos::ParameterList& parameter_list,
                                  Array<std::string>& warning_messages );

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_ParameterListHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_PARAMETER_LIST_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_ParameterListHelpers.hpp
//---------------------------------------------------------------------------//
